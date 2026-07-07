#include <stdio.h>
#include <stdlib.h>
#include "../includes/exclusao.h"
#include "../includes/localizacao.h"
#include "../includes/types.h"

sensor_t *acha_anterior(sensor_t *lista, sensor_t *atual)
{   
    if (lista == atual) {
        return lista;
    } else {
        for (lista; lista != NULL; lista = lista->prox) {
            if (lista->prox == atual) return lista;
        }
    }
}

void exclui_sensor_no_setor(setor_t **lista, setor_t *lista_de_setores)
{
    sensor_t *atual = acha_sensor_no_setor(lista_de_setores);

    if (atual == NULL) return;

    sensor_t *anterior = acha_anterior(lista_de_setores->sensores_instalados, atual);

    if (anterior == atual) {
        (*lista)->sensores_instalados = atual->prox;
        free(atual); 
    } else {
        anterior->prox = atual->prox;
        free(atual);
    }
    (*lista)->qtd_sensores_instalados--;
}