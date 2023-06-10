#include "filaPedidosPendentes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no_pedidosPendentes
{
    pedidos valor;
    struct no_pedidosPendentes *proximo;
} No_pedidosPendentes;

typedef struct fila
{
    No_pedidosPendentes *inicio;
    No_pedidosPendentes *fim;
    int qtd;
} Fila_PedidosPendentes;

// IMPLEMENTACOES
Fila_PedidosPendentes *criar_filaPedidosPendentes()
{
    Fila_PedidosPendentes *f = (Fila_PedidosPendentes *)malloc(sizeof(Fila_PedidosPendentes));

    f->qtd = 0;
    f->inicio = NULL;
    f->fim = NULL;

    return f;
}

int filaVazia(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return NULL_QUEUE;
    if (f->qtd == 0)
        return 0;
    else
        return 1;
}

int filaCheia(Fila_PedidosPendentes *f)
{
    return 1;
}

int inserirPedidoPendente(Fila_PedidosPendentes *f, pedidos *x)
{
    if (f == NULL)
        return NULL_QUEUE;

    No_pedidosPendentes *no = (No_pedidosPendentes *)malloc(sizeof(No_pedidosPendentes));
    no->valor = *x;
    no->proximo = NULL;

    if (filaVazia(f) == 0)
        f->inicio = no;
    else
        f->fim->proximo = no->proximo;

    f->fim = no;
    f->qtd++;

    return 0;
}

int removerPedidoPendente(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return NULL_QUEUE;
    if (filaVazia(f) == 0)
        return EMPTY_QUEUE;

    No_pedidosPendentes *no = f->inicio;
    f->inicio = no->proximo;
    free(no);

    if (f->inicio == NULL)
        f->fim = NULL;

    f->qtd--;

    return 0;
}

int consultarProxPedido(Fila_PedidosPendentes *f, pedidos **x)
{
    if (f == NULL)
        return NULL_QUEUE;
    if (filaVazia(f) == 0)
        return EMPTY_QUEUE;

    *x = &f->inicio->valor;

    return 0;
}

void limparFila(Fila_PedidosPendentes *f)
{
    while (filaVazia(f) != 0)
        removerPedidoPendente(f);

    free(f);
    f = NULL;
}

int tamanhoFila(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return -1;

    return f->qtd;
}

void mostrarPedidosPendentes(Fila_PedidosPendentes *f)
{
    if (f != NULL)
    {
        printf("---------------------------------------------");
        No_pedidosPendentes *no = f->inicio;
        while (no != NULL)
        {
            printf("%s\n", no->valor.nome_rest);
            printf("%d\n", no->valor.codigo);
            for (int i = 0; i < no->valor.qtdPratosPed; i++)
            {
                printf("%s | %f.2\n", no->valor.pratosPed->nome, no->valor.pratosPed->preco);
            }
            printf("Valor Total: R$ %f.2\n", no->valor.precoTotal);
            printf("---------------------------------------------\n");
            no = no->proximo;
        }
    }
}

int mostrarProxPedido(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return NULL_QUEUE;
    if (filaVazia(f) == 0)
        return EMPTY_QUEUE;

    pedidos *x;
    consultarProxPedido(f, &x);

    printf("Proximo Pedido: ");
    printf("Codigo: %d", x->codigo);
    for (int i = 0; i < x->qtdPratosPed; i++)
    {
        printf("%s | %f.2\n", x->pratosPed->nome, x->pratosPed->preco);
    }

    return 0;
}

int copiarFilaPedidosPendentes(Fila_PedidosPendentes *f1, Fila_PedidosPendentes *f2)
{
    if (f1 == NULL || f2 == NULL)
        return NULL_QUEUE;

    No_pedidosPendentes *no = f1->inicio;

    while (no != NULL)
    {
        inserirPedidoPendente(f2, &no->valor);
        no = no->proximo;
    }

    return 0;
}
