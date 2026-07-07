#ifndef _TYPES_H
#define _TYPES_H

#define ABSURDO 9999999
#define FIM 0
#define MAX_SENSOR_LOCAL 3
#define T_STR 100

typedef char string[T_STR];

typedef struct horario {
    int horas;
    int minutos;
} horario_t;

typedef struct sensor {
    int id;
    string tipo;
    float minimo_faixa_leitura;
    float maximo_faixa_leitura;
    horario_t horario_primeira_leitura;
    horario_t horario_segunda_leitura;
    float primeira_medicao;
    float segunda_medicao;
    struct sensor *prox;
} sensor_t;

typedef struct setor {
    int id;
    string descricao;
    sensor_t *sensores_instalados;
    int qtd_sensores_instalados;
    struct setor *prox;
} setor_t;

#endif