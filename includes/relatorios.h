#ifndef _RELATORIOS_H
#define _RELATORIOS_H

#include "types.h"

void relata_leituras(setor_t *lista_de_setores);
void relata_leituras_csv(setor_t *lista_de_setores);
float relata_variacao(setor_t *lista_de_setores);
void relata_variacao_csv(setor_t *lista_de_setores);
float relata_media(setor_t *lista_de_setores);
void relata_media_csv(setor_t *lista_de_setores);

#endif