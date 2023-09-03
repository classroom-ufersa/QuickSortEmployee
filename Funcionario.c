#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[30], cargo[30];
    int documento;
} Funcionario;

void preencher(Funcionario *funcionario)
{
    printf("Nome: ");
    scanf(" %[^\n]", funcionario->nome);
    printf("Cargo: ");
    scanf(" %[^\n]", funcionario->cargo);
    printf("Documento: ");
    scanf("%d", &funcionario->documento);
}

int compararFuncionarios(const void *a, const void *b)
{
    const Funcionario *funcionarioA = (const Funcionario *)a;
    const Funcionario *funcionarioB = (const Funcionario *)b;
    return strcmp(funcionarioA->nome, funcionarioB->nome);
}

void imprimirArquivo()
{
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return;
    }

    char linha[100];

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        printf("%s", linha); // Imprime a linha do arquivo
    }

    fclose(arquivo);
}

void criarArquivo(Funcionario *funcionario, int n)
{
    // Abra o arquivo em modo anexar para adicionar os dados
    FILE *arquivo = fopen("funcionarios.txt", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Verifique se o arquivo está vazio
    fseek(arquivo, 0, SEEK_END);
    int arquivoVazio = ftell(arquivo) == 0;
    rewind(arquivo);

    if (arquivoVazio)
    {
        fprintf(arquivo, "*Funcionários cadastrados (ordenados por nome)*\n");
        fprintf(arquivo, "Nome\t Cargo\t Documento\t\n");
    }

    // Ordenar os funcionários antes de escrevê-los no arquivo
    qsort(funcionario, n, sizeof(Funcionario), compararFuncionarios);

    for (int i = 0; i < n; i++)
    {
<<<<<<< HEAD
        fprintf(arquivo, "%s\t", funcionario[i].nome);
        fprintf(arquivo, "%s\t", funcionario[i].cargo);
        fprintf(arquivo, "%d\t\n", funcionario[i].documento);
    }

    fclose(arquivo);
    printf("Dados salvos em 'funcionarios.txt'\n");
=======
        printf("\n\tFuncionario %i\n", i+1);

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
        printf("Funcionario %i\n", i+1);
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
>>>>>>> 016e93cc1bc22b8cd59ba7094eca051666b1ce7c
}
