#include "filaPedidosPendentes.h"

// defines de auxilio
#define NULL_LIST 3
#define EMPTY_LIST 2

// structs

typedef struct plateR
{
    char nome[40];
    char descricao[100];
    float preco;
} pratosR;

typedef struct pedR
{
    int codigo;
    float precoTotal;
    char nome_rest[40];
    pratosR *ped; // vetor em que cada elemento eh um prato e juntando todos os pratos que o cliente pediu torna-se o pedido completo
    int qtdPed;  // tamanho do vetor
} pedidosR;

typedef struct rest
{
    char nome[40];
    char email[40];
    char senha[15];
    char categoria[30];
    int codigo;
    int status; // se quer participar do programa de fidelidade
    pratosR *menu;
    pedidosR *historico;
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
Lista_restaurantes *criar_listaRestaurantes(); // ok
//restaurante *criar_restaurante(char *nome, char *login, int senha, int codigo, char *categoria, pratosR *menu, pedidos *historico, int status, Fila_PedidosPendentes *f);
int criar_listaCategoria(Lista_restaurantes *l1, Lista_restaurantes *l2, char *categoria); // ok

// auxiliares
int listaVaziaRest(Lista_restaurantes *l); // ok
int listaCheiaRest(Lista_restaurantes *l);
void limparRest(Lista_restaurantes *l);
int tamanhoRest(Lista_restaurantes *l);

// insercao
int inserirInicioRest(Lista_restaurantes *l, restaurante item); // ok
int inserirFimRest(Lista_restaurantes *l, restaurante item);    // ok
int inserirPosicao(Lista_restaurantes *l, restaurante item, int pos);

// remocao
int removerInicioRest(Lista_restaurantes *l);
int removerFimRest(Lista_restaurantes *l);
int removerPosRest(Lista_restaurantes *l, int pos);
int removerRest(Lista_restaurantes *l, int codigo);

// busca
int buscarCodigoRest(Lista_restaurantes *l, int codigo, restaurante *item);
int buscarRestaurante(Lista_restaurantes *l, restaurante *item);
int buscarRestEmailCodigo(Lista_restaurantes *l, char *email, int codigo, restaurante *item);
// int buscarNome(Lista_restaurantes *l, restaurante *nome);


// visualização cliente
// void mostrarCategoria(Lista_restaurantes *l);
// void mostrarRestaurantes(Lista_restaurantes *l); // fer
void mostrarInfoRest(Lista_restaurantes *l); 

// visualização funcionário
// void mostrarHistoricoPedidos();
// void mostrarPedidosPendentes(); // alice
// int atualizarMenu();

// visualização ADM
void mostrarRest(Lista_restaurantes *l);

// outros
int loginRestaurante(Lista_restaurantes *l, char *email, char *senha, restaurante *item);
void copiarRestaurante(restaurante *A, restaurante *B);
int alterarSenhaRest(Lista_restaurantes *l, int codigo, char *novaSenha, char *confirmNovaSenha);
int sortearCodigoRest(Lista_restaurantes *l);