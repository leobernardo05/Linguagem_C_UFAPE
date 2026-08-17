#include <stdio.h>

int main(void){
    int idade = 19;
    // ponteiro
    int *ponteiro;

    //ponteiro recebe 19
    ponteiro = &idade;

    printf("valor de idade: %d\n",idade);
    printf("Endereco da idade: %p\n", (void*)&idade);
    printf("Endereco armazenado no ponteiro: %p\n",(void*)ponteiro);
    printf("Valor acessado pelo ponteiro: %d\n", *ponteiro);
}