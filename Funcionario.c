#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
    char nome[30], cargo[30];
    int documento;
    
}Funcionario;
void preencher(Funcionario **funcionario, int n){
    for (int i = 0; i < n; i++){

      printf("\n\tFuncionarios %i\n", i+1);

      printf("Nome: ");
      scanf(" %[^\n]", funcionario[i]->nome);
      printf("Cargo: ");
      scanf(" %[^\n]", funcionario[i]->cargo);
      printf("Documento: ");
      scanf("%i", &funcionario[i]->documento);
    }
}
void imprimir(Funcionario **funcionario, int n){
        printf("\n**Funcionario cadastratos**\n");
    for (int i = 0; i < n; i++){
      printf("Funcionario %i\n", i+1);
      printf("Nome: %s\n", funcionario[i]->nome);
      printf("Cargo: %s\n", funcionario[i]->cargo);
      printf("Documento: %i\n", funcionario[i]->documento);   
    }
}
int main(void){
  int n;
      printf("Digite a quantidade de funcionarios: \n");
      scanf("%i", &n);
  Funcionario **funcionario = (Funcionario**) malloc(n * sizeof(Funcionario*));
     if(funcionario == NULL){
        printf("Memoria insuficiente!");
        exit(1);
     }
     for(int i = 0; i < n; i++){
        funcionario[i] = (Funcionario*) malloc(n * sizeof(Funcionario));
     }
     preencher(funcionario, n);
     imprimir(funcionario, n);
     for(int i = 0; i < n; i++){
        free(funcionario[i]);
     }
     free(funcionario);
     return 0;
}
