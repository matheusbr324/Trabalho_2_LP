#include <stdio.h>
#include <stdlib.h>
#include "../includes/arquivos.h"
#include "../includes/types.h"

//salva lista
void salva_lista_sensores(sensor_t *lista)
{
    FILE *fp = fopen("./base_de_dados/lista_sensores", "wb");
    for (lista; lista != NULL; lista = lista->prox) {
        fwrite(&(lista->id), sizeof(int), 1, fp);
        fwrite(&(lista->tipo), sizeof(string), 1, fp);
        fwrite(&(lista->maximo_faixa_leitura), sizeof(float), 1, fp);
        fwrite(&(lista->minimo_faixa_leitura), sizeof(float), 1, fp);
    }
    fclose(fp);
}

void salva_lista_setores(setor_t *lista)
{
    FILE *fp = fopen("./base_de_dados/lista_setores", "wb");
    for (lista; lista != NULL; lista = lista->prox) {
        fwrite(&(lista->id), sizeof(int), 1, fp);
        fwrite(&(lista->descricao), sizeof(string), 1, fp);
        fwrite(&(lista->qtd_sensores_instalados), sizeof(int), 1, fp);

        if (lista->qtd_sensores_instalados != 0) {
            for (lista->sensores_instalados; lista->sensores_instalados != NULL; lista->sensores_instalados = lista->sensores_instalados->prox) {
                fwrite(lista->sensores_instalados, sizeof(sensor_t), 1, fp);
            }
        }
    }
    fclose(fp);
}

//lê lista
int le_lista_sensores(sensor_t **lista)
{
    int qtd = 0;
    sensor_t *novo = NULL;
    sensor_t *loopador = (*lista);
    FILE *fp = fopen("./base_de_dados/lista_sensores", "rb");

    if(fp != NULL) {
        while (!feof(fp)) {
            novo = (sensor_t *)calloc(sizeof(sensor_t), 1);
            fread(&(novo->id), sizeof(int), 1, fp);
            fread(&(novo->tipo), sizeof(string), 1, fp);
            fread(&(novo->maximo_faixa_leitura), sizeof(float), 1, fp);
            fread(&(novo->minimo_faixa_leitura), sizeof(float), 1, fp);
            novo->prox = NULL;

            if (!feof(fp)) {

                //insere pelo final
                if (!(*lista)) {
                    (*lista) = novo;
                    qtd++;
                } else {
                    for (loopador; loopador != NULL; loopador = loopador->prox ) {
                        if (!(loopador->prox)) {
                            loopador->prox = novo;
                            qtd++;
                            break;
                        }
                    }
                }
            }
            loopador = (*lista);
        }
    }
    fclose(fp);

    //mantem a contagem de sensores
    return qtd;
}

int le_lista_setores(setor_t **lista)
{
    int qtd = 0;
    setor_t *novo = NULL;
    setor_t *loopador = (*lista);
    sensor_t *novo_sensor_no_setor = NULL;
    FILE *fp = fopen("./base_de_dados/lista_setores", "rb");

    if(fp != NULL) {
        while (!feof(fp)) {
            novo = (setor_t *)calloc(sizeof(setor_t), 1);
            fread(&(novo->id), sizeof(int), 1, fp);
            fread(&(novo->descricao), sizeof(string), 1, fp);
            fread(&(novo->qtd_sensores_instalados), sizeof(int), 1, fp);
            novo->prox = NULL;

            if (!feof(fp)) {

                //insere pelo final
                if (!(*lista)) {
                    (*lista) = novo;
                    qtd++;
                } else {
                    for (loopador; loopador != NULL; loopador = loopador->prox ) {
                        if (!(loopador->prox)) {
                            loopador->prox = novo;
                            qtd++;
                            break;
                        }
                    }
                }

                //recoloca os sensores nos setores
                if (novo->qtd_sensores_instalados != 0) {
                    for (int i = 0; i < novo->qtd_sensores_instalados; i++) {
                        novo_sensor_no_setor = (sensor_t *)calloc(sizeof(sensor_t), 1);
                        fread(novo_sensor_no_setor, sizeof(sensor_t), 1, fp);
                        if (!feof(fp)) {
                            novo_sensor_no_setor->prox = (*lista)->sensores_instalados;
                            (*lista)->sensores_instalados = novo_sensor_no_setor;
                        }
                    }
                }
            }
            loopador = (*lista);
        }
    }

    fclose(fp);

    //mantem a contagem de setores
    return qtd;
}