#include <stdio.h>
#include <stdlib.h>
#include "../includes/types.h"
#include "../includes/localizacao.h"
#include "../includes/cadastro.h"

sensor_t *cadastro_sensor(int qtd_sensores)
{
    sensor_t *sensor = (sensor_t *)calloc(sizeof(sensor_t), 1);
    sensor->prox = NULL;

    sensor->id = qtd_sensores + 1;
    printf("Sensor de id: %i\n", sensor->id);

    printf("Qual o tipo do sensor? ");
    fgets(sensor->tipo, T_STR, stdin);
    remove_enter(sensor->tipo);
    formata_maiusculo(sensor->tipo, 0);

    printf("Qual o valor mínimo lido pelo sensor? ");
    scanf("%f", &sensor->minimo_faixa_leitura);
    getchar();

    printf("Qual o valor máximo lido pelo sensor? ");
    scanf("%f", &sensor->maximo_faixa_leitura);
    getchar();

    return sensor;
}

void coloca_sensor_na_lista(sensor_t *loop, sensor_t **lista, int qtd_sensores)
{
    sensor_t *novo_sensor = cadastro_sensor(qtd_sensores);
    
    //adiciona pelo final
    if (!(*lista)) {
        (*lista) = novo_sensor;
    } else {
        for (loop; loop != NULL; loop = loop->prox ) {
            if (!((*lista)->prox)) {
                (*lista)->prox = novo_sensor;
            }
        }
    }

    //garante que não fiquem pontas soltas
    novo_sensor = NULL;
    free(novo_sensor);
}

setor_t *cadastro_setor(int qtd_setores)
{
    setor_t *setor = (setor_t *)calloc(sizeof(setor_t), 1);

    setor->qtd_sensores_instalados = 0;
    setor->prox = NULL;

    setor->id = qtd_setores + 1;
    printf("Setor de id: %i\n", setor->id);

    printf("Descrição do setor: ");
    fgets(setor->descricao, T_STR, stdin);
    remove_enter(setor->descricao);
    formata_maiusculo(setor->descricao, 0);

    return setor;
}

void coloca_setor_na_lista(setor_t *loop, setor_t **lista, int qtd_setores)
{
    setor_t *novo_setor = cadastro_setor(qtd_setores);
    
    //adiciona pelo final
    if (!(*lista)) {
        (*lista) = novo_setor;
    } else {
        for (loop; loop != NULL; loop = loop->prox ) {
            if (!((*lista)->prox)) {
                (*lista)->prox = novo_setor;
            }
        }
    }

    //garante que não fiquem ponteiros soltos
    novo_setor = NULL;
    free(novo_setor);
}

void distribui_sensor(setor_t **lista_de_setor, sensor_t *lista_de_sensor)
{
    int id_setor = pede_id_setor((*lista_de_setor));
    setor_t *setor = localiza_setor_por_id((*lista_de_setor), id_setor);

    if (!setor) {
        printf("Setor não encontrado ou não existe!\n");
        return;
    }

    if (setor->qtd_sensores_instalados > MAX_SENSOR_LOCAL) {
        printf("Número máximo de sensores instalados no setor indicado\n");
        return;
    }

    int id_sensor = pede_id_sensor(lista_de_sensor);
    sensor_t *sensor = localiza_sensor_por_id(lista_de_sensor, id_sensor);

    if (!sensor) {
        printf("Sensor não encontrado ou não existe!\n");
        return;
    }

    sensor_t *aux = copia_sensor(sensor);

    do {
        printf("Hora da primeira leitura do sensor (entre 0 e 23): ");
        scanf("%i", &aux->horario_primeira_leitura.horas);
    } while (aux->horario_primeira_leitura.horas > 23 || aux->horario_primeira_leitura.horas < 0);

    do {
        printf("Minuto da primeira leitura do sensor (entre 0 e 59): ");
        scanf("%i", &aux->horario_primeira_leitura.minutos);
    } while (aux->horario_primeira_leitura.minutos > 59 || aux->horario_primeira_leitura.minutos < 0);

        do {
        printf("Hora da segunda leitura do sensor (entre 0 e 23): ");
        scanf("%i", &aux->horario_segunda_leitura.horas);
    } while (aux->horario_segunda_leitura.horas > 23 || aux->horario_segunda_leitura.horas < 0);

    do {
        printf("Minuto da segunda leitura do sensor (entre 0 e 59): ");
        scanf("%i", &aux->horario_segunda_leitura.minutos);
        getchar();
    } while (aux->horario_segunda_leitura.minutos > 59 || aux->horario_segunda_leitura.minutos < 0);
    
    aux->primeira_medicao = ABSURDO;
    aux->segunda_medicao = ABSURDO;

    aux->prox = setor->sensores_instalados;
    setor->sensores_instalados = aux;

    aux = NULL;
    free(aux);
}

sensor_t *copia_sensor(sensor_t *sensor)
{
    sensor_t *aux = (sensor_t *)calloc(sizeof(sensor_t), 1);
    aux->id = sensor->id;
    strcpy(aux->tipo, sensor->tipo);
    aux->minimo_faixa_leitura = sensor->minimo_faixa_leitura;
    aux->maximo_faixa_leitura = sensor->maximo_faixa_leitura;
    aux->prox = NULL;

    return aux;
}