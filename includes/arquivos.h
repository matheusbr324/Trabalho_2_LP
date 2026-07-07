#ifndef _ARQUIVOS_H
#define _ARQUIVOS_H

#include "types.h"

void salva_lista_sensores(sensor_t *lista);
void salva_lista_setores(setor_t *lista);
int le_lista_sensores(sensor_t **lista);
int le_lista_setores(setor_t **lista);

#endif