#ifndef _EXPORTACAO_H
#define _EXPORTACAO_H

#include "types.h"

void css_para_HTML(FILE *fp);
void exportar_sensores_HTML(FILE *fp, sensor_t *lista);
void exportar_setores_HTML(FILE *fp, setor_t *lista);

#endif