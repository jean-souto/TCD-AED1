#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct plate
{
    char nome[40];
    char descricao[100];
    float preco;
} pratos;

typedef struct ped
{
    int codigo;
    float precoTotal;
    char nome_rest[40];
    pratos *pratosPed; // vetor em que cada elemento eh um prato e juntando todos os pratos que o cliente pediu torna-se o pedido completo
    int qtdPratosPed;
} pedidos;

#endif
