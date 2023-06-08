#include "filaPedidosPendentes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (f == NULL) return 2;
    if (f->qtd == 0) return 0;
    else return 1;
}

int filaCheia(Fila_PedidosPendentes *f)
{
    return 1;
}

int inserirPedidoPendente(Fila_PedidosPendentes *f, pedidos *x)
{
    if (f == NULL) return 2;

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
    if (f == NULL) return 3;
    if (filaVazia(f) == 0) return 0;

    No_pedidosPendentes *aux = f->inicio;

    if (f->inicio->proximo == NULL)
    {
        f->inicio = NULL;
        f->fim = NULL;
        free(aux);
    }
    else
    {
        f->inicio = aux->proximo;
        free(aux);
    }

    return 0;
}

/*int removerP(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return 2;
    if (filaVazia(f) == 0)
        return 1;
    No_pedidosPendentes *temp = f->inicio;
    f->inicio = temp->proximo;
    free(temp);
    if (f->inicio == NULL)
        f->fim = NULL;
    f->qtd--;
    return 0;
}*/

int consultarProxPedido(Fila_PedidosPendentes *f, pedidos **x)
{
    if (f == NULL)
        return 2;
    if (filaVazia(f) == 0)
        return 1;

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

int mostrarProxPedido(Fila_PedidosPendentes *f)
{
    if (f == NULL)
        return 2;
    if (filaVazia(f) == 0)
        return 1;

    pedidos *x;
    consultarProxPedido(f, &x);

    printf("Proximo Pedido: ");
    printf("Codigo: %d", x->codigo);
    for (int i = 0; i < x->qtdPed; i++)
    {
        printf("%s | %f.2\n", x->ped->nome, x->ped->preco);
    }

    return 0;
}
