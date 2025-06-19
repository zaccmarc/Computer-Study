#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h> // Para tipos de inteiros com tamanho fixo, como uint8_t

// Usar #define é uma forma de criar um "apelido".
// O pré-processador irá substituir toda ocorrência de "Class" por "struct".
#define Class struct

// 1. Definição da "Classe" Person
Class Person
{
    // Atributos (dados)
    char nome[10];
    uint8_t age;
    uint8_t height;

    // "Método" (ponteiro para uma função)
    void (*show)(Class Person *self);
};

// 2. Implementação da função que servirá como método
void person_print(Class Person *self)
{
    printf("Nome: %s, Idade: %d, Altura: %dcm\n",
           self->nome, self->age, self->height);
}

// 3. Definição do "Construtor" (uma função fábrica)
Class Person *newPerson(char name[], uint8_t age, uint8_t height)
{
    // Aloca memória para um "objeto" Person na HEAP
    Class Person *self = (Class Person *)malloc(sizeof(Class Person));

    // Inicializa os atributos (usando os parâmetros, ao contrário do original)
    // strncpy é mais seguro que strcpy pois evita buffer overflow.
    strncpy(self->nome, name, 9);
    self->nome[9] = '\0'; // Garante que a string sempre terá um terminador nulo
    self->age = age;
    self->height = height;

    // Associa o ponteiro de função "show" ao endereço da função real person_print
    self->show = &person_print;

    // Retorna o ponteiro para o objeto recém-criado
    return self;
}

// 4. Função principal
int main()
{
    // Cria uma instância (um "objeto") de Person usando o "construtor"
    Class Person *person2 = newPerson("Isaac", 21, 185);

    // Chama o "método" show do objeto person2
    person2->show(person2);

    // Libera a memória alocada na HEAP para evitar memory leak
    free(person2);

    return 0;
}