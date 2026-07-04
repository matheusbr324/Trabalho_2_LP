#include <stdio.h>
#include "../includes/menus.h"

int menu_principal(void)
{
    int opcao;

    printf("|  MENU PRINCIPAL  |\n");
    printf("--------------------\n");
    printf("1.Menu de sensores\n");
    printf("2.Menu de leituras\n");
    printf("0.Sair do programa\n");
    printf("--------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_setor_sensor(void)
{
    int opcao;

    printf("|   MENU SENSORES   |\n");
    printf("---------------------\n");
    printf("1.Cadastrar sensor\n");
    printf("2.Listar sensores cadastrados\n");
    printf("3.Cadastrar setor\n");
    printf("4.Listar setores cadastrados\n");
    printf("5.Distribuir sensor\n");
    printf("6.Listar sensores distribuídos\n");
    printf("0.Retornar ao menu principal\n");
    printf("--------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_leituras(void)
{
    int opcao;

    printf("|   MENU RELATÓRIOS   |\n");
    printf("-----------------------\n");
    printf("1.Inserir dados de leitura do sensor\n");
    printf("2.Relatório de leituras (na tela)\n");
    printf("3.Relatório de leituras (.csv)\n");
    printf("4.Relatório de variação de leitura (na tela)\n");
    printf("5.Relatório de variação de leitura (.csv)\n");
    printf("6.Relatório de média de leitura (na tela)\n");
    printf("7.Relatório de média de leitura (.csv)\n");
    printf("0.Retornar ao menu principal\n");
    printf("-----------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_arquivos(void)
{
    int opcao;
    
    printf("|    MENU ARQUIVOS    |\n");
    printf("-----------------------\n");
    printf("1.Exportar os dados em HTML\n");
    printf("0.Retornar ao menu principal\n");
    printf("-----------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}