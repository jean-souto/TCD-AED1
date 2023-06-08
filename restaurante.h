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
Lista_restaurantes *criar_listaRestaurantes(); 
int criar_listaCategoria(Lista_restaurantes *l1, Lista_restaurantes *l2, char *categoria);

// auxiliares
int listaVaziaRest(Lista_restaurantes *l);
int listaCheiaRest(Lista_restaurantes *l);
void limparRest(Lista_restaurantes *l);
int tamanhoRest(Lista_restaurantes *l);

// insercao
int inserirInicioRest(Lista_restaurantes *l, restaurante item);
int inserirFimRest(Lista_restaurantes *l, restaurante item);   
int inserirPosicaoRest(Lista_restaurantes *l, restaurante item, int pos);

// remocao
int removerInicioRest(Lista_restaurantes *l);
int removerFimRest(Lista_restaurantes *l);
int removerPosRest(Lista_restaurantes *l, int pos);
int removerRestCodigo(Lista_restaurantes *l, int codigo);

// busca
int buscarRestCodigo(Lista_restaurantes *l, int codigo, restaurante *item);
int buscarRestEmailCodigo(Lista_restaurantes *l, char *email, int codigo, restaurante *item);
int buscarRestNome(Lista_restaurantes *l, char *nome);
//int buscarRestPos(Lista_restaurantes *l, int pos, restaurante *item);


// visualização cliente
// void mostrarRestaurantes(Lista_restaurantes *l); 
void mostrarInfoRest(Lista_restaurantes *l); 

// visualização funcionário
// void mostrarHistoricoPedidos(Lista_restaurantes *l, char *nome);

// visualização ADM
void mostrarListaRest(Lista_restaurantes *l); 

// outros
int loginRestaurante(Lista_restaurantes *l, char *email, char *senha, restaurante *item);
int alterarSenhaRest(Lista_restaurantes *l, int codigo, char *novaSenha, char *confirmNovaSenha);
// int alterarEmailRest(Lista_restaurantes *l, int codigo, char *novoEmail, char *confirmNovoEmail);
int sortearCodigoRest(Lista_restaurantes *l);
void copiarRestaurante(restaurante *A, restaurante *B);