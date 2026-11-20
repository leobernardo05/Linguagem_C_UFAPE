// =========== calculadora utilizando funções ============
#include <stdio.h>

float Globalresultado = 0;

// função soma
void sum (float a, float b) {
    Globalresultado = a + b;
    printf("%.1f", &Globalresultado);
}

// função subtração
void sub (float a,float b) {
    Globalresultado = a - b;
    printf("%.1f", &Globalresultado);
}

// função multiplicação
void mult (float a, float b) {
    Globalresultado = a * b;
    printf("%.1f", &Globalresultado);
}

// função divisao
void div (float a,float b) {
    Globalresultado = a / b;
    printf("%.1f", &Globalresultado);
}

int main(){
    float a, b;
    int cont;
    // implementando valores
    printf("Digite um valor:");
    scanf("%d", &a);
    printf("Digite outro valor:");
    scanf("%d", &b);

    // switch para escolher a operação da calculadora
    printf("Digite 1 - soma\nDigite 2 - subtracao\nDigite 3 - multiplicacao\nDigite 4 - divisao\nEscolha: ");
    scanf("%d", &cont);
    
    switch (cont) {
        case 1:
            sum(a,b);
            break;
        case 2:
            sub(a,b);
            break;
        case 3:
            mult(a,b);
            break;
        case 4:
            div(a,b);
            break;
        default:
            printf("Digite um valor valido!");
    }

    return 0;
}