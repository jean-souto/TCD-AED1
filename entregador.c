#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "entregador.h"

Lista_entregadores* criar_lista_entregadores () // função que cria a lista de entregadores
{
    Lista_entregadores *l = (Lista_entregadores*) malloc (sizeof(Lista_entregadores));
    l->inicio = NULL;
    return l;
}

int listaVaziaEntregador (Lista_entregadores *l) // verifica se a lista está vazia
{
    if (l == NULL) return 2;
    if (l->inicio == NULL) return 0;
    
    return 1;
}

int sortearCodigoEntregador (Lista_entregadores *l)
{
    int codigo = 0;
    srand(time(NULL));

    while (codigo == 0)
    {
        codigo = rand()%9999;
    }

    if (l == NULL || listaVaziaEntregador(l) == 0) return codigo;

    No_entregador *aux = l->inicio;
    
    while (aux != NULL)
    {
        if (codigo == aux->valor.codigo)
        {
            codigo = rand()%9999;
            aux = l->inicio;
        }
        aux = aux->prox;
    }

    return codigo;
}

int inserirInicioEntregador (Lista_entregadores *l, entregador item) // insere no inicio da lista
{
    if (l == NULL) return NULL_LIST;

    No_entregador *noaux = (No_entregador*) malloc (sizeof(No_entregador));

    if (listaVaziaEntregador(l) != 0)
    {
        noaux->valor = item;
        noaux->valor.codigo = sortearCodigoEntregador(l);
        l->inicio->ant = noaux;
        noaux->prox = l->inicio;
        noaux->ant = NULL;
        l->inicio = noaux;
    }
    else
    {
        noaux->valor = item;
        noaux->valor.codigo = sortearCodigoEntregador(l);
        l->inicio = noaux;
        noaux->prox = NULL;
        noaux->ant = NULL;
    }

    return 0;
}

int inserirFimEntregador (Lista_entregadores *l, entregador item, int *codig) // insere no fim da lista
{
    if (l == NULL) return NULL_LIST;

    No_entregador *noaux = (No_entregador*) malloc (sizeof(No_entregador));
    No_entregador *nofim = l->inicio;
    
    noaux->valor = item;
    noaux->valor.codigo = sortearCodigoEntregador(l);
    noaux->prox = NULL;
    *codig = noaux->valor.codigo;

    if (listaVaziaEntregador(l) != 0) 
    {   
        while (nofim->prox != NULL)
        {
            nofim = nofim->prox;
        }
        nofim->prox = noaux;
        noaux->ant = nofim;
    }
    else 
    {
        l->inicio = noaux;
        noaux->ant = NULL;
    }
    return 0;
}

int removerInicioEntregador (Lista_entregadores *l) // remove no inicio da lista
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return 0;

    No_entregador *aux = l->inicio;
    
    if (l->inicio->prox == NULL)
    {
        l->inicio = NULL;
        free(aux);
    }
    else
    {
        l->inicio = aux->prox;
        aux->prox->ant = NULL;
        free(aux);
    }
    return 0;
}

int removerFimEntregador (Lista_entregadores *l) // remove no fim da lista
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return 0;

    No_entregador *aux = l->inicio;

    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }

    if (l->inicio->prox != NULL) aux->ant->prox = NULL;
    else l->inicio = NULL;
    free(aux);
    return 0;
}

int removerPosiEntregador (Lista_entregadores *l, int pos) // remove uma posicao X da lista, se pos >= tamanhoEntregador da lista ela remove o último elemento
{
    if (l == NULL) return 3;
    if (listaVaziaEntregador(l) == 0) return 0;
    if (pos == 0) 
    {
        removerInicioEntregador(l); 
        return 0;
    }
    if (pos >= tamanhoEntregador(l)-1)
    {
        removerFimEntregador(l);
        return 0;
    }

    No_entregador *aux = l->inicio;

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

int removerItemEntregador (Lista_entregadores *l, int codigo) // remove o item correspondente ao código passado 
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return EMPTY_LIST;

    No_entregador *aux;
    aux = l->inicio;
    int pos = 0;

    while (aux != NULL && aux->valor.codigo != codigo)
    {
        pos++;
        aux = aux->prox;
    }
    if (aux->valor.codigo == codigo)
    {
        removerPosiEntregador(l, pos);
        return 0;
    }
    return 1;
}

int buscarItemEntregador (Lista_entregadores *l, int codigo, entregador *item) // busca o entregador correspondente ao codigo e retorna ele por parametro
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return EMPTY_LIST;

    No_entregador *aux = l->inicio;

    while (aux != NULL && aux->valor.codigo != codigo)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == codigo)
    {
        copiarEntregador(&(aux->valor), &(*item));
        return 0;
    }
    else return 1;
}

int buscarEntregador (Lista_entregadores *l, entregador *item) // busca um entregador pra fazer a entrega e já ocupa ele (status = 1)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return EMPTY_LIST;

    No_entregador *aux;
    aux = l->inicio;

    while (aux != NULL)
    {
        if (aux->valor.status == 0)
        {
            aux->valor.status = 1;
            copiarEntregador (&(aux->valor), &(*item));
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}

int liberarEntregador (Lista_entregadores *l, int codigo) // libera o entregador (status = 0)
{
    No_entregador *aux = l->inicio;

    while (aux != NULL && aux->valor.codigo != codigo)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == codigo)
    {
        aux->valor.status = 0;
        return 0;
    }
    else return 1;
}

int ocuparEntregador (Lista_entregadores *l, int codigo) // ocupa o entregador (desnecessaria dado que a buscarEntregador já faz isso e mais)
{
    No_entregador *aux = l->inicio;

    while (aux != NULL && aux->valor.codigo != codigo)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == codigo)
    {
        aux->valor.status = 1;
        return 0;
    }
    else return 1;
}

int adicionarCorridaNota (Lista_entregadores *l, int codigo, float nota) // adiciona ao entregador (passado por codigo) +1 corrida, a media acrescida da nota dada e também já libera ele (status = 0)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return EMPTY_LIST;

    No_entregador *aux = l->inicio;
    while (aux != NULL && aux->valor.codigo != codigo)
    {
        aux = aux->prox;
    }
    if (aux->valor.codigo == codigo)
    {
        aux->valor.corridas++;
        aux->valor.rank.quantidade++;
        aux->valor.rank.total = nota+aux->valor.rank.total;
        aux->valor.rank.media = ((aux->valor.rank.total/aux->valor.rank.quantidade)*1.0);
        liberarEntregador(l, aux->valor.codigo);
        return 0;
    } else return 1;
}

int limparEntregador (Lista_entregadores *l) // limpa a lista
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return 0;
    while (l->inicio != NULL)
    {
        removerFimEntregador(l);
    }
    return 0;
}

int tamanhoEntregador (Lista_entregadores *l) // retorna o tamanhoEntregador da lista 
{
    No_entregador *aux = l->inicio;
    int tam = 0;

    while (aux != NULL)
    {
        tam++;
        aux = aux->prox;
    }
    return tam;
}

void mostrar_entregador (Lista_entregadores *l) // mostra as principais informações de cada entregador
{
    if (l != NULL)
    {
        printf ("[");
        
        if (listaVaziaEntregador(l) != 0)
        {
            No_entregador *aux = l->inicio;
            do
            {
                printf(" {%d, ", aux->valor.codigo);
                printf("%s, ", aux->valor.nome);
                printf("%.2f, ", aux->valor.rank.media);
                printf("%d, ", aux->valor.corridas);
                printf("%d}", aux->valor.status);
                aux = aux->prox;
            }while(aux != NULL);
        } printf(" ]\n");
    }
}

void mostrar_tudo_entregador (Lista_entregadores *l) // mostra TODAS as informações do entregador
{
    if (l != NULL)
    {   
        if (listaVaziaEntregador(l) != 0)
        {
            No_entregador *aux = l->inicio;
            do
            {
                printf("{%d, ", aux->valor.codigo);
                printf("%s, ", aux->valor.nome);
                printf("%s, ", aux->valor.cpf);
                printf("%s, ", aux->valor.email);
                printf("%.2f, ", aux->valor.rank.media);
                printf("%d, ", aux->valor.corridas);
                printf("%d}\n", aux->valor.status);
                aux = aux->prox;
            }while(aux != NULL);
        }
    }
}

void copiarEntregador (entregador *A, entregador *B) // função de auxílio. copia todas as informações de um elemento para outro
{
    int i, j;

    B->codigo = A->codigo;
    B->corridas = A->corridas;
    B->status = A->status;
    B->rank.media = A->rank.media;
    B->rank.quantidade = A->rank.quantidade;
    B->rank.total = A->rank.total;
    strcpy (B->cpf, A->cpf);
    strcpy (B->email, A->email);
    strcpy (B->nome, A->nome);

    B->historico = (pedidosE*) realloc (B->historico, A->quant_pedidos*sizeof(pedidosE));
    for (i = 0; i < A->quant_pedidos; i++)
    {
        B->historico[i].precoTotal = A->historico[i].precoTotal;
        strcpy(B->historico[i].nome_rest, A->historico[i].nome_rest);
        B->historico[i].codigo = A->historico[i].codigo;
        B->historico[i].qtdPed = A->historico[i].qtdPed;

        B->historico[i].ped = (pratosE*) realloc (B->historico[i].ped, A->historico[i].qtdPed*sizeof(pratosE));

        for (j = 0; j < A->historico[i].qtdPed; j++)
        {
            B->historico[i].ped[j].preco = A->historico[i].ped[j].preco;
            strcpy(B->historico[i].ped[j].nome, A->historico[i].ped[j].nome);
            strcpy(B->historico[i].ped[j].descricao, A->historico[i].ped[j].descricao);
        }
    }
}

int loginCodigo (Lista_entregadores *l, char *email, int codigo, entregador *item)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return EMPTY_LIST;

    No_entregador *aux = l->inicio;

    while (aux->prox != NULL && (strcmp(aux->valor.email, email) != 0))
    {
        aux = aux->prox;
    }

    if ((strcmp(aux->valor.email, email) == 0) && (aux->valor.codigo == codigo))
    {
        copiarEntregador(&aux->valor, &(*item));
        return 0;
    }
    return 1;
}

int alterarEmailEntregador (Lista_entregadores *l, int codigo, char *novo_email)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return EMPTY_LIST; 

    No_entregador *aux = l->inicio;

    while (aux != NULL && aux->valor.codigo != codigo)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == codigo)
    {
        strcpy(aux->valor.email, novo_email);
        return 0;
    }
    return 1;
}

int buscarEntregadorEmailCPF (Lista_entregadores *l, char *email, char *cpf, entregador *item)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return EMPTY_LIST;

    No_entregador *aux = l->inicio;

    while (aux->prox != NULL && (strcmp(aux->valor.email, email) != 0))
    {
        aux = aux->prox;
    }

    if (strcmp(aux->valor.email, email) != 0) return 1;
    if ((strcmp(aux->valor.email, email) == 0) && (strcmp(aux->valor.cpf, cpf) == 0))
    {
        copiarEntregador(&aux->valor, &(*item));
        return 0;
    }
    return 1;
}

int inserirPedidoHistoricoEntregador (Lista_entregadores *l, int codigo, pedidosE novo_pedido)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return EMPTY_LIST;

    No_entregador *aux = l->inicio;
    int i;

    while ((aux != NULL) && (aux->valor.codigo != codigo))
    {
        aux = aux->prox;
    }
    
    if (aux->valor.codigo == codigo)
    {  
        aux->valor.quant_pedidos++;
        aux->valor.historico = (pedidosE*) realloc (aux->valor.historico, aux->valor.quant_pedidos*sizeof(pedidosE));
        
        aux->valor.historico[aux->valor.quant_pedidos-1].codigo = novo_pedido.codigo;
        aux->valor.historico[aux->valor.quant_pedidos-1].precoTotal = novo_pedido.precoTotal;
        aux->valor.historico[aux->valor.quant_pedidos-1].qtdPed = novo_pedido.qtdPed;
        strcpy(aux->valor.historico[aux->valor.quant_pedidos-1].nome_rest, novo_pedido.nome_rest);

        for (i = 0; i < novo_pedido.qtdPed; i++)
        {
            aux->valor.historico->ped = (pratosE*) realloc (aux->valor.historico->ped, novo_pedido.qtdPed*sizeof(pratosE));
            strcpy(aux->valor.historico[aux->valor.quant_pedidos-1].ped[i].nome, novo_pedido.ped[i].nome);
            strcpy(aux->valor.historico[aux->valor.quant_pedidos-1].ped[i].descricao, novo_pedido.ped[i].descricao);
            aux->valor.historico[aux->valor.quant_pedidos-1].ped[i].preco = novo_pedido.ped[i].preco;
        }
        return 0;
    } 
    return 1;
}

int trocaCodigo (Lista_entregadores *l, int codigo_atual, int *novo_codigo)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return EMPTY_LIST;

    No_entregador *aux = l->inicio;

    while ((aux->prox != NULL) && (aux->valor.codigo != codigo_atual))
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == codigo_atual)
    {
        codigo_atual = sortearCodigoEntregador(l);
        *novo_codigo = codigo_atual;
        aux->valor.codigo = codigo_atual;
        return 0;
    }
    return 1;
}

int trocaEmail (Lista_entregadores *l, int codigo, char *novo_email)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaEntregador(l) == 0) return EMPTY_LIST;

    No_entregador *aux = l->inicio;

    while ((aux->prox != NULL) && (aux->valor.codigo != codigo))
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == codigo)
    {
        strcpy(aux->valor.email, novo_email);
        return 0;
    }
    return 1;
}