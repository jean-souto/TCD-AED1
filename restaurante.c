#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

int listaCheiaRest(Lista_restaurantes *l)
{
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
    no->valor.codigo = sortearCodigoRest(l);
    no->ant = NULL;

    if(listaVaziaRest(l) == 0)
    {
        no->prox = NULL;
    }

    no->prox = l->inicio;
    l->inicio = no;

    return 0;
}

// insere no fim da lista
int inserirFimRest(Lista_restaurantes *l, restaurante item)
{
    if (l == NULL) return NULL_LIST;

    No_restaurante *no = (No_restaurante *)malloc(sizeof(No_restaurante));
    No_restaurante *aux = l->inicio;

    no->valor = item;
    no->valor.codigo = sortearCodigoRest(l);

    if (listaVaziaRest(l) != 0)
    {
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    else
    {
        l->inicio = no;
        no->ant = NULL;
    }

    no->prox = NULL;

    return 0;
}

// insere posição desejada na lista
int inserirPosicao(Lista_restaurantes *l, restaurante item, int pos) //att essa bomba
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return inserirInicioRest(l, item);
    if (pos <= 1)
        return inserirInicioRest(l, item);
    if (pos > tamanhoRest(l))
        return inserirFimRest(l, item);

    No_restaurante *no = l->inicio;
    No_restaurante *noaux = (No_restaurante *)malloc(sizeof(No_restaurante));
    noaux->valor = item;

    int i = 0;
    while (i != pos && no->prox != NULL)
    {
        no = no->prox;
        i++;
        if (i == pos)
        {
            if (no->ant)
                no->ant->prox = noaux;
            noaux->ant = no->ant;
            noaux->prox = no;
            no->ant = noaux;
        }
    }
    return i;
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
int buscarCodigoRest(Lista_restaurantes *l, int codigo, restaurante *item)
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

/*
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
        if (aux->valor.email == 0)
        {
            aux->valor.email = 1;
            copiarRestaurante(&(aux->valor), &(*item));
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}*/

int buscarRestEmailCodigo(Lista_restaurantes *l, char *email, int codigo, restaurante *item) //revisar 
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *aux = l->inicio;

    while (aux->prox != NULL && (strcmp(aux->valor.email, email) != 0))
    {
        aux = aux->prox;
    }

    if ((strcmp(aux->valor.email, email) == 0) && (aux->valor.codigo == codigo))
    {
        copiarRestaurante(&aux->valor, &(*item));
        return 0;
    }
    return 1;
}

// mostra as principais informacoes de cada restaurante para cliente
void mostrarInfoRest(Lista_restaurantes *l)
{
    if (l != NULL)
    {
        printf("---------------------------------------------\n");
        No_restaurante *no = l->inicio;
        while (no != NULL)
        {
            printf("%s\n", no->valor.nome);
            // printf("Codigo: %d\n", no->valor.codigo);
            printf("Categoria: %d\n", no->valor.categoria);

            printf("---------------------------------------------\n");
            no = no->prox;
        }
    }
}

void mostrarRest(Lista_restaurantes *l) // mostra as principais informações de cada restaurante para ADM
{
    if (l != NULL)
    {
        printf("[");

        if (listaVaziaRest(l) != 0)
        {
            No_restaurante *no = l->inicio;

            do
            {
                printf(" {%s, ", no->valor.nome);
                printf("%s, ", no->valor.email);
                printf("%s, ", no->valor.categoria);
                printf("%d, ", no->valor.codigo);
                printf("%d} ", no->valor.status);
                no = no->prox;
            } while (no != NULL);
        }
        printf(" ]\n");
    }
}

int loginRestaurante(Lista_restaurantes * l, char *email, char *senha, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *no = l->inicio;

    while (no->prox != NULL && (strcmp(no->valor.email, email) != 0))
    {
        no = no->prox;
    }

    if ((strcmp(no->valor.email, email) == 0) && (strcmp(no->valor.senha, senha) == 0))
    {
        copiarRestaurante(&no->valor, &(*item));
        return 0;
    }

    return 1;
}

// copia todas as informacoes de um elemento para outro
void copiarRestaurante(restaurante * A, restaurante * B)
{
    strcpy(B->nome, A->nome);
    strcpy(B->email, A->email);
    strcpy(B->senha, A->senha);
    strcpy(B->categoria, A->categoria);
    B->codigo = A->codigo;
    B->status = A->status;
    // copiarRestaurante mennu
    // copiarRestaurante historico
    // copiarRestaurante fila pedidosPendentes
}

int alterarSenhaRest(Lista_restaurantes * l, int codigo, char *novaSenha, char *confirmNovaSenha)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *no = l->inicio;

    while (no != NULL && no->valor.codigo != codigo)
    {
        no = no->prox;
    }

    if (no->valor.codigo == codigo)
    {
        if (strcmp(novaSenha, confirmNovaSenha) == 0)
        {
            strcmp(no->valor.senha, novaSenha);
            return 0;
         }
    }
    return 1;
}

int sortearCodigoRest(Lista_restaurantes *l)
{
    int codigo = 0;
    srand(time(NULL));

    while (codigo == 0)
    {
        codigo = rand() % 9999;
    }

    if (l == NULL || listaVaziaRest(l) == 0)
        return codigo;

    No_restaurante *no = l->inicio;

    while (no->prox != NULL)
    {
        if (codigo == no->valor.codigo)
        {
            codigo = rand() % 9999;
            no = l->inicio;
        }
        no = no->prox;
    }

    return codigo;
}

/*
// função de auxílio. copia todas as informações de um elemento para outro
void copiarRestaurante(restaurante *A, restaurante *B)
{
    int i, j;

    strcpy(B->nome, A->nome);
    strcpy(B->email, A->email);
    strcpy(B->senha, A->senha);
    strcpy(B->categoria, A->categoria);

    B->codigo = A->codigo;
    B->status = A->status;

    B->menu = (pratosR*) malloc(sizeof(pratosR) * )

     B->historico = (pedidosC *)malloc(B->historico, A->quant_pedidos * sizeof(pedidosC));
    for (i = 0; i < A->quant_pedidos; i++)
    {
        B->historico[i].precoTotal = A->historico[i].precoTotal;
        strcpy(B->historico[i].nome_rest, A->historico[i].nome_rest);
        B->historico[i].codigo = A->historico[i].codigo;
        B->historico[i].qtdPed = A->historico[i].qtdPed;

        B->historico[i].ped = (pratosC *)malloc(B->historico[i].ped, A->historico[i].qtdPed * sizeof(pratosC));

        for (j = 0; j < A->historico[i].qtdPed; j++)
        {
            B->historico[i].ped[j].preco = A->historico[i].ped[j].preco;
            strcpy(B->historico[i].ped[j].nome, A->historico[i].ped[j].nome);
            strcpy(B->historico[i].ped[j].descricao, A->historico[i].ped[j].descricao);
        }
    }

    B->enderecos = (endereco *)malloc(B->enderecos, A->quant_enderecos * sizeof(endereco));
    for (i = 0; i < A->quant_enderecos; i++)
    {
        strcpy(B->enderecos[i].cep, A->enderecos[i].cep);
        strcpy(B->enderecos[i].numero, A->enderecos[i].numero);
        strcpy(B->enderecos[i].rua, A->enderecos[i].rua);
    } 
}
*/