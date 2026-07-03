#include <stdio.h>
#include <stdlib.h>
#include "../includes/localizacao.h"
#include "../includes/types.h"

void relata_leituras(setor_t *lista_de_setores) 
{
    sensor_t *sensor = acha_sensor_no_setor(lista_de_setores);
    if (!sensor) return;

    printf("Horario: \n");
    printf("%02i:%02i -- ", sensor->horario_primeira_leitura.horas, sensor->horario_primeira_leitura.minutos);
    if (sensor->primeira_medicao == ABSURDO) {
        printf("Não há leituras nesse horário\n");
    } else {
        printf("%.2f\n", sensor->primeira_medicao);
    }

    printf("%02i:%02i -- ", sensor->horario_segunda_leitura.horas, sensor->horario_segunda_leitura.minutos);
    if (sensor->segunda_medicao == ABSURDO) {
        printf("Não há leituras nesse horário\n");
    } else {
        printf("%.2f\n", sensor->segunda_medicao);
    }
}

void relata_leituras_csv(setor_t *lista_de_setores) 
{
    sensor_t *sensor = acha_sensor_no_setor(lista_de_setores);
    FILE *fp = NULL;
    fp = fopen("relatorios.csv", "w");
    if (!sensor) return;

    fprintf(fp, "Horario: ;");
    fprintf(fp, "%02i:%02i;", sensor->horario_primeira_leitura.horas, sensor->horario_primeira_leitura.minutos);
    fprintf(fp, "%02i:%02i\n", sensor->horario_segunda_leitura.horas, sensor->horario_segunda_leitura.minutos);
    fprintf(fp, "Leituras: ;");

    if (sensor->primeira_medicao == ABSURDO) {
        fprintf(fp, "Não há leituras nesse horário;");
    } else {
        fprintf(fp, "%.2f;", sensor->primeira_medicao);
    }

    if (sensor->segunda_medicao == ABSURDO) {
        fprintf(fp, "Não há leituras nesse horário;");
    } else {
        fprintf(fp, "%.2f;", sensor->segunda_medicao);
    }

    fclose(fp);
}

float relata_variacao(setor_t *lista_de_setores)
{
    sensor_t *sensor = acha_sensor_no_setor(lista_de_setores);

    float primeira = sensor->primeira_medicao;
    float segunda = sensor->segunda_medicao;
    float variacao;

    if (sensor->primeira_medicao == ABSURDO && sensor->segunda_medicao == ABSURDO) {
        printf("Não há leituras feitas por esse sensor registradas no sistema\n");
        return ABSURDO;
    }

    if (sensor->primeira_medicao == ABSURDO) return segunda;
    if (sensor->segunda_medicao == ABSURDO) return primeira;

    if (primeira > segunda) {
        return (primeira - segunda);
    } else {
        return (segunda - primeira);
    }
}

void relata_variacao_csv(setor_t *lista_de_setores)
{
    sensor_t *sensor = acha_sensor_no_setor(lista_de_setores);

    FILE *fp = fopen("variacao.csv", "w");

    float primeira, segunda, variacao;

    fprintf(fp, "Primeira medição;");
    fprintf(fp, "Segunda medição;");
    fprintf(fp, "Variação (maior - menor)\n");

    if (sensor->primeira_medicao == ABSURDO) {
        fprintf(fp, "Sem medidas;");
        primeira = 0;
    } else {
        fprintf(fp, "%f;", sensor->primeira_medicao);
        primeira = sensor->primeira_medicao;
    }

    if (sensor->segunda_medicao == ABSURDO) {
        fprintf(fp, "Sem medidas;");
        segunda = 0;
    } else {
        fprintf(fp, "%f;", sensor->segunda_medicao);
        segunda = sensor->segunda_medicao;
    }

    if (primeira > segunda) {
        variacao = primeira - segunda;
    } else {
        variacao = segunda - primeira;
    }

    if (sensor->segunda_medicao == ABSURDO && sensor->primeira_medicao == ABSURDO) {
        fprintf(fp, "Não há medidas para calcular;");
    } else {
        fprintf(fp, "%f;", variacao);
    }

    fclose(fp);
}

float relata_media(setor_t *lista_de_setores)
{
    sensor_t *sensor = acha_sensor_no_setor(lista_de_setores);

    float primeira = sensor->primeira_medicao;
    float segunda = sensor->segunda_medicao;
    float media = (primeira + segunda) / 2;

    if (sensor->primeira_medicao == ABSURDO && sensor->segunda_medicao == ABSURDO) {
        printf("Não há leituras feitas por esse sensor registradas no sistema\n");
        return ABSURDO;
    }
    if (sensor->primeira_medicao == ABSURDO) return segunda;
    if (sensor->segunda_medicao == ABSURDO) return primeira;

    return media;
}

void relata_media_csv(setor_t *lista_de_setores)
{
    sensor_t *sensor = acha_sensor_no_setor(lista_de_setores);

    FILE *fp = fopen("media.csv", "w");

    float primeira = sensor->primeira_medicao;
    float segunda = sensor->segunda_medicao;
    float media = (primeira + segunda) / 2;

    fprintf(fp, "Primeira medição;");
    fprintf(fp, "Segunda medição;");
    fprintf(fp, "Média\n");

    if (sensor->primeira_medicao == ABSURDO) {
        fprintf(fp, "Sem medidas;");
    } else {
        fprintf(fp, "%f;", sensor->primeira_medicao);
    }

    if (sensor->segunda_medicao == ABSURDO) {
        fprintf(fp, "Sem medidas;");
    } else {
        fprintf(fp, "%f;", sensor->segunda_medicao);
    }

    if (sensor->segunda_medicao == ABSURDO && sensor->primeira_medicao == ABSURDO) {
        fprintf(fp, "Não há medidas para calcular;");
    } else {
        fprintf(fp, "%f;", media);
    }

    fclose(fp);
}