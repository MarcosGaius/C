#include <stdio.h>
#include <stdlib.h> //exit
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAX 1600

FILE * arquivo;
char conteudoArquivo[MAX];
char conteudoManutencao[MAX];

//CHECA SE O ARQUIVO ABRIU
void checarArquivo(FILE * arquivo){

    if(arquivo == NULL){
        printf("O arquivo nao foi aberto!\n\n");
        exit(1);
    }
    else{
        printf("O arquivo foi aberto com sucesso!\n\n");
    }
}

int i = 1;

void checarManutencao(FILE *arquivo){
    if(arquivo == NULL){
        printf("Nao existem manutencoes periodicas cadastradas!\n\n");
        i = 0;
    }
    else{
        printf("---------------------------\nManutencoes periodicas:\n---------------------------\n\n");
    }
}

//APRESENTA AS ORDENS DE SERVIcO INSERIDAS
int visualizarArquivo(char title[20]){
    arquivo = fopen(title, "r");

    checarArquivo(arquivo);

    if(i==0){
        return 0;
    }

    printf("\n\n---------------------------\nOrdem de servico:\n---------------------------\n\n");
    while(!feof(arquivo)){
        fgets(conteudoManutencao, sizeof(arquivo), arquivo);
        printf("%s", conteudoManutencao);
    }
    fclose(arquivo);
}

//REMOVE ORDENS DE SERVIcO/MANUTENCAO
void removerArquivo(char title[20]){
    remove(title);
    printf("\nArquivo excluido com sucesso.\n\n");
}

//CRIAR NOME PARA ORDEM DE SERVIcO
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

//FUNcaO PARA CRIAR A ORDEM DE SERVIcO
void criarOrdem(){
    int CPF, telefone, dia, mes, ano, run, aux;
    float preco;
    char prestador[50], cliente[50], descricao[800], status[50], escolha;
    
    escolha = 'S';
    run = 1;
    aux = 0;

    while(escolha == 'S'){
        arquivo = fopen("os.txt", "w");
        
        checarArquivo(arquivo);
        
        printf("Preencha os dados da ordem de servico:\n---------------------------\n");
        
        fflush(stdout);        
        printf("Prestador do servico: ");
        scanf(" %1599[^\n]", prestador);
        fprintf(arquivo, "Prestador do servico: %s\n", prestador);
        printf("\n");
        
        fflush(stdout);
        printf("Cliente: ");
        scanf(" %1599[^\n]", cliente);
        fprintf(arquivo, "Cliente: %s\n", cliente);
        printf("\n");

        fflush(stdout);
        printf("CPF/CPNJ (apenas numeros): "); //por algum motivo não lê o primeiro 0.
        getchar();
        scanf("%d", &CPF);
        fprintf(arquivo, "CPF/CPNJ: %d\n", CPF);
        printf("\n");

        fflush(stdout);
        printf("Telefone (apenas numeros): ");
        scanf("%d", &telefone);
        fprintf(arquivo, "Telefone para contato: %d\n", telefone);
        printf("\n");

        fflush(stdout);
        printf("Descricao: ");
        scanf(" %1599[^\n]", descricao);
        fprintf(arquivo, "Descricao: %s\n", descricao);
        printf("\n");
        
        fflush(stdout);
        printf("Dia (apenas numeros): ");
        scanf("%d", &dia);
        printf("\n");
        fflush(stdout);
        printf("Mes (apenas numeros): ");
        scanf("%d", &mes);
        printf("\n");
        fflush(stdout);
        printf("Ano (apenas numeros): ");
        scanf("%d", &ano);
        fprintf(arquivo, "Data: %d/%d/%d\n", dia, mes, ano);
        printf("\n");

        fflush(stdout);
        printf("Status: ");
        scanf(" %1599[^\n]", status);
        fprintf(arquivo, "Status: %s\n", status);
        printf("\n");

        fflush(stdout);
        printf("Preco total (apenas numeros): ");
        scanf("%f", &preco);
        fprintf(arquivo, "Preco: R$%.2f\n", preco);
        printf("\n");

        fclose(arquivo);
        nomeOrdem();

        escolha = 'S';
        printf("Deseja cadastrar outra ordem de servico? (S/N)\n");
        scanf(" %c", &escolha);
        fflush(stdout);
        printf("\n");

        if('S' == escolha || 'N' == escolha){
            aux = 1;
        }
    
        while(aux != 1){
            printf("Insira uma opcao valida\n");
            scanf(" %c", &escolha);
            if(escolha == 'S' || escolha == 'N'){
                aux = 1;
            }
        }

        if(escolha == 'S'){
            run = 1;
        }
        else if(escolha == 'N'){
            run = 0;
        }
    }
}


//FUNcaO PARA ADICIONAR MANUNTENcÕES PERIoDICAS
void adicionarManutencao(){
    char descricao[800], periodo[100], escolha;
    int dia, mes, ano, aux, run;
    
    run = 1;
    aux = 0;

    while(run == 1){
        arquivo = fopen("manutencao.txt", "a");

        checarArquivo(arquivo);
        
        printf("Insira a descricao da manutencao: ");
        scanf(" %1599[^\n]", descricao);
        fflush(stdout);
        printf("\nInsira o dia: ");
        scanf("%d", &dia);
        fflush(stdout);
        printf("\nInsira o mes: ");
        scanf("%d", &mes);
        fflush(stdout);
        printf("\nInsira o ano: ");
        scanf("%d", &ano);
        fflush(stdout);
        printf("\nInsira a periodicidade: ");
        scanf(" %1599[^\n]", periodo);
        fflush(stdout);

        fprintf(arquivo, "Descricao: %s\nData: %d/%d/%d\nPeriodicidade: %s\n---------------------------\n", descricao, dia, mes, ano, periodo);
        fclose(arquivo);

        printf("\nDeseja adicionar mais uma manutencao periodica? (S/N)\n");
        scanf(" %c", &escolha);
        fflush(stdout);
        printf("\n");

        if('S' == escolha || 'N' == escolha){
            aux = 1;
        }
    
        while(aux != 1){
            printf("Insira uma opcao valida\n");
            scanf(" %c", &escolha);
            if(escolha == 'S' || escolha == 'N'){
                aux = 1;
            }
        }

        if(escolha == 'S'){
            run = 1;
        }
        else if(escolha == 'N'){
            run = 0;
        }
    }
}

//FUNcaO QUE APRESENTA AS MANUTENcÕES PERIoDICAS
int apresentarManutencao(){
    arquivo = fopen("manutencao.txt", "r");

    checarManutencao(arquivo);

    if(i==0){
        return 0;
    }

    while(!feof(arquivo)){
        //fscanf(arquivo, "%*s %1599[^\n]", conteudoManutencao); //lê o máximo de caracteres contando com o \n
        fgets(conteudoManutencao, sizeof(arquivo), arquivo);
        printf("%s", conteudoManutencao);
    }
    fclose(arquivo);
}

int main(){
    printf("\n\n\t\tSistema de ordem de servicos\n\n\n");

    time_t t;
    time(&t);

    printf("Dia e hora atual: %s\n\n", ctime(&t));
    apresentarManutencao();

    printf("\n[Opcoes]:\n\n");
    printf("1- Adicionar manutencao periodica.\n2- Cadastrar ordem de servico.\n3- Remover ordem de servico.\n4- Apresentar ordem de servico.\n5- Encerrar.\n\n");
    
    int opcao;
    opcao = 0;
    
    printf("Insira a opcao desejada.\n");
    scanf("%d", &opcao);

    while(isdigit(opcao) == 0 && opcao > 5 || opcao < 1){
        printf("Insira uma opcao valida\n");
        scanf("%d", &opcao);
    }

    char titulo[20];
    char nome[20];

    switch(opcao){
        case 1:
        adicionarManutencao();
        printf("Execucao finalizada!\n\n");
        break;
    
        case 2:
        criarOrdem();
        printf("Execucao finalizada!\n\n");
        break;

        case 3:
        printf("Insira o nome do arquivo a ser excluido, com a extensao: ");
        scanf("%s", titulo);
        removerArquivo(titulo);
        printf("Execucao finalizada!\n\n");
        break;

        case 4:
        printf("Insira o nome da ordem a ser apresentada, com a extensao: ");
        scanf("%s", nome);
        printf("\n");
        visualizarArquivo(nome);
        printf("\nExecucao finalizada!\n\n");
        break;

        case 5:
        exit(0);
        break;
    }
        
    return 0;
}