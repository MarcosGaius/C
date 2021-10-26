#include <stdio.h>
#include <stdlib.h> //exit
#include <locale.h> 

FILE *arquivo;
char c;

int contarVogaisArquivo(char *nome){
    int i = 0;
    arquivo = fopen(nome, "r");

    if(arquivo == NULL){
        printf("Arquivo não foi aberto.");
        exit(0);
    }

    while((c = fgetc(arquivo)) != EOF){
        if(c == 'a' || c == 'A' || c == 'e' || c == 'E' || c == 'i' || c == 'I' || c == 'o' || c == 'O' || c == 'u' || c == 'U'){
            i++;
        }        
    }

    return i+1; //contagem começa em 0.
}


int main(){
    char nomeArquivo[100];

    printf("Insira o nome do arquivo com a extensão.\n");
    scanf("%s", nomeArquivo);

    int numVogais = contarVogaisArquivo(nomeArquivo);

    printf("O número de vogais do arquivo é: %d\n", numVogais);
}