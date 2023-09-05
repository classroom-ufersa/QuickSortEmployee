#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

// Definição da estrutura Funcionario que representa os dados de um funcionário
typedef struct
{
    char nome[30];      // Nome do funcionário
    char cargo[30];     // Cargo do funcionário
    int documento;      // Número de documento do funcionário
} Funcionario;

// Função para transformar a primeira letra do nome/cargo em maiúscula e o restante em minúscula
void capitalizeString(char *str);

// Função para preencher os dados de um funcionário
void preencher(Funcionario *funcionario);

// Função de comparação utilizada pelo qsort para ordenar as linhas do arquivo
int compararLinhas(const void *a, const void *b);

// Função para imprimir o conteúdo do arquivo "funcionarios.txt"
void imprimirArquivo();

// Função para criar ou atualizar o arquivo "funcionarios.txt" com os dados dos funcionários
void criarArquivo(Funcionario *funcionarios, int n);

// Função para ordenar as linhas do arquivo "funcionarios.txt" em ordem alfabética
void ordenarLinhasArquivo();

#endif /* FUNCIONARIOS_H */
