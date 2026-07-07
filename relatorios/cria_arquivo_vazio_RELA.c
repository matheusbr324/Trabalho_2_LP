#include <stdio.h>

int main (void)
{
    FILE *fp = NULL;
    fp = fopen("./relatorios/leituras.csv", "w");
    fclose(fp);
    fp = fopen("./relatorios/variacao.csv", "w");
    fclose(fp);
    fp = fopen("./relatorios/media.csv", "w");
    fclose(fp);
    return 0;
}
