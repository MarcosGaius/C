#include <stdio.h>
#include <stdlib.h> //exit

#define MAX 1600

FILE *arquivo;
char texto[MAX];

void abrirArquivo(char title[20]){
    arquivo = fopen(title, "r");

    if(arquivo == NULL){
        printf("O arquivo não foi aberto!\n\n");
        exit(1);
    }
    else{
        printf("O arquivo foi aberto com sucesso!\n\n");
    }

    printf("-----------------------------------------------------------------------------------------------\n");
    printf("%s\n", title);
    printf("-----------------------------------------------------------------------------------------------\n\n");

    while(!feof(arquivo)){
        fscanf(arquivo,"%*s %1600[^\n]", texto);
        printf("%s", texto);
    }
    
    fclose(arquivo);
}

int main(){
    char titulo[20];

    printf("Digite o nome do arquivo que deseja abrir, com a extensão.\n");
    scanf("%s", titulo);

    abrirArquivo(titulo);
    printf("\n");

    return 0;
}