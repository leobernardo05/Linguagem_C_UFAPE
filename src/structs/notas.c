#include <stdio.h>
#include <stdlib.h>

//define uma cpnstante para o numero de alunos
#define N 3

// struct
typedef struct{
    int matricula;
    char nome[20];
    float notas[3];
} aluno;

int main (){
    aluno alunos[N]; //declara um vetor de 5 estruturas do tipo aluno
    int i;

    // laço para entrada de dados
    for (i = 0; i < N; i++){
        printf("\n--- Aluno %d ---\n", i + 1);

        // Lê a matricula do aluno 5 vezes
        printf("\ninforme a matricula do aluno: ");
        scanf("%d", &alunos[i].matricula);

        // Lê o nome do aluno
        printf("\ninforme o nome do aluno: ");
        scanf(" %19[^\n]", &alunos[i].nome);

        for (int j = 0; j < 3; j++){     
            printf("\ninforme a %d° nota do aluno: ", j+1);
            scanf("%f", &alunos[i].notas[j]);
        }
        printf("\n");
    }

    // laço para exibição de dados
    for (i = 0; i < N; i++){
        printf("\n--- Dados do aluno %d ---\n", i + 1);

        // Exibe a matricula do aluno
        printf("A matricula do aluno é: %d\n", alunos[i].matricula);
        
        // Exbibe o nome do aluno
        printf("Nome do aluno é: %s\n", alunos[i].nome);
        
        printf("As notas do aluno %s são: \n", alunos[i].nome);
        for (int j = 0; j < 3; j++){     
            printf("\n%.2f ", alunos[i].notas[j]);
        }
        printf("\n");
    }
    return 0;
}