#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

struct Person
{
    char nome[10];
    uint8_t age;
    uint8_t height;
};

// 1. Função principal que aceita um ponteiro de função como argumento (o "callback")
void createPerson(
    char name[],
    uint8_t age,
    uint8_t height,
    // Este é o parâmetro de callback: um ponteiro para uma função
    // que recebe uma 'struct Person' por valor.
    void (*function_pointer)(struct Person))
{
    // Cria uma struct Person na STACK da função createPerson
    struct Person person;

    // Inicializa a struct com os parâmetros recebidos (versão corrigida)
    strncpy(person.nome, name, 9);
    person.nome[9] = '\0'; // Boa prática para evitar problemas de string
    person.age = age;
    person.height = height;

    // 2. A "chamada de volta" (callback) acontece aqui.
    // Executa a função cujo endereço foi passado como argumento.
    (*function_pointer)(person);
}

// 3. Primeira implementação de função que pode ser usada como callback
void printPerson(struct Person person)
{
    printf("Person -> Nome: %s, Idade: %d, Altura: %dcm\n",
           person.nome, person.age, person.height);
}

// 4. Segunda implementação de função que pode ser usada como callback
void printPerson2(struct Person person)
{
    printf("======================\n");
    printf("Relatório da Pessoa:\n");
    printf("  - Nome: %s\n  - Idade: %d\n  - Altura: %dcm\n",
           person.nome, person.age, person.height);
    printf("======================\n");
}

int main()
{
    // 5. Chama a função createPerson, passando o ENDEREÇO da função printPerson
    createPerson("Isaac", 21, 185, &printPerson);

    // 6. Chama a mesma função, mas agora passando o ENDEREÇO da função printPerson2
    createPerson("Maria", 30, 165, &printPerson2);

    return 0;
}