#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filaPedidosPendentes.h"
#include "restaurante.h"

// funcao que cria a lista de restaurantes
Lista_restaurantes *criar_listaRestaurantes()
{
    Lista_restaurantes *l = (Lista_restaurantes *)malloc(sizeof(Lista_restaurantes));
    l->inicio = NULL;
    return l;
}

// funcao que cria uma nova lista separada por categoria desejada do cliente
int criar_listaCategoria(Lista_restaurantes *l1, Lista_restaurantes *l2, char *categoria)
{
    if (l2 == NULL) 
    {
        l2 = criar_listaRestaurantes(); 
    }        

    No_restaurante *no = l1->inicio;

    while (no->prox != NULL)
    {
        no = no->prox;
        if (no->valor.categoria == categoria)
        {
            inserirFimRest(l2, no->valor);
        }
    }

    return 0;
}

// retorna 0 se estiver vazia
int listaVaziaRest(Lista_restaurantes *l)
{
    if (l == NULL)
        return NULL_LIST;
    if (l->inicio == NULL)
        return 0;
    else
        return 1;
}

// limpa a lista
void limparRest(Lista_restaurantes *l)
{
    while (listaVaziaRest(l) != 0)
        removerInicioRest(l);
    free(l);
    l = NULL;
}

// retorna o tamanho da lista
int tamanhoRest(Lista_restaurantes *l)
{
    if (l == NULL)
        return -1;
    No_restaurante *no = l->inicio;
    int tam = 0;
    while (no != NULL)
    {
        tam++;
        no = no->prox;
    }
    return tam;
}

// insere no inicio da lista
int inserirInicioRest(Lista_restaurantes *l, restaurante item)
{
    if (l == NULL)
        return NULL_LIST;

    No_restaurante *no = (No_restaurante *)malloc(sizeof(No_restaurante));
    no->valor = item;
    no->prox = l->inicio;
    no->ant = NULL;

    if (l->inicio != NULL)
    {
        l->inicio->ant = no;
    }
    l->inicio = no;

    return 0;
}

// insere no fim da lista
int inserirFimRest(Lista_restaurantes *l, restaurante item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == EMPTY_LIST)
         inserirInicioRest(l, item);

    No_restaurante *noaux = l->inicio;
    while (noaux->prox != NULL)
        noaux = noaux->prox;

    No_restaurante *no = (No_restaurante *)malloc(sizeof(No_restaurante));
    no->valor = item;
    no->prox = NULL;
    no->ant = noaux;
    noaux->prox = no;

    return 0;
}

// remove no inicio da lista
int removerInicioRest(Lista_restaurantes *l)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *no = l->inicio;
    l->inicio = no->prox;
    if (l->inicio->prox != NULL)
        l->inicio->ant = NULL;
    free(no);

    return 0;
}

// remove no fim da lista
int removerFimRest(Lista_restaurantes *l)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *aux = l->inicio;

    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    if (l->inicio->prox != NULL)
        aux->ant->prox = NULL;
    else
        l->inicio = NULL;

    free(aux);

    return 0;
}

// remove uma posicao X da lista, se pos >= tamanho da lista ela remove o ultimo elemento
int removerPosRest(Lista_restaurantes *l, int pos)
{
    if (l == NULL)
        return 3;
    if (listaVaziaRest(l) == 0)
        return 0;
    if (pos == 0)
    {
        removerInicioRest(l);
        return 0;
    }
    if (pos >= tamanhoRest(l) - 1)
    {
        removerFimRest(l);
        return 0;
    }

    No_restaurante *aux = l->inicio;

    while (pos > 0)
    {
        aux = aux->prox;
        pos--;
    }

    aux->prox->ant = aux->ant;
    aux->ant->prox = aux->prox;
    free(aux);

    return 0;
}

// remove o item correspondente ao codigo passado
int removerRest(Lista_restaurantes *l, int codigo)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *aux;
    aux = l->inicio;
    int pos = 0;

    while (aux != NULL && aux->valor.codigo != codigo)
    {
        pos++;
        aux = aux->prox;
    }
    if (aux->valor.codigo == codigo)
    {
        removerPosRest(l, pos);
        return 0;
    }
    return 1;
}

// busca o restaurante correspondente ao codigo e retorna ele por parametro
/*int buscarCodigoRest(Lista_restaurantes *l, int codigo, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *aux = l->inicio;

    while (aux != NULL && aux->valor.codigo != codigo)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == codigo)
    {
        copiarRestaurante(&(aux->valor), &(*item));
        return 0;
    }
    else
        return 1;
}

// busca um restaurante
int buscarRest(Lista_restaurantes *l, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *aux;
    aux = l->inicio;

    while (aux != NULL)
    {
        if (aux->valor.status == 0)
        {
            aux->valor.status = 1;
            copiarRestaurante(&(aux->valor), &(*item));
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

// mostra as principais informacoes de cada restaurante
void mostrarInfoRestaurante(Lista_restaurantes *l)
{
    if (l != NULL)
    {
        printf("[");

        if (listaVaziaRest(l) != 0)
        {
            No_restaurante *aux = l->inicio;
            do
            {
                printf(" {%d, ", aux->valor.codigo);
                printf("%s, ", aux->valor.nome);
                printf("%.2f, ", aux->valor.categoria);
                printf("%d}", aux->valor.status);
                aux = aux->prox;
            } while (aux != NULL);
        }
        printf(" ]\n");
    }
}*/

// copia todas as informacoes de um elemento para outro
void copiarRestaurante(restaurante *A, restaurante *B)
{
    strcpy(B->nome, A->nome);
    strcpy(B->email, A->email);
    strcpy(B->senha, A->senha);
    strcpy(B->categoria, A->categoria);
    B->codigo = A->codigo;
    B->status = A->status;
    //copiarRestaurante mennu
    //copiarRestaurante historico
    //copiarRestaurante fila pedidosPendentes
    
}