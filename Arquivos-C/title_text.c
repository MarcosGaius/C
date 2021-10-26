#include <stdio.h>
#include <stdlib.h> //exit

#define MAX 1000

FILE *arquivo;

void criarArquivo(char title[20], char text[MAX]){
    arquivo = fopen(title, "w");

    fprintf(arquivo, "%s", text);
}

void verificarArquivo(char title[20]){
    arquivo = fopen(title, "w");

    if(arquivo == NULL){
        printf("O arquivo não foi criado.\n");
        exit(1);
    }
    else{
        printf("O arquivo foi criado com sucesso.\n");
    }
    fclose(arquivo);
}

int main(){
    char titulo[20];
    char texto[MAX];
    //int tamanho;

    printf("Insira o nome do arquivo com a extensão, de até 20 caracteres.\n");
    scanf("%s", titulo);
    printf("\n");

    printf("Insira o conteúdo do arquivo.\n");
    scanf(" %999[^\n]", texto);
    printf("\n");

    criarArquivo(titulo, texto);
    verificarArquivo(titulo);

    return 0;
}