#include <stdio.h>
#include <stdlib.h> //exit
#include <locale.h> 

FILE *arquivo;

int contarCaracteresArquivo(char *nome){
    int i;
    arquivo = fopen(nome, "r+");
    char caractere = fgetc(arquivo);

    if(arquivo == NULL){
        printf("Arquivo não foi aberto.");
        exit(0);
    }
    
    char c;

    while((c = fgetc(arquivo)) != EOF){
        if(c != ' '){
            i++;
        }
    }

    fprintf(arquivo, "; %d", i); //escreve o número de caracteres na última linha

    fclose(arquivo);

    return i;
}


int main(){
    char nomeArquivo[100];

    printf("Insira o nome do arquivo com a extensão.\n");
    scanf("%s", nomeArquivo);

    int numCaracteres = contarCaracteresArquivo(nomeArquivo);

    printf("O número de caracteres do arquivo é: %d\n", numCaracteres);
}