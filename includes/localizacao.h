#ifndef _LOCALIZACAO_H
#define _LOCALIZACAO_H

//funções que pedem pro usuario
int pede_id_sensor(sensor_t *lista);
int pede_id_setor(setor_t *lista);

//funções que localizam id
sensor_t *localiza_sensor_por_id(sensor_t *lista, int id);
setor_t *localiza_setor_por_id(setor_t *lista, int id);

//função que acha sensores em setores
sensor_t *acha_sensor_no_setor(setor_t *lista_de_setores);

#endif