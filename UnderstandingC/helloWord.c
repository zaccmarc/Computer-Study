#include <stdio.h>

void f2(char hello[])
{
    // 3. Chegamos em f2
    printf("from f2: %p\n", (void *)&hello); // Endereço do ponteiro local 'hello' em f2
    printf("%s\n", hello);                   // Imprime a string original
}

void f1(char hello[])
{
    // 2. Chegamos em f1
    printf("from f1: %p\n", (void *)&hello); // Endereço do ponteiro local 'hello' em f1
    f2(hello);                               // Chama f2, passando o mesmo endereço
}

int main()
{ // main deveria retornar int por padrão
    // 1. O programa começa aqui
    char hello[] = "Hello World";
    printf("from main: %p\n", (void *)&hello); // Endereço do array 'hello' em main
    f1(hello);                                 // Chama f1, passando o array

    return 0; // Retorno padrão para sucesso
}