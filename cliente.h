#include "structs.h"

#define NULL_LIST 3
#define EMPTY_LIST 2

typedef struct card
{
	char numero[17];
	int cvv;
	char validade[6];
	char tipo[8];
}cartao;

typedef struct end
{
    char cep[10];
    char rua[40];
    char numero[10];
}endereco;

typedef struct cliente
{
    char nome[40];
    char email[40];
    char cpf[12];
    char senha_8d[15];
    int codigo;
    cartao *pagamentos;
    int quantidade_cartoes;
    pedidos *historico; // aqui
    int quant_pedidos;
    float gasto_total;
    endereco *enderecos;
    int quant_enderecos;
}Cliente;

typedef struct no_client
{
    Cliente valor;
    struct no_client *ant;
    struct no_client *prox;
}No_cliente;

typedef struct lista
{
    No_cliente *inicio;
}Lista_cliente;

Lista_cliente *criarCliente (); // função criação

// inserções
int inserirInicioCliente (Lista_cliente *l, Cliente item); // insere no inicio da lista
int inserirFimCliente (Lista_cliente *l, Cliente item); // insere no fim da lista
int inserirCartaoCliente (Lista_cliente *l, int codigo, cartao novo_cartao);
int inserirPedidoHistorico (Lista_cliente *l, int codigo, pedidos novo_pedido);
int inserirEnderecoCliente (Lista_cliente *l, int codigo, endereco novo_end);

// remoções
int removerInicioCliente (Lista_cliente *l); // remove no inicio da lista
int removerFimCliente (Lista_cliente *l); // remove no fim da lista
int removerPosiCliente (Lista_cliente *l, int pos); // remove uma posicao X da lista, se pos >= tamanho da lista ela remove o último elemento
int removerItemCliente (Lista_cliente *l, int codigo); // remove o item correspondente ao código passado 
int removerCartaoCliente (Lista_cliente *l, int codigo, int posicao);
int removerEnderecoCliente (Lista_cliente *l, int codigo, int posicao);

// auxiliares
int listaVaziaCliente (Lista_cliente *l);
int sortearCodigoCliente (Lista_cliente *l);
int limparCliente (Lista_cliente *l); // limpa a lista
int tamanhoCliente (Lista_cliente *l); // retorna o tamanho da lista 

//auxiliares 2 (voids)
void mostrar_cliente (Lista_cliente *l); // mostra as principais informações de cada entregador
void mostrar_pagamentos (Cliente item);
void mostrar_pedidos (Cliente item);
void mostrar_tudo_cliente (Lista_cliente *l); // mostra TODAS as informações do entregador
void mostrar_enderecos (Cliente item);
void copiarCliente (Cliente *A, Cliente *B); // função de auxílio. copia todas as informações de um elemento para outro

// alterações
int alterarSenha (Lista_cliente *l, int codigo, char *nova_senha1, char *nova_senha2);
int alterarEmail (Lista_cliente *l, int codigo, char *novo_email);

//busca
int loginCliente (Lista_cliente *l, char *email, char *senha, Cliente *item);
int buscarItemCliente (Lista_cliente *l, int codigo, Cliente *item); // busca o entregador correspondente ao codigo e retorna ele por parametro
int buscarClienteEmailCPF (Lista_cliente *l, char *email, char *cpf, Cliente *item);