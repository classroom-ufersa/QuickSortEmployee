#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionario.c"


int main(void)
{
    Funcionario *funcionario = NULL;
    int n = 0, opcao;
    do
    {
        printf("\nMenu:\n");
        printf("1 - Cadastrar funcionario\n");
        printf("2 - Ver funcionarios\n");
        printf("3 - Encerrar programa\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            while (1)
            {
                funcionario = (Funcionario *)realloc(funcionario, (n+1) * sizeof(Funcionario));

                if (funcionario == NULL)
                {
                    printf("Memoria insuficiente!\n");
                    exit(1);
                }

                preencher(&funcionario[n]); // Passa o endereço do funcionário atual
                n++;

                printf("Registrar novo funcionario?\n1 = Sim\t2 = Nao: ");
                scanf("%d", &opcao);

                if (opcao == 2)
                {
                    break;
                }
            }
            criarArquivo(funcionario,n);
            free(funcionario);
            funcionario = NULL;
            n=0;
            ordenarLinhasArquivo();
        break;
        case 2:
            imprimirArquivo();
            break;

        case 3:
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("\nOpcao invalida. Tente novamente.\n");
            break;
        }

    } while (opcao != 3);


    free(funcionario);

    return 0;
}
