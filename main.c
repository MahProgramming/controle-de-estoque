
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF-8");

    int opcao, quantidade, estoque, cont;
    int disponivel, encontrou, removido, continuar;
    char nome[100], nome2[100], linha[20], entrada[100], resp;
    FILE *arq, *temp;

    continuar = 1;

    while (continuar == 1) {
        printf("\n================================\n");
        printf("       Controle de Estoque\n");
        printf("================================\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Estoque\n");
        printf("4. Sair\n");
        printf("Opção: ");

        fgets(entrada, 100, stdin);

        if (sscanf(entrada, "%d", &opcao) != 1) {
            printf("Opção inválida! Tente novamente.\n");
            continue;
        }

        if (opcao < 1 || opcao > 4) {
            printf("Opção inválida! Tente novamente.\n");
            continue;
        }

        if (opcao == 1) {
            printf("Digite o nome do item: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite a quantidade: ");
            fgets(entrada, 100, stdin);

            if (sscanf(entrada, "%d", &quantidade) != 1 || quantidade <= 0) {
                printf("Quantidade inválida!\n");
            } else {
                arq = fopen("inventory.txt", "a");

                if (arq != NULL) {
                    fprintf(arq, "%s\n%d\n", nome, quantidade);
                    fclose(arq);
                    printf("Item adicionado com sucesso!\n");
                }
            }
        }

        else if (opcao == 2) {
            printf("Digite o nome do item: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Digite a quantidade a ser removida: ");
            fgets(entrada, 100, stdin);

            if (sscanf(entrada, "%d", &quantidade) != 1 || quantidade <= 0) {
                printf("Quantidade inválida!\n");
            } else {
                arq = fopen("inventory.txt", "r");
                temp = fopen("temp.txt", "w");

                encontrou = 0;
                removido = 0;
                disponivel = 0;

                if (arq != NULL && temp != NULL) {
                    while (fgets(nome2, 100, arq) != NULL &&
                           fgets(linha, 20, arq) != NULL) {

                        nome2[strcspn(nome2, "\n")] = '\0';
                        estoque = atoi(linha);

                        if (strcmp(nome, nome2) == 0 && encontrou == 0) {
                            encontrou = 1;
                            disponivel = estoque;

                            if (quantidade > estoque) {
                                fprintf(temp, "%s\n%d\n", nome2, estoque);
                            } else if (quantidade == estoque) {
                                removido = 1;
                            } else {
                                fprintf(temp, "%s\n%d\n", nome2, estoque - quantidade);
                            }
                        } else {
                            fprintf(temp, "%s\n%d\n", nome2, estoque);
                        }
                    }

                    fclose(arq);
                    fclose(temp);

                    if (encontrou == 0) {
                        remove("temp.txt");
                        printf("Item não encontrado.\n");
                    } else if (quantidade > disponivel) {
                        remove("temp.txt");
                        printf("Estoque insuficiente. Quantidade disponível: %d\n", disponivel);
                    } else {
                        remove("inventory.txt");
                        rename("temp.txt", "inventory.txt");

                        if (removido == 1) {
                            printf("Item removido do estoque!\n");
                        } else {
                            printf("Quantidade atualizada com sucesso!\n");
                        }
                    }
                } else {
                    if (arq != NULL) fclose(arq);
                    if (temp != NULL) fclose(temp);
                    printf("Não foi possível acessar o arquivo!\n");
                }
            }
        }

        else if (opcao == 3) {
            arq = fopen("inventory.txt", "r");

            if (arq != NULL) {
                cont = 0;

                printf("=============================\n");
                printf("       Estoque Atual\n");
                printf("=============================\n");

                while (fgets(nome, 100, arq) != NULL &&
                       fgets(linha, 20, arq) != NULL) {

                    nome[strcspn(nome, "\n")] = '\0';

                    printf("\nNome: %s\n", nome);
                    printf("Quantidade: %s", linha);
                    cont++;
                }

                if (cont == 0) {
                    printf("O estoque está vazio.\n");
                }

                fclose(arq);
            } else {
                printf("O estoque está vazio.\n");
            }
        }

        else if (opcao == 4) {
            printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
            break;
        }

        printf("\nDeseja realizar outra operação? (s/n): ");
        scanf(" %c", &resp);
        getchar();

        if (resp != 's' && resp != 'S') {
            continuar = 0;
            printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
        }
    }

    return 0;
}
