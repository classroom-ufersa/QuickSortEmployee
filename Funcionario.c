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
        fprintf(arquivo, "%s\t", funcionario[i].nome);
        fprintf(arquivo, "%s\t", funcionario[i].cargo);
        fprintf(arquivo, "%d\t\n", funcionario[i].documento);
    }

    fclose(arquivo);
    printf("Dados salvos em 'funcionarios.txt'\n");
}
