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


int compararLinhas(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
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
    // Abre o arquivo em modo leitura para verificar o cabeçalho
    FILE *arquivoVerificacao = fopen("funcionarios.txt", "r");

    // Verifica se o cabeçalho já existe
    int cabecalhoExiste = 0;
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivoVerificacao) != NULL)
    {
        if (strstr(linha, "*Funcionários cadastrados*") != NULL)
        {
            cabecalhoExiste = 1;
            break;
        }
    }

    fclose(arquivoVerificacao);

    // Abre o arquivo em modo anexar para adicionar os dados
    FILE *arquivo = fopen("funcionarios.txt", "a");

    if (arquivo == NULL)
    {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    if (!cabecalhoExiste)
    {
        fprintf(arquivo, "*Funcionários cadastrados*\n");
        fprintf(arquivo, "Nome\t Cargo\t Documento\t\n");
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(arquivo, "%s\t", funcionario[i].nome);
        fprintf(arquivo, "%s\t", funcionario[i].cargo);
        fprintf(arquivo, "%d\t\n", funcionario[i].documento);
    }
    
    fclose(arquivo);

    printf("Dados salvos em 'funcionarios.txt'\n");
}


void ordenarLinhasArquivo() {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    char **linhas = NULL;
    char linha[100];
    int numLinhas = 0;
    int linhaAtual = 0; // Variável de controle para ignorar as duas primeiras linhas

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (linhaAtual >= 2) { // Ignora as duas primeiras linhas
            // Remove o caractere de nova linha
            linha[strcspn(linha, "\n")] = '\0';
            
            // Aloca memória para a linha e copia o conteúdo
            linhas = realloc(linhas, (numLinhas + 1) * sizeof(char *));
            linhas[numLinhas] = strdup(linha);
            numLinhas++;
        }
        linhaAtual++;
    }

    fclose(arquivo);

    // Ordena as linhas usando qsort
    qsort(linhas, numLinhas, sizeof(char *), compararLinhas);

    // Reabre o arquivo em modo de escrita (sobrescrevendo o conteúdo existente)
    arquivo = fopen("funcionarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita");
        exit(1);
    }
    
    fprintf(arquivo, "*Funcionários cadastrados*\n");
    fprintf(arquivo, "Nome\t Cargo\t Documento\t\n");

    // Escreve as linhas ordenadas de volta para o arquivo
    for (int i = 0; i < numLinhas; i++) {
        fprintf(arquivo, "%s\n", linhas[i]);
        free(linhas[i]); // Libera a memória alocada para a linha
    }

    fclose(arquivo);
    free(linhas);
}
