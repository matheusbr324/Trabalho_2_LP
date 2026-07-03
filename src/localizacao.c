#include <stdio.h>
#include <stdlib.h>
#include "../includes/types.h"
#include "../includes/prints.h"

sensor_t *acha_sensor_no_setor(setor_t *lista_de_setores)
{
    setor_t *lista = (setor_t *)calloc(sizeof(setor_t), 1);
    int id;

    do {
        id = pede_id_setor(lista_de_setores);
        lista = localiza_setor_por_id(lista_de_setores, id);

        if (!lista) {
            printf("Setor não encontrado!\n");
            printf("Para sair da operação digite 0\n");
        }
    } while (!lista && id != 0);
    
    if (id == 0) {
        printf("Operação cancelada!\n");
        return NULL;
    }

    if (!lista->sensores_instalados) {
        printf("Não há sensores instalados nesse setor\n");
        printf("Operação cancelada!\n");
        return NULL;
    }

    sensor_t *sensor = (sensor_t *)calloc(sizeof(sensor_t), 1);
    do {
        id = pede_id_sensor(lista->sensores_instalados);
        sensor = localiza_sensor_por_id(lista->sensores_instalados, id);

        if (!sensor) {
            printf("Sensor não encontrado!\n");
            printf("Para sair da operação digite 0\n");
        }
    } while (!sensor && id != 0);
    
    if (id == 0) {
        printf("Operação cancelada!\n");
        return NULL;
    }

    return sensor;
}

int pede_id_sensor(sensor_t *lista)
{
    int id;
    printf("Sensores: \n");
    lista_sensores(lista);
    
    printf("Digite o id do sensor desejado: ");
    scanf("%i", &id);
    getchar();

    return id;
}

int pede_id_setor(setor_t *lista)
{
    int id;
    printf("Setores: \n");
    lista_setores(lista);
    
    printf("Digite o id do setor desejado: ");
    scanf("%i", &id);
    getchar();
    
    return id;
}

sensor_t *localiza_sensor_por_id(sensor_t *lista, int id)
{
    for (lista; lista != NULL; lista = lista->prox) {
        if (lista->id == id) {
            return lista;
        }
    }

    return lista;
}

setor_t *localiza_setor_por_id(setor_t *lista, int id) 
{
    for (lista; lista != NULL; lista = lista->prox) {
        if (lista->id == id) {
            return lista;
        }
    }

    return lista;   
}
