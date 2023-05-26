#include "filaPedidosPendentes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    pratos *ped; //vetor em que cada elemento eh um prato e juntando todos os pratos que o cliente pediu torna-se o pedido completo
    int qtdPed; //tamanho do vetor
} pedidos;

typedef struct no_pedidosPendentes
{
    pedidos valor;
    struct no *proximo;
} No_pedidosPendentes;

typedef struct fila
{
    No_pedidosPendentes *inicio;
    No_pedidosPendentes *fim;
    int qtd;
} Fila_PedidosPendentes;

Fila_PedidosPendentes *criarFilaP()
{
    Fila_PedidosPendentes *f = (Fila_PedidosPendentes *)malloc(sizeof(Fila_PedidosPendentes));
    f->qtd = 0;
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

int filaVaziaP(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return 2;
    if (f->qtd == 0)
        return 0;
    else
        return 1;
}

int filaCheiaP(Fila_PedidosPendentes *f)
{
    return 1;
}

int inserirP(Fila_PedidosPendentes *f, pedidos *x)
{
    if (f == NULL)
        return 2;
    No_pedidosPendentes *no = (No_pedidosPendentes *)malloc(sizeof(No_pedidosPendentes));
    no->valor = *x;
    no->proximo = NULL;
    if (filaVaziaP(f) == 0)
        f->inicio = no;
    else
        f->fim->proximo = no;
    f->fim = no;
    f->qtd++;
    return 0;
}

int removerP(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return 2;
    if (filaVaziaP(f) == 0)
        return 1;
    No_pedidosPendentes *temp = f->inicio;
    f->inicio = temp->proximo;
    free(temp);
    if (f->inicio == NULL)
        f->fim = NULL;
    f->qtd--;
    return 0;
}

int consultarP(Fila_PedidosPendentes *f, pedidos **x)
{
    if (f == NULL)
        return 2;
    if (filaVaziaP(f) == 0)
        return 1;
    *x = &f->inicio->valor;
    return 0;
}

void limparP(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return;
    while (filaVaziaP(f) != 0)
        removerP(f);
    free(f);
    f = NULL;
}

int tamanhoP(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return -1;
    return f->qtd;
}

void mostrarP(Fila_PedidosPendentes *f)
{
    if (f != NULL)
    {
        printf("---------------------------------------------");
        No_pedidosPendentes *no = f->inicio;
        while (no != NULL)
        {
            printf("%s\n", no->valor.nome_rest);
            printf("%d\n", no->valor.codigo);
            for (int i = 0; i < no->valor.qtdPed; i++)
            {
                printf("%s | %f.2\n", no->valor.ped->nome, no->valor.ped->preco);
            }
            printf("Valor Total: R$ %f.2\n", no->valor.precoTotal);
            printf("---------------------------------------------\n");
            no = no->proximo;
        }
        
    }
}

int mostrarProxP(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return 2;
    if (filaVaziaP(f) == 0)
        return 1;

    pedidos *x;
    consultarP(f, &x);

    printf("Proximo Pedido: ");
    printf("Codigo: %d", x->codigo);
    for (int i = 0; i < x->qtdPed; i++)
    {
        printf("%s | %f.2\n", x->ped->nome, x->ped->preco);
    }

    return 0;
}
