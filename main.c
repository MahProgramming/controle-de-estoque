#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF-8");

    int opcao, quantidade, estoque, novo, cont;
    char nome[100], nome2[100], linha[20], resp;
    FILE *arq, *temp;

    do {
        printf("\n===== CONTROLE DE ESTOQUE =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar estoque\n");
        printf("4 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            printf("Nome do produto: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Quantidade: ");
            scanf("%d", &quantidade);
            getchar();

            if (quantidade > 0) {
                arq = fopen("inventory.txt", "a");

                if (arq != NULL) {
                    fprintf(arq, "%s\n%d\n", nome, quantidade);
                    fclose(arq);
                    printf("Item adicionado com sucesso!\n");
                }
            } else {
                printf("Quantidade inválida!\n");
            }
        }

        else if (opcao == 2) {
            printf("Nome do produto: ");
            fgets(nome, 100, stdin);
            nome[strcspn(nome, "\n")] = '\0';

            printf("Quantidade a remover: ");
            scanf("%d", &quantidade);
            getchar();

            arq = fopen("inventory.txt", "r");
            temp = fopen("temp.txt", "w");

            cont = 0;
            novo = 0;

            if (arq != NULL && temp != NULL && quantidade > 0) {
                while (fgets(nome2, 100, arq) != NULL &&
                       fgets(linha, 20, arq) != NULL) {

                    nome2[strcspn(nome2, "\n")] = '\0';
                    estoque = atoi(linha);

                    if (strcmp(nome, nome2) == 0 && cont == 0) {
                        cont = 1;

                        if (quantidade > estoque) {
                            novo = 1;
                            fprintf(temp, "%s\n%d\n", nome2, estoque);
                        } else if (quantidade < estoque) {
                            fprintf(temp, "%s\n%d\n", nome2, estoque - quantidade);
                        }
                    } else {
                        fprintf(temp, "%s\n%d\n", nome2, estoque);
                    }
                }

                fclose(arq);
                fclose(temp);

                if (cont == 0) {
                    remove("temp.txt");
                    printf("Item não encontrado.\n");
                } else if (novo == 1) {
                    remove("temp.txt");
                    printf("Estoque insuficiente. Quantidade disponível: %d\n", estoque);
                } else {
                    remove("inventory.txt");
                    rename("temp.txt", "inventory.txt");

                    if (estoque == quantidade) {
                        printf("Item removido do estoque!\n");
                    } else {
                        printf("Quantidade atualizada com sucesso!\n");
                    }
                }
            } else {
                if (arq != NULL) fclose(arq);
                if (temp != NULL) fclose(temp);
                printf("Não foi possível acessar o arquivo ou quantidade inválida!\n");
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
        }

        else {
            printf("Opção inválida! Tente novamente.\n");
        }

        if (opcao >= 1 && opcao <= 3) {
            printf("\nDeseja realizar outra operação? (s/n): ");
            scanf(" %c", &resp);
        }

    } while (opcao != 4 && (resp == 's' || resp == 'S'));

    if (opcao != 4) {
        printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
    }

    return 0;
}