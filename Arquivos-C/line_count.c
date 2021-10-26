#include <stdio.h>
#include <stdlib.h> //exit

FILE * arquivo;

int contarLinhas(char title[20]){
    arquivo = fopen(title, "r");
    int lines;

    while(!feof(arquivo)){
        if((fgetc(arquivo)) == '\n'){
            lines++;
        }
    }

    return lines+1; //a última linha não é contada pelo \n
}

int main(){
    int linhas;
    char titulo[20];

    printf("Digite o nome do arquivo com a extensão\n");
    scanf("%s", titulo);
    printf("\n");

    linhas = contarLinhas(titulo);

    printf("A quantidade de linhas é: %d\n", linhas);

    return 0;
}