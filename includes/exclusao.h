#ifndef _EXCLUSAO_H
#define _EXCLUSAO_H

#include "../includes/types.h"

sensor_t *acha_anterior(sensor_t *lista, sensor_t *atual);
void exclui_sensor_no_setor(setor_t **lista, setor_t *lista_de_setores);

#endif