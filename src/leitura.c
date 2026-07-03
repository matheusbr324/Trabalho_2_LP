#include <stdio.h>
#include "../includes/types.h"
#include "../includes/localizacao.h"

void insere_dados_de_leitura(setor_t *lista_de_setores)
{
    int opc;
    float leitura;
    sensor_t *sensor = acha_sensor_no_setor(lista_de_setores);

    if (!sensor) return;

    printf("Dados da leitura: ");
    scanf("%f", &leitura);
    getchar();

    if (leitura > sensor->maximo_faixa_leitura || leitura < sensor->minimo_faixa_leitura) {
        char resposta;
        printf("A leitura está fora dos limites do sensor\n");
        printf("Deseja inserir os dados mesmo assim?(Digite S para confirmar) ");
        scanf("%c", &resposta);
        getchar();

        if (resposta != 'S' && resposta != 's') {
            printf("Operação cancelada!\n");
            return;
        }
    }

    do {
        printf("Em qual horário deseja inserir a leitura?\n");
        printf("1.Primeira leitura: %02i:%02i\n", sensor->horario_primeira_leitura.horas, sensor->horario_primeira_leitura.minutos);
        printf("2.Segunda leitura: %02i:%02i\n", sensor->horario_segunda_leitura.horas, sensor->horario_segunda_leitura.minutos);
        printf("0.Cancelar\n");
        scanf("%i", &opc);
        getchar();
        
        if (opc == 1) {
            sensor->primeira_medicao = leitura;         
            printf("Leitura inserida com sucesso!\n"); 
            break;
        } else {
            if (opc == 2) {
                sensor->segunda_medicao = leitura;         
                printf("Leitura inserida com sucesso!\n");
                break;
            }
        }
    } while (opc != 0);
    return;
}