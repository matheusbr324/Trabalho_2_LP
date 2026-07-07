#include <stdio.h>
#include "../includes/exportacao.h"

void css_para_HTML(FILE *fp)
{
    //informação pro navegador
    fprintf(fp, "<!DOCTYPE html>");

    //abre o cabeçalho
    fprintf(fp, "<head>");
    
    //formatação pra exibir acentos e 'ç' corretamente
    fprintf(fp, "   <meta charset=\"UTF-8\">");

    //estilização
    fprintf(fp, "   <style>");

    //centralização das tabelas
    fprintf(fp, "       .tabela {");
    fprintf(fp, "           display: inline-block;");
    fprintf(fp, "           vertical-align: top;");
    fprintf(fp, "           width: 45%%;");
    fprintf(fp, "           margin-right: 4%%");
    fprintf(fp, "           box-sizing: border-box");
    fprintf(fp, "       }");

    //estilo das células
    //indices
    fprintf(fp, "       th {");
    fprintf(fp, "           border: 2px solid #111;");
    fprintf(fp, "           padding: 9px;");
    fprintf(fp, "       }");

    //dados
    fprintf(fp, "       td {");
    fprintf(fp, "           border: 1px solid #333;");
    fprintf(fp, "           padding: 9px;");
    fprintf(fp, "       }");

    //termina a estilização
    fprintf(fp, "   </style>");

    //fecha o cabeçalho
    fprintf(fp, "</head>");

}

void exportar_sensores_HTML(FILE *fp, sensor_t *lista)
{   
    //bloco de corpo do site
    fprintf(fp, "<body>\n");

    //bloco para a formatação das tabelas
    fprintf(fp, "<div class=\"tabela\">\n");

    //começa a tabela
    fprintf(fp, "<table>\n");

    //primeira linha de cabeçalho
    fprintf(fp, "   <th>Sensores</th>\n");

    //segunda linha de cabeçalho
    fprintf(fp, "   <tr>\n");
    fprintf(fp, "       <th>Id</th>");
    fprintf(fp, "       <th>Tipo</th>");
    fprintf(fp, "       <th>Leitura mínima</th>");
    fprintf(fp, "       <th>Leitura máxima</th>\n");
    fprintf(fp, "   </tr>\n");

    //percorre sensores
    for (lista; lista != NULL; lista = lista->prox) {
        
        //insere os dados do sensor em uma nova linha 
        fprintf(fp, "   <tr>\n");
        fprintf(fp, "     <td>%i</td>", lista->id);
        fprintf(fp, "     <td>%s</td>", lista->tipo);
        fprintf(fp, "     <td>%.2f</td>", lista->minimo_faixa_leitura);
        fprintf(fp, "     <td>%.2f</td>\n", lista->maximo_faixa_leitura);
        fprintf(fp, "   </tr>\n");
    }

    //fecha a tabela
    fprintf(fp, "</table>");
    fprintf(fp, "</div>");
}

void exportar_setores_HTML(FILE *fp, setor_t *lista)
{
    //bloco para a formatação das tabelas
    fprintf(fp, "<div class=\"tabela\">\n");
    
    //começa a tabela
    fprintf(fp, "<table>\n");

    //primeira linha de cabeçalho
    fprintf(fp, "   <th>Setores</th>\n");

    //segunda linha de cabeçalho
    fprintf(fp, "   <tr>\n");
    fprintf(fp, "       <th>Id</th>");
    fprintf(fp, "       <th>Descrição</th>");
    fprintf(fp, "       <th>Quantidade de sensores instalados</th>");
    fprintf(fp, "       <th>Sensores instalados</th>\n");
    fprintf(fp, "   </tr>\n");

    //percorre setores
    for (lista; lista != NULL; lista = lista->prox) {
        
        //insere os dados do setor em uma nova linha 
        fprintf(fp, "<tr>\n");
        fprintf(fp, "   <td>%i</td>", lista->id);
        fprintf(fp, "   <td>%s</td>", lista->descricao);
        fprintf(fp, "   <td>%i</td>", lista->qtd_sensores_instalados);
        
        //lista os sensores
        fprintf(fp, "   <td>");
        
        if (lista->qtd_sensores_instalados > 0) {
            sensor_t *sensor = lista->sensores_instalados;
            for (sensor; sensor != NULL; sensor = sensor->prox) {
                fprintf(fp, "Id: %i, Tipo: %s<br>", sensor->id, sensor->tipo);
            }
        } else {
            fprintf(fp, "   Não há sensores instalados\n");
        }

        fprintf(fp, "   </td>\n");
        fprintf(fp, "</tr>\n");
    }

    //fecha a tabela
    fprintf(fp, "</table>");
    fprintf(fp, "</div>");

    //fecha o corpo do site
    fprintf(fp, "<body>\n");

}