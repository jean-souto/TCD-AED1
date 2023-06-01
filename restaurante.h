#include "filaPedidosPendentes.h"

// defines de auxilio
#define NULL_LIST 3
#define EMPTY_LIST 2

// structs
typedef struct ped
{
    int codigo;
    float precoTotal;
    char nome_rest[40];
    pratos *ped; // vetor em que cada elemento eh um prato e juntando todos os pratos que o cliente pediu torna-se o pedido completo
    int qtdPed;  // tamanho do vetor
} pedidos;

typedef struct card
{
    char numero[17];
    int cvv;
    char validade[6];
    char tipo[8];
} cartao;

typedef struct client
{
    char nome[40];
    char email[40];
    char cpf[12];
    int senha_6d;
    cartao *pagamentos;
    int quantidade_cartoes;
    pedidos *historico;
    float valor_gasto;
    int quant_pedidos;
} cliente;

typedef struct plate
{
    char nome[40];
    char descricao[100];
    float preco;
} pratos;

typedef struct rest
{
    char nome[40];
    char login[15];
    int senha;
    int codigo;
    char categoria[30];
    pratos *menu;
    pedidos *historico;
    int status; // se quer participar do programa de fidelidade
    Fila_PedidosPendentes *pedidosPendentes;
} restaurante;

typedef struct no_restaurante
{
    restaurante valor;
    struct no_restaurante *ant;
    struct no_restaurante *prox;
} No_restaurante;

typedef struct list // lista
{
    No_restaurante *inicio;
} Lista_restaurantes;

// criar
Lista_restaurantes *criar_listaRestaurantes(); // ok
restaurante *criar_restaurante(char *nome, char *login, int senha, int codigo, char *categoria, pratos *menu, pedidos *historico, int status, Fila_PedidosPendentes *f);
int criar_listaCategoria(Lista_restaurantes *l1, Lista_restaurantes *l2, char *categoria); // ok

// auxiliares
int listaVazia(Lista_restaurantes *l); // ok
int limpar(Lista_restaurantes *l);
int tamanho(Lista_restaurantes *l);

// insercao
int inserirInicioRestaurante(Lista_restaurantes *l, restaurante item); // ok
int inserirFimRestaurante(Lista_restaurantes *l, restaurante item);    // ok

// remocao
int removerInicio(Lista_restaurantes *l);
int removerFim(Lista_restaurantes *l);
int removerPosicao(Lista_restaurantes *l, int pos);
int removerRestaurante(Lista_restaurantes *l, int codigo);

// mostrar opcao do menuCliente
int buscarNome(Lista_restaurantes *l, restaurante *nome);
void mostrarCategoria(Lista_restaurantes *l);
void mostrarRestaurantes(Lista_restaurantes *l); // fer

// mostrar opcao do menuFuncionario
void mostrarHistoricoPedidos();
void mostrarPedidosPendentes(); // alice
int atualizarMenu();
int login();

