#include <stdio.h>
#include <stdlib.h>
#include "../includes/tela.h"

void mostrar_mensagem(void)
{
    printf("PARA RETORNAR AO MENU PRESSIONE ENTER\n");
    getchar();
}

void limpar_tela(void)
{
    system("clear");
}