#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIM 0
#define MAX_SENSOR_LOCAL 3
#define T_STR 100

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
    struct sensor *prox;
} sensor_t;

typedef struct setor {
    int id;
    string descricao;
    sensor_t *sensores_instalados;
    int qtd_sensores_instalados;
    struct setor *prox;
} setor_t;

typedef struct verificacao {
    int indice_sensor;
    int indice_setor;
    int true_false;
} verificacao_t;

//funções de menu
int menu_principal(void);
int menu_setor_sensor(void);
int menu_leituras(void);

//funções de formatação de string
void remove_enter(string str);
void formata_maiusculo(string str);

//funções de limpesa de tela
void mostrar_mensagem(void);
void limpar_tela(void);

//funções de print:
    //id e nome(todos) 
    void lista_sensores(sensor_t *sensor);
    void lista_setores(setor_t *setor);

    //id, nome e descrições
    void dados_sensor(sensor_t *sensor);
    void dados_todos_sensor(sensor_t *sensor);
    void dados_setor(setor_t *setor);
    void dados_todos_setor(setor_t *setor);
    void mostra_sensores_por_setor(setor_t *setor);

//funções de cadastro
sensor_t *cadastro_sensor(int qtd_sensores);
void coloca_sensor_na_lista(sensor_t *loop, sensor_t **lista, int qtd_sensores);
setor_t *cadastro_setor(int qtd_setores);
void coloca_setor_na_lista(setor_t *loop, setor_t **lista, int qtd_setores);
    //função que distribui sensores em setores
    sensor_t *copia_sensor(sensor_t *sensor);
    void distribui_sensor(setor_t **lista_de_setor, sensor_t *lista_de_sensor);

//funções que pedem pro usuario
int pede_id_sensor(sensor_t *lista);
int pede_id_setor(setor_t *lista);

//funções que localizam id
sensor_t *localiza_sensor_por_id(sensor_t *lista, int id);
setor_t *localiza_setor_por_id(setor_t *lista, int id);

int main(void)
{
    //ponteiros de structs
    sensor_t *lista_de_sensores = NULL;
    setor_t *lista_de_setores = NULL;

    //variáveis que controlam quantidade
    int qtd_sensores = 0;
    int qtd_setores = 0;

    //variáveis de menu
    int opcao, opc_1, opc_2;
    
    //variáveis dos relatórios
    float variacao, media;

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
                            coloca_sensor_na_lista(lista_de_sensores, &lista_de_sensores, qtd_sensores);
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
                            coloca_setor_na_lista(lista_de_setores, &lista_de_setores, qtd_setores);
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
                            break;

                        //Relatório de leituras
                        case 2:
                            break;

                        //Relatório de variação de leitura
                        case 3: 
                            break;

                        //Relatório de média de leitura
                        case 4: 
                            break;
                    }
                } while (opc_2 != FIM);
                break;
        }
    } while (opcao != FIM);

    return 0;
}

//implementações de funções
//menus
int menu_principal(void)
{
    int opcao;

    printf("|   SENSORES AM    |\n");
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
    printf("2.Relatório de leituras\n");
    printf("3.Relatório de variação de leitura\n");
    printf("4.Relatório de média de leitura\n");
    printf("0.Retornar ao menu principal\n");
    printf("-----------------------\n");
    printf("::: ");
    scanf("%i", &opcao);
    getchar();

    return opcao;
}


//formatação de string
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


//limpa tela
void mostrar_mensagem(void)
{
    printf("PARA RETORNAR AO MENU PRESSIONE ENTER\n");
    getchar();
}

void limpar_tela(void)
{
    system("clear");
}


//prints
void lista_sensores(sensor_t *sensor)
{
    for (sensor; sensor != NULL; sensor = sensor->prox ) {
        printf("Id: %i, tipo: %s\n", sensor->id, sensor->tipo);
    }
    printf("\n");
}

void lista_setores(setor_t *setor)
{
    for (setor; setor != NULL; setor = setor->prox ) {
        printf("Id: %i, descrição: %s\n", setor->id, setor->descricao);
    }
    printf("\n");
}

void dados_sensor(sensor_t *sensor)
{
    printf("Id do sensor..............: %i\n", sensor->id);
    printf("Tipo do sensor............: %s\n", sensor->tipo);
    printf("Faixa de leitura do sensor: %.2f à %.2f\n", sensor->minimo_faixa_leitura, sensor->maximo_faixa_leitura);
}

void dados_todos_sensor(sensor_t *sensor)
{
    for (sensor; sensor != NULL; sensor = sensor->prox ) {
        dados_sensor(sensor);
    }
    printf("\n");
}

void dados_setor(setor_t *setor)
{
    printf("Id: %i, descrição: %s\n", setor->id, setor->descricao);
    mostra_sensores_por_setor(setor);
}

void dados_todos_setor(setor_t *setor)
{
    for (setor; setor != NULL; setor = setor->prox ) {
        dados_setor(setor);
    }
    printf("\n");
}

void mostra_sensores_por_setor(setor_t *setor)
{
    if (!setor->sensores_instalados) {
        printf("Não há sensores cadastrados nesse setor!\n");
    } else {
        printf("Sensores instalados: \n");
        for (setor; setor->sensores_instalados != NULL; setor->sensores_instalados = setor->sensores_instalados->prox ) {
            dados_sensor(setor->sensores_instalados);
            printf("Horário da primeira leitura %02i:%02i\n", setor->sensores_instalados->horario_primeira_leitura.horas, setor->sensores_instalados->horario_primeira_leitura.minutos);
            printf("Horário da segunda leitura %02i:%02i\n", setor->sensores_instalados->horario_segunda_leitura.horas, setor->sensores_instalados->horario_segunda_leitura.minutos);
        }
    }
    printf("\n");
}

//cadastros
sensor_t *cadastro_sensor(int qtd_sensores)
{
    sensor_t *sensor = (sensor_t *)calloc(sizeof(sensor_t), 1);
    sensor->prox = NULL;

    sensor->id = qtd_sensores + 1;
    printf("Sensor de id: %i\n", sensor->id);

    printf("Qual o tipo do sensor? ");
    fgets(sensor->tipo, T_STR, stdin);
    remove_enter(sensor->tipo);
    formata_maiusculo(sensor->tipo);

    printf("Qual o valor mínimo lido pelo sensor? ");
    scanf("%f", &sensor->minimo_faixa_leitura);
    getchar();

    printf("Qual o valor máximo lido pelo sensor? ");
    scanf("%f", &sensor->maximo_faixa_leitura);
    getchar();

    return sensor;
}

void coloca_sensor_na_lista(sensor_t *loop, sensor_t **lista, int qtd_sensores)
{
    sensor_t *novo_sensor = cadastro_sensor(qtd_sensores);
    
    //adiciona pelo final
    if (!(*lista)) {
        (*lista) = novo_sensor;
    } else {
        for (loop; loop != NULL; loop = loop->prox ) {
            if (!((*lista)->prox)) {
                (*lista)->prox = novo_sensor;
            }
        }
    }

    //garante que não fiquem pontas soltas
    novo_sensor = NULL;
    free(novo_sensor);
}

setor_t *cadastro_setor(int qtd_setores)
{
    setor_t *setor = (setor_t *)calloc(sizeof(setor_t), 1);

    setor->qtd_sensores_instalados = 0;
    setor->prox = NULL;

    setor->id = qtd_setores + 1;
    printf("Setor de id: %i\n", setor->id);

    printf("Descrição do setor: ");
    fgets(setor->descricao, T_STR, stdin);
    remove_enter(setor->descricao);
    formata_maiusculo(setor->descricao);

    return setor;
}

void coloca_setor_na_lista(setor_t *loop, setor_t **lista, int qtd_setores)
{
    setor_t *novo_setor = cadastro_setor(qtd_setores);
    
    //adiciona pelo final
    if (!(*lista)) {
        (*lista) = novo_setor;
    } else {
        for (loop; loop != NULL; loop = loop->prox ) {
            if (!((*lista)->prox)) {
                (*lista)->prox = novo_setor;
            }
        }
    }

    //garante que não fiquem ponteiros soltos
    novo_setor = NULL;
    free(novo_setor);
}

void distribui_sensor(setor_t **lista_de_setor, sensor_t *lista_de_sensor)
{
    int id_setor = pede_id_setor((*lista_de_setor));
    setor_t *setor = localiza_setor_por_id((*lista_de_setor), id_setor);

    if (!setor) {
        printf("Setor não encontrado ou não existe!\n");
        return;
    }

    if (setor->qtd_sensores_instalados > MAX_SENSOR_LOCAL) {
        printf("Número máximo de sensores instalados no setor indicado\n");
        return;
    }

    int id_sensor = pede_id_sensor(lista_de_sensor);
    sensor_t *sensor = localiza_sensor_por_id(lista_de_sensor, id_sensor);

    if (!sensor) {
        printf("Sensor não encontrado ou não existe!\n");
        return;
    }

    sensor_t *aux = copia_sensor(sensor);

    do {
        printf("Hora da primeira leitura do sensor (entre 0 e 23): ");
        scanf("%i", &aux->horario_primeira_leitura.horas);
    } while (aux->horario_primeira_leitura.horas > 23 || aux->horario_primeira_leitura.horas < 0);

    do {
        printf("Minuto da primeira leitura do sensor (entre 0 e 59): ");
        scanf("%i", &aux->horario_primeira_leitura.minutos);
    } while (aux->horario_primeira_leitura.minutos > 59 || aux->horario_primeira_leitura.minutos < 0);

        do {
        printf("Hora da segunda leitura do sensor (entre 0 e 23): ");
        scanf("%i", &aux->horario_segunda_leitura.horas);
    } while (aux->horario_segunda_leitura.horas > 23 || aux->horario_segunda_leitura.horas < 0);

    do {
        printf("Minuto da segunda leitura do sensor (entre 0 e 59): ");
        scanf("%i", &aux->horario_segunda_leitura.minutos);
    } while (aux->horario_segunda_leitura.minutos > 59 || aux->horario_segunda_leitura.minutos < 0);

    aux->prox = setor->sensores_instalados;
    setor->sensores_instalados = aux;

    aux = NULL;
    free(aux);
}

sensor_t *copia_sensor(sensor_t *sensor)
{
    sensor_t *aux = (sensor_t *)calloc(sizeof(sensor_t), 1);
    aux->id = sensor->id;
    strcpy(aux->tipo, sensor->tipo);
    aux->minimo_faixa_leitura = sensor->minimo_faixa_leitura;
    aux->maximo_faixa_leitura = sensor->maximo_faixa_leitura;
    aux->prox = NULL;

    return aux;
}


//pede id pro usuário
int pede_id_sensor(sensor_t *lista)
{
    int id;
    printf("Sensores: \n");
    lista_sensores(lista);
    
    printf("Digite o id do sensor desejado: ");
    scanf("%i", &id);
    getchar();

    return id;
}

int pede_id_setor(setor_t *lista)
{
    int id;
    printf("Setores: \n");
    lista_setores(lista);
    
    printf("Digite o id do setor desejado: ");
    scanf("%i", &id);
    getchar();
    
    return id;
}


///localiza por id
sensor_t *localiza_sensor_por_id(sensor_t *lista, int id)
{
    for (lista; lista != NULL; lista = lista->prox) {
        if (lista->id == id) {
            return lista;
        }
    }

    return lista;
}

setor_t *localiza_setor_por_id(setor_t *lista, int id) 
{
    for (lista; lista != NULL; lista = lista->prox) {
        if (lista->id == id) {
            return lista;
        }
    }

    return lista;   
}
