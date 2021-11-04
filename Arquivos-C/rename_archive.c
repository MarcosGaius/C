#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE * arquivo;

void nomeOrdem(){
    int num;
    arquivo = fopen("index.txt", "r+");
    
    //fazendo o index
    num = 0;    
    while((fgetc(arquivo)) != EOF){
        num++;
    }

    fprintf(arquivo, "a");
    fclose(arquivo);

    //procurando tres digitos CPF/CNPJ
    char str[100];
    int cpf;

    arquivo = fopen("os.txt", "r");

    int aux = 0;
    while(fgets(str, sizeof(str), arquivo) && aux == 0){
        if(strstr(str, "Cliente:")){
            fseek(arquivo, 10, SEEK_CUR); // lê 10 posições depois do final da string que contém "Cliente: ", que é onde começa o CPF
            fscanf(arquivo, "%3d", &cpf);
            aux = 1;
        }
    }
    fclose(arquivo);

    //formando o nome do arquivo
    char charnum[10];
    char charcpf[10];
    char nome[20];
    char os[20] = "os";
    char traco[2] = "-\0";
    strcat(os, itoa(num,charnum,10));
    strcat(os, traco);
    strcat(os, itoa(cpf,charcpf,10));
    strcat(os, ".txt");

    //renomeando o arquivo
    rename("os.txt", os);
    printf("O nome da ordem de servico e: %s\n", os);
}

int main(){
    nomeOrdem();

    return 0;
}