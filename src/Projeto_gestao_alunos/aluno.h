#ifndef ALUNO_H
#define ALUNO_H

#define CAPACIDADE_INICIAL 10
#define INCREMENTO 10
#define NUM_DISCIPLINAS 7
#define TAM_NOME 50
#define ARQUIVO "alunos.txt"

typedef struct {
    int matricula;
    float notas[NUM_DISCIPLINAS];
    char nome[TAM_NOME];
    int codTurma;
    int faltas[NUM_DISCIPLINAS];
} Aluno;

/*
 * Variáveis globais do sistema.
 */
extern Aluno *alunos;
extern int qtdAlunos;
extern int capacidade;

/*
 * Inicialização e finalização do sistema.
 */
void inicializarSistema(void);
void liberarSistema(void);

/*
 * Manipulação dos alunos.
 */
int inserirAluno(Aluno novoAluno);
int removerAluno(int matricula);
int procurarAluno(int matricula);
int tamanho(void);

/*
 * Listagens.
 */
void listarAlunos(void);
void listarAprovados(void);
void listarReprovados(void);

/*
 * Manipulação do arquivo.
 */
int carregarArquivo(void);
int salvarArquivo(void);

#endif