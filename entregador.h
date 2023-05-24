// defines de auxilio
#define NULL_LIST 3
#define EMPTY_LIST 2

//structs
typedef struct ranking // para garantir o bom funcionamento da nota do entregador
{
    int quantidade;
    float total;
    float media;
}nota;

typedef struct motoboy // o proprio motoboy
{
    char nome[40];
    char cpf[12];
    char email[40];
    int codigo;
    int status;
    nota rank;
    int corridas;
}entregador;

typedef struct No_motoboy // no
{
    entregador valor;
    struct No_motoboy *prox;
    struct No_motoboy *ant;
}No_entregador;

typedef struct list // lista
{
    No_entregador *inicio;
}Lista_entregadores;

//basicas
Lista_entregadores* criar_lista_entregadores (); // ok
int listaVazia (Lista_entregadores *l); // ok 
int sortearCodigoEntregador (Lista_entregadores *l); // ok

//inserção
int inserirInicioEntregador (Lista_entregadores *l, entregador item); // ok
int inserirFimEntregador (Lista_entregadores *l, entregador item); // ok

//remoção
int removerInicioEntregador (Lista_entregadores *l); // ok
int removerFimEntregador (Lista_entregadores *l); // ok
int removerPosiEntregador (Lista_entregadores *l, int pos); // ok
int removerItemEntregador (Lista_entregadores *l, int codigo); // ok

//auxiliares 1
int buscarItemEntregador (Lista_entregadores *l, int codigo, entregador *item); // ok
int buscarEntregador (Lista_entregadores *l, entregador *item); // ok
int liberarEntregador (Lista_entregadores *l, int codigo); // ok 
int ocuparEntregador (Lista_entregadores *l, int codigo); // desnecessario, mas ok
int adicionarCorridaNota (Lista_entregadores *l, int codigo, float nota); // ok
int inicializar_entregador (entregador *item); // ok

//auxiliares 2
int limparEntregador (Lista_entregadores *l); // ok
int tamanhoEntregador (Lista_entregadores *l); // ok
void mostrar_entregador (Lista_entregadores *l); // ok
void mostrar_tudo_entregador (Lista_entregadores *l); // ok
void copiarEntregador (entregador *A, entregador *B); // ok