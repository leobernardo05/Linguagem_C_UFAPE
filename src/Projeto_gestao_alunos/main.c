#include <stdio.h>

#include "aluno.h"


/*
 * Limpa os caracteres restantes no buffer de entrada.
 */
void limparBuffer(void)
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        /* Apenas descarta os caracteres. */
    }
}


/*
 * Le uma string com espacos.
 */
void lerString(char *texto, int tamanho)
{
    fgets(texto, tamanho, stdin);

    /*
     * Remove o '\n' colocado pelo fgets.
     */
    texto[strcspn(texto, "\n")] = '\0';
}


/*
 * Exibe o menu principal.
 */
void menu(void)
{
    printf("\n");
    printf("=========================================\n");
    printf("        SISTEMA DE GESTAO DE ALUNOS\n");
    printf("=========================================\n");
    printf("1  - Inserir aluno\n");
    printf("2  - Listar alunos aprovados\n");
    printf("3  - Listar alunos reprovados\n");
    printf("4  - Listar todos os alunos\n");
    printf("6  - Remover aluno\n");
    printf("7  - Procurar aluno\n");
    printf("8  - Mostrar quantidade de alunos\n");
    printf("-1 - Sair\n");
    printf("=========================================\n");
    printf("Escolha uma opcao: ");
}


/*
 * Funcao principal.
 */
int main(void)
{
    int opcao;
    int matricula;
    int posicao;
    int i;

    Aluno novoAluno;

    /*
     * Inicializa o sistema.
     */
    inicializarSistema();

    do
    {
        menu();

        if (scanf("%d", &opcao) != 1)
        {
            printf("\nErro: opcao invalida.\n");
            limparBuffer();
            continue;
        }

        limparBuffer();

        switch (opcao)
        {
            /*
             * =====================================
             * INSERIR
             * =====================================
             */
            case 1:

                printf("\n========== INSERIR ALUNO ==========\n");

                /*
                 * Matricula.
                 */
                printf("Digite a matricula: ");
                scanf("%d", &novoAluno.matricula);
                limparBuffer();

                /*
                 * Verifica se a matricula ja existe.
                 */
                if (procurarAluno(novoAluno.matricula) != -1)
                {
                    printf("\nErro: essa matricula ja esta cadastrada.\n");
                    break;
                }

                /*
                 * Nome.
                 */
                printf("Digite o nome: ");
                lerString(novoAluno.nome, TAM_NOME);

                /*
                 * Codigo da turma.
                 */
                printf("Digite o codigo da turma: ");
                scanf("%d", &novoAluno.codTurma);
                limparBuffer();

                /*
                 * Notas.
                 */
                printf("\nDigite as notas das 7 disciplinas:\n");

                for (i = 0; i < NUM_DISCIPLINAS; i++)
                {
                    do
                    {
                        printf(
                            "Nota da disciplina %d: ",
                            i + 1
                        );

                        scanf("%f", &novoAluno.notas[i]);

                        if (
                            novoAluno.notas[i] < 0 ||
                            novoAluno.notas[i] > 10
                        )
                        {
                            printf(
                                "Erro: a nota deve estar entre 0 e 10.\n"
                            );
                        }

                    } while (
                        novoAluno.notas[i] < 0 ||
                        novoAluno.notas[i] > 10
                    );

                    limparBuffer();
                }

                /*
                 * Faltas.
                 */
                printf("\nDigite as faltas das 7 disciplinas:\n");

                for (i = 0; i < NUM_DISCIPLINAS; i++)
                {
                    do
                    {
                        printf(
                            "Faltas da disciplina %d: ",
                            i + 1
                        );

                        scanf("%d", &novoAluno.faltas[i]);

                        if (novoAluno.faltas[i] < 0)
                        {
                            printf(
                                "Erro: a quantidade de faltas nao pode ser negativa.\n"
                            );
                        }

                    } while (novoAluno.faltas[i] < 0);

                    limparBuffer();
                }

                /*
                 * Insere o aluno.
                 */
                if (inserirAluno(novoAluno))
                {
                    printf("\nAluno inserido com sucesso!\n");
                }

                break;


            /*
             * =====================================
             * LISTAR APROVADOS
             * =====================================
             */
            case 2:

                listarAprovados();

                break;


            /*
             * =====================================
             * LISTAR REPROVADOS
             * =====================================
             */
            case 3:

                listarReprovados();

                break;


            /*
             * =====================================
             * LISTAR TODOS
             * =====================================
             */
            case 4:

                listarAlunos();

                break;


            /*
             * =====================================
             * REMOVER
             * =====================================
             */
            case 6:

                if (tamanho() == 0)
                {
                    printf("\nErro: nao existem alunos cadastrados.\n");
                    break;
                }

                printf("\n========== REMOVER ALUNO ==========\n");

                printf("Digite a matricula do aluno: ");
                scanf("%d", &matricula);
                limparBuffer();

                removerAluno(matricula);

                break;


            /*
             * =====================================
             * PROCURAR
             * =====================================
             */
            case 7:

                if (tamanho() == 0)
                {
                    printf("\nNenhum aluno cadastrado.\n");
                    break;
                }

                printf("\n========== PROCURAR ALUNO ==========\n");

                printf("Digite a matricula: ");
                scanf("%d", &matricula);
                limparBuffer();

                posicao = procurarAluno(matricula);

                if (posicao == -1)
                {
                    printf("\nAluno nao encontrado.\n");
                }
                else
                {
                    printf("\nAluno encontrado!\n");
                    printf("Posicao no vetor: %d\n", posicao);
                    printf("Matricula: %d\n",
                           alunos[posicao].matricula);
                    printf("Nome: %s\n",
                           alunos[posicao].nome);
                    printf("Turma: %d\n",
                           alunos[posicao].codTurma);
                }

                break;


            /*
             * =====================================
             * TAMANHO
             * =====================================
             */
            case 8:

                printf(
                    "\nQuantidade de alunos cadastrados: %d\n",
                    tamanho()
                );

                break;


            /*
             * =====================================
             * SAIR
             * =====================================
             */
            case -1:

                printf("\nEncerrando o sistema...\n");

                break;


            /*
             * =====================================
             * OPCAO INVALIDA
             * =====================================
             */
            default:

                printf("\nErro: opcao invalida.\n");

                break;
        }

    } while (opcao != -1);


    /*
     * Libera a memoria antes de encerrar.
     */
    liberarSistema();

    return 0;
}