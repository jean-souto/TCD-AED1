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

    while (no != NULL)
    {
        if (strcmp(no->valor.categoria, categoria) == 0)
        {
            inserirFimRest(l2, &no->valor);
        }
        no = no->prox;
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

    item.codigo = sortearCodigoRest(l);
    no->valor = item;
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
int inserirFimRest(Lista_restaurantes *l, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;

    No_restaurante *no = (No_restaurante *)malloc(sizeof(No_restaurante));
    No_restaurante *aux = l->inicio;

    item->codigo = sortearCodigoRest(l);
    no->valor = *item;
    no->prox = NULL;

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
        return inserirFimRest(l, &item);

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

int inserirPratoRest(Lista_restaurantes *l, pratos novoPrato, restaurante item)
{
    if (l == NULL)
        return NULL_LIST;

    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *aux = l->inicio;

    while (aux != NULL && aux->valor.codigo != item.codigo)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == item.codigo)
    { 
        // verifica se é a primeira inserção e da um malloc.
        if (aux->valor.cardapio == NULL)
        {
            aux->valor.cardapio = (pratos *)malloc(sizeof(pratos));
        }
        else
        {
            aux->valor.cardapio = (pratos *)realloc(aux->valor.cardapio, (aux->valor.qtdCardapio + 1) * sizeof(pratos));
        }

        if (aux->valor.cardapio != NULL)
        {
            aux->valor.cardapio[aux->valor.qtdCardapio] = novoPrato;
            aux->valor.qtdCardapio++;
            return 0;
        }
    }

    return 1;
}

int inserirPedidoHistoricoRest(Lista_restaurantes *l, pedidos novoPedido, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;

    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    if (buscarRestNome(l, item->nome, item) == 0) // verifica se o nome está na lista
    {
        // verifica se é a primeira inserção e da um malloc.
        if (item->historico == NULL)
        {
            item->historico = (pedidos *)malloc(sizeof(pedidos));
        }
        else
        {
            item->historico = (pedidos *)realloc(item->historico, (item->qtdHistorico + 1) * sizeof(pedidos));
        }

        if (item->historico != NULL)
        {
            item->historico[item->qtdHistorico] = novoPedido;
            item->qtdHistorico++;
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

    if (no->prox == NULL)
    {
        l->inicio = NULL;
    }
    else
    {
        l->inicio = no->prox;
        no->prox->ant = NULL;
    }

    free(no->valor.cardapio);
    for (int i = 0; i < no->valor.qtdHistorico; i++)
    {
        free(no->valor.historico[i].pratosPed);
    }
    free(no->valor.historico);
    limparFila(no->valor.pedidosPendentes);
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

    No_restaurante *no = l->inicio;
    while (no->prox != NULL)
    {
        no = no->prox;
    }

    if (l->inicio->prox != NULL)
        no->ant->prox = NULL;
    else
        l->inicio = NULL;

    free(no->valor.cardapio);
    for (int i = 0; i < no->valor.qtdHistorico; i++)
    {
        free(no->valor.historico[i].pratosPed);
    }
    free(no->valor.historico);
    limparFila(no->valor.pedidosPendentes);
    free(no);

    return 0;
}

// remove uma posicao X da lista, se pos >= tamanho da lista ela remove o ultimo elemento
int removerPosRest(Lista_restaurantes *l, int pos)
{
    if (l == NULL)
        return NULL_LIST;

    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

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

    No_restaurante *no = l->inicio;

    while (pos > 0)
    {
        no = no->prox;
        pos--;
    }

    no->prox->ant = no->ant;
    no->ant->prox = no->prox;

    free(no->valor.cardapio);
    for (int i = 0; i < no->valor.qtdHistorico; i++)
    {
        free(no->valor.historico[i].pratosPed);
    }
    free(no->valor.historico);
    limparFila(no->valor.pedidosPendentes);
    free(no);

    return 0;
}

// remove o item correspondente ao codigo passado
int removerRestCodigo(Lista_restaurantes *l, int codigo)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *no = l->inicio;

    int pos = 0;

    while ((no != NULL) && (no->valor.codigo != codigo))
    {
        pos++;
        no = no->prox;
    }

    if (no->valor.codigo == codigo)
    {
        removerPosRest(l, pos);
        return 0;
    }
    return 1;
}

int removerPratoRest(Lista_restaurantes *l, char *nomePrato, float precoPrato, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        EMPTY_LIST;

    if (buscarRestNome(l, item->nome, item) == 0)
    {
        for (int i = 0; i < item->qtdCardapio; i++)
        {
            if (strcmp(item->cardapio[i].nome, nomePrato) == 0 && item->cardapio[i].preco == precoPrato)
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

int buscarRestPos(Lista_restaurantes *l, int pos, restaurante *item)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaRest(l) == 0) return EMPTY_LIST;

    No_restaurante *aux = l->inicio;

    if (pos == 0) 
    {
        copiarRestaurante(&(aux->valor), &(*item));
        return 0;
    }
    if (pos > tamanhoRest(l)-1)
    {
        return 1;
    }

    while (pos > 0)
    {
        aux = aux->prox;
        pos--;
    }

    copiarRestaurante(&(aux->valor), &(*item));
    return 0;
}

int buscarRestCodigo(Lista_restaurantes *l, int codigo, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0) 
        return EMPTY_LIST;

    No_restaurante *no = l->inicio;

    while (no != NULL)
    {
        if (no->valor.codigo == codigo) 
        {
            copiarRestaurante(&no->valor, item);
            return 0;
        }
        
        no = no->prox;
    }

    return 1;
}

int buscarRestEmailCodigo(Lista_restaurantes *l, char *email, int codigo, restaurante *item) // revisar
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    if (buscarRestEmail(l, email, item) == 0)
    {
        if (item->codigo == codigo)
        {
            return 0;
        }
    }
    
    return 1;
}

int buscarRestNome(Lista_restaurantes *l, char *nome, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;
    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *no = l->inicio;

    while (strcmp(no->valor.nome, nome) != 0) //enquanto nao encontro
    {
        if(no->prox == NULL) //se o proximo for nulo morre
        	return 1;
        		
        no = no->prox; //se nao segue
    }

    //*item = no->valor;
    copiarRestaurante(&no->valor, &(*item));

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
	copiarRestaurante(&no->valor, &(*item));
	
	return 0;
}

//mostrar restaurante para restaurante
void mostrarRestaurante(restaurante *item)
{
    if (item != NULL)
    {
        printf("---------------------------------------------\n");
        printf("%s\n" // colocar em negrito
               "Email: %s\n"                
               "Codigo: %d\n"
               "Categoria: %s\n",
               item->nome, item->email, item->codigo, item->categoria);

        if (item->status == 1)
            printf("Status: Restaurante aberto\n");
        else
            printf("Status: Restaurante fechado\n");
        printf("---------------------------------------------\n");
    }
}

void mostrarInfoRest(Lista_restaurantes *l)
{
    if (l != NULL)
    {
        printf("---------------------------------------------\n");
        No_restaurante *no = l->inicio;
        while (no != NULL)
        {
            printf("%s\n", no->valor.nome);
            printf("Categoria: %s\n", no->valor.categoria);
            if (no->valor.status == 1)
                printf("Status: Restaurante aberto\n");
            else
                printf("Status: Restaurante fechado\n");
            printf("---------------------------------------------\n");
            no = no->prox;
        }
    }
}

void mostrarCardapio(Lista_restaurantes *l, restaurante item)
{
    No_restaurante *aux = l->inicio;
    int i;

    while (aux != NULL && aux->valor.codigo != item.codigo)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == item.codigo)
    {
        printf ("( ");
        for (i = 0; i < aux->valor.qtdCardapio; i++)
        {
            printf ("%d. {Nome do prato: %s / Descricao: %s / Valor: %.2f} ", i+1, aux->valor.cardapio[i].nome, aux->valor.cardapio[i].descricao, aux->valor.cardapio[i].preco);
        }
        printf (")");
    }
}

void mostrarHistoricoRest(restaurante item)
{
    int i, j;

    printf(" ( ");
    for (i = 0; i < item.qtdHistorico; i++)
    {
        printf("[%d, ", item.historico->codigo);
        printf("%s, ", item.historico->nome_rest);
        printf("%.2f /", item.historico->precoTotal);

        for (j = 0; j < item.historico->qtdPratosPed; j++)
        {
            printf(" %s, ", item.historico->pratosPed[j].nome);
            printf("%.2f /", item.historico->pratosPed[j].preco);
        }
        printf("] ");
    }
    printf(") ");
}

void mostrarHistoricoRestPorNomePrato(restaurante *item, char *nomePrato)
{
    int i, j;

    for (i = 0; i < item->qtdHistorico; i++)
    {
        pedidos pedido = item->historico[i];

        for (j = 0; j < pedido.qtdPratosPed; j++)
        {
            pratos prato = pedido.pratosPed[j];
            if (strcmp(prato.nome, nomePrato) == 0)
            {
                printf("Codigo do pedido: %d\n", pedido.codigo);
                printf("Nome do prato: %s\n", prato.nome);
                printf("Descricao do prato: %s\n", prato.descricao);
                printf("Preco do prato: %.2f\n\n", prato.preco);
            }
        }
    }
}

void mostrarPedidoPorCodigo(restaurante *item, int codigoPedido)
{
    int i, j;
    for (i = 0; i < item->qtdHistorico; i++)
    {
        pedidos pedido = item->historico[i];

        if (pedido.codigo == codigoPedido)
        {
            printf("Preco total: %.2f\n", pedido.precoTotal);
            printf("Nome do restaurante: %s\n", pedido.nome_rest);
            printf("Pratos:\n");
            for (j = 0; j < pedido.qtdPratosPed; j++)
            {
                pratos prato = pedido.pratosPed[j];
                printf("Nome do prato: %s\n", prato.nome);
                printf("Descrição do prato: %s\n", prato.descricao);
                printf("Preço do prato: %.2f\n", prato.preco);
            }
        } else
            printf("Nenhum pedido encontrado com o código %d\n", codigoPedido);
    }
}

// mostra as principais informações de cada restaurante para ADM
void mostrarListaRest(Lista_restaurantes *l)
{
    int i = 1;
    if (l != NULL)
    {
        printf("[");

        if (listaVaziaRest(l) != 0)
        {
            No_restaurante *no = l->inicio;

            do
            {
                printf("%d. {%s, ", i, no->valor.nome);
                printf("%s, ", no->valor.email);
                printf("%s, ", no->valor.categoria);
                printf("%d, ", no->valor.codigo);
                printf("%d} ", no->valor.status);
                no = no->prox;
                i++;
            } while (no != NULL);
        }
        printf(" ]\n");
    }
}

int alterarCodigoRest(Lista_restaurantes *l, int codigoAtual, int *novoCodigo)
{
    if (l == NULL)
        return NULL_LIST;

    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *no = l->inicio;

    while ((no != NULL) && (no->valor.codigo != codigoAtual))
    {
        no = no->prox;
    }

    if (no->valor.codigo == codigoAtual)
    {
        codigoAtual = sortearCodigoRest(l);
        *novoCodigo = codigoAtual;
        no->valor.codigo = codigoAtual;
        return 0;
    }
    
    return 1;
}

int alterarSenhaRest(Lista_restaurantes *l, int codigo, char *novaSenha, char *confirmNovaSenha, restaurante *item)
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
            *item = no->valor;
            return 0;
        }
    }
    return 1;
}

int alterarEmailRest(Lista_restaurantes *l, int codigo, char *novoEmail, restaurante *item)
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
        strcpy(no->valor.email, novoEmail);
        *item = no->valor;
        return 0;
    }

    return 1;
}

int alterarCategoria(Lista_restaurantes *l, int codigo, char *categoria, restaurante *item)
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
        strcpy(no->valor.categoria, categoria);
        *item = no->valor;
        return 0;
    }

    return 1;
}

int alterarStatusRest(Lista_restaurantes *l, int codigo, int statusAtual, int *novoStatus)
{
    if (l == NULL)
        return NULL_LIST;

    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    No_restaurante *no = l->inicio;

    while ((no != NULL) && (no->valor.codigo != codigo))
    {
        no = no->prox;
    }

    if (no->valor.codigo == codigo)
    {
        no->valor.status = statusAtual;
        *novoStatus = statusAtual;
        return 0;
    }

    return 1;
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

    limparVariavelRest(item);

    return 1;
}

int sortearCodigoRest(Lista_restaurantes *l)
{
    int codigo = 0;

    if (l == NULL)
        return codigo;

    srand(time(NULL));
    codigo = rand() % 9999 + 1; // Adiciona 1 para evitar código 0

    if (listaVaziaRest(l) == 0)
        return codigo;
    
    No_restaurante *no = l->inicio;

    while (no != NULL) // Altera a condição do loop para verificar o final da lista
    {
        if (codigo == no->valor.codigo)
        {
            codigo = rand() % 9999 + 1; // Gera novo código diferente do existente
            no = l->inicio;             // Reinicia a verificação desde o início da lista
        }
        else
        {
            no = no->prox; // Avança para o próximo nó na lista
        }
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
    B->qtdCardapio = A->qtdCardapio;
    B->qtdHistorico = A->qtdHistorico;

    int i, j;

    if (A->qtdCardapio != 0)
    {
        B->cardapio = (pratos *)malloc(sizeof(pratos) * A->qtdCardapio);

        for (i = 0; i < A->qtdCardapio; i++)
        {
            strcpy(B->cardapio[i].nome, A->cardapio[i].nome);
            strcpy(B->cardapio[i].descricao, A->cardapio[i].descricao);
            B->cardapio[i].preco = A->cardapio[i].preco;
        }
    }

    if (A->qtdHistorico != 0)
    {
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
    }

    // Copiar a fila de pedidos pendentes 
    B->pedidosPendentes = criar_filaPedidosPendentes();
    copiarFilaPedidosPendentes(A->pedidosPendentes, B->pedidosPendentes);
}

void limparVariavelRest(restaurante *item)
{
    strcpy(item->nome, "-");
    strcpy(item->email, "-");
    strcpy(item->senha, "-");
    strcpy(item->categoria, "-");
    item->cardapio = NULL;
    item->qtdCardapio = 0;
    item->historico = NULL;
    item->qtdHistorico = 0;
    item->status = -1;
    item->pedidosPendentes = NULL;
}

int buscarPratoRest (Lista_restaurantes *l, int cod_rest, int coord_prato, pratos *novo_prato)
{
    No_restaurante *aux = l->inicio;

    while (aux != NULL && aux->valor.codigo != cod_rest)
    {
        aux = aux->prox;
    }

    if (aux->valor.codigo == cod_rest)
    {
        novo_prato->preco = aux->valor.cardapio[coord_prato].preco;
        strcpy (novo_prato->nome, aux->valor.cardapio[coord_prato].nome);
        strcpy (novo_prato->descricao, aux->valor.cardapio[coord_prato].descricao);
        return 0;
    }
    return 1;
}

int inserirPedidoHistoricoRestNome (Lista_restaurantes *l, char *nome, pedidos novo_pedido)
{
    if (l == NULL) return NULL_LIST;
    if (listaVaziaRest(l) == 0) return EMPTY_LIST;

    No_restaurante *aux = l->inicio;
    int i;

    while ((aux != NULL) && (strcmp(aux->valor.nome, nome) != 0))
    {
        aux = aux->prox;
    }
    
    if (strcmp(aux->valor.nome, nome) == 0)
    {  
        aux->valor.qtdHistorico++;
        aux->valor.historico = (pedidos*) realloc (aux->valor.historico, aux->valor.qtdHistorico*sizeof(pedidos));

        aux->valor.historico[aux->valor.qtdHistorico-1].codigo = novo_pedido.codigo;
        aux->valor.historico[aux->valor.qtdHistorico-1].precoTotal = novo_pedido.precoTotal;
        aux->valor.historico[aux->valor.qtdHistorico-1].qtdPratosPed = novo_pedido.qtdPratosPed;
        strcpy(aux->valor.historico[aux->valor.qtdHistorico-1].nome_rest, novo_pedido.nome_rest);

        aux->valor.historico[aux->valor.qtdHistorico-1].pratosPed = (pratos*) malloc (novo_pedido.qtdPratosPed*sizeof(pratos));

        for (i = 0; i < novo_pedido.qtdPratosPed; i++)
        {
            strcpy(aux->valor.historico[aux->valor.qtdHistorico-1].pratosPed[i].nome, novo_pedido.pratosPed[i].nome);
            strcpy(aux->valor.historico[aux->valor.qtdHistorico-1].pratosPed[i].descricao, novo_pedido.pratosPed[i].descricao);
            aux->valor.historico[aux->valor.qtdHistorico-1].pratosPed[i].preco = novo_pedido.pratosPed[i].preco;
        }
        return 0;
    } 
    return 1;
}

