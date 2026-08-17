#include <stdio.h>
#include <stdlib.h>

//define uma cpnstante para o numero de alunos
#define N 5

// struct
typedef struct{
    int id;
    char nome[30];
} livro;

int main (){
    livro livros[N]; //declara um vetor de 5 estruturas do tipo aluno
    int i;

    // laço para entrada de dados
    for (i = 0; i < N; i++){
        printf("\n--- Livro %d ---\n", i + 1);

        // id do livro
        printf("\ninforme o id do livro: ");
        scanf("%d", &livros[i].id);

        // Lê o nome do aluno
        printf("\ninforme o nome do livro: ");
        scanf(" %29[^\n]", &livros[i].nome);

        printf("\n");
    }

    // laço para exibição de dados
    for (i = 0; i < N; i++){
        printf("\n--- Dados do livro %d ---\n", i + 1);

        // Exibe o id do livro
        printf("O id do livro é: %d\n", livros[i].id);
        
        // Exibe o nome do livro
        printf("Nome do livro é: %s\n", livros[i].nome);
    
    }
    return 0;
}