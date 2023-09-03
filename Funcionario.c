#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[30], cargo[30];
    int documento;
} Funcionario;

void preencher(Funcionario *funcionario, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n\tFuncionario %i\n", i ++);

        printf("Nome: ");
        scanf(" %[^\n]", funcionario[i].nome);
        printf("Cargo: ");
        scanf(" %[^\n]", funcionario[i].cargo);
        printf("Documento: ");
        scanf("%d", &funcionario[i].documento);
    }
}

void imprimir(Funcionario *funcionario, int n)
{
    printf("\n**Funcionarios cadastrados**\n");
    for (int i = 0; i < n; i++)
    {
        printf("Funcionario %i\n", i + 1);
        printf("Nome: %s\n", funcionario[i].nome);
        printf("Cargo: %s\n", funcionario[i].cargo);
        printf("Documento: %d\n", funcionario[i].documento);
    }
}

int main(void)
{
    Funcionario *funcionario = NULL;
    int n = 0, opcao;

    while (opcao != 2)
    {
        funcionario = (Funcionario *)realloc(funcionario, (n + 1) * sizeof(Funcionario));

        if (funcionario == NULL)
        {
            printf("Memoria insuficiente!\n");
            exit(1);
        }

        printf("Registrar novo funcionario?\n1 = Sim\t2 = Nao: ");
        scanf("%d", &opcao);
        n++;
        preencher(funcionario, n);
    }
        imprimir(funcionario, n);

    free(funcionario);

    return 0;
}
