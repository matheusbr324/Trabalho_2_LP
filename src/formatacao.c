#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../includes/formatacao.h"
#include "../includes/types.h"

void remove_enter(string str)
{
    str[strlen(str)-1] = '\0';
}

//função recursiva
void formata_maiusculo(string str, int i)
{
    //salvaguarda
    if (i > strlen(str)) {
        return;
    }

    str[i] = toupper(str[i]);
    i++;
    formata_maiusculo(str, i);
}