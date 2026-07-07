CC = gcc
DEL = rm
SRC = ./src
OBJS = ./objs
DB = ./base_de_dados
RELA = ./relatorios

TARGET = Industria

all: objetos
	$(CC) $(OBJS)/main.o $(OBJS)/tela.o $(OBJS)/relatorios.o $(OBJS)/prints.o $(OBJS)/menus.o $(OBJS)/localizacao.o $(OBJS)/leitura.o $(OBJS)/formatacao.o $(OBJS)/exclusao.o $(OBJS)/cadastro.o $(OBJS)/arquivos.o -o $(TARGET)

objetos:
	$(CC) -c $(SRC)/arquivos.c -o $(OBJS)/arquivos.o
	$(CC) -c $(SRC)/cadastro.c -o $(OBJS)/cadastro.o
	$(CC) -c $(SRC)/exclusao.c -o $(OBJS)/exclusao.o
	$(CC) -c $(SRC)/formatacao.c -o $(OBJS)/formatacao.o
	$(CC) -c $(SRC)/leitura.c -o $(OBJS)/leitura.o
	$(CC) -c $(SRC)/localizacao.c -o $(OBJS)/localizacao.o
	$(CC) -c $(SRC)/menus.c -o $(OBJS)/menus.o
	$(CC) -c $(SRC)/prints.c -o $(OBJS)/prints.o
	$(CC) -c $(SRC)/relatorios.c -o $(OBJS)/relatorios.o
	$(CC) -c $(SRC)/tela.c -o $(OBJS)/tela.o
	$(CC) -c main.c -o $(OBJS)/main.o

limpar:
	$(DEL) $(OBJS)/*.o
	$(DEL) $(TARGET)

reset_base_de_dados:
	$(DEL) $(DB)/lista_sensores
	$(DEL) $(DB)/lista_setores
	$(CC) $(DB)/cria_arquivo_vazio_DB.c -o $(DB)/cria_arquivo_vazio_DB
	$(DB)/cria_arquivo_vazio_DB

reset_relatorios:
	$(DEL) $(RELA)/*.csv
	$(CC) $(RELA)/cria_arquivo_vazio_RELA.c -o $(RELA)/cria_arquivo_vazio_RELA
	$(RELA)/cria_arquivo_vazio_RELA