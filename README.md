# Documentação do Programa de Ordenação de Strings com Quick Sort

Este documento descreve um programa de gerenciamento de funcionários escrito em linguagem C. O programa permite que os usuários cadastrem funcionários e visualizem a lista de funcionários cadastrados.

Além disso, foi desenvolvido um programa em JavaScript que permite aos usuários enviar uma planilha ou criar uma do zero. Após o envio e/ou cadastro de novos usuários, a lista é reordenada em ordem alfabética usando a função QuickSort, que será explicada ao longo desta documentação.

link para acessar o programa: http://pedrohraulino.github.io/

## Arquivos Fonte

### main.c

O arquivo `main.c` é o arquivo principal do programa e contém a função `main()`. Ele é responsável por gerenciar o menu principal e as operações do programa.

### funcionario.c

O arquivo `funcionario.c` contém várias funções relacionadas a funcionários, incluindo preenchimento de dados, ordenação de funcionários e manipulação de arquivos.

#### Funções em `funcionario.c`

1. **`capitalizeString(char *str)`**: Transforma a primeira letra de uma string em maiúscula e o restante em minúscula.

2. **`preencher(Funcionario *funcionario)`**: Preenche os dados de um funcionário, incluindo nome, cargo e documento.

3. **`compararLinhas(const void *a, const void *b)`**: Função de comparação usada para ordenar as linhas do arquivo.

4. **`imprimirArquivo()`**: Lê e imprime o conteúdo do arquivo "funcionarios.txt".

5. **`criarArquivo(Funcionario *funcionario, int n)`**: Cria ou atualiza o arquivo "funcionarios.txt" com os dados dos funcionários.

6. **`ordenarLinhasArquivo()`**: Ordena as linhas do arquivo "funcionarios.txt" em ordem alfabética.

### funcionario.h

O arquivo `funcionario.h` contém as definições de estrutura e protótipos de função utilizados em `funcionario.c`.

#### Estruturas e Protótipos de Função em `funcionario.h`

1. **`Funcionario`**: Estrutura que representa os dados de um funcionário.

2. **`capitalizeString(char *str)`**: Protótipo da função para transformar a primeira letra de uma string em maiúscula e o restante em minúscula.

3. **`preencher(Funcionario *funcionario)`**: Protótipo da função para preencher os dados de um funcionário.

4. **`compararLinhas(const void *a, const void *b)`**: Protótipo da função de comparação usada para ordenar as linhas do arquivo.

5. **`imprimirArquivo()`**: Protótipo da função para imprimir o conteúdo do arquivo "funcionarios.txt".

6. **`criarArquivo(Funcionario *funcionario, int n)`**: Protótipo da função para criar ou atualizar o arquivo "funcionarios.txt" com os dados dos funcionários.

7. **`ordenarLinhasArquivo()`**: Protótipo da função para ordenar as linhas do arquivo "funcionarios.txt" em ordem alfabética.

## Uso do Programa

Para utilizar o programa, siga as seguintes etapas:

1. Compile o programa executando o arquivo `main.c` junto com os arquivos `funcionario.c` e `funcionario.h`.

2. Execute o programa compilado.

3. O programa exibirá um menu com as seguintes opções:
   - "Cadastrar funcionario": Permite ao usuário cadastrar um novo funcionário.
   - "Ver funcionarios": Mostra a lista de funcionários cadastrados em ordem alfabética.
   - "Encerrar programa": Encerra o programa.

4. Siga as instruções do programa para realizar as operações desejadas.

5. Os dados dos funcionários serão armazenados em um arquivo chamado "funcionarios.txt".

# Função QuickSort
O Quicksort é um algoritmo de ordenação eficiente que divide a lista em subgrupos, rearranja esses grupos em relação a um pivô e depois os combina para obter a lista ordenada. Ele é rápido na maioria dos casos, com complexidade média de O(nlogn), mas pode ser lento no pior caso  O(n 2 )) se o pivô for escolhido inadequadamente.

## Como funciona
A Quicksort é um algoritmo de ordenação que funciona seguindo três passos simples:

**Escolha do Pivô**: Primeiro, escolha um elemento da lista, chamado de "pivô". A escolha do pivô é fundamental para o desempenho do algoritmo.

**Divisão**: Em seguida, reorganize a lista de forma que todos os elementos menores que o pivô fiquem à esquerda, e todos os elementos maiores fiquem à direita. Isso significa que o pivô estará em sua posição final na lista.

**Recursão**: Agora, aplique o mesmo processo de ordenação às sublistas à esquerda e à direita do pivô. Isso é feito de forma recursiva até que todas as sublistas tenham apenas um elemento, que já está ordenado.

O processo de escolher um pivô, dividir a lista e ordenar as sublistas continua até que a lista completa esteja ordenada.

A grande sacada do Quicksort é a escolha inteligente do pivô, que pode tornar o algoritmo muito eficiente na prática. O algoritmo explora a ideia de "dividir para conquistar", que é uma estratégia poderosa para resolver problemas complexos, como a ordenação de uma lista.

![image](https://github.com/pedrohraulino/Projeto3/assets/116983278/4e8a34f3-5f37-45fd-b033-1567c0639b78)
(reprodução https://www.enjoyalgorithms.com/blog/quick-sort-algorithm)

## Estrutura da Função e Complexidade de Tempo

```c
void quicksort(int arr[], int left, int right) { 
    if (left < right) {
        int pivot = partition(arr, left, right);
        quicksort(arr, left, pivot - 1);
        quicksort(arr, pivot + 1, right);
    }
}

int partition(int arr[], int left, int right) {
    int pivot = arr[right]; 
    int i = (left - 1); 

    for (int j = left; j <= right - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]); 
        }
    }

    swap(&arr[i + 1], &arr[right]);
    return (i + 1); 
}

void swap(int* a, int* b) {
    int t = *a; 
    *a = *b; 
    *b = t; 
}
```

**Melhor Caso:** O melhor caso ocorre quando o Quicksort divide a lista de entrada em partes iguais em cada chamada recursiva. Isso leva a um desempenho mais rápido, e a complexidade de tempo é \(O(n \log n)\).

**Caso Médio:** No cenário mais realista, o Quicksort divide a lista de entrada de forma desigual em algumas chamadas recursivas, mas a média de todas as chamadas ainda resulta em \(O(n \log n)\).

**Pior Caso:** O pior caso ocorre quando o Quicksort sempre escolhe o pivô de forma que apenas um elemento seja colocado em uma sublista e os outros (n-1) elementos em outra. Isso leva a (n) chamadas recursivas, cada uma lidando com um único elemento, resultando em um desempenho significativamente mais lento. A complexidade de tempo no pior caso é \(O(n^2)\).
Em resumo, o Quicksort geralmente tem um desempenho rápido, com complexidade \(O(n \log n)\) na maioria dos casos. No entanto, é importante estar ciente do pior caso, que pode ser evitado com estratégias adequadas de escolha do pivô e otimização do algoritmo.


## Vantagens:

**Eficiência na Maioria dos Casos:** O Quicksort é notavelmente eficiente na maioria dos cenários, especialmente em listas grandes. Sua complexidade média é \(O(n \log n)\), tornando-o mais rápido do que muitos outros algoritmos de ordenação.

**In-Place:** O Quicksort é um algoritmo "in-place", o que significa que ordena a lista diretamente sem requerer memória adicional para armazenar cópias temporárias dos elementos. Isso economiza espaço de memória.

**Flexibilidade na Escolha do Pivô:** O Quicksort permite a escolha flexível do pivô, o que pode ser otimizado para cenários específicos. Existem variações que escolhem o pivô de maneira inteligente, reduzindo o risco do pior caso.


## Desvantagens:

**Pior Caso Ineficiente:** O Quicksort pode ser muito ineficiente no pior caso, quando o pivô é escolhido inadequadamente e resulta em muitas partições desbalanceadas. Nesse caso, a complexidade é \(O(n^2)\), tornando-o mais lento do que algoritmos como o Merge Sort.

**Não é Estável:** O Quicksort não é um algoritmo de ordenação estável, o que significa que a ordem relativa dos elementos iguais não é preservada após a ordenação. Isso pode ser um problema em algumas aplicações.

**Complexidade de Implementação:** A implementação do Quicksort pode ser complexa em comparação com outros algoritmos mais simples, como o Bubble Sort ou o Insertion Sort.


Em resumo, o Quicksort é um algoritmo de ordenação eficiente, mas sua eficácia depende da escolha do pivô e da natureza dos dados. Ele é geralmente preferido para ordenar listas grandes, onde seu desempenho médio é uma vantagem significativa. No entanto, é importante estar ciente do pior caso e tomar medidas para evitá-lo quando necessário.

## Considerações Finais

Este programa oferece funcionalidades básicas de gerenciamento de funcionários, incluindo cadastro, visualização e armazenamento em arquivo. Ele pode ser estendido e aprimorado para atender a requisitos adicionais, como edição e exclusão de funcionários, além de melhorias na interface do usuário.

