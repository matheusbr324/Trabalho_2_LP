#include <stdio.h>

int main (void)
{
    FILE *fp = NULL;
    fp = fopen("./base_de_dados/lista_setores", "wb");
    fclose(fp);
    fp = fopen("./base_de_dados/lista_sensores", "wb");
    fclose(fp);
    return 0;
}