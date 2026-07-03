#ifndef _CADASTRO_H
#define _CADASTRO_H

//funções de cadastro void lista_setores(setor_t *setor);
sensor_t *cadastro_sensor(int qtd_sensores);
void coloca_sensor_na_lista(sensor_t *loop, sensor_t **lista, int qtd_sensores);
setor_t *cadastro_setor(int qtd_setores);
void coloca_setor_na_lista(setor_t *loop, setor_t **lista, int qtd_setores);

//função que distribui sensores em setores
sensor_t *copia_sensor(sensor_t *sensor);
void distribui_sensor(setor_t **lista_de_setor, sensor_t *lista_de_sensor);

#endif