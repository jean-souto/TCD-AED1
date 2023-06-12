#include "filaPedidosPendentes.h"
#include "structs.h"

// defines de auxilio
#define NULL_LIST 3
#define EMPTY_LIST 2

typedef struct rest
{
    char nome[40];
    char email[40];
    char senha[15];
    char categoria[30];
    int codigo;
    int status; // se ta aberto ou fechado
    pratos *cardapio;
    int qtdCardapio;
    pedidos *historico;
    int qtdHistorico;
    Fila_PedidosPendentes *pedidosPendentes;
} restaurante;

typedef struct no_restaurante
{
    restaurante valor;
    struct no_restaurante *ant;
    struct no_restaurante *prox;
} No_restaurante;

typedef struct listaR // lista
{
    No_restaurante *inicio;
} Lista_restaurantes;

// criar
Lista_restaurantes *criar_listaRestaurantes(); 
int criar_listaCategoria(Lista_restaurantes *l1, Lista_restaurantes *l2, char *categoria);

// auxiliares
int listaVaziaRest(Lista_restaurantes *l);
int listaCheiaRest(Lista_restaurantes *l);
void limparRest(Lista_restaurantes *l);
int tamanhoRest(Lista_restaurantes *l);

// insercao
int inserirInicioRest(Lista_restaurantes *l, restaurante item);
int inserirFimRest(Lista_restaurantes *l, restaurante *item);   
int inserirPosicaoRest(Lista_restaurantes *l, restaurante item, int pos);
int inserirPratoRest(Lista_restaurantes *l, pratos novoPrato, restaurante item);
int inserirPedidoHistoricoRest(Lista_restaurantes *l, pedidos novoPedido, restaurante *item);
int inserirPedidoHistoricoRestNome (Lista_restaurantes *l, char *nome, pedidos novo_pedido);

// remocao
int removerInicioRest(Lista_restaurantes *l);
int removerFimRest(Lista_restaurantes *l);
int removerPosRest(Lista_restaurantes *l, int pos);
int removerRestCodigo(Lista_restaurantes *l, int codigo);
int removerPratoRest(Lista_restaurantes *l, char *nomePrato, float precoPrato, restaurante *item);

// busca
int buscarRestPos(Lista_restaurantes *l, int pos, restaurante *item);
int buscarRestCodigo(Lista_restaurantes *l, int codigo, restaurante *item);
int buscarRestEmailCodigo(Lista_restaurantes *l, char *email, int codigo, restaurante *item);
int buscarRestNome(Lista_restaurantes *l, char *nome, restaurante *item);
int buscarRestEmail(Lista_restaurantes *l, char *email, restaurante *item);

// visualização usuário
void mostrarRestaurante(restaurante *item); 
void mostrarInfoRest(Lista_restaurantes *l); 
// void mostrarHistoricoPedidos(Lista_restaurantes *l, char *nome);
void mostrarCardapio(Lista_restaurantes *l, restaurante item);
void mostrarHistoricoRest(restaurante item);
void mostrarHistoricoRestPorNomePrato(restaurante *item, char *nomePrato);
void mostrarPedidoPorCodigo(restaurante *item, int codigoPedido);

// visualização ADM
void mostrarListaRest(Lista_restaurantes *l); 

//alteracoes de usuario
int alterarCodigoRest(Lista_restaurantes *l, int codigoAtual, int *novoCodigo);
int alterarSenhaRest(Lista_restaurantes *l, int codigo, char *novaSenha, char *confirmNovaSenha, restaurante *item);
int alterarEmailRest(Lista_restaurantes *l, int codigo, char *novoEmail, restaurante *item);
int alterarCategoria(Lista_restaurantes *l, int codigo, char *categoria, restaurante *item);
int alterarStatusRest(Lista_restaurantes *l, int codigo, int statusAtual, int *novoStatus);

// outros
int loginRestaurante(Lista_restaurantes *l, char *email, char *senha, restaurante *item);

int sortearCodigoRest(Lista_restaurantes *l);
void copiarRestaurante(restaurante *A, restaurante *B);
void limparVariavelRest(restaurante *item);
int buscarPratoRest (Lista_restaurantes *l, int cod_rest, int coord_prato, pratos *novo_prato);
