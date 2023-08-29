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
