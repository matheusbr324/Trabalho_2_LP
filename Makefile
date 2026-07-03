CC = gcc
DEL = rm
SRC = ./src
OBJS = ./objs

TARGET = Industria

all: objetos
	$(CC) $(OBJS)/main.o $(OBJS)/tela.o $(OBJS)/relatorios.o $(OBJS)/prints.o $(OBJS)/menus.o $(OBJS)/localizacao.o $(OBJS)/leitura.o $(OBJS)/formatacao.o $(OBJS)/cadastro.o -o $(TARGET)

objetos:
	$(CC) -c main.c -o main.o
	$(CC) -c $(SRC)/cadastro.c -o $(OBJS)/cadastro.o
	$(CC) -c $(SRC)/formatacao.c -o $(OBJS)/formatacao.o
	$(CC) -c $(SRC)/leitura.c -o $(OBJS)/leitura.o
	$(CC) -c $(SRC)/localizacao.c -o $(OBJS)/localizacao.o
	$(CC) -c $(SRC)/menus.c -o $(OBJS)/menus.o
	$(CC) -c $(SRC)/prints.c -o $(OBJS)/prints.o
	$(CC) -c $(SRC)/relatorios.c -o $(OBJS)/relatorios.o
	$(CC) -c $(SRC)/tela.c -o $(OBJS)/tela.o

limpar:
	$(DEL) $(OBJS)/*.o
	$(DEL) $(TARGET)