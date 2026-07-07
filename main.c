#include "all_includes.h"

int main(void)
{
    //ponteiros de structs
    sensor_t *lista_de_sensores = NULL;
    setor_t *lista_de_setores = NULL;

    //variáveis que controlam quantidade
    int qtd_sensores = 0;
    int qtd_setores = 0;

    //variáveis flags
    int tem_leituras = 0;

    //variáveis de menu
    int opcao, opc_1, opc_2, opc_3;
    
    //variáveis dos relatórios
    float variacao, media;

    qtd_sensores = le_lista_sensores(&lista_de_sensores);
    qtd_setores = le_lista_setores(&lista_de_setores);

    //menu principal
    do {
        limpar_tela();
        opcao = menu_principal();

        switch (opcao) {
            //menu de sensores
            case 1: 
                do {
                    limpar_tela();
                    opc_1 = menu_setor_sensor();

                    switch (opc_1) {
                        //Cadastrar sensor
                        case 1: 
                            coloca_sensor_na_lista(&lista_de_sensores, qtd_sensores);
                            printf("Sensor cadastrado!\n");
                            qtd_sensores++;
                            mostrar_mensagem();
                            break;

                        //Listar sensores cadastrados
                        case 2: 
                            if (!lista_de_sensores) {
                                printf("Não há sensores cadastrados!\n");
                            } else {
                                lista_sensores(lista_de_sensores);
                            }
                            mostrar_mensagem();
                            break;

                        //Cadastrar setor
                        case 3: 
                            coloca_setor_na_lista(&lista_de_setores, qtd_setores);
                            printf("Setor cadastrado!\n");
                            qtd_setores++;
                            mostrar_mensagem();
                            break;

                        //Listar setores cadastrados
                        case 4: 
                            if (!lista_de_setores) {
                                printf("Não há setores cadastrados!\n");
                            } else {
                                lista_setores(lista_de_setores);
                            }
                            mostrar_mensagem();
                            break;

                        //Distribuir sensor
                        case 5: 
                            if (!lista_de_sensores) {
                                printf("Não há sensores cadastrados!\n");
                            } else {
                                if (!lista_de_setores) {
                                    printf("Não há setores cadastrados!\n");
                                } else {
                                    distribui_sensor(&lista_de_setores, lista_de_sensores);
                                    printf("Sensor distribuido com sucesso!\n");
                                }
                            }
                            mostrar_mensagem();
                            break;

                        //Listar sensores distribuídos
                        case 6: 
                            if (!lista_de_sensores) {
                                printf("Não há sensores cadastrados!\n");
                            } else {
                                if (!lista_de_setores) {
                                    printf("Não há setores cadastrados!\n");
                                } else {
                                    dados_todos_setor(lista_de_setores);
                                }
                            }
                            mostrar_mensagem();
                            break;
                    }
                } while (opc_1 != FIM);
                break;

            //menu de leituras
            case 2: 
                do {
                    limpar_tela();
                    opc_2 = menu_leituras();

                    switch (opc_2) {
                        //Inserir dados de leitura do sensor
                        case 1: 
                            if (!lista_de_sensores) {
                                printf("Não há sensores cadastrados!\n");
                            } else {
                                if (!lista_de_setores) {
                                    printf("Não há setores cadastrados!\n");
                                } else {
                                    insere_dados_de_leitura(lista_de_setores);
                                    tem_leituras = 1;
                                }
                            }
                            mostrar_mensagem();
                            break;

                        //Relatório de leituras (na tela)
                        case 2:
                            if (tem_leituras == 0) {
                                printf("Ainda não há leituras cadastradas no sistema");
                            } else {
                                relata_leituras(lista_de_setores);
                            }
                            mostrar_mensagem();
                            break;

                        //Relatório de leituras (em .csv)
                        case 3: 
                            if (tem_leituras == 0) {
                                printf("Ainda não há leituras cadastradas no sistema");
                            } else {
                                relata_leituras_csv(lista_de_setores);
                            }
                            break;

                        //Relatório de variação de leitura (na tela)
                        case 4: 
                            variacao = relata_variacao(lista_de_setores);
                            if (variacao != ABSURDO) {
                                printf("A variação das leituras é: %.2f", variacao);
                            }
                            mostrar_mensagem();
                            break;

                        //Relatório de variação de leitura (.csv)
                        case 5: 
                            relata_variacao_csv(lista_de_setores);
                            break;

                        //Relatório de média de leitura (na tela)
                        case 6:
                            media = relata_media(lista_de_setores);
                            if (media != ABSURDO) {
                                printf("A média das leituras é: %.2f", media);
                            }
                            mostrar_mensagem();
                            break;

                        //Relatório de média de leitura (.csv)
                        case 7:
                            relata_media_csv(lista_de_setores);
                            break;

                        case 8: 
                            FILE *fp = fopen("sensores_e_setores.html", "w");
                            css_para_HTML(fp);
                            exportar_sensores_HTML(fp, lista_de_sensores);
                            exportar_setores_HTML(fp, lista_de_setores);
                            fclose(fp);
                            break;
                    }
                } while (opc_2 != FIM);
                break;

            //menu de exclusão
            case 3: 
                do {
                    limpar_tela();
                    opc_3 = menu_exclusao();

                    switch (opc_3) {
                        case 1:
                            exclui_sensor_no_setor(&lista_de_setores, lista_de_setores);
                            mostrar_mensagem();
                            break;
                    }
                } while(opc_3 != FIM);
                break;
        }
    } while (opcao != FIM);

    salva_lista_sensores(lista_de_sensores);
    salva_lista_setores(lista_de_setores);

    return 0;
}