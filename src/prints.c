#include <stdio.h>
#include <stdlib.h>
#include "../includes/types.h"
#include "../includes/prints.h"

void lista_sensores(sensor_t *sensor)
{
    for (sensor; sensor != NULL; sensor = sensor->prox ) {
        printf("Id: %i, tipo: %s\n", sensor->id, sensor->tipo);
    }
    printf("\n");
}

void lista_setores(setor_t *setor)
{
    for (setor; setor != NULL; setor = setor->prox ) {
        printf("Id: %i, descrição: %s\n", setor->id, setor->descricao);
    }
    printf("\n");
}

void lista_sensores_por_setor(setor_t *setor)
{
    if (!setor->sensores_instalados) {
        printf("Não há sensores cadastrados nesse setor!\n");
    } else {
        printf("Sensores instalados: \n");
        lista_sensores(setor->sensores_instalados);
        
    }
    printf("\n");
}

void dados_sensor(sensor_t *sensor)
{
    printf("Id do sensor..............: %i\n", sensor->id);
    printf("Tipo do sensor............: %s\n", sensor->tipo);
    printf("Faixa de leitura do sensor: %.2f à %.2f\n", sensor->minimo_faixa_leitura, sensor->maximo_faixa_leitura);
}

void dados_todos_sensor(sensor_t *sensor)
{
    for (sensor; sensor != NULL; sensor = sensor->prox ) {
        dados_sensor(sensor);
    }
    printf("\n");
}

void dados_setor(setor_t *setor)
{
    printf("Id: %i, descrição: %s\n", setor->id, setor->descricao);
    mostra_sensores_por_setor(setor);
}

void dados_todos_setor(setor_t *setor)
{
    for (setor; setor != NULL; setor = setor->prox ) {
        dados_setor(setor);
    }
    printf("\n");
}

void mostra_sensores_por_setor(setor_t *setor)
{
    if (!setor->sensores_instalados) {
        printf("Não há sensores cadastrados nesse setor!\n");
    } else {
        printf("Sensores instalados: \n");
        sensor_t *sensor = (sensor_t *)calloc(sizeof(sensor_t), 1); 
        sensor = setor->sensores_instalados;
        for (sensor; sensor != NULL; sensor = sensor->prox) {
            dados_sensor(sensor);
            printf("Horário da primeira leitura %02i:%02i\n", sensor->horario_primeira_leitura.horas, sensor->horario_primeira_leitura.minutos);
            printf("Horário da segunda leitura %02i:%02i\n", sensor->horario_segunda_leitura.horas, sensor->horario_segunda_leitura.minutos);
        }
        free(sensor);
    }
    printf("\n");
}