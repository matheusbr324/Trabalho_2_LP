#ifndef _PRINTS_H
#define _PRINTS_H

//id e nome(todos) 
void lista_sensores(sensor_t *sensor);
void lista_setores(setor_t *setor);
void lista_sensores_por_setor(setor_t *setor);

//id, nome e descrições
void dados_sensor(sensor_t *sensor);
void dados_todos_sensor(sensor_t *sensor);
void dados_setor(setor_t *setor);
void dados_todos_setor(setor_t *setor);
void mostra_sensores_por_setor(setor_t *setor);

#endif