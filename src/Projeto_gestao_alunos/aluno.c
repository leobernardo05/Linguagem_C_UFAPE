#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"

/*
 * Variáveis globais.
 */
Aluno *alunos = NULL;
int qtdAlunos = 0;
int capacidade = 0;


/*
 * Inicializa o sistema.
 *
 * Aloca inicialmente espaço para 10 alunos.
 */
void inicializarSistema(void)
{
    capacidade = CAPACIDADE_INICIAL;
    qtdAlunos = 0;

    alunos = (Aluno *) malloc(capacidade * sizeof(Aluno));

    if (alunos == NULL)
    {
        printf("Erro: nao foi possivel alocar memoria.\n");
        exit(EXIT_FAILURE);
    }

    /*
     * Tenta carregar os alunos que estavam salvos
     * anteriormente no arquivo.
     */
    carregarArquivo();
}


/*
 * Libera a memoria utilizada pelo vetor.
 */
void liberarSistema(void)
{
    free(alunos);

    alunos = NULL;
    qtdAlunos = 0;
    capacidade = 0;
}


/*
 * Procura um aluno pela matricula.
 *
 * Retorna:
 * - posicao do aluno caso encontrado;
 * -1 caso nao encontrado.
 */
int procurarAluno(int matricula)
{
    int i;

    /*
     * Antes da procura, os dados do arquivo sao
     * considerados como fonte dos dados persistidos.
     */
    for (i = 0; i < qtdAlunos; i++)
    {
        if (alunos[i].matricula == matricula)
        {
            return i;
        }
    }

    return -1;
}


/*
 * Retorna a quantidade de alunos cadastrados.
 */
int tamanho(void)
{
    return qtdAlunos;
}


/*
 * Aumenta a capacidade do vetor em 10 posicoes.
 */
static int aumentarCapacidade(void)
{
    Aluno *novoVetor;

    novoVetor = (Aluno *) realloc(
        alunos,
        (capacidade + INCREMENTO) * sizeof(Aluno)
    );

    if (novoVetor == NULL)
    {
        printf("Erro: nao foi possivel aumentar a memoria.\n");
        return 0;
    }

    alunos = novoVetor;
    capacidade += INCREMENTO;

    return 1;
}


/*
 * Insere um novo aluno no final do vetor.
 *
 * Retorna:
 * 1 -> insercao realizada com sucesso;
 * 0 -> erro na insercao.
 */
int inserirAluno(Aluno novoAluno)
{
    /*
     * Verifica se a matricula ja esta cadastrada.
     */
    if (procurarAluno(novoAluno.matricula) != -1)
    {
        printf("\nErro: ja existe um aluno com essa matricula.\n");
        return 0;
    }

    /*
     * Se o vetor estiver cheio, aumenta sua capacidade
     * em mais 10 elementos.
     */
    if (qtdAlunos >= capacidade)
    {
        if (!aumentarCapacidade())
        {
            return 0;
        }

        printf("\nCapacidade aumentada em %d alunos.\n", INCREMENTO);
    }

    /*
     * Insere o aluno no final do vetor.
     */
    alunos[qtdAlunos] = novoAluno;

    qtdAlunos++;

    /*
     * Atualiza o arquivo.
     */
    if (!salvarArquivo())
    {
        printf("Aviso: aluno inserido na memoria, mas houve erro ao salvar o arquivo.\n");
    }

    return 1;
}


/*
 * Remove um aluno pela matricula.
 *
 * Os elementos que estavam depois do aluno removido
 * sao deslocados uma posicao para a esquerda.
 *
 * Retorna:
 * 1 -> removido;
 * 0 -> nao encontrado ou erro.
 */
int removerAluno(int matricula)
{
    int posicao;
    int i;

    posicao = procurarAluno(matricula);

    if (posicao == -1)
    {
        printf("\nErro: aluno nao encontrado.\n");
        return 0;
    }

    /*
     * Desloca todos os elementos posteriores uma
     * posicao para a esquerda.
     */
    for (i = posicao; i < qtdAlunos - 1; i++)
    {
        alunos[i] = alunos[i + 1];
    }

    qtdAlunos--;

    /*
     * Atualiza o arquivo.
     */
    if (!salvarArquivo())
    {
        printf("Aviso: aluno removido da memoria, mas houve erro ao atualizar o arquivo.\n");
    }

    printf("\nAluno removido com sucesso.\n");

    return 1;
}


/*
 * Salva todos os alunos no arquivo texto.
 *
 * Cada aluno ocupa uma linha.
 *
 * Formato:
 *
 * matricula|nome|turma|nota1|nota2|...|nota7|
 * falta1|falta2|...|falta7
 */
int salvarArquivo(void)
{
    FILE *arquivo;
    int i;
    int j;

    arquivo = fopen(ARQUIVO, "w");

    if (arquivo == NULL)
    {
        printf("Erro: nao foi possivel abrir o arquivo para escrita.\n");
        return 0;
    }

    for (i = 0; i < qtdAlunos; i++)
    {
        fprintf(
            arquivo,
            "%d|%s|%d",
            alunos[i].matricula,
            alunos[i].nome,
            alunos[i].codTurma
        );

        /*
         * Salva as 7 notas.
         */
        for (j = 0; j < NUM_DISCIPLINAS; j++)
        {
            fprintf(arquivo, "|%.2f", alunos[i].notas[j]);
        }

        /*
         * Salva as 7 quantidades de faltas.
         */
        for (j = 0; j < NUM_DISCIPLINAS; j++)
        {
            fprintf(arquivo, "|%d", alunos[i].faltas[j]);
        }

        fprintf(arquivo, "\n");
    }

    fclose(arquivo);

    return 1;
}


/*
 * Carrega os alunos do arquivo para a memoria.
 */
int carregarArquivo(void)
{
    FILE *arquivo;
    Aluno alunoLido;
    int resultado;
    int i;

    arquivo = fopen(ARQUIVO, "r");

    /*
     * Se o arquivo ainda nao existe, nao e um erro.
     * Ele sera criado quando o primeiro aluno for inserido.
     */
    if (arquivo == NULL)
    {
        return 1;
    }

    while (1)
    {
        resultado = fscanf(
            arquivo,
            "%d|%49[^|]|%d",
            &alunoLido.matricula,
            alunoLido.nome,
            &alunoLido.codTurma
        );

        if (resultado != 3)
        {
            break;
        }

        /*
         * Le as 7 notas.
         */
        for (i = 0; i < NUM_DISCIPLINAS; i++)
        {
            if (fscanf(
                arquivo,
                "|%f",
                &alunoLido.notas[i]
            ) != 1)
            {
                fclose(arquivo);
                return 0;
            }
        }

        /*
         * Le as 7 faltas.
         */
        for (i = 0; i < NUM_DISCIPLINAS; i++)
        {
            if (fscanf(
                arquivo,
                "|%d",
                &alunoLido.faltas[i]
            ) != 1)
            {
                fclose(arquivo);
                return 0;
            }
        }

        /*
         * Se nao houver memoria suficiente,
         * aumenta a capacidade.
         */
        if (qtdAlunos >= capacidade)
        {
            if (!aumentarCapacidade())
            {
                fclose(arquivo);
                return 0;
            }
        }

        alunos[qtdAlunos] = alunoLido;
        qtdAlunos++;
    }

    fclose(arquivo);

    return 1;
}


/*
 * Calcula a media das 7 disciplinas de um aluno.
 */
static float calcularMedia(Aluno aluno)
{
    float soma = 0.0f;
    int i;

    for (i = 0; i < NUM_DISCIPLINAS; i++)
    {
        soma += aluno.notas[i];
    }

    return soma / NUM_DISCIPLINAS;
}


/*
 * Lista todos os alunos cadastrados.
 */
void listarAlunos(void)
{
    int i;
    int j;

    if (qtdAlunos == 0)
    {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }

    printf("\n========== ALUNOS CADASTRADOS ==========\n");

    for (i = 0; i < qtdAlunos; i++)
    {
        printf("\nAluno %d\n", i + 1);
        printf("Matricula: %d\n", alunos[i].matricula);
        printf("Nome: %s\n", alunos[i].nome);
        printf("Codigo da turma: %d\n", alunos[i].codTurma);

        printf("Notas: ");

        for (j = 0; j < NUM_DISCIPLINAS; j++)
        {
            printf("%.2f ", alunos[i].notas[j]);
        }

        printf("\nFaltas: ");

        for (j = 0; j < NUM_DISCIPLINAS; j++)
        {
            printf("%d ", alunos[i].faltas[j]);
        }

        printf("\nMedia: %.2f\n", calcularMedia(alunos[i]));
    }

    printf("\n=========================================\n");
}


/*
 * Lista somente os alunos aprovados.
 *
 * Para este sistema, considera-se aprovado
 * quem possui media maior ou igual a 6.0.
 */
void listarAprovados(void)
{
    int i;
    int encontrou = 0;
    float media;

    printf("\n========== ALUNOS APROVADOS ==========\n");

    for (i = 0; i < qtdAlunos; i++)
    {
        media = calcularMedia(alunos[i]);

        if (media >= 6.0f)
        {
            printf(
                "Matricula: %d | Nome: %s | Media: %.2f\n",
                alunos[i].matricula,
                alunos[i].nome,
                media
            );

            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("Nenhum aluno aprovado.\n");
    }

    printf("======================================\n");
}


/*
 * Lista somente os alunos reprovados.
 *
 * Para este sistema, considera-se reprovado
 * quem possui media menor que 6.0.
 */
void listarReprovados(void)
{
    int i;
    int encontrou = 0;
    float media;

    printf("\n========== ALUNOS REPROVADOS ==========\n");

    for (i = 0; i < qtdAlunos; i++)
    {
        media = calcularMedia(alunos[i]);

        if (media < 6.0f)
        {
            printf(
                "Matricula: %d | Nome: %s | Media: %.2f\n",
                alunos[i].matricula,
                alunos[i].nome,
                media
            );

            encontrou = 1;
        }
    }

    if (!encontrou)
    {
        printf("Nenhum aluno reprovado.\n");
    }

    printf("========================================\n");
}