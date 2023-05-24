#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "entregador.h"
#include "cliente.h"

int main ()
{
    Lista_cliente *l_clientes;
    Cliente item;
    cartao item_cartao;
    hist_pedidosClientes pedido_historico;

    l_clientes = criar();

    item.codigo = 1598;
    strcpy(item.cpf, "12345678999");
    inicializar_cliente(&item);
    strcpy(item.email, "asdfgh@gmail.com");
    strcpy(item.nome, "Alan");
    strcpy(item.senha_8d, "asdfgh");

    inserirFimCliente(l_clientes, item);
    mostrar_cliente(l_clientes);

    item.codigo = 147;
    strcpy(item.cpf, "12345678999");
    inicializar_cliente(&item);
    strcpy(item.email, "asdfgh@gmail.com");
    strcpy(item.nome, "Pedro");
    strcpy(item.senha_8d, "asdfgh");
    
    inserirFimCliente(l_clientes, item);
    mostrar_cliente(l_clientes);

    strcpy(pedido_historico.nome_prato,"Peixe");
    strcpy(pedido_historico.nome_rest, "Beiramar");
    pedido_historico.valor = 22.50;
    inserirPedidoHistorico(l_clientes, 1598, pedido_historico);
    strcpy(pedido_historico.nome_prato,"Acai");
    strcpy(pedido_historico.nome_rest, "Sorveteria");
    pedido_historico.valor = 12.96;
    inserirPedidoHistorico(l_clientes, 1598, pedido_historico);

    //mostrar_tudo_cliente(l_clientes);

    item_cartao.cvv = 123;
    strcpy(item_cartao.numero, "1234123478947894");
    strcpy(item_cartao.tipo, "debito");
    strcpy(item_cartao.validade, "1225");
    inserirCartaoCliente(l_clientes,1598,item_cartao);

    mostrar_tudo_cliente(l_clientes);

    removerFimCliente (l_clientes);
    mostrar_cliente (l_clientes);
    removerFimCliente (l_clientes);
    mostrar_cliente (l_clientes);




    /*Lista_entregadores *l;
    entregador item_e;

    l = criar_lista_entregadores();

    inicializar_entregador(&item_e);
    item_e.codigo = 113;
    strcpy (item_e.nome, "Alan Ferreira");
    strcpy (item_e.email, "asfesfs@dsf.com");
    strcpy (item_e.cpf, "12345678999");
    inserirInicioEntregador(l, item_e);
    mostrar_entregador(l); 

    item.codigo = 333;
    strcpy (item.nome, "Alan Silva");
    strcpy (item.email, "asfesfs@dsf.com");
    strcpy (item.cpf, "12345678999");
    inserirFimEntregador(l, item);
    mostrar_entregador(l);

    item.codigo = 126;
    strcpy (item.nome, "Joao Pedro");
    strcpy (item.email, "asfesfs@dsf.com");
    strcpy (item.cpf, "12345678999");
    inserirInicioEntregador(l, item);
    mostrar_entregador(l);

    item.codigo = 785;
    strcpy (item.nome, "Tiago Resende");
    strcpy (item.email, "asfesfs@dsf.com");
    strcpy (item.cpf, "12345678999");
    inserirFimEntregador(l, item);
    mostrar_entregador(l);
    
    removerItem(l, 113);
    mostrar_entregador(l);

    removerItem(l, 785);
    mostrar_entregador(l);

    removerItem(l, 126);
    mostrar_entregador(l);*/

    /*removerPosi(l, 0);
    mostrar_entregador(l);

    removerPosi(l, 1);
    mostrar_entregador(l);

    removerPosi(l, 10);
    mostrar_entregador(l);

    removerPosi(l, 10);
    mostrar_entregador(l);*/

    /*removerFim(l);
    mostrar_entregador(l);

    removerFim(l);
    mostrar_entregador(l);

    removerFim(l);
    mostrar_entregador(l);

    removerFim(l);
    mostrar_entregador(l);

    buscarEntregador(l, &item);
    printf ("\n\n%d, %s, %s, %d, %.1f, %d", item.codigo, item.nome, item.cpf, item.corridas, item.rank.media, item.status);

    buscarEntregador(l, &item);
    printf ("\n\n%d, %s, %s, %d, %.1f, %d", item.codigo, item.nome, item.cpf, item.corridas, item.rank.media, item.status);

    buscarEntregador(l, &item);
    printf ("\n\n%d, %s, %s, %d, %.1f, %d", item.codigo, item.nome, item.cpf, item.corridas, item.rank.media, item.status);

    buscarEntregador(l, &item);
    printf ("\n\n%d, %s, %s, %d, %.1f, %d", item.codigo, item.nome, item.cpf, item.corridas, item.rank.media, item.status);
    
    liberarEntregador(l, 333);
    buscarItem (l, 333, &item);
    printf ("\n\n%d, %s, %s, %d, %.1f, %d", item.codigo, item.nome, item.cpf, item.corridas, item.rank.media, item.status);

    printf ("\n\nSeu pedido esta indo: \n");
    buscarEntregador(l, &item);
    printf ("\n%d, %s, %s, %d, %.1f, %d\n", item.codigo, item.nome, item.cpf, item.corridas, item.rank.media, item.status);

    printf ("\nSeu pedido chegou: \n");
    adicionarCorridaNota(l, 333, 4.5);
    //liberarEntregador(l, 333); esta dentro da funcao acima
    buscarItem(l, 333, &item);
    printf ("\n%d, %s, %s, %d, %.1f, %d\n", item.codigo, item.nome, item.cpf, item.corridas, item.rank.media, item.status);

    mostrar_tudo_entregador(l);
    limpar(l);
    mostrar_entregador(l);

    free(l);*/

    return 0; 
}