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
            inserirFimRest(l2, &no->valor);
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

int inserirPratoRest(Lista_restaurantes *l, pratos novoPrato, restaurante *item)
{
    if (l == NULL)
        return NULL_LIST;

    if (listaVaziaRest(l) == 0)
        return EMPTY_LIST;

    if (buscarRestNome(l, item->nome, item) == 0) // verifica se o nome está na lista
    {
        // verifica se é a primeira inserção e da um malloc.
        if (item->cardapio == NULL)
        {
            item->cardapio = (pratos *)malloc(sizeof(pratos));
        }
        else
        {
            item->cardapio = (pratos *)realloc(item->cardapio, (item->qtdCardapio + 1) * sizeof(pratos));
        }

        if (item->cardapio != NULL)
        {
            item->cardapio[item->qtdCardapio] = novoPrato;
            item->qtdCardapio++;
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
	*item = no->valor;
	//copiarRestaurante(&aux->valor, &(*item));
	
	return 0;
}

void mostrarRestaurante(restaurante *item)
{
    if (item != NULL)
    {
        printf("---------------------------------------------\n");
        printf("%s\n" // colocar em negrito
               "Email: %s\n"                
               "Codigo: %d\n"
               "Categoria: %s\n"
               "Status: %d\n",
               item->nome, item->email, item->codigo, item->categoria, item->status);
        printf("---------------------------------------------\n");
    }
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

    if (buscarRestNome(l, item->nome, item) == 0)
    {

        for (int i = 0; i < item->qtdCardapio; i++)
        {
            printf("%s\n"
                   "%s\n"
                   "%0.2f\n",
                   item->cardapio[i].nome, item->cardapio[i].descricao, item->cardapio[i].preco);
        }
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

/* void mostrarPedidosPorPreco(restaurante *item, float preco, char opcao)
{
    int i,j;

    for (i = 0; i < item->qtdHistorico; i++)
    {
        pedidos pedido = item->historico[i];

        if (opcao == '<' && pedido.precoTotal < preco)
        {
            printf("Código do pedido: %d\n", pedido.codigo);
            printf("Preço total: %.2f\n", pedido.precoTotal);
            printf("Nome do restaurante: %s\n", pedido.nome_rest);

            printf("Pratos:\n");
            for (j = 0; j < pedido.qtdPratosPed; j++)
            {
                pratos prato = pedido.pratosPed[j];
                printf("Nome do prato: %s\n", prato.nome);
                printf("Descrição do prato: %s\n", prato.descricao);
                printf("Preço do prato: %.2f\n", prato.preco);
            }
        }
        else if (opcao == '>' && pedido.precoTotal > preco)
        {
            printf("Código do pedido: %d\n", pedido.codigo);
            printf("Preço total: %.2f\n", pedido.precoTotal);
            printf("Nome do restaurante: %s\n", pedido.nome_rest);

            printf("Pratos:\n");
            for (j = 0; j < pedido.qtdPratosPed; j++)
            {
                pratos prato = pedido.pratosPed[j];
                printf("Nome do prato: %s\n", prato.nome);
                printf("Descrição do prato: %s\n", prato.descricao);
                printf("Preço do prato: %.2f\n", prato.preco);
            }
        }
        else if (opcao == '=' && pedido.precoTotal == preco)
        {
            printf("Código do pedido: %d\n", pedido.codigo);
            printf("Preço total: %.2f\n", pedido.precoTotal);
            printf("Nome do restaurante: %s\n", pedido.nome_rest);

            printf("Pratos:\n");
            for (j = 0; j < pedido.qtdPratosPed; j++)
            {
                pratos prato = pedido.pratosPed[j];
                printf("Nome do prato: %s\n", prato.nome);
                printf("Descrição do prato: %s\n", prato.descricao);
                printf("Preço do prato: %.2f\n", prato.preco);
            }
        }
    }
}
*/

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

    int i, j;

    if (A->qtdCardapio != 0)
    {
        // copiar o cardápio
        B->cardapio = (pratos *)malloc(sizeof(pratos) * A->qtdCardapio);

        for (i = 0; i < A->qtdCardapio; i++)
        {
            printf("20\n"); // ERRO AQUI
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
            printf("40\n"); // ERRO AQUI
            B->historico[i].codigo = A->historico[i].codigo;
            B->historico[i].precoTotal = A->historico[i].precoTotal;
            strcpy(B->historico[i].nome_rest, A->historico[i].nome_rest);
            B->historico[i].qtdPratosPed = A->historico[i].qtdPratosPed;

            // Copiar o vetor de pratos
            B->historico[i].pratosPed = (pratos *)malloc(sizeof(pratos) * A->historico[i].qtdPratosPed);
            for (j = 0; j < A->historico[i].qtdPratosPed; j++)
            {
                printf("50\n"); // ERRO AQUI
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

void salvarListaRest(Lista_restaurantes *l)
{
    FILE *arquivo = fopen("restaurantes.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    No_restaurante *no = l->inicio;

    while (no != NULL)
    {
        fprintf(arquivo, "%s;%s;%s;%s;%d;%d;%s;%s;%f;%d;%d;%f;%s;%s;%s;%f;%d;\n",
                no->valor.nome, no->valor.email, no->valor.senha, no->valor.categoria,
                no->valor.codigo, no->valor.status,
                no->valor.cardapio->nome, no->valor.cardapio->descricao, no->valor.cardapio->preco, no->valor.qtdCardapio,
                no->valor.historico->codigo, no->valor.historico->precoTotal, no->valor.historico->nome_rest,
                no->valor.historico->pratosPed->nome, no->valor.historico->pratosPed->descricao, no->valor.historico->pratosPed->preco, no->valor.historico->qtdPratosPed,
                no->valor.qtdHistorico);
        no = no->prox;
    }

    fclose(arquivo);
}