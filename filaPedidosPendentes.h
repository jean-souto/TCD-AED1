// biblioteca

// STRUCTS
typedef struct plate
{
    char nome[40];
    char descricao[100];
    float preco;
} pratos;

typedef struct ped
{
    int codigo;
    float precoTotal;
    char nome_rest[40];
    pratos *ped; // vetor em que cada elemento eh um prato e juntando todos os pratos que o cliente pediu torna-se o pedido completo
    int qtdPed;  // tamanho do vetor
} pedidos;

typedef struct no_pedidosPendentes
{
    pedidos valor;
    struct no_pedidosPendentes *proximo;
} No_pedidosPendentes;

typedef struct fila
{
    No_pedidosPendentes *inicio;
    No_pedidosPendentes *fim;
    int qtd;
} Fila_PedidosPendentes;

//IMPLEMENTACOES
Fila_PedidosPendentes *criar_filaPedidosPendentes();

int filaVazia(Fila_PedidosPendentes *f);
int filaCheia(Fila_PedidosPendentes *f);

int inserirPedidoPendente(Fila_PedidosPendentes *f, pedidos *x);
int removerPedidoPendente(Fila_PedidosPendentes *f);
int consultarProxPedido(Fila_PedidosPendentes *f, pedidos **x);

void limparFila(Fila_PedidosPendentes *f);
int tamanhoFila(Fila_PedidosPendentes *f);
void mostrarPedidosPendentes(Fila_PedidosPendentes *f);

int mostrarProxPedido(Fila_PedidosPendentes *f);
