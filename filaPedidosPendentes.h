// biblioteca

typedef struct ped pedidos;
typedef struct no_pedidosPendentes No_pedidosPendentes;
typedef struct fila Fila_PedidosPendentes;

Fila_PedidosPendentes *criarFilaP();

int filaVaziaP(Fila_PedidosPendentes *f);
int filaCheiaP(Fila_PedidosPendentes *f);

int inserirP(Fila_PedidosPendentes *f, pedidos *x);
int removerP(Fila_PedidosPendentes *f);
int consultarP(Fila_PedidosPendentes *f, pedidos **x);

void limparP(Fila_PedidosPendentes *f);
int tamanhoP(Fila_PedidosPendentes *f);
void mostrarP(Fila_PedidosPendentes *f);

int mostrarProxP(Fila_PedidosPendentes *f);
