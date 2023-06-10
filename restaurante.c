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

    if (listaVaziaRest(l) == 0)
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
    if (l == NULL)
        return NULL_LIST;

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
int inserirPosicaoRest(Lista_restaurantes *l, restaurante item, int pos) // att essa bomba
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

int inserirPratoRest(Lista_restaurantes *l, pratos novoPrato, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        EMPTY_LIST;

    if (buscarRestNome(l, item->nome) == 0)
    {
    	//verificar se e a 1a insercao e dar um malloc.
        item->cardapio = (pratos *)realloc(item->cardapio, (item->qtdCardapio + 1) * sizeof(pratos));

        if (item->cardapio != NULL)
        {
            item->cardapio[item->qtdCardapio] = novoPrato;
            item->qtdCardapio++;
            return 0;
        }
    }
    return 1;
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
int removerRestCodigo(Lista_restaurantes *l, int codigo)
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

int removerPratoRest(Lista_restaurantes *l, char *nomePrato, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        EMPTY_LIST;

    if (buscarRestNome(l, item->nome) == 0)
    {
        for (int i = 0; i < item->qtdCardapio; i++)
        {
            if (strcmp(item->cardapio[i].nome, nomePrato) == 0)
            {
                // Deslocar os pratos restantes para sobrepor o que deseja ser removido
                for (int j = i; j < item->qtdCardapio - 1; j++)
                {
                    item->cardapio[j] = item->cardapio[j + 1];
                }

                item->cardapio = (pratos *)realloc(item->cardapio, (item->qtdCardapio - 1) * sizeof(pratos));
                (item->qtdCardapio)--;

                return 0;
            }
        }
    }

    return 1;
}

// busca o restaurante correspondente ao codigo e retorna ele por parametro
int buscarRestCodigo(Lista_restaurantes *l, int codigo, restaurante *item)
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

    return 1;
}

int buscarRestEmailCodigo(Lista_restaurantes *l, char *email, int codigo, restaurante *item) // revisar
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

    if ((strcmp(no->valor.email, email) == 0) && (no->valor.codigo == codigo))
    {
        copiarRestaurante(&no->valor, &(*item));
        return 0;
    }
    return 1;
}

int buscarRestNome(Lista_restaurantes *l, char *nome) //adicionar retorno por referencia do restaurante
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *no = l->inicio;

    while (strcmp(no->valor.nome, nome)) //enquanto nao encontro
        {
        	if(no->prox == NULL) //se o proximo for nulo morre
        		return 1;
        		
            no = no->prox; //se nao segue
        }

    return 0;
}

int buscarRestEmail(Lista_restaurantes *l, char *email, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *no = l->inicio;

    while (strcmp(no->valor.email, email)) //enquanto nao encontro
    {
    	if(no->prox == NULL) //se o proximo for nulo morre
    		return 1;
    		
        no = no->prox; //se nao segue
    }
    
	//chegou aqui de fora deu certo
	//*item = no->valor;
	//copiarRestaurante(&aux->valor, &(*item));
	
	return 0;
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
            printf("Codigo: %d\n", no->valor.codigo);
            printf("Categoria: %s\n", no->valor.categoria);
            printf("---------------------------------------------\n");
            no = no->prox;
        }
    }
}

void mostrarCardapio(Lista_restaurantes *l, restaurante *item)
{

    if (buscarRestNome(l, item->nome) == 0)
    {
        printf("[ Cardapio ]");

        for (int i = 0; i < item->qtdCardapio; i++)
        {
            printf("%s\n"
                   "%s\n"
                   "%0.2f\n",
                   item->cardapio->nome, item->cardapio->descricao, item->cardapio->preco);
        }
    }
}

// mostra as principais informações de cada restaurante para ADM
void mostrarListaRest(Lista_restaurantes *l)
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

int loginRestaurante(Lista_restaurantes *l, char *email, char *senha, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;
	
    int retorno = buscarRestEmail(l, email, item);

    if (retorno == 0 && strcmp(item->senha,senha) == 0)	{
    	return 0;
	}
	
	//limpar o item
    return 1;
}

int alterarSenhaRest(Lista_restaurantes *l, int codigo, char *novaSenha, char *confirmNovaSenha)
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
            strcpy(no->valor.senha, novaSenha);
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

// copia todas as informacoes de um elemento para outro
void copiarRestaurante(restaurante *A, restaurante *B)
{
    strcpy(B->nome, A->nome);
    strcpy(B->email, A->email);
    strcpy(B->senha, A->senha);
    strcpy(B->categoria, A->categoria);
    B->codigo = A->codigo;
    B->status = A->status;

    int i, j;

    // copiar o cardápio
    B->cardapio = (pratos *)malloc(sizeof(pratos) * A->qtdCardapio);
    for (i = 0; i < A->qtdCardapio; i++)
    {
        strcpy(B->cardapio[i].nome, A->cardapio[i].nome);
        strcpy(B->cardapio[i].descricao, A->cardapio[i].descricao);
        B->cardapio[i].preco = A->cardapio[i].preco;
    }
    
    // copiar o histórico de pedidos
    B->historico = (pedidos *)malloc(sizeof(pedidos) * A->qtdHistorico);
    for (i = 0; i < A->qtdHistorico; i++)
    {
        B->historico[i].codigo = A->historico[i].codigo;
        B->historico[i].precoTotal = A->historico[i].precoTotal;
        strcpy(B->historico[i].nome_rest, A->historico[i].nome_rest);
        B->historico[i].qtdPratosPed = A->historico[i].qtdPratosPed;

        // Copiar o vetor de pratos
        B->historico[i].pratosPed = (pratos *)malloc(sizeof(pratos) * A->historico[i].qtdPratosPed);
        for (j = 0; j < A->historico[i].qtdPratosPed; j++)
        {
            strcpy(B->historico[i].pratosPed[j].nome, A->historico[i].pratosPed[j].nome);
            strcpy(B->historico[i].pratosPed[j].descricao, A->historico[i].pratosPed[j].descricao);
            B->historico[i].pratosPed[j].preco = A->historico[i].pratosPed[j].preco;
        }
    }

    // Copiar a fila de pedidos pendentes
    B->pedidosPendentes = criar_filaPedidosPendentes();
    copiarFilaPedidosPendentes(A->pedidosPendentes, B->pedidosPendentes);
}
