#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define FIM 0
#define MAX_SENSORES 30
#define MAX_SENSOR_LOCAL 3
#define MAX_SETORES 10
#define T_STR 100
#define T_TIPO_SENSOR 12

typedef char string[T_STR];

typedef struct horario {
    int horas;
    int minutos;
} horario_t;

typedef struct sensor {
    int id;
    string tipo;
    float minimo_faixa_leitura;
    float maximo_faixa_leitura;
    horario_t horario_primeira_leitura;
    horario_t horario_segunda_leitura;
    float primeira_medicao;
    float segunda_medicao;
} sensor_t;

typedef struct monitoramento {
    int id;
    string descricao;
    sensor_t sensores_instalados[MAX_SENSOR_LOCAL];
    int qtd_sensores_instalados;
} monitoramento_t;

typedef struct verificacao {
    int indice_sensor;
    int indice_setor;
    int true_false;
} verificacao_t;
//até aqui tudo feito

//Funções auxiliares
int menu_principal(void); //feito
int menu_sensor(void); //feito
int menu_monitoramento(void); //feito
int menu_relatorios(void); //feito
void remove_enter(string str); //feito
void formata_maiusculo(string str); //feito
void mostra_setor(void); //feito
void mostra_dados_sensor(int indice); //feito
void mostra_sensores_por_setor(void); //feito
void mostra_dados_setores(void); //feito
sensor_t cadastro_sensor(void); //feito
monitoramento_t cadastro_setor(void); //feito
void distribui_sensor(int id_do_sensor, int id_do_setor); //feito
int le_id_setor(void); //feito
int le_id_sensor(void); //feito
void relatorio_sensor(void); //removido
void relatorio_setor(void); //removido
int encontrar_sensor(int id); //feito
int encontrar_setor(int id); //feito
void inserir_dados_de_leitura(void); //feito
void relatorio_de_leituras(void); //feito
float variacao_de_leitura(void);
float media_de_leitura(void);
verificacao_t verificacao_se_sensor_E_setor(void); //feito
void mostrar_mensagem(void); //feito
void limpar_tela(void); //feito


//Vetores de dados
sensor_t sensores[MAX_SENSORES]; //substituido
monitoramento_t setores[MAX_SETORES]; //substituido

//Contadores de quantidade
int qtd_sensores = 0; //substituido
int qtd_setores = 0; //substituido

int main()
{
    int opcao, opc_1, opc_2, opc_3;

    do {
        limpar_tela();
        opcao = menu_principal();

        switch (opcao) {
            case 1: do {
                        limpar_tela();
                        opc_1 = menu_sensor();

                        switch (opc_1) {
                            case 1: 
                                sensores[qtd_sensores] = cadastro_sensor();
                                qtd_sensores++;
                                break;

                            case 2: 
                                if (qtd_sensores == 0) {
                                    printf("Não há sensores cadastrados!\n\n");
                                    mostrar_mensagem();
                                    break;
                                }
                                for (int i = 0; i < qtd_sensores; i++) {
                                    mostra_dados_sensor(i);
                                }
                                mostrar_mensagem();
                                break;
                        }
                    } while (opc_1 != FIM);
                    break;
            case 2: do {
                        limpar_tela();
                        opc_2 = menu_monitoramento();

                        switch (opc_2) {
                            case 1: 
                                setores[qtd_setores] = cadastro_setor();
                                qtd_setores++;
                                break;

                            case 2: 
                                if (qtd_sensores < 1) {
                                    printf("Não há sensores cadastrados!\n");
                                    mostrar_mensagem();
                                    break;
                                }

                                if (qtd_setores < 1) {
                                    printf("Não há setores cadastrados!\n");
                                    mostrar_mensagem();
                                    break;
                                }

                                mostra_setor();
                                int id_setor = le_id_setor();
                                if (id_setor == -1) {
                                    printf("Operação cancelada!");
                                    mostrar_mensagem();
                                    break;
                                }

                                for (int i = 0; i < qtd_sensores; i++) {
                                    mostra_dados_sensor(i);
                                }
                                int id_sensor = le_id_sensor();
                                if (id_sensor == -1) {
                                    printf("Operação cancelada!");
                                    mostrar_mensagem();
                                    break;
                                }

                                distribui_sensor(id_sensor, id_setor);
                                mostrar_mensagem();
                                break;

                            case 3: 
                                if (qtd_setores != 0) {
                                    mostra_sensores_por_setor();
                                }
                                else {
                                    printf("Não há setores cadastrados!\n");
                                    mostrar_mensagem();
                                }
                                mostrar_mensagem();
                                break;

                            case 4: 
                                if (qtd_sensores == 0) {
                                    printf("Não há sensores cadastrados!\n");
                                    mostrar_mensagem();
                                    break;
                                }
                                if (qtd_setores == 0) {
                                    printf("Não há setores cadastrados!\n");
                                    mostrar_mensagem();
                                    break;
                                }
                                inserir_dados_de_leitura();
                                mostrar_mensagem();
                                break;
                        }
                    } while (opc_2 != FIM);
                    break;
            case 3: do {
                        limpar_tela();
                        opc_3 = menu_relatorios();

                        switch (opc_3) {
                            case 1: relatorio_sensor();
                                    mostrar_mensagem();
                                    break;
                            
                            case 2: relatorio_setor();
                                    mostrar_mensagem();
                                    break;
                            
                            case 3: relatorio_de_leituras();
                                    mostrar_mensagem();
                                    break;
                            
                            case 4: float variacao = variacao_de_leitura();
                                    if (variacao == -1) {
                                        break;
                                    }
                                    printf("A variação é igual a: %.2f\n\n", variacao);
                                    mostrar_mensagem();
                                    break;
                            
                            case 5: float media = media_de_leitura();
                                    printf("A média é igual a: %.2f\n\n", media);
                                    mostrar_mensagem();
                                    break;
                        }

                    } while (opc_3 != FIM);
                }

            } while (opcao != FIM);

        return 0;
    }


// Implementação funções auxiliares
int menu_principal()
{
    int opcao;

    printf("|   SENSORES AM    |\n");
    printf("--------------------\n");
    printf("1.Menu de sensores\n");
    printf("2.Menu de monitoramento\n");
    printf("3.Menu de relatórios\n");
    printf("0.Sair do programa\n");
    printf("--------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_sensor()
{
    int opcao;

    printf("|   MENU SENSORES   |\n");
    printf("---------------------\n");
    printf("1.Cadastrar sensor\n");
    printf("2.Listar sensores cadastrados\n");
    printf("0.Retornar ao menu principal\n");
    printf("--------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_monitoramento()
{
    int opcao;

    printf("|   MENU MONITORAMENTO   |\n");
    printf("--------------------------\n");
    printf("1.Cadastrar setor\n");
    printf("2.Distribuir sensor\n");
    printf("3.Listar sensores distribuídos\n");
    printf("4.Inserir dados de leitura do sensor\n");
    printf("0.Retornar ao menu principal\n");
    printf("-------------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

int menu_relatorios()
{
    int opcao;

    printf("|   MENU RELATÓRIOS   |\n");
    printf("-----------------------\n");
    printf("1.Relatório de sensores\n");
    printf("2.Relatório de setores\n");
    printf("3.Relatório de leituras\n");
    printf("4.Relatório de variação de leitura\n");
    printf("5.Relatório de média de leitura\n");
    printf("0.Retornar ao menu principal\n");
    printf("-----------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}

void remove_enter(string str)
{
    str[strlen(str)-1] = '\0';
}

void formata_maiusculo(string str)
{
    for (int i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

sensor_t cadastro_sensor()
{
    sensor_t sensor;

    sensor.id = qtd_sensores + 1;
    printf("Sensor de id: %i\n", sensor.id);

    printf("Qual o tipo do sensor? ");
    fgets(sensor.tipo, T_STR, stdin);
    remove_enter(sensor.tipo);
    formata_maiusculo(sensor.tipo);

    //alterei faixa de leitura pra maximo e minimo
    printf("Qual o valor mínimo lido pelo sensor? ");
    scanf("%f", &sensor.minimo_faixa_leitura);

    printf("Qual o valor máximo lido pelo sensor? ");
    scanf("%f", &sensor.maximo_faixa_leitura);

    return sensor;
}

monitoramento_t cadastro_setor()
{
    monitoramento_t setor;

    setor.id = qtd_setores + 1;
    setor.qtd_sensores_instalados = 0;
    printf("Setor de id: %i\n", setor.id);

    printf("Descrição do setor: ");
    fgets(setor.descricao, T_STR, stdin);
    remove_enter(setor.descricao);
    formata_maiusculo(setor.descricao);

    //removi o cadastro de horario do setor e movi pra distribuição de sensores
    
    return setor;
}

void mostra_setor()
{
    for (int i = 0; i < qtd_setores; i++) {
        printf("Setor: %s\n", setores[i].descricao);
        printf("Id do setor: %i\n\n", setores[i].id);
    }
}

void mostra_dados_sensor(int indice)
{
    printf("Id do sensor.........: %i\n", sensores[indice].id);
    printf("Tipo do sensor.......: %s\n", sensores[indice].tipo);
    printf("Faixa de leitura.....: %.2f à %.2f\n\n", sensores[indice].minimo_faixa_leitura, sensores[indice].maximo_faixa_leitura);
}

void distribui_sensor(int id_do_sensor, int id_do_setor)
{
    for (int i = 0; i < qtd_setores; i++) {
        if (setores[i].id == id_do_setor) {
            if (setores[i].qtd_sensores_instalados == 3) {
                printf("Número máximo de sensores instalados no setor!\n");
                break;
            }
            for (int j = 0; j < qtd_sensores; j++) {
                if (sensores[j].id == id_do_sensor) {
                    setores[i].sensores_instalados[setores[i].qtd_sensores_instalados] = sensores[j];

                    //horas de leitura movidas pra hora que distribui o sensor
                    printf("Hora da primeira leitura do sensor: ");
                    scanf("%i", &setores[i].sensores_instalados[setores[i].qtd_sensores_instalados].horario_primeira_leitura.horas);
                    getchar();

                    printf("Minuto da primeira leitura do sensor: ");
                    scanf("%i", &setores[i].sensores_instalados[setores[i].qtd_sensores_instalados].horario_primeira_leitura.minutos);
                    getchar();

                    printf("Hora da segunda leitura do sensor: ");
                    scanf("%i", &setores[i].sensores_instalados[setores[i].qtd_sensores_instalados].horario_segunda_leitura.horas);
                    getchar();

                    printf("Minuto da segunda leitura do sensor: ");
                    scanf("%i", &setores[i].sensores_instalados[setores[i].qtd_sensores_instalados].horario_segunda_leitura.minutos);
                    getchar();
                    printf("\n");

                    setores[i].qtd_sensores_instalados++;

                    printf("Sensor distribuído com sucesso!\n\n");
                    break;
                }
            }
            break;
        }
    }
}

int le_id_setor()
{
    int id;
    do {
        printf("Id do setor: ");
        scanf("%i", &id);

        for (int i = 0; i < qtd_setores; i++) {
            if (setores[i].id == id) {
                return id;
            }
        }

        printf("Id inválido!\n");
        printf("Para sair digite 0!\n");
    } while (id != FIM);
    return -1;
}

int le_id_sensor()
{
    int id;
    do {
        printf("Id do sensor: ");
        scanf("%i", &id);

        for (int i = 0; i < qtd_sensores; i++) {
            if (sensores[i].id == id) {
                return id;
            }
        }

        printf("Id inválido!\n");
        printf("Para sair digite 0!\n");
    } while (id != FIM);
    return -1;
}

void mostra_sensores_por_setor()
{
    for (int i = 0; i < qtd_setores; i++) {
        if (setores[i].qtd_sensores_instalados == 0) {
            printf("Não há sensores cadastrados no setor de ID: %i\n\n", setores[i].id);
        }
        else {
            for (int j = 0; j < setores[i].qtd_sensores_instalados; j++) {
                printf("Id do sensor.........: %i\n", setores[i].sensores_instalados[j].id);
                printf("Tipo do sensor.......: %s\n", setores[i].sensores_instalados[j].tipo);
                printf("Faixa de leitura.....: %.2f à %.2f\n", setores[i].sensores_instalados[j].minimo_faixa_leitura, setores[i].sensores_instalados[j].maximo_faixa_leitura);
                printf("Horário da primeira leitura %02i:%02i\n", setores[i].sensores_instalados[j].horario_primeira_leitura.horas, setores[i].sensores_instalados[j].horario_primeira_leitura.minutos);
                printf("Horário da segunda leitura %02i:%02i\n\n", setores[i].sensores_instalados[j].horario_segunda_leitura.horas, setores[i].sensores_instalados[j].horario_segunda_leitura.minutos);
            }                
        }
    }
}

void mostra_dados_setores()
{
    for (int i = 0; i < qtd_setores; i++) {
        printf("Setor de id: %i\n", setores[i].id);
        printf("Descrição do setor: %s\n", setores[i].descricao);
        for (int j = 0; j < setores[i].qtd_sensores_instalados; j++) {
            printf("Hora da primeira leitura: %02i\n", setores[i].sensores_instalados[j].horario_primeira_leitura.horas);
            printf("Minuto da primeira leitura: %02i\n", setores[i].sensores_instalados[j].horario_primeira_leitura.minutos);
            printf("Hora da segunda leitura: %02i\n", setores[i].sensores_instalados[j].horario_segunda_leitura.horas);
            printf("Minuto da segunda leitura: %02i\n\n", setores[i].sensores_instalados[j].horario_segunda_leitura.minutos);
        }
    }
}

void relatorio_sensor(void)
{
    printf("---------- RELATÓRIO SENSOR ----------\n");
    for (int i = 0; i < qtd_sensores; i++) {
        mostra_dados_sensor(i);
    }
}


void relatorio_setor()
{
    printf("---------- RELATÓRIO SETOR ----------\n");
    for (int i = 0; i < qtd_setores; i++) {
        printf("Setor de id: %i\n", setores[i].id);
        printf("Descrição do setor: %s\n", setores[i].descricao);
        printf("Quantidade de sensores instalados: %i\n\n", setores[i].qtd_sensores_instalados);
    }
}

int encontrar_sensor(int id)
{
    for (int i = 0; i < qtd_sensores; i++) {
        if (sensores[i].id == id){
            return i; 
        }
    }
    return -1;
}


int encontrar_setor(int id)
{
    for (int i = 0; i < qtd_setores; i++) {
        if (setores[i].id == id){
            return i; 
        }
    }
    return -1;
}

verificacao_t verificacao_se_sensor_E_setor(void)
{
    verificacao_t verificacao;
    int id_setor, id_sensor, flag = 1, opcao = -1;
    verificacao.true_false = 0;
    verificacao.indice_sensor = 0;
    verificacao.indice_setor = 0;

    printf("Qual o ID do setor?\n");
    scanf("%i", &id_setor);
    getchar();
    
    if (encontrar_setor(id_setor) == -1) {
        printf("Setor não encontrado!\n");
        verificacao.true_false = -1;
        return verificacao;
    }
    verificacao.indice_setor = encontrar_setor(id_setor);

    if (setores[verificacao.indice_setor].qtd_sensores_instalados != 0){
        do {
            printf("Digite o número da opção que contém o sensor desejado:\n");
            for (int i = 0; i < setores[verificacao.indice_setor].qtd_sensores_instalados; i++) {
                printf("%i.ID: %i, tipo: %s\n", i + 1, setores[verificacao.indice_setor].sensores_instalados[i].id, setores[verificacao.indice_setor].sensores_instalados[i].tipo);
            }
            printf("0.Cancelar operação\n");
            scanf("%i", &opcao);
            getchar();

            switch (opcao) {
                case 1: verificacao.indice_sensor = (opcao - 1);
                        flag = 0;        
                        break;
                
                case 2: if (setores[verificacao.indice_setor].qtd_sensores_instalados < 2) {
                            break;
                        }
                        verificacao.indice_sensor = (opcao - 1);
                        flag = 0;        
                        break;

                case 3: if (setores[verificacao.indice_setor].qtd_sensores_instalados < 3) {
                            break;
                        }
                        verificacao.indice_sensor = (opcao - 1);
                        flag = 0;        
                        break;
            }
        } while (flag != FIM && opcao != FIM);
    } else {
        printf("Não há sensores cadastrados no setor\n");
        verificacao.true_false = -1;
        mostrar_mensagem();
    }

    if (opcao == 0) {
        printf("Operação cancelada\n");
        verificacao.true_false = -1;
        mostrar_mensagem();
    }
    return verificacao;
}
//encontrar_sensor(setores[verificacao.indice_setor].sensores_instalados [opcao - 1].id)
void inserir_dados_de_leitura(void)
{
    verificacao_t verificacao = verificacao_se_sensor_E_setor();
    int opcao, flag = 1;

    if (verificacao.true_false == -1) {
        return;
    }

    do {
            printf("Horario de leitura: \n");
            printf("1.Primeira leitura\n");
            printf("2.Segunda leitura\n");
            printf("0.Cancelar operação\n");
            scanf("%i", &opcao);
            getchar();

            switch(opcao){
            case 1: printf("Dado da primeira leitura: \n");
                    scanf("%f", &setores[verificacao.indice_setor].sensores_instalados[verificacao.indice_sensor].primeira_medicao);
                    getchar();
                    flag = 0;
                    break; 
            case 2: printf("Dado da segunda leitura: \n");
                    scanf("%f", &setores[verificacao.indice_setor].sensores_instalados[verificacao.indice_sensor].segunda_medicao);
                    getchar();
                    flag = 0;
                    break;
        }
    } while(opcao != FIM && flag != FIM);
}

void relatorio_de_leituras(void)
{
    printf("---------- RELATÓRIO DE LEITURA ----------\n");
    for (int i = 0; i < qtd_setores; i++) {
        printf("Setor: %i\n", setores[i].id);
        for (int j = 0; j < setores[i].qtd_sensores_instalados; j++) {
            printf("Id do sensor.........: %i\n", setores[i].sensores_instalados[j].id);
            printf("Tipo do sensor.......: %s\n", setores[i].sensores_instalados[j].tipo);
            printf("Primeira leitura.....: %.2f\n", setores[i].sensores_instalados[j].primeira_medicao);
            printf("Segunda leitura......: %.2f\n\n", setores[i].sensores_instalados[j].segunda_medicao);
        }
    }
}

float variacao_de_leitura(void)
{
    verificacao_t verificacao = verificacao_se_sensor_E_setor();
    float maior, menor, resultado;
    if (verificacao.true_false == -1) {
        return -1;
    }
    if (setores[verificacao.indice_setor].sensores_instalados[verificacao.indice_sensor].primeira_medicao > setores[verificacao.indice_setor].sensores_instalados[verificacao.indice_sensor].segunda_medicao) {
        maior = setores[verificacao.indice_setor].sensores_instalados[verificacao.indice_sensor].primeira_medicao;
        menor = setores[verificacao.indice_setor].sensores_instalados[verificacao.indice_sensor].segunda_medicao;
    }
    else {
        maior = setores[verificacao.indice_setor].sensores_instalados[verificacao.indice_sensor].segunda_medicao;
        menor = setores[verificacao.indice_setor].sensores_instalados[verificacao.indice_sensor].primeira_medicao;
    }
    resultado = maior - menor;
    return resultado;
}

float media_de_leitura(void)
{
    verificacao_t verificacao = verificacao_se_sensor_E_setor();
    float resultado;
    if (verificacao.true_false == -1) {
        return -1;
    }
    resultado = (setores[verificacao.indice_setor].sensores_instalados[verificacao.indice_sensor].primeira_medicao + setores[verificacao.indice_setor].sensores_instalados[verificacao.indice_sensor].segunda_medicao) / (float) 2;
    return resultado;
}

void mostrar_mensagem(void)
{
    printf("PARA RETORNAR AO MENU PRESSIONE ENTER\n");
    getchar();
}

void limpar_tela(void)
{
    system("clear");
}