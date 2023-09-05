#include "funcionario.h"

void capitalizeString(char *str)
{
    if (str[0] != '\0')
    {
        str[0] = toupper(str[0]);
        for (int i = 1; str[i] != '\0'; i++)
        {
            str[i] = tolower(str[i]);
        }
    }
}

void preencher(Funcionario *funcionario)
{
    printf("Nome: ");
    scanf(" %[^\n]", funcionario->nome);
    capitalizeString(funcionario->nome); // Formata o nome
    printf("Cargo: ");
    scanf(" %[^\n]", funcionario->cargo);
    capitalizeString(funcionario->cargo); // Formata o cargo
    printf("Documento: ");
    int valorValido = 0;

    while (!valorValido)
    {
        if (scanf("%d", &funcionario->documento) == 1)
        {
            valorValido = 1;
        }
        else
        {
            printf("Documento invalido. Digite um numero inteiro valido para o documento.\n");
            while (getchar() != '\n')
                ;
        }
    }
}

int compararLinhas(const void *a, const void *b)
{
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
        if (strstr(linha, "Funcionarios cadastrados") != NULL)
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
        fprintf(arquivo, "Funcionarios cadastrados\n");
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

void ordenarLinhasArquivo()
{
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo");
        exit(1);
    }

    char **linhas = NULL;
    char linha[100];
    int numLinhas = 0;
    int linhaAtual = 0; // Variável de controle para ignorar as duas primeiras linhas

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (linhaAtual >= 2)
        { // Ignora as duas primeiras linhas
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
    clock_t inicio = clock();
    // Executar o algoritmo
    qsort(linhas, numLinhas, sizeof(char *), compararLinhas);
    double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
    tempo = tempo * 1000; // milisegundos
    // Reabre o arquivo em modo de escrita (sobrescrevendo o conteúdo existente)
    arquivo = fopen("funcionarios.txt", "w");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita");
        exit(1);
    }

    fprintf(arquivo, "Funcionarios cadastrados\n");
    fprintf(arquivo, "Nome\t Cargo\t Documento\t\n");

    // Escreve as linhas ordenadas de volta para o arquivo
    for (int i = 0; i < numLinhas; i++)
    {
        fprintf(arquivo, "%s\n", linhas[i]);
        free(linhas[i]); // Libera a memória alocada para a linha
    }

    fclose(arquivo);
    free(linhas);
}
