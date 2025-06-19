# Computer-Study

# Understanding C

Este repositório documenta uma jornada de estudos em Ciência da Computação utilizando a linguagem C, baseada em uma série de vídeos de referência de Fábio Akita. O objetivo é solidificar o conhecimento teórico sobre o funcionamento de computadores, gerenciamento de memória e estruturas de dados através de exemplos práticos e comentados.

Os códigos aqui presentes servem como um laboratório para visualizar "por debaixo dos panos" os conceitos que formam a base de quase toda a programação moderna.

## Vídeos de Referência

O conteúdo teórico que inspirou estes estudos foi extraído dos seguintes vídeos:

1. [**Hello World Como Você Nunca Viu! | Entendendo C**](https://youtu.be/Gp2m8ZuXoPg?si=3wuwGGkC-wxcbcO0): Uma imersão nos fundamentos da representação de dados, bits, bytes e o gerenciamento básico de memória na Stack.
2. [**Estruturas de Dados | Programação Além do Básico**](https://youtu.be/YyWMN_0g3BQ?si=D1U-5m7OqDlt_7zo): Aprofundamento em estruturas como Listas Ligadas e Hash Tables, gerenciamento de memória e introdução à complexidade de algoritmos (Big O).
3. [**Algoritmos e Estruturas de Dados | O Guia para o Próximo Nível**](https://youtu.be/9GdesxWtOgs?si=_TF5YXSVP55YCRSR): Exploração de estruturas não-lineares como Árvores (BST, B-Trees), essenciais em bancos de dados e sistemas de arquivos.

## Análise dos Códigos

Cada código foi projetado para isolar e demonstrar um conceito-chave discutido nos vídeos.

### 1. A Pilha (Stack) e o "Array Decay"

Este código demonstra o comportamento mais fundamental da memória em C: a pilha de execução (Stack) e como os arrays são passados entre funções.

- **Conceito-chave:** Toda variável local e chamada de função empilha um novo "quadro" na Stack. Ao passar um array para uma função, não o copiamos; passamos um ponteiro para seu primeiro elemento (fenômeno conhecido como *array decay*).
- **Conexão com os vídeos:** Visualiza na prática o gerenciamento de memória da Stack explicado no **Vídeo 1**.

```c
#include <stdio.h>void f2(char hello[]) {
    // hello aqui é um ponteiro que recebeu o endereço do array original.
    printf("from f2: %s\n", hello);
}

void f1(char hello[]) {
    f2(hello); // Passa o mesmo ponteiro adiante.
}

int main() {
    // "hello" é um array alocado na Stack do main.
    char hello[] = "Hello World";
    f1(hello); // Inicia a cadeia de chamadas.
    return 0;
}
```

### 2. Memória na Heap e Aritmética de Ponteiros

Aqui, introduzimos a alocação dinâmica na Heap e a manipulação direta de endereços de memória.

- **Conceitos-chave:**
    - **Stack vs. Heap:** A `Stack` é automática, enquanto a `Heap` é para alocação manual (`malloc`) e exige liberação explícita (`free`).
    - **Aritmética de Ponteiros:** Um ponteiro pode ser "movido" para apontar para outras posições de um bloco de memória (`ponteiro + N`), permitindo percorrer dados de forma eficiente.
- **Conexão com os vídeos:** Aplica os conceitos de `malloc` e gerenciamento de memória discutidos no **Vídeo 2**.

```c
`#include <stdio.h>#include <stdlib.h>#include <string.h>int main() {
    char hello[] = "Hello Word"; // Na Stack
    
    // Aloca memória na Heap e copia a string para lá.
    char *hello2 = malloc(sizeof(hello));
    strcpy(hello2, hello);

    // hello3 aponta para o meio da string na Heap.
    char *hello3 = hello2 + 6;
    
    printf("from hello2: %s\n", hello2); // Imprime "Hello Word"
    printf("from hello3: %s\n", hello3); // Imprime "Word"
    
    free(hello2); // Libera a memória da Heap.
    return 0;
}`
```

### 3. Simulação de Orientação a Objetos

Este exemplo avançado mostra como usar `structs` e ponteiros de função para simular o paradigma de Programação Orientada a Objetos (POO) em C.

- **Conceitos-chave:**
    - **Classe como `struct`**: Uma `struct` agrupa dados (atributos).
    - **Método como Ponteiro de Função**: A `struct` armazena um ponteiro para uma função, associando comportamento aos dados.
    - **Objeto como Bloco na Heap**: Um "objeto" é criado com `malloc`, e uma função "construtora" (`newPerson`) inicializa seus atributos e métodos.
- **Conexão com os vídeos:** Leva a um nível mais alto a manipulação de `structs` e ponteiros discutida nos **Vídeos 1 e 2**, mostrando como C pode ser usado para construir abstrações complexas.

```c
#include <stdio.h>#include <stdlib.h>#include <string.h>struct Person {
    char nome[10];
    void (*show)(struct Person *); // Ponteiro para "método"
};

void person_print(struct Person *self) { /* ... */ }

struct Person *newPerson(char name[]) {
    struct Person *self = malloc(sizeof(struct Person));
    strcpy(self->nome, name);
    self->show = &person_print; // Associa o método
    return self;
}

int main() {
    struct Person *p = newPerson("Isaac");
    p->show(p); // Chama o "método"
    free(p);
    return 0;
}
```

### 4. Funções de Callback

Demonstra o poderoso padrão de *callback*, onde uma função é passada como argumento para outra, permitindo um código mais flexível e desacoplado.

- **Conceito-chave:** Uma função (`createPerson`) recebe um ponteiro para outra função (`printPerson`) e a "chama de volta" (*calls back*) para completar uma tarefa. Isso permite que a ação executada seja customizável.
- **Conexão com os vídeos:** Embora não seja um tema central, callbacks são uma aplicação direta do poder dos ponteiros e da arquitetura de software discutida em um nível conceitual, onde diferentes componentes do sistema se comunicam de forma modular.

```c
#include <stdio.h>#include <string.h>struct Person { char nome[10]; };

void createPerson(char name[], void (*callback)(struct Person)) {
    struct Person p;
    strcpy(p.nome, name);
    callback(p); // Chama a função que foi passada como argumento
}

void printPerson(struct Person p) { /* ... */ }
void printPerson2(struct Person p) { /* ... */ }

int main() {
    // Passa a função printPerson como callback
    createPerson("Isaac", &printPerson);
    // Passa a função printPerson2 como callback
    createPerson("Maria", &printPerson2);
    return 0;
}
```

## Como Compilar e Executar

Todos os códigos foram escritos em C padrão e podem ser compilados com o GCC (GNU Compiler Collection).

```bash
# Para compilar um arquivo específico
gcc nome_do_arquivo.c -o executavel

# Para executar
./executavel
```

## Conclusão da Jornada

Este estudo prático reforça que a compreensão dos fundamentos de memória (Stack vs. Heap), o domínio de ponteiros e a habilidade de manipular estruturas de dados são os pilares da programação de software robusto e eficiente. Os vídeos forneceram o "porquê" teórico, e os códigos, o "como" prático, solidificando a ponte entre saber e fazer.
