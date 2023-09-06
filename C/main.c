#include "funcionario.h"

int testeFormato(char *valor) {
    int i;
    for (i = 0; valor[i] != '\0'; i++) {
        if (!(valor[i] >= '0' && valor[i] <= '9')) {
            return 1;   // a entrada possui outros caracteres além de números
        }
    }
    return 0;   // a entrada só possui números
}

int testeInput(char *op) {
    scanf(" %2[^\n]", op); // recebe o input

    if (strlen(op) > 1) {
        printf("\nDigite apenas um caracter\n");
        return 0;
    }
    else {
        if (testeFormato(op) == 1) {
            return 0;
        }
    }

    return atoi(op);
}



int main(void)
{
    Funcionario *funcionario = NULL;
    int n = 0;
    char opcao[3];
    int entrada;
    int valorValido = 0;
    do
    {
        clock_t inicio = clock();
        // Executar o algoritmo
        ordenarLinhasArquivo();
        double tempo = (double)(clock() - inicio) / CLOCKS_PER_SEC;
        tempo = tempo * 1000; // milisegundos
        printf("Tempo de execucao: %.10f\n", tempo);
        printf("\nMenu:\n");
        printf("1 - Cadastrar funcionario\n");
        printf("2 - Ver funcionarios\n");
        printf("3 - Encerrar programa\n");
        printf("Escolha uma opcao: ");
        while (!valorValido)
        {
            entrada = testeInput(opcao);
            if (entrada != 0)
            {
                // A leitura foi bem-sucedida, o valor é um número inteiro
                if (entrada >= 1 && entrada <= 3)
                {
                    // Verifica se o número é menor ou igual a 3
                    valorValido = 1;
                }
                else
                {
                    printf("Digite uma das opcoes do menu (1 ou 2).\n");
                }
            }
            else
            {
                // A leitura não foi bem-sucedida, o valor não é um número inteiro
                printf("Digite uma das opcoes do menu (1 ou 2).\n");
                while (getchar() != '\n')
                    ;
            }
        }
        valorValido = 0;

        switch (entrada)
        {
        case 1:
            while (entrada != 2)
            {
                funcionario = (Funcionario *)realloc(funcionario, (n + 1) * sizeof(Funcionario));

                if (funcionario == NULL)
                {
                    printf("Memoria insuficiente!\n");
                    exit(1);
                }

                preencher(&funcionario[n]); // Passa o endereço do funcionário atual
                n++;

                printf("Registrar novo funcionario?\n1 = Sim\t2 = Nao: ");
                while (!valorValido)
                {
                    entrada = testeInput(opcao);
                    if (entrada != 0)
                    {
                        // A leitura foi bem-sucedida, o valor é um número inteiro
                        if (entrada == 1 || entrada == 2)
                        {
                            valorValido = 1; // Se o usuário escolher 1, o loop continua
                        }
                        else
                        {
                            printf("Digite uma das opcoes do menu (1 ou 2).\n");
                        }
                    }
                    else
                    {
                        // A leitura não foi bem-sucedida, o valor não é um número inteiro
                        printf("Digite uma das opcoes do menu (1 ou 2).\n");
                        while (getchar() != '\n')
                            ;
                    }
                }
                valorValido = 0;
            }
            criarArquivo(funcionario, n);
            free(funcionario);
            funcionario = NULL;
            n = 0;
            break;
        case 2:
            imprimirArquivo();
            break;

        case 3:
            printf("Encerrando o programa...\n");
            break;
        }
    } while (entrada != 3);

    free(funcionario);

    return 0;
}
