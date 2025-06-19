#include <stdio.h>
#include <stdlib.h> // Necessário para malloc() e free()
#include <string.h> // Necessário para strcpy()

int main()
{
    // Parte 1: Variável na Stack
    char hello[] = "Hello Word"; // "World" escrito como "Word" no original
    printf("Endereço do array 'hello' na STACK: %p\n", (void *)hello);

    // Parte 2: Alocação e Cópia na Heap
    char *hello2 = malloc(sizeof(hello)); // Aloca memória na HEAP
    strcpy(hello2, hello);                // Copia o conteúdo de 'hello' para o novo espaço
    printf("Endereço apontado por 'hello2' na HEAP: %p\n", (void *)hello2);

    // Parte 3: Aritmética de Ponteiros
    char *hello3 = hello2 + 6; // 'hello3' aponta para 6 bytes depois de 'hello2'

    // Parte 4: Impressão dos Resultados
    printf("String a partir de hello2: %s\n", hello2);
    printf("String a partir de hello3: %s\n", hello3);

    free(hello2); // Libera a memória alocada para evitar memory leak

    return 0;
}