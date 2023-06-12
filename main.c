// BIBLIOTECAS, TADs E DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <Windows.h>
#include "entregador.h"
#include "cliente.h"
#include "restaurante.h"
#include "filaPedidosPendentes.h"

// STRUCTS EXTRAS //
typedef struct juncao
{
    entregador entregador_do_pedido;
    pedidos pedido_em_andamento;
    Cliente comprador;
}pedidosglobais;

// funções para o gerenciador global de pedidos em andamento

void copiarPedidoCpC(pedidos *A, pedidos *B); // criar possivel funcao que copiará pedido para pedido entre tipos de pedidos e tals
void copiarPpP (pratos *A, pratos *B, int tam);
pedidosglobais* inserirControleGlobal(pedidosglobais *pg, entregador entregador_atual, pedidos pedido_atual, Cliente cliente_atual, int *qtd);
pedidosglobais* removerControleGlobal(pedidosglobais *pg, int numero_pedido, int *qtd, Lista_cliente *l_cliente, Lista_entregadores *l_entregador, Lista_restaurantes *l_restaurante, float nota); // deve remover do controle, liberar entregador e adicionar aos historicos
pedidos* buscarPedidoAndamento (pedidosglobais *pg, int qtd, int codigo_cliente, int *num_pedidos);
int buscarPedidoAndamentoEntregador (pedidosglobais *pg, int qtd, int codigo_entregador, pedidos *em_andamento);
void mostrarPedidosGlobais (pedidosglobais *pg, int qtd);
pratos* adicionarPratoPed (int *qtd, pratos *novo_prato_vet, pratos novo_prato);

// FUNÇÕES EXTRAS

void inicializar_entregador(entregador *item); // usada ao criar um novo cadastro de entregador (zera todas as informações para evitar lixo e erros)
void limpar_variavel_entregador(entregador *item); // limpa a variavel para evitar erros ao sobrepor
void inicializar_cliente(Cliente *item); // usada ao criar um novo_cliente cadastro de entregador (zera todas as informações para evitar lixo e erros)
void inicializar_restaurante(restaurante *item);
void limpar_variavel_cliente(Cliente *item); // limpa a variavel para evitar erros ao sobrepor
void limpar_variavel_rest(restaurante *item); // limpa a variavel para evitar erros ao sobrepor
void limpar_variavel_prato(pratos *item);
void mostrarCardapioItem (restaurante item);

// MENUS

int menu_inicial(); // permite a escolha entre os diferentes usuários
int menu_inicial_cliente(); // permite ao cliente escolher
int menu_cliente(); // permite ao cliente escolher após logado
int menu_pedido_cliente(); // permite ao cliente escolher após logado
int menu_config_cliente(); // permite ao cliente escolher após logado
int menu_inicial_restaurante(); // permite ao restaurante escolher
int menu_restaurante();
int menu_categoria();
int menu_cardapio_restaurante();
int menu_pedidosPendentes_restaurante();
int menu_historicoPedidos_restaurante();
int menu_configuracoes_restaurante();
int menu_adm(); // permite ao adm escolher
int menu_inicial_entregador(); // permite ao entregador escolher
int menu_entregador(); // permite ao entregador escolher após logar
int menu_config_entregador(); // permite ao entregador escolher após logar

// MAIN

int main()
{
    srand(time(NULL));

    // declarações relacionadas ao gerenciador global de pedidos
    pedidosglobais *controlePedidos = NULL;
    int qtdPratosPedidosAndamento = 0;
    pratos *novo_prato_ped = NULL;
    pratos novo_prato_simples;
    int nun_novo_prato_ped = 0;
    int codigo_geral = 10000;

    // declarações relacionadas aos clientes
    Lista_cliente *lista_principal_clientes;
    Cliente logado_cliente, novo_cliente;
    Cliente esqueceu_senha_cliente, inicializados_cliente;
    cartao novo_cartao;
    endereco novo_endereco;
    pedidos *em_andamento, novoped_pedido;

    // declarações relacionadas aos restaurantes
    Lista_restaurantes *lista_principal_restaurantes;
    Lista_restaurantes *lista_categoria;
    restaurante novo_restaurante, logado_restaurante;
    restaurante login_restaurante, inicializados_restaurante;
    restaurante pedido_rest;
    int codigo_loginR;
    pratos novo_prato;
    char nome_prato[40];
    char nome_rest[40];
    float preco_prato;

    // declaracoes relacionadas a fila de pedidos pendentes
    Fila_PedidosPendentes *fila_pedidosPendentes;
    pedidos *pedidoPendente;

    // declarações relacionadas aos entregadores
    Lista_entregadores *lista_principal_entregadores;
    entregador novo_entregador, logado_entregador, esqueceu_senha_entregador, novoped_entregador;
    int cod_novo = -1;
    int codigo_loginE = -1;

    // declarações adm
    char loginADM[15];
    char senhaADM[15];

    // declarações gerais
    int option = -1;
    int verify = -1;
    char email[40];
    char senha[15];
    char cpf[12];
    char confirmSenha[15];
    char categoria[30];
    int codigo_pedido;
    float precoTotal_pedido;

    // inicializações
    lista_principal_clientes = criarCliente();
    lista_principal_entregadores = criar_lista_entregadores();
    lista_principal_restaurantes = criar_listaRestaurantes();
    lista_categoria = criar_listaRestaurantes();
    fila_pedidosPendentes = criar_filaPedidosPendentes();

    inicializar_cliente (&esqueceu_senha_cliente);
    inicializar_entregador (&esqueceu_senha_entregador);
    inicializar_entregador (&novoped_entregador);
    limpar_variavel_entregador (&esqueceu_senha_entregador);
    inicializar_restaurante(&login_restaurante);
    limparVariavelRest(&pedido_rest);

    // criando testes
    restaurante base_rest;
    pratos base_restPratos;

    // LOGIN ADM
    strcpy(loginADM, "souADM");
    strcpy(senhaADM, "123ADM");

    // AQUI COMEÇA O PROGRAMA EM SI

    while (option != 0) // mantém o programa rodando até que seja escolhido sair
    {
        option = menu_inicial();

        switch (option)
        {
            case 0: // sair
                limparCliente(lista_principal_clientes);
                free(lista_principal_clientes);
                limparEntregador(lista_principal_entregadores);
                free(lista_principal_entregadores);
                limparRest(lista_principal_restaurantes);
                free(lista_principal_restaurantes);
                
                printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)\n");
                
                return 0;
            break;

            case 1: // sou cliente

                while (option != 3)
                {
                    option = menu_inicial_cliente();

                    switch (option)
                    {
                        case 0: // sair
                            limparCliente(lista_principal_clientes);
                            free(lista_principal_clientes);
                            limparEntregador(lista_principal_entregadores);
                            free(lista_principal_entregadores);
                            //limparRest(lista_principal_restaurantes);
                            //free(lista_principal_restaurantes);

                            printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)\n");
                            
                            return 0;
                        break;

                        case 1:; // quero me cadastrar
                            int i = 0;
                            
                            printf("\n---------- CADASTRO ----------\n\n");
                            printf("\nMuito bem! Vamos realizar seu cadastro: \n");

                            printf("\nDigite seu nome: ");
                            setbuf(stdin, NULL);
                            scanf("%[^\n]s", novo_cliente.nome);

                            printf("\nDigite seu e-mail: ");
                            setbuf(stdin, NULL);
                            scanf("%[^\n]s", novo_cliente.email);

                            printf("\nDigite seu CPF (somente numeros): ");
                            setbuf(stdin, NULL);
                            scanf("%[^\n]s", novo_cliente.cpf);

                            do
                            {
                                printf("\nDigite sua senha (ate 8 digitos): ");
                                setbuf(stdin, NULL);
                                scanf("%[^\n]s", novo_cliente.senha_8d);

                                i = strlen(novo_cliente.senha_8d);

                                if (i > 8) printf ("\nSenha muito grande. Tente novamente!");
                            }while(i > 8);

                            inicializar_cliente(&novo_cliente);

                            if ((inserirFimCliente(lista_principal_clientes, novo_cliente)) == 0) printf("\nCadastro realizado com sucesso!\n");

                            printf("Voce ja pode fazer o Login!\n");

                            Sleep(1000);
                            
                            limpar_variavel_cliente(&novo_cliente);
                            mostrar_cliente(lista_principal_clientes);
                        break;

                        case 2:; // ja tenho cadastro

                            verify = -1;

                            while (verify != 0)
                            {
                                printf("\n---------- LOGIN ----------\n\n");
                                printf("\nDigite seu e-mail: ");
                                setbuf(stdin, NULL);
                                scanf("%[^\n]s", &email);

                                printf("\nDigite sua senha: ");
                                setbuf(stdin, NULL);
                                scanf("%[^\n]s", &senha);

                                verify = loginCliente(lista_principal_clientes, &(*email), &(*senha), &logado_cliente);

                                strcpy(email, "000");
                                strcpy(senha, "000");

                                if (verify != 0)
                                {
                                    printf("\nLogin ou senha invalidos. Tente novamente!\n");
                                    Sleep(1000);
                                }
                                if (verify == 0)
                                {
                                    printf("\nLogin efetuado com sucesso. Bem vindo(a) de volta, %s!\n", logado_cliente.nome);
                                    break;
                                }

                                if (verify == 0) break;
                                
                                printf("\nTentar Novamente (Digite 0)\n"
                                       "Voltar (Digite 5)\n"
                                       "Esqueceu a senha? (Digite 6)\n");
                                scanf("%d", &verify);

                                if (verify == 5) break;
                                if (verify == 6)
                                {
                                    printf ("\n----------ALTERAR SENHA----------\n");
                                    while (verify != 0)
                                    {
                                        printf("\nDigite seu email: ");
                                        setbuf(stdin, NULL);
                                        scanf("%[^\n]s", &email);

                                        printf("\nDigite seu CPF: ");
                                        setbuf(stdin, NULL);
                                        scanf("%[^\n]s", &cpf);

                                        verify = buscarClienteEmailCPF(lista_principal_clientes, &(*email), &(*cpf), &esqueceu_senha_cliente);

                                        if (verify == 0)
                                        {
                                            verify = -1;
                                            char senha1[15];
                                            char senha2[15];

                                            while (verify != 0)
                                            {
                                                if (verify != 1) printf("\nTe encontramos!");

                                                printf("\nDigite sua nova senha: ");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", &senha1);

                                                printf("\nDigite sua nova senha novamente: ");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", &senha2);

                                                verify = alterarSenha(lista_principal_clientes, esqueceu_senha_cliente.codigo, senha1, senha2);

                                                if (verify == 0) printf("\nSenha alterada com sucesso! ");
                                                if (verify != 0) printf("\nSenhas diferentes. Tente novamente! ");
                                            }
                                        }
                                        else 
                                        {
                                            printf("\nAlgo deu errado. Tente novamente!");
                                            printf("\nContinuar (Digite 1)\nSair(Digite 0)\n ");
                                            scanf ("%d", &verify);
                                        }
                                    }
                                }
                                if (verify == 0) verify = 1;
                            }

                            if (verify == 5) break; // sair e voltar ao menu anterior

                            while (option != 7) // voltar após selecionar voltar
                            {
                                option = menu_cliente();

                                switch (option) // opções do cliente após logar
                                {
                                    case 0: // sair
                                        limparCliente(lista_principal_clientes);
                                        free(lista_principal_clientes);
                                        limparEntregador(lista_principal_entregadores);
                                        free(lista_principal_entregadores);
                                        //limparRest(lista_principal_restaurantes);
                                        //free(lista_principal_restaurantes);
                                        
                                        printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)");
                                        
                                        return 0;
                                    break;

                                    case 1: // fazer pedido

                                        while (option != 4)
                                        {
                                            option = menu_pedido_cliente();

                                            switch (option)
                                            {
                                                case 1: // mostrar todos os restaurantes
                                                    verify = -1;
                                                    buscarItemCliente (lista_principal_clientes, logado_cliente.codigo, &logado_cliente);
                                                    printf("\n----------RESTAURANTES----------\n");

                                                    while (verify != 0)
                                                    {
                                                        printf ("\nAqui estao todos os restaurantes disponiveis: \n");
                                                        mostrarInfoRest(lista_principal_restaurantes);

                                                        Sleep(2000);

                                                        printf("\nVoltar (Digite 0)\nPara acessar algum restaurante (Digite 1)\n");
                                                        scanf ("%d", &verify);

                                                        if (verify != 0)
                                                        {
                                                            printf ("\nDigite qual o numero do restaurante que voce deseja visualizar:\n");
                                                            scanf ("%d", &verify);
                                                            verify--; // verify = verify - 1

                                                            buscarRestPos(lista_principal_restaurantes, verify, &pedido_rest);

                                                            mostrarCardapioItem (pedido_rest);

                                                            printf ("\nDigite 0 para voltar ou 1 para fazer um pedido: ");
                                                            scanf ("%d", &verify);

                                                            if (verify != 0)
                                                            {
                                                                if (pedido_rest.status != 1)
                                                                {
                                                                    printf ("\nInfelizmente o restaurante esta fechado. Volta novamente mais tarde. ");
                                                                    verify = 0; 
                                                                    break;
                                                                } 
                                                                while (verify != 0)
                                                                {
                                                                    int coord = 0;
                                                                    printf ("\n------------VAMOS FAZER UM PEDIDO------------\n");
                                                                    printf ("\nAqui esta o cardapio do restaurante selecionado:\n");
                                                                    mostrarCardapioItem(pedido_rest);

                                                                    printf ("\n\nDigite 0 para voltar ou digite o numero do prato que voce quer adicionar ao pedido: ");
                                                                    scanf ("%d", &coord);
                                                                    
                                                                    if (coord < 0 || coord > pedido_rest.qtdCardapio) 
                                                                    {
                                                                        printf ("\nNumero invalido!");
                                                                        verify = 0;
                                                                    }

                                                                    if (verify == 0 || coord == 0) break;

                                                                    coord--;

                                                                    verify = buscarPratoRest(lista_principal_restaurantes, pedido_rest.codigo, coord, &novo_prato_simples);
                                                                    novo_prato_ped = adicionarPratoPed (&nun_novo_prato_ped, novo_prato_ped, novo_prato_simples);

                                                                    if (verify == 0)
                                                                    {
                                                                        printf ("\nPrato adicionado com sucesso ao carrinho. Digite 1 para adicionar mais ou 2 para finalizar o pedido: ");
                                                                        scanf ("%d", &verify);
                                                                    }
                                                                    else 
                                                                    {
                                                                        printf ("\nHouve um erro. Tente novamente!");
                                                                        verify = 0;
                                                                        nun_novo_prato_ped = 0;
                                                                        free(novo_prato_ped);
                                                                        break;
                                                                    }
                                                                    if (verify == 0) break;

                                                                    if (verify != 0 && verify != 1)
                                                                    {
                                                                        if (logado_cliente.quant_enderecos == 0)
                                                                        {
                                                                            printf ("\nVoce nao possui enderecos cadastrados. Cadastre algum para fazer seu pedido!");
                                                                            verify = 0;
                                                                            nun_novo_prato_ped = 0;
                                                                            free(novo_prato_ped);
                                                                            break;
                                                                        }
                                                                        if (verify == 0) break;

                                                                        if (logado_cliente.quant_enderecos > 1)
                                                                        {
                                                                            verify = -1;
                                                                            do 
                                                                            {
                                                                                printf ("\nEm qual endereco voce quer receber seu pedido? \n");
                                                                                mostrar_enderecos (logado_cliente);
                                                                                printf ("Opcao (1, 2, 3...): ");
                                                                                scanf ("%d", &verify);
                                                                            }while(verify < logado_cliente.quant_enderecos && verify > logado_cliente.quant_enderecos);
                                                                        }
                                                                        else
                                                                        {
                                                                            printf ("\nVoce recebera seu pedido no unico endereco cadastrado. :)");
                                                                        }
                                                                        
                                                                        verify = -1;

                                                                        do
                                                                        {
                                                                            printf ("\nDigite qual sera a forma de pagamento: \n");
                                                                            printf ("1. Dinheiro\n");
                                                                            printf ("2. Cartao\n");
                                                                            scanf ("%d", &verify);
                                                                        }while(verify != 1 && verify != 2);

                                                                        if (verify == 1) printf ("\nPerfeito! Seu pagamento sera feito na entrega.");
                                                                        else
                                                                        {
                                                                            if (logado_cliente.quantidade_cartoes == 0)
                                                                            {
                                                                                do
                                                                                {
                                                                                    printf ("\nInfelizmente voce nao possui cartoes cadastrados. Deseja pagar em dinheiro ou cancelar o pedido? \n");
                                                                                    printf ("1. Pagar em dinheiro\n");
                                                                                    printf ("2. Cancelar\n");
                                                                                    printf ("Opcao: ");
                                                                                    scanf ("%d", &verify);
                                                                                }while(verify != 1 && verify != 2);

                                                                                if (verify == 1)
                                                                                {
                                                                                    printf ("\nPerfeito! Seu pagamento sera feito na entrega. ");
                                                                                    verify = 15;
                                                                                }
                                                                                else
                                                                                {
                                                                                    printf ("\nPedido cancelado! ");
                                                                                    verify = 0;
                                                                                    break;
                                                                                }
                                                                            }
                                                                            else
                                                                            {
                                                                                if (logado_cliente.quantidade_cartoes > 1)
                                                                                {
                                                                                    verify = -1;
                                                                                    do 
                                                                                    {
                                                                                        printf ("\nEm qual cartao voce quer receber pagar pedido? \n");
                                                                                        mostrar_pagamentos (logado_cliente);
                                                                                        printf ("Opcao (1, 2, 3...): ");
                                                                                        scanf ("%d", &verify);
                                                                                    }while(verify < logado_cliente.quantidade_cartoes && verify > logado_cliente.quantidade_cartoes);
                                                                                    printf ("\nPerfeito! Seu pedido sera cobrado no cartao selecionado. ");
                                                                                }
                                                                                else
                                                                                {
                                                                                    printf ("\nVoce recebera seu pedido no unico cartao cadastrado. :)");
                                                                                }
                                                                            }
                                                                        }
                                                                        if (verify == 0) break;
                                                                        novoped_pedido.pratosPed = (pratos*) malloc (nun_novo_prato_ped*sizeof(pratos));
                                                                        novoped_pedido.pratosPed = novo_prato_ped;
                                                                        
                                                                        buscarEntregador (lista_principal_entregadores, &novoped_entregador);
                                                                        
                                                                        novoped_pedido.qtdPratosPed = nun_novo_prato_ped;
                                                                        strcpy(novoped_pedido.nome_rest, pedido_rest.nome);
                                                                        novoped_pedido.precoTotal = 0;
                                                                        novoped_pedido.codigo = ++codigo_geral;

                                                                        for (i = 0; i < nun_novo_prato_ped; i++)
                                                                        {
                                                                            novoped_pedido.precoTotal += novo_prato_ped[i].preco;
                                                                        }
                                                                        
                                                                        controlePedidos = inserirControleGlobal (controlePedidos, novoped_entregador, novoped_pedido, logado_cliente, &qtdPratosPedidosAndamento);
                                                                        
                                                                        nun_novo_prato_ped = 0;
                                                                        free (novo_prato_ped);
                                                                        printf ("\nPedido efetuado com sucesso! ");
                                                                        verify = 0;
                                                                    }
                                                                }   
                                                            }
                                                        }
                                                    }
                                                break;

                                                case 2: // filtrar por categoria
                                                printf("\n-------------------------------------------\n");
                                                verify = -1;
                                                verify = menu_categoria();

                                                switch (verify)
                                                {
                                                    case 1:
                                                        strcpy(categoria, "Comida brasileira");
                                                    break;

                                                    case 2:
                                                        strcpy(categoria, "Comida estrangeira");
                                                    break;

                                                    case 3:
                                                        strcpy(categoria, "FastFood");
                                                    break;

                                                    case 4:
                                                        strcpy(categoria, "Acai e sorvetes");
                                                    break;

                                                    case 5:
                                                        strcpy(categoria, "Padaria e cafeteria");
                                                    break;

                                                    case 6:
                                                        strcpy(categoria, "Pizzaria");
                                                    break;

                                                    case 7:
                                                        strcpy(categoria, "Doces");
                                                    break;

                                                    case 8:
                                                        strcpy(categoria, "Fitness");
                                                    break;

                                                    case 9:
                                                        strcpy(categoria, "Bebidas");
                                                    break;

                                                    case 10:
                                                        strcpy(categoria, "Outros");
                                                    break;
                                                }

                                                criar_listaCategoria (lista_principal_restaurantes, lista_categoria, categoria);

                                                verify = -1;
                                                buscarItemCliente (lista_principal_clientes, logado_cliente.codigo, &logado_cliente);
                                                printf("\n----------RESTAURANTES----------\n");

                                                while (verify != 0)
                                                {
                                                    printf ("\nAqui estao todos os restaurantes disponiveis: \n");
                                                    mostrarListaRest (lista_categoria);

                                                    Sleep(2000);

                                                    printf("\nVoltar (Digite 0)\nPara acessar algum restaurante (Digite 1)\n");
                                                    scanf ("%d", &verify);

                                                    if (verify != 0)
                                                    {
                                                        printf ("\nDigite qual o numero do restaurante que voce deseja visualizar:\n");
                                                        scanf ("%d", &verify);
                                                        verify--; // verify = verify - 1

                                                        buscarRestPos(lista_categoria, verify, &pedido_rest);
                                                        buscarRestCodigo (lista_principal_restaurantes, pedido_rest.codigo, &pedido_rest);
                                                        mostrarCardapioItem (pedido_rest);

                                                        printf ("\nDigite 0 para voltar ou 1 para fazer um pedido: ");
                                                        scanf ("%d", &verify);

                                                        if (verify != 0)
                                                        {
                                                            if (pedido_rest.status != 1)
                                                            {
                                                                printf ("\nInfelizmente o restaurante esta fechado. Volta novamente mais tarde. ");
                                                                verify = 0; 
                                                                break;
                                                            } 
                                                            while (verify != 0)
                                                            {
                                                                int coord = 0;
                                                                printf ("\n------------VAMOS FAZER UM PEDIDO------------\n");
                                                                printf ("\nAqui esta o cardapio do restaurante selecionado:\n");
                                                                mostrarCardapioItem(pedido_rest);

                                                                printf ("\n\nDigite 0 para voltar ou digite o numero do prato que voce quer adicionar ao pedido: ");
                                                                scanf ("%d", &coord);
                                                                    
                                                                if (coord < 0 || coord > pedido_rest.qtdCardapio) 
                                                                {
                                                                    printf ("\nNumero invalido!");
                                                                    verify = 0;
                                                                }

                                                                if (verify == 0 || coord == 0) break;

                                                                coord--;

                                                                verify = buscarPratoRest(lista_principal_restaurantes, pedido_rest.codigo, coord, &novo_prato_simples);
                                                                novo_prato_ped = adicionarPratoPed (&nun_novo_prato_ped, novo_prato_ped, novo_prato_simples);

                                                                if (verify == 0)
                                                                {
                                                                    printf ("\nPrato adicionado com sucesso ao carrinho. Digite 1 para adicionar mais ou 2 para finalizar o pedido: ");
                                                                    scanf ("%d", &verify);
                                                                }
                                                                else 
                                                                {
                                                                    printf ("\nHouve um erro. Tente novamente!");
                                                                    verify = 0;
                                                                    nun_novo_prato_ped = 0;
                                                                    free(novo_prato_ped);
                                                                    break;
                                                                }
                                                                if (verify == 0) break;

                                                                if (verify != 0 && verify != 1)
                                                                {
                                                                    if (logado_cliente.quant_enderecos == 0)
                                                                    {
                                                                        printf ("\nVoce nao possui enderecos cadastrados. Cadastre algum para fazer seu pedido!");
                                                                        verify = 0;
                                                                        nun_novo_prato_ped = 0;
                                                                        free(novo_prato_ped);
                                                                        break;
                                                                    }
                                                                    if (verify == 0) break;

                                                                    if (logado_cliente.quant_enderecos > 1)
                                                                    {
                                                                        verify = -1;
                                                                        do 
                                                                        { 
                                                                            printf ("\nEm qual endereco voce quer receber seu pedido? \n");
                                                                            mostrar_enderecos (logado_cliente);
                                                                            printf ("Opcao (1, 2, 3...): ");
                                                                            scanf ("%d", &verify);
                                                                        }while(verify < logado_cliente.quant_enderecos && verify > logado_cliente.quant_enderecos);
                                                                    }
                                                                    else
                                                                    {
                                                                        printf ("\nVoce recebera seu pedido no unico endereco cadastrado. :)");
                                                                    }
                                                                        
                                                                    verify = -1;

                                                                    do
                                                                    {
                                                                        printf ("\nDigite qual sera a forma de pagamento: \n");
                                                                        printf ("1. Dinheiro\n");
                                                                        printf ("2. Cartao\n");
                                                                        scanf ("%d", &verify);
                                                                    }while(verify != 1 && verify != 2);

                                                                    if (verify == 1) printf ("\nPerfeito! Seu pagamento sera feito na entrega.");
                                                                    else
                                                                    {
                                                                        if (logado_cliente.quantidade_cartoes == 0)
                                                                        {
                                                                            do
                                                                            {
                                                                                printf ("\nInfelizmente voce nao possui cartoes cadastrados. Deseja pagar em dinheiro ou cancelar o pedido? \n");
                                                                                printf ("1. Pagar em dinheiro\n");
                                                                                printf ("2. Cancelar\n");
                                                                                printf ("Opcao: ");
                                                                                scanf ("%d", &verify);
                                                                            }while(verify != 1 && verify != 2);

                                                                            if (verify == 1)
                                                                            {
                                                                                printf ("\nPerfeito! Seu pagamento sera feito na entrega. ");
                                                                                verify = 15;
                                                                            }
                                                                            else
                                                                            {
                                                                                printf ("\nPedido cancelado! ");
                                                                                verify = 0;
                                                                                break;
                                                                            }
                                                                        }
                                                                        else
                                                                        {
                                                                            if (logado_cliente.quantidade_cartoes > 1)
                                                                            {
                                                                                verify = -1;
                                                                                do 
                                                                                {
                                                                                    printf ("\nEm qual cartao voce quer receber pagar pedido? \n");
                                                                                    mostrar_pagamentos (logado_cliente);
                                                                                    printf ("Opcao (1, 2, 3...): ");
                                                                                    scanf ("%d", &verify);
                                                                                }while(verify < logado_cliente.quantidade_cartoes && verify > logado_cliente.quantidade_cartoes);
                                                                                printf ("\nPerfeito! Seu pedido sera cobrado no cartao selecionado. ");
                                                                            }
                                                                            else
                                                                            {
                                                                                printf ("\nVoce recebera seu pedido no unico cartao cadastrado. :)");
                                                                            }
                                                                        }
                                                                    }
                                                                    if (verify == 0) break;
                                                                    novoped_pedido.pratosPed = (pratos*) malloc (nun_novo_prato_ped*sizeof(pratos));
                                                                    novoped_pedido.pratosPed = novo_prato_ped;
                                                                    
                                                                    buscarEntregador (lista_principal_entregadores, &novoped_entregador);
                                                                    
                                                                    novoped_pedido.qtdPratosPed = nun_novo_prato_ped;
                                                                    strcpy(novoped_pedido.nome_rest, pedido_rest.nome);
                                                                    novoped_pedido.precoTotal = 0;
                                                                    novoped_pedido.codigo = ++codigo_geral;

                                                                    for (i = 0; i < nun_novo_prato_ped; i++)
                                                                    {
                                                                        novoped_pedido.precoTotal += novo_prato_ped[i].preco;
                                                                    }
                                                                        
                                                                    controlePedidos = inserirControleGlobal (controlePedidos, novoped_entregador, novoped_pedido, logado_cliente, &qtdPratosPedidosAndamento);
                                                                        
                                                                    nun_novo_prato_ped = 0;
                                                                    free (novo_prato_ped);
                                                                    printf ("\nPedido efetuado com sucesso! ");
                                                                    verify = 0;
                                                                }
                                                            }   
                                                        }
                                                    }
                                                }
                                                printf("\n-------------------------------------------\n");

                                                break;

                                                case 3: // procurar por nome
                                                    printf("\n-------------------------------------------\n");

                                                    printf ("\nDigite o nome do restaurante que voce deseja procurar: ");
                                                    setbuf (stdin, NULL);
                                                    scanf ("%[^\n]s", &nome_rest);

                                                    buscarRestNome (lista_principal_restaurantes, nome_rest, &pedido_rest);



                                                    printf("\n-------------------------------------------\n");
                                                break;

                                                case 4: // voltar
                                                break;
                                            }
                                        }
                                    break;

                                    case 2: // histórico
                                        printf("\n----------HISTORICO----------\n\n");
                                        buscarItemCliente (lista_principal_clientes, logado_cliente.codigo, &logado_cliente);                                        
                                        printf ("\nAqui estao seus ultimos pedidos: \n");
                                        mostrar_pedidos (logado_cliente);
                                        Sleep(1000);

                                        break;

                                    case 3: // cartões (cadastrar e excluir)
                                        printf("\n----------CARTOES----------\n\n");
                                        printf("\nVoce possui os seguintes cartoes cadastrados: \n");
                                        buscarItemCliente(lista_principal_clientes, logado_cliente.codigo, &logado_cliente);
                                        mostrar_pagamentos(logado_cliente);
                                        Sleep(1000);

                                        printf("\nVoce deseja: ");
                                        printf("\n1. Cadastrar novo cartao");
                                        printf("\n2. Excluir cartao");
                                        printf("\n3. Voltar\n");
                                        scanf("%d", &option);

                                        if (option == 1)
                                        {
                                            int temp = -1;
                                            printf("\n\nVamos la!\n");

                                            printf("\nDigite o numero do cartao(sem espacos): ");
                                            setbuf(stdin, NULL);
                                            scanf("%[^\n]s", novo_cartao.numero);

                                            printf("\nDigite a data de validade (MMAA): ");
                                            setbuf(stdin, NULL);
                                            scanf("%[^\n]s", novo_cartao.validade);

                                            printf("\nDigite o CVV: ");
                                            setbuf(stdin, NULL);
                                            scanf("%d", &novo_cartao.cvv);

                                            do
                                            {
                                                printf("\nO cartao eh de: \n1. Debito\n2.Credito\n");
                                                scanf("%d", &temp);
                                            } while (temp < 1 || temp > 2);

                                            if (temp == 1) strcpy(novo_cartao.tipo, "Debito");
                                            else strcpy(novo_cartao.tipo, "Credito");

                                            temp = inserirCartaoCliente(lista_principal_clientes, logado_cliente.codigo, novo_cartao);

                                            if (temp == 0) printf("\nCadastro realizado com sucesso!\n");
                                            else printf("\nAlgum erro inesperado aconteceu. Tente novamente!\n");
                                            Sleep(1000);
                                        }

                                        if (option == 2)
                                        {
                                            int temp = -1;

                                            printf("Digite qual o cartao que voce quer excluir (1, 2, 3...): ");
                                            scanf("%d", &temp);

                                            temp = removerCartaoCliente(lista_principal_clientes, logado_cliente.codigo, temp);

                                            if (temp == 0) printf("\nExcluido com sucesso!\n");
                                            else printf("\nAlgum erro inesperado aconteceu. Tente novamente!\n");
                                            Sleep(1000);
                                        }
                                    break;

                                    case 4: // endereços (cadastrar ou excluir)

                                        printf("\n---------- ENDERECOS ----------\n\n");
                                        printf("\nVoce possui os seguintes enderecos cadastrados: \n");

                                        buscarItemCliente(lista_principal_clientes, logado_cliente.codigo, &logado_cliente);
                                        mostrar_enderecos(logado_cliente);

                                        Sleep(1000);

                                        printf("\nVoce deseja: ");
                                        printf("\n1. Cadastrar novo endereco");
                                        printf("\n2. Excluir endereco");
                                        printf("\n3. Voltar\n");
                                        scanf("%d", &option);

                                        if (option == 1)
                                        {
                                            int temp = -1;
                                            printf("\n\nVamos la!\n");

                                            printf("\nDigite a rua: ");
                                            setbuf(stdin, NULL);
                                            scanf("%[^\n]s", novo_endereco.rua);

                                            printf("\nDigite o numero: ");
                                            setbuf(stdin, NULL);
                                            scanf("%[^\n]s", novo_endereco.numero);

                                            printf("\nDigite o CEP: ");
                                            setbuf(stdin, NULL);
                                            scanf("%[^\n]s", novo_endereco.cep);

                                            temp = inserirEnderecoCliente(lista_principal_clientes, logado_cliente.codigo, novo_endereco);

                                            if (temp == 0) printf("\nCadastro realizado com sucesso!");
                                            else printf("\nAlgum erro inesperado aconteceu. Tente novamente!");
                                            Sleep(1000);
                                        }

                                        if (option == 2)
                                        {
                                            int temp = -1;

                                            printf("Digite qual o endereco que voce quer excluir (1, 2, 3...): ");
                                            scanf("%d", &temp);

                                            temp = removerEnderecoCliente(lista_principal_clientes, logado_cliente.codigo, temp);

                                            if (temp == 0) printf("\nExcluido com sucesso!");
                                            else printf("\nAlgum erro inesperado aconteceu. Tente novamente!");
                                            Sleep(1000);
                                        }
                                    break;

                                    case 5: // pedidos em andamento cliente
                                        verify = 0;

                                        int nun_ped = 0;

                                        em_andamento = buscarPedidoAndamento (controlePedidos, qtdPratosPedidosAndamento, logado_cliente.codigo, &nun_ped); // problema está aqui quando tem mais de um pedido para a mesma pessoa
                                        
                                        int i, j;

                                        if (nun_ped == 0)
                                        {
                                            printf ("\nVoce nao possui pedidos em andamento. Esta na hora de fazer um!\n\n");
                                            free(em_andamento);
                                        }
                                        else
                                        {
                                            printf("\n---------- MEUS PEDIDOS ----------\n\n");
                                            printf ("\nVoce possui %d pedidos em andamento!", nun_ped);
                                            for (i = 0; i < nun_ped; i++)
                                            {
                                                printf ("\n%d: %s\n", i+1, em_andamento[i].nome_rest);
                                                printf ("Total: %.2f\n", em_andamento[i].precoTotal);
                                                for (j = 0; j < em_andamento[i].qtdPratosPed; j++)
                                                {
                                                    printf ("%s: %.2f\n", em_andamento[i].pratosPed[j].nome, em_andamento[i].pratosPed[j].preco);
                                                }
                                            }

                                            printf ("\nAlgum dos seus pedidos chegou?\n1. Sim\n 0.Nao\nOpcao: ");
                                            scanf ("%d", &verify);

                                            if (verify == 1)
                                            {
                                                float nota = 0;
                                                i = 0;
                                                do 
                                                {
                                                    printf ("Digite o numero do pedido que chegou (1, 2, 3... ou 0 para voltar): ");
                                                    scanf ("%d", &i);

                                                    if (i < 0 || i > nun_ped) printf ("\nOpcao invalida. Tente novamente! ");
                                                }while(i < 0 || i > nun_ped); 
                                                if (i == 0) break;
                                                i = em_andamento[i-1].codigo;

                                                Sleep(1000);

                                                printf ("\nQual nota voce da para o entregador (0 - 5)? ");
                                                scanf ("%f", &nota);

                                                controlePedidos = removerControleGlobal(controlePedidos, i, &qtdPratosPedidosAndamento, lista_principal_clientes, lista_principal_entregadores, lista_principal_restaurantes, nota);

                                                free(em_andamento);
                                            }
                                            else
                                            {
                                                printf ("\nTudo bem! Nao esqueca de nos avisar caso chegue.\n");
                                            }
                                        }
                                    break;

                                    case 6: // configuracoes

                                        while ((option != 5) && (option != 15))
                                        {
                                            option = menu_config_cliente();

                                            switch (option)
                                            {
                                                case 1:; // alterar senha

                                                    printf("\n----------ALTERAR SENHA----------\n");

                                                    verify = -1;
                                                    char senha_atual[15];

                                                    while (verify != 0)
                                                    {
                                                        printf("\nDigite sua senha atual: ");
                                                        setbuf(stdin, NULL);
                                                        scanf("%[^\n]s", &senha_atual);

                                                        verify = strcmp(logado_cliente.senha_8d, senha_atual);

                                                        if (verify != 0)
                                                        {
                                                            printf("\nSenha atual incorreta!\nTentar novamente (Digite 1)\nVoltar(Digite 2)\n");
                                                            scanf("%d", &verify);
                                                        }

                                                        if (verify == 2) break;
                                                    }

                                                    if (verify == 2) break;

                                                    verify = -1;

                                                    while (verify != 0)
                                                    {
                                                        char senha1[15];
                                                        char senha2[15];

                                                        printf("\nDigite sua nova senha: ");
                                                        setbuf(stdin, NULL);
                                                        scanf("%[^\n]s", &senha1);

                                                        printf("\nDigite sua nova senha novamente: ");
                                                        setbuf(stdin, NULL);
                                                        scanf("%[^\n]s", &senha2);

                                                        verify = alterarSenha(lista_principal_clientes, logado_cliente.codigo, senha1, senha2);

                                                        if (verify == 0)
                                                        {
                                                            printf("\nSenha alterada com sucesso!\n");
                                                            buscarItemCliente(lista_principal_clientes, logado_cliente.codigo, &logado_cliente);
                                                        }
                                                        if (verify != 0) printf("\nSenhas diferentes. Tente novamente!\n");
                                                    }

                                                break;

                                                case 2:; // alterar email

                                                    verify = -1;

                                                    printf("\n----------ALTERAR EMAIL----------\n");

                                                    while (verify != 0)
                                                    {
                                                        printf("\nDigite sua senha atual: ");
                                                        setbuf(stdin, NULL);
                                                        scanf("%[^\n]s", &senha_atual);

                                                        verify = strcmp(logado_cliente.senha_8d, senha_atual);

                                                        if (verify != 0)
                                                        {
                                                            printf("\nSenha atual incorreta! Digite 1 para continuar ou 2 para voltar: ");
                                                            scanf("%d", &verify);
                                                        }

                                                        if (verify == 2) break;
                                                    }

                                                    if (verify == 2) break;

                                                    verify = -1;

                                                    char novo_email[40];

                                                    printf("\nDigite seu novo e-mail: ");
                                                    setbuf(stdin, NULL);
                                                    scanf("%[^\n]s", &novo_email);

                                                    verify = alterarEmail(lista_principal_clientes, logado_cliente.codigo, novo_email);

                                                    if (verify == 0)
                                                    {
                                                        printf("\nE-mail alterado com sucesso!\n");
                                                        buscarItemCliente(lista_principal_clientes, logado_cliente.codigo, &logado_cliente);
                                                    }
                                                    if (verify != 0) printf("\nAlgo deu errado. Tente novamente!\n");
                                                break;

                                                case 3: // mostrar dados

                                                    buscarItemCliente(lista_principal_clientes, logado_cliente.codigo, &logado_cliente);
                                                    printf ("\n-------------INFORMACOES-------------\n");
                                                    printf ("Nome: %s\n", logado_cliente.nome);
                                                    printf ("E-mail: %s\n", logado_cliente.email);
                                                    printf ("CPF: %s\n", logado_cliente.cpf);

                                                    printf ("\nDigite enter para continuar...");
                                                    setbuf (stdin, NULL);
                                                    getchar ();

                                                break;

                                                case 4: // apagar conta

                                                    printf("\n----------EXCLUIR CONTA----------\n");

                                                    printf("\nVoce esta prestes a apagar sua conta e tudo que esta contido nela. Voce tem certeza? ");
                                                    printf("\nDigite 1 para sim e 2 para nao: ");
                                                    scanf("%d", &verify);

                                                    if (verify == 1)
                                                    {
                                                        printf("\nMuito bem. Digite sua senha: ");
                                                        setbuf(stdin, NULL);
                                                        scanf("%[^\n]s", &senha_atual);

                                                        verify = strcmp(logado_cliente.senha_8d, senha_atual);

                                                        if (verify == 0)
                                                        {
                                                            verify = removerItemCliente(lista_principal_clientes, logado_cliente.codigo);

                                                            if (verify == 0)
                                                            {
                                                                printf("\nFoi um prazer ter voce conosco! Sua conta foi excluida com sucesso.");
                                                                limpar_variavel_cliente(&logado_cliente);
                                                                option = 15;
                                                            }
                                                            else
                                                            {
                                                                printf("\nHouve algum erro. Tente novamente.");
                                                            }
                                                        }
                                                        else
                                                        {
                                                            printf("\nSenha incorreta. Tente novamente.");
                                                            option = -1;
                                                        }
                                                        break;
                                                    }

                                                    if (verify != 1)
                                                    {
                                                        option = -1;
                                                        break;
                                                    }
                                                break;

                                                case 5: // voltar
                                                break;
                                            }
                                        }
                                        if (option == 15) option = 7;
                                    break;

                                    case 7: // sair da conta (voltar)
                                    break;
                                }
                            }
                        break;

                        case 3: // voltar
                        break;
                    }
                }
            break;

            case 2: // sou restaurante

                while (option != 3)
                {
                    option = menu_inicial_restaurante();

                    switch (option)
                    {
                        case 0: // Sair
                            limparCliente(lista_principal_clientes);
                            free(lista_principal_clientes);
                            limparEntregador(lista_principal_entregadores);
                            free(lista_principal_entregadores);
                            //limparRest(lista_principal_restaurantes);
                            //free(lista_principal_restaurantes);
                            
                            printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)");
                            
                            return 0;
                        break;

                        case 1: // Quero me cadastrar

                        printf("\n---------- CADASTRO ----------\n\n");
                        printf("\nMuito bem! Vamos realizar o cadastro: \n");

                        printf("\nDigite o nome do restaurante: ");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]s", novo_restaurante.nome);

                        printf("\nDigite o e-mail: ");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]s", novo_restaurante.email);

                        printf("\nDigite a senha (ate 14 digitos): ");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]s", senha);

                        printf("\nDigite a senha novamente (ate 14 digitos): ");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]s", confirmSenha);

                        if (strcmp(senha, confirmSenha) == 0)
                        {
                                strcpy(novo_restaurante.senha, senha);
                            } else {
                                printf("Senha Incorreta!\n");
                                break;
                            }

                            inicializar_restaurante(&novo_restaurante);

                            if ((inserirFimRest(lista_principal_restaurantes, &novo_restaurante)) == 0)
                            {
                                printf("\nEscolha uma categoria em que seu restaurante se encaixa.\nNao se preocupe! Voce podera alterar no futuro.\n\n");


                                int op = menu_categoria();

                                switch (op)
                                {
                                    case 1:
                                        strcpy(categoria, "Comida brasileira");
                                    break;

                                    case 2:
                                        strcpy(categoria, "Comida estrangeira");
                                    break;

                                    case 3:
                                        strcpy(categoria, "FastFood");
                                    break;

                                    case 4:
                                        strcpy(categoria, "Acai e sorvetes");
                                    break;

                                    case 5:
                                        strcpy(categoria, "Padaria e cafeteria");
                                    break;

                                    case 6:
                                        strcpy(categoria, "Pizzaria");
                                    break;

                                    case 7:
                                        strcpy(categoria, "Doces");
                                    break;

                                    case 8:
                                        strcpy(categoria, "Fitness");
                                    break;

                                    case 9:
                                        strcpy(categoria, "Bebidas");
                                    break;

                                    case 10:
                                        strcpy(categoria, "Outros");
                                    break;
                                }

                                if (alterarCategoria(lista_principal_restaurantes, novo_restaurante.codigo, categoria, &novo_restaurante) == 0)
                                {
                                    printf("\nCadastro realizado com sucesso!\n\n");
                                    Sleep(700);

                                    printf("\nMEU PERFIL\n");
                                    mostrarRestaurante(&novo_restaurante);
                                    printf("Voce ja pode fazer seu login!\n");
                                } else
                                    printf("Algo deu errado! Tente Novamente\n");
                            } else 
                                printf("Algo deu errado! Tente Novamente\n");
                            
                            limpar_variavel_rest(&novo_restaurante);
                        break;

                        case 2:; // Ja tenho cadastro
                            verify = -1;

                            while (verify != 0)
                            {
                                printf("\n---------- LOGIN ----------\n\n");
                                printf("\nDigite o e-mail: ");
                                setbuf(stdin, NULL);
                                scanf("%[^\n]s", &email);

                                printf("\nDigite a senha: ");
                                setbuf(stdin, NULL);
                                scanf("%[^\n]s", &senha);
                            
                                verify = loginRestaurante(lista_principal_restaurantes, email, senha, &logado_restaurante);

                                strcpy(email, " ");
                                strcpy(senha, " ");

                                if (verify != 0)
                                {
                                    printf("\nLogin ou senha invalidos. Tente novamente!\n");

                                } else if (verify == 0)
                                {
                                    printf("\nLogin efetuado com sucesso. Bem vindos de volta, %s!\n", logado_restaurante.nome);
                                    break;
                                }

                                printf("\n\nTentar Novamente (Digite 0)\n"
                                    "Voltar (Digite 5)\n"
                                    "Esqueceu a senha? (Digite 6)\n\n");
                                scanf("%d", &verify);

                                if (verify == 5) break;

                                if (verify == 6)
                                {
                                    printf("\n----------ALTERAR SENHA----------\n");
                                    while (verify != 0)
                                    {
                                        printf("\nDigite o email: ");
                                        setbuf(stdin, NULL);
                                        scanf("%[^\n]s", email);

                                        setbuf(stdin, NULL);
                                        printf("\nDigite o codigo do restaurante: ");
                                        scanf("%d", &codigo_loginR);

                                        verify = buscarRestEmailCodigo(lista_principal_restaurantes, email, codigo_loginR, &login_restaurante);

                                        if (verify == 0)
                                        {
                                            verify = -1;

                                            while (verify != 0)
                                            {
                                                if (verify != 1) 
                                                    printf("\nTe encontramos!");

                                                printf("\nDigite sua nova senha: "); 
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", senha);

                                                printf("\nDigite sua nova senha novamente: ");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", confirmSenha);

                                                verify = alterarSenhaRest(lista_principal_restaurantes, codigo_loginR, senha, confirmSenha, &login_restaurante);

                                                if (verify == 0)
                                                    printf("\nSenha alterada com sucesso! ");
                                                if (verify != 0)
                                                    printf("\nSenhas diferentes. Tente novamente! ");
                                            }
                                        }
                                        else
                                        {
                                            printf("\nAlgo deu errado. Tente novamente!");
                                            printf("\nContinuar (Digite 1)\nSair (Digite 0)\n");
                                            scanf ("%d", &verify);
                                        }
                                    }
                                }
                                if (verify == 0) verify = 1;
                            }

                            if (verify == 5) break; // sair e voltar ao menu anterior

                            while (option != 5) 
                            {
                                option = menu_restaurante();
                           
                                switch (option)
                                {
                                case 0: // sair
                                    limparCliente(lista_principal_clientes);
                                    free(lista_principal_clientes);
                                    limparEntregador(lista_principal_entregadores);
                                    free(lista_principal_entregadores);
                                    //limparRest(lista_principal_restaurantes);
                                    //free(lista_principal_restaurantes);

                                    printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)");

                                    return 0;
                                break;

                                case 1: // atualizar cardapio

                                    while (option != 4)
                                    {
                                        option = menu_cardapio_restaurante();

                                        switch (option)
                                        {
                                            case 1:

                                            printf("\n----------CARDAPIO----------\n");

                                            buscarRestCodigo(lista_principal_restaurantes, logado_restaurante.codigo, &logado_restaurante);
                                            mostrarCardapio(lista_principal_restaurantes, logado_restaurante);
                                            Sleep(2000);

                                            break;

                                            case 2:

                                                printf("\n----------INSERINDO PRATO----------\n");

                                                printf("\nMuito bem!Vamos inserir um novo prato\n");

                                                printf("Digite o nome:\n");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", novo_prato.nome);

                                                printf("Descricao:\nEx.: Bedida, Ingredientes\n:\n");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", novo_prato.descricao);

                                                printf("Entre com o preco: ");
                                                setbuf(stdin, NULL);
                                                scanf("%f", &novo_prato.preco);
 
                                                if (inserirPratoRest(lista_principal_restaurantes, novo_prato, logado_restaurante) == 0)
                                                {
                                                    printf("Item adicionado com sucesso!\n");
                                                } else {
                                                    printf("Algum erro inesperado aconteceu. Tente Novamente\n");
                                                    break;
                                                }
                                                
                                            break;
                                            
                                            case 3:
                                            printf("\n----------REMOVENDO PRATO----------\n");

                                                printf("Nome do prato a ser removido: ");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", &nome_prato);

                                                printf("Preco do prato a ser removido: ");
                                                setbuf(stdin, NULL);
                                                scanf("%f", &preco_prato);

                                            if (removerPratoRest(lista_principal_restaurantes, nome_prato, preco_prato, &logado_restaurante) == 0)
                                            {
                                                    printf("Item removido com sucesso!\n");
                                                }
                                                else
                                                {
                                                    printf("Item nao encontrado.\n");
                                                    break;
                                                }
                                            break;
                                                
                                            case 4: // voltar 
                                            break;
                                        }
                                    }
                                break;

                                case 2:; // pedidos pendentes

                                    while ((option != 3) && (option != 16))
                                    {
                                        option = menu_pedidosPendentes_restaurante();

                                        switch (option)
                                        {

                                            case 1: // mostrar a fila toda
                                                if (filaVazia(logado_restaurante.pedidosPendentes) != EMPTY_QUEUE)
                                                {
                                                    Sleep(2000);

                                                    printf("\n----------PEDIDOS PENDENTES----------\n");

                                                    mostrarPedidosPendentes(logado_restaurante.pedidosPendentes);
                                                }
                                                else
                                                    printf("Nao ha pedidos pendentes por enquanto... ;)\n");

                                            break;

                                            case 2: // mostrar apenas o proximo
                                                if (filaVazia(logado_restaurante.pedidosPendentes) != EMPTY_QUEUE)
                                                {
                                                    printf("\n----------PROXIMO PEDIDO----------\n");
                                                    consultarProxPedido(logado_restaurante.pedidosPendentes, &pedidoPendente);
                                                }
                                                else
                                                    printf("Nao ha nenhum pedido pendente por enquanto... ;)\n");

                                            break;

                                            case 3:
                                            option = 16;
                                            break;
                                        }
                                    }

                                break;

                                case 3:; // historico de pedidos

                                    while ((option != 4) && (option != 15))
                                    {
                                        option = menu_historicoPedidos_restaurante();

                                        switch (option)
                                        {

                                            case 1: // todos os pedidos ja feitos no restaurante
                                            printf("\n---------- HISTORICO ----------\n\n");

                                            if (buscarRestCodigo(lista_principal_restaurantes, logado_restaurante.codigo, &logado_restaurante) == 0)
                                            {
                                                    if (logado_restaurante.historico != NULL)
                                                    {
                                                        Sleep(2000);

                                                        printf("Aqui estao os ultimos pedidos de %s\n", logado_restaurante.nome);
                                                        mostrarHistoricoRest(logado_restaurante);
                                                    } else
                                                        printf("%s ainda nao tem pedidos concluidos\n", logado_restaurante.nome);
                                                }

                                            break;

                                            case 2: // filtrar por nome do prato

                                                if (buscarRestCodigo(lista_principal_restaurantes, logado_restaurante.codigo, &logado_restaurante) == 0)
                                                {
                                                    if (logado_restaurante.historico != NULL)
                                                    {
                                                        printf("Nome do prato: ");
                                                        setbuf(stdin, NULL);
                                                        scanf("%[^\n]s", &nome_prato);

                                                        Sleep(2000);

                                                        printf("Aqui estao os ultimos pedidos de %s\n", nome_prato);
                                                        mostrarHistoricoRestPorNomePrato(&logado_restaurante, nome_prato);
                                                    }
                                                    else
                                                        printf("%s ainda nao tem pedidos concluidos\n", logado_restaurante.nome);
                                                }

                                            break;

                                            case 3: // mostrar pedido buscado por codigo

                                                if (buscarRestCodigo(lista_principal_restaurantes, logado_restaurante.codigo, &logado_restaurante) == 0)
                                                {
                                                    if (logado_restaurante.historico != NULL)
                                                    {
                                                        printf("Entre com codigo do pedido: ");
                                                        setbuf(stdin, NULL);
                                                        scanf("%d", &codigo_pedido);
                                                        Sleep(2000);

                                                        printf("Aqui esta o pedido com codigo %d\n", codigo_pedido);
                                                        mostrarPedidoPorCodigo(&logado_restaurante, codigo_pedido);                                   
                                                    }
                                                    else
                                                        printf("%s ainda nao tem pedidos concluidos\n", logado_restaurante.nome);
                                                }
                                            break;

                                            case 4:
                                            option = 15;
                                            break;
                                        }
                                    }

                                break;
                                

                                case 4: // configuracoes

                                while ((option != 8) && (option != 17))
                                {
                                        option = menu_configuracoes_restaurante();

                                        switch (option)
                                        {

                                            case 1: // mostrar dados pessoais

                                            buscarRestCodigo(lista_principal_restaurantes, logado_restaurante.codigo, &logado_restaurante);
                                            
                                            printf("\n-------------INFORMACOES-------------\n");
                                            mostrarRestaurante(&logado_restaurante);
                                            printf("\nDigite enter para continuar...");
                                            setbuf(stdin, NULL);
                                            getchar();

                                            break;

                                            case 2: // alterar codigo de acesso

                                            verify = -1;

                                            printf("\n----------ALTERAR CODIGO----------\n");

                                            buscarRestCodigo(lista_principal_restaurantes, logado_restaurante.codigo, &logado_restaurante);

                                            while (verify != 0)
                                            {
                                                printf("\nDigite seu codigo de acesso atual: ");
                                                scanf("%d", &cod_novo);

                                                if (cod_novo != logado_restaurante.codigo)
                                                {
                                                    verify = 1;
                                                    printf("\nCodigo incorreto. Tente novamente! ");
                                                }
                                                else
                                                {
                                                    printf("\nCodigo reconhecido! ");
                                                    verify = alterarCodigoRest(lista_principal_restaurantes, logado_restaurante.codigo, &cod_novo);
                                                    buscarRestCodigo(lista_principal_restaurantes, cod_novo, &logado_restaurante);
                                                    printf("\nSeu novo codigo eh %d. \n", cod_novo);
                                                }

                                                if (verify != 0)
                                                {
                                                    printf("Deseja continuar? (Digite 1)\nPara sair sem alterar (Digite 0)\nOpcao: ");
                                                    scanf("%d", &verify);
                                                }
                                            }

                                            break;

                                            case 3: // alterar senha

                                            verify = -1;

                                            printf("\n----------ALTERAR SENHA----------\n");
                                            while (verify != 0)
                                            {
                                                printf("\nDigite sua senha atual: ");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", &senha);

                                                verify = strcmp(logado_restaurante.senha, senha);

                                                if (verify != 0)
                                                {
                                                    printf("\nSenha atual incorreta! Digite 1 para continuar ou 2 para voltar: ");
                                                    scanf("%d", &verify);
                                                }

                                                if (verify == 2)
                                                    break;
                                            }

                                            if (verify == 2)
                                                break;

                                            verify = -1;

                                            while (verify != 0)
                                            {
                                                printf("\nDigite sua nova senha: ");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", &senha);

                                                printf("\nDigite sua nova senha novamente: ");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", &confirmSenha);

                                                verify = alterarSenhaRest(lista_principal_restaurantes, logado_restaurante.codigo, senha, confirmSenha, &logado_restaurante);

                                                if (verify == 0)
                                                {
                                                    printf("\nSenha alterada com sucesso!\n");
                                                }
                                                if (verify != 0)
                                                    printf("\nSenhas diferentes. Tente novamente!\n");
                                            }

                                            break;

                                            case 4: // alterar e-mail

                                            verify = -1;
                                            printf("\n----------ALTERAR EMAIL----------\n");

                                            while (verify != 0)
                                            {

                                                printf("\nDigite sua senha atual: ");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", &senha);

                                                verify = strcmp(logado_restaurante.senha, senha);

                                                if (verify != 0)
                                                {
                                                    printf("\nSenha atual incorreta! Digite 1 para continuar ou 2 para voltar: ");
                                                    scanf("%d", &verify);
                                                }

                                                if (verify == 2)
                                                    break;
                                            }

                                            if (verify == 2)
                                                break;

                                            verify = -1;

                                            printf("\nDigite seu novo e-mail: ");
                                            setbuf(stdin, NULL);
                                            scanf("%[^\n]s", &email);

                                            verify = alterarEmailRest(lista_principal_restaurantes, logado_restaurante.codigo, email, &logado_restaurante);

                                            if (verify == 0)
                                            {
                                                printf("\nE-mail alterado com sucesso!\n");
                                            }
                                            if (verify != 0)
                                                printf("\nAlgo deu errado. Tente novamente!\n");

                                            break;

                                            case 5: // alterar categoria

                                            verify = -1;
                                            printf("\n----------ALTERAR CATEGORIA----------\n");

                                            while (verify != 0)
                                            {
                                                printf("\nDigite o codigo do restaurante: ");
                                                setbuf(stdin, NULL);
                                                scanf("%d", &codigo_loginR);

                                                verify = buscarRestCodigo(lista_principal_restaurantes, codigo_loginR, &logado_restaurante);

                                                if (verify != 0)
                                                {
                                                    printf("\nCodigo nao encontrado!\nTentar novamente (Digite 1)\nVoltar (Digite 2)\n\n");
                                                    setbuf(stdin, NULL);
                                                    scanf("%d", &verify);
                                                }

                                                if (verify == 2)
                                                    break;
                                            }

                                            if (verify == 2)
                                                break;

                                            printf("\nDigite sua nova categoria:\n");
                                            
                                            int op = menu_categoria();

                                            switch (op)
                                            {
                                                case 1:
                                                    strcpy(categoria, "Comida brasileira");
                                                break;

                                                case 2:
                                                    strcpy(categoria, "Comida estrangeira");
                                                break;

                                                case 3:
                                                    strcpy(categoria, "FastFood");
                                                break;

                                                case 4:
                                                    strcpy(categoria, "Acai e sorvetes");
                                                break;

                                                case 5:
                                                    strcpy(categoria, "Padaria e cafeteria");
                                                break;

                                                case 6:
                                                    strcpy(categoria, "Pizzaria");
                                                break;

                                                case 7:
                                                    strcpy(categoria, "Doces");
                                                break;

                                                case 8:
                                                    strcpy(categoria, "Fitness");
                                                break;

                                                case 9:
                                                    strcpy(categoria, "Bebidas");
                                                break;

                                                case 10:
                                                    strcpy(categoria, "Outros");
                                                break;
                                            }

                                            verify = alterarCategoria(lista_principal_restaurantes, logado_restaurante.codigo, categoria, &logado_restaurante);

                                            if (verify == 0)
                                            {
                                                printf("\nCategoria alterada com sucesso!\n");
                                            }
                                            if (verify != 0)
                                                printf("\nAlgo deu errado. Tente novamente!\n");

                                            break;

                                            case 6:

                                            printf("\n---------- STATUS ----------\n\n");

                                            printf("\nMuito bem. Digite o codigo do restaurante: ");
                                            setbuf(stdin, NULL);
                                            scanf("%d", &codigo_loginR);

                                            if (buscarRestCodigo(lista_principal_restaurantes, codigo_loginR, &logado_restaurante) == 0)
                                            {
                                                if (logado_restaurante.status == 1)
                                                    printf("\n%s esta aberto!\n", logado_restaurante.nome);
                                                else
                                                    printf("\n%s esta fechado!\n", logado_restaurante.nome);

                                                printf("\n1. Abrir restaurante\n2. Fechar restaurante\nOpcao: ");
                                                scanf("%d", &verify);

                                                if (alterarStatusRest(lista_principal_restaurantes, logado_restaurante.codigo, verify, &logado_restaurante.status) == 0)
                                                {
                                                    if (logado_restaurante.status == 1)
                                                        printf("\n%s esta aberto!\n", logado_restaurante.nome);
                                                    else
                                                        printf("\n%s esta fechado!\n", logado_restaurante.nome);
                                                } else
                                                    printf("Algo deu errado, tente novamente!\n");
                                            } else
                                                printf("Codigo errado, tente novamente!\n");

                                            break;

                                            case 7: // apagar conta
                                            printf("\n----------APAGAR CONTA----------\n");

                                            printf("\nVoce esta prestes a apagar esta conta e tudo que esta contido nela. Voce tem certeza? ");
                                            printf("\n1. Sim\n2. Nao\nOpcao: ");
                                            scanf("%d", &verify);

                                            if (verify == 1)
                                            {
                                                printf("\nMuito bem. Digite sua senha: ");
                                                setbuf(stdin, NULL);
                                                scanf("%[^\n]s", senha);

                                                verify = strcmp(logado_restaurante.senha, senha);

                                                if (verify == 0)
                                                {
                                                    verify = removerRestCodigo(lista_principal_restaurantes, logado_restaurante.codigo);

                                                    if (verify == 0)
                                                    {
                                                        printf("\nFoi um prazer ter voce conosco! Sua conta foi excluida com sucesso.");
                                                        limpar_variavel_rest(&logado_restaurante);
                                                        option = 17;
                                                    }
                                                    else
                                                    {
                                                        printf("\nHouve algum erro. Tente novamente.");
                                                    }
                                                }
                                                else
                                                {
                                                    printf("\nSenha incorreta. Tente novamente.");
                                                    option = -1;
                                                }
                                                break;
                                                }

                                                if (verify != 1)
                                                {
                                                    option = -1;
                                                    break;
                                                }
                                            break;

                                            case 8: // voltar
                                            break;
                                        }
                                    }
                                    if (option == 17) option = 5;
                                break;

                                case 5: //sair da conta (voltar)
                                break;     
                            }
                        }
                    break;
                        
                    case 3: // Voltar
                    break;
                }
            }
        break;

        case 3:; // sou entregador

                option = -1;

                while (option != 3) // voltar
                {
                    option = menu_inicial_entregador();
                    verify = -1;

                    switch (option)
                    {

                        case 0: // sair
                            limparCliente(lista_principal_clientes);
                            free(lista_principal_clientes);
                            limparEntregador(lista_principal_entregadores);
                            free(lista_principal_entregadores);
                            //limparRest(lista_principal_restaurantes);
                            //free(lista_principal_restaurantes);
                            
                            printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)");
                            
                            return 0;
                        break;

                        case 1: // cadastrar entregador

                        printf("\n---------- CADASTRO ----------\n\n");
                        printf("\nMuito bem! Vamos te cadastrar como entregador: ");

                        printf("\nDigite seu nome: ");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]s", &novo_entregador.nome);

                        printf("\nDigite seu CPF (somente numeros): ");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]s", &novo_entregador.cpf);

                        printf("\nDigite seu e-mail: ");
                        setbuf(stdin, NULL);
                        scanf("%[^\n]s", &novo_entregador.email);

                        inicializar_entregador(&novo_entregador);

                        verify = -1;

                        if ((inserirFimEntregador(lista_principal_entregadores, novo_entregador, &cod_novo)) == 0)
                            printf("\nCadastro realizado com sucesso! Bem vindo, %s! Seu novo codigo de acesso eh: %d.", novo_entregador.nome, cod_novo);
                        limpar_variavel_entregador(&novo_entregador);

                        break;

                        case 2: // login entregador

                        printf("\n---------- LOGIN ----------\n\n");
                        verify = -1;

                        while (verify != 0)
                        {
                            printf("\nDigite o seu e-mail: ");
                            setbuf(stdin, NULL);
                            scanf("%[^\n]s", &email);

                            printf("\nDigite o seu codigo de acesso: ");
                            scanf("%d", &codigo_loginE);

                            verify = loginCodigo(lista_principal_entregadores, email, codigo_loginE, &logado_entregador);

                            if (verify == 0)
                            {
                                printf("\nBem vindo de volta, %s!", logado_entregador.nome);
                                break;
                            }
                            else
                            {
                                printf("\nOcorreu algum erro. Tente novamente! \n");
                            }

                            if (verify == 0)
                                break;

                            printf("\nDigite 5 para voltar, 6 se esqueceu o codigo de acesso e 0 para continuar: ");
                            scanf("%d", &verify);

                            if (verify == 5)
                                break;
                            if (verify == 6) // preciso fazer verificação de status == 1 ou == 0
                            {
                                while (verify != 0)
                                {
                                        printf("\n----------ALTERAR CODIGO----------\n");

                                        printf("\nDigite o seu e-mail:");
                                        setbuf(stdin, NULL);
                                        scanf("%[^\n]s", &email);

                                        printf("\nAgora digite o seu CPF (sem espacos): ");
                                        setbuf(stdin, NULL);
                                        scanf("%[^\n]s", &cpf);

                                        verify = buscarEntregadorEmailCPF(lista_principal_entregadores, email, cpf, &esqueceu_senha_entregador);

                                        if (verify == 0)
                                        {
                                            printf("\nTe encontramos!");
                                            if (esqueceu_senha_entregador.status == 1)
                                            {
                                                verify = 15;
                                                printf ("\nInfelizmente voce esta em uma corrida e nao pode alterar seu codigo. Tente novamente mais tarde.\n");
                                                break;
                                            }
                                            trocaCodigo(lista_principal_entregadores, esqueceu_senha_entregador.codigo, &cod_novo);
                                            printf ("\nSeu novo codigo eh: %d.", cod_novo);
                                        }
                                        else
                                        {
                                            printf ("\nAlgo esta errado. Tente novamente! ");
                                            printf ("\nDigite 0 para sair ou 1 para continuar: ");
                                            scanf ("%d", &verify);
                                        }
                                    }
                                }
                                if (verify == 0) verify = 1;
                                if (verify == 15)
                                {
                                    verify = 5;
                                    break;
                                }
                            }

                            if (verify == 5) break;

                            while (option != 5)
                            {
                                option = menu_entregador();

                                switch (option)
                                {
                                    case 0: // sair
                                        limparCliente(lista_principal_clientes);
                                        free(lista_principal_clientes);
                                        limparEntregador(lista_principal_entregadores);
                                        free(lista_principal_entregadores);
                                        //limparRest(lista_principal_restaurantes);
                                        //free(lista_principal_restaurantes);
                                        
                                        printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)");

                                        return 0;
                                    break;

                                    case 1:; // mostrar corrida atual (pedido em andamento)

                                    printf("\n----------CORRIDA ATUAL----------\n");

                                    pedidos em_andamento_entregador;
                                    int i;

                                    verify = 0;

                                    verify = buscarPedidoAndamentoEntregador(controlePedidos, qtdPratosPedidosAndamento, logado_entregador.codigo, &em_andamento_entregador);

                                    if (verify == 0)
                                    {
                                        printf("\nVoce nao esta em uma corrida atualmente! ");
                                        }
                                        else
                                        {
                                            printf ("\nAqui estao as informacoes sobre sua corrida atual:\n");
                                            printf ("Nome do restaurante: %s\n", em_andamento_entregador.nome_rest);
                                            printf ("Itens do pedido:\n");
                                            for (i = 0; i < em_andamento_entregador.qtdPratosPed; i++)
                                            {
                                                printf ("%d. %s\n", i+1, em_andamento_entregador.pratosPed[i].nome);
                                            }
                                            printf ("\n\nDigite enter para continuar...");
                                            setbuf (stdin, NULL);
                                            getchar();
                                        }
                                    break;

                                    case 2: // mostrar nota

                                        printf("\n----------NOTA----------\n");

                                        buscarItemEntregador (lista_principal_entregadores, logado_entregador.codigo, &logado_entregador);
                                        printf ("\nVoce foi avaliado por %d clientes!", logado_entregador.rank.quantidade);
                                        printf ("\nSua nota eh %.1f! ", logado_entregador.rank.media);
                                        if (logado_entregador.rank.media >= 4)
                                        {
                                            printf ("\nContinue o bom trabalho! ");
                                        }
                                        else
                                        {
                                            printf ("\nTalvez voce precise melhorar. ");
                                        }
                                    break;

                                    case 3: // mostrar historico
                                        buscarItemEntregador (lista_principal_entregadores, logado_entregador.codigo, &logado_entregador);
                                        printf ("\nAqui estao seus ultimos pedidos: \n");
                                        mostrar_pedidos_entregador (logado_entregador);
                                    break;

                                    case 4:
                                        while (option != 5 && option != 15 && option != 14)
                                        {
                                            option = menu_config_entregador();

                                            switch (option)
                                            {
                                                case 1: // mostrar dados pessoais
                                                    buscarItemEntregador (lista_principal_entregadores, logado_entregador.codigo, &logado_entregador);
                                                    
                                                    printf ("\n\n-------------INFORMACOES-------------\n");
                                                    printf ("\nNome: %s", logado_entregador.nome);
                                                    printf ("\nCPF: %s", logado_entregador.cpf);
                                                    printf ("\nE-mail: %s", logado_entregador.email);
                                                    printf ("\nSeu codigo de acesso eh: %d.", logado_entregador.codigo);
                                                    
                                                    if (logado_entregador.status == 1) printf ("\nVoce esta em uma corrida atualmente!\n ");
                                                    else printf ("\nVoce nao esta em uma corrida!\n");
                                                    
                                                    printf ("\nAperte enter para continuar ");
                                                    setbuf (stdin, NULL);
                                                    getchar();
                                                break;

                                                case 2: // alterar codigo de acesso // se estiver em corrida nao poderá alterar

                                                    verify = -1;
                                                    printf("\n----------ALTERAR CODIGO----------\n");

                                                    buscarItemEntregador(lista_principal_entregadores, logado_entregador.codigo, &logado_entregador);
                                                    if (logado_entregador.status == 1)
                                                    {
                                                        printf ("\nInfelizmente voce nao pode alterar seu codigo durante uma corrida! Tente novamente mais tarde.\n ");
                                                        verify = 0;
                                                    }

                                                    while (verify != 0)
                                                    {
                                                        printf ("\nDigite seu codigo de acesso atual: ");
                                                        scanf ("%d", &cod_novo);

                                                        if (cod_novo != logado_entregador.codigo)
                                                        {
                                                            verify = 1;
                                                            printf ("\nCodigo incorreto. Tente novamente! ");
                                                        }
                                                        else
                                                        {
                                                            //verify = 0;
                                                            printf ("\nCodigo reconhecido! ");
                                                            verify = trocaCodigo (lista_principal_entregadores, logado_entregador.codigo, &cod_novo);
                                                            buscarItemEntregador (lista_principal_entregadores, cod_novo, &logado_entregador);
                                                            printf ("\nSeu novo codigo eh %d. \n", cod_novo);
                                                        }

                                                        if (verify != 0)
                                                        {
                                                            printf ("Digite 1 para continuar ou 0 para sair sem alterar: ");
                                                            scanf ("%d", &verify);
                                                        }
                                                    }
                                                break;

                                                case 3: // alterar email
                                                    
                                                    verify = -1;

                                                    printf("\n----------ALTERAR EMAIL----------\n");

                                                    while (verify != 0)
                                                    {
                                                        printf ("\nDigite seu codigo de acesso atual: ");
                                                        scanf ("%d", &cod_novo);

                                                        if (cod_novo != logado_entregador.codigo)
                                                        {
                                                            verify = 1;
                                                            printf ("\nCodigo incorreto. Tente novamente! ");
                                                        }
                                                        else
                                                        {
                                                            //verify = 0;
                                                            printf ("\nCodigo reconhecido! ");

                                                            printf ("\nDigite seu novo e-mail: ");
                                                            setbuf (stdin, NULL);
                                                            scanf ("%[^\n]s", &email);

                                                            verify = trocaEmail(lista_principal_entregadores, logado_entregador.codigo, email);
                                                        }

                                                        if (verify != 0)
                                                        {
                                                            printf ("Digite 1 para continuar ou 0 para sair sem alterar: ");
                                                            scanf ("%d", &verify);
                                                        }
                                                        else printf ("\nE-mail alterado com sucesso! ");
                                                    }
                                                break;

                                                case 4: // excluir conta // se estiver em corrida não poderá excluir

                                                printf("\n----------EXCLUIR CONTA----------\n");

                                                verify = -1;

                                                buscarItemEntregador(lista_principal_entregadores, logado_entregador.codigo, &logado_entregador);
                                                if (logado_entregador.status == 1)
                                                {
                                                        printf ("\nInfelizmente voce nao pode excluir sua conta durante uma corrida! Tente novamente mais tarde.\n ");
                                                        verify = 0;
                                                    }

                                                    if (verify == 0)
                                                    {
                                                        option = -1;
                                                        break;
                                                    }

                                                    printf("\nVoce esta prestes a apagar sua conta e tudo que esta contido nela. Voce tem certeza? ");
                                                    printf("\nDigite 1 para sim e 2 para nao: ");
                                                    scanf("%d", &verify);

                                                    if (verify == 1)
                                                    {
                                                        codigo_loginE = 0;

                                                        printf("\nMuito bem. Digite seu codigo de acesso: ");
                                                        scanf("%d", &codigo_loginE);

                                                        if (logado_entregador.codigo == codigo_loginE) verify = 0;

                                                        if (verify == 0)
                                                        {
                                                            verify = removerItemEntregador (lista_principal_entregadores, codigo_loginE);

                                                            if (verify == 0)
                                                            {
                                                                printf("\nFoi um prazer ter voce conosco! Sua conta foi excluida com sucesso.");
                                                                limpar_variavel_entregador (&logado_entregador);
                                                                option = 15;
                                                            }
                                                            else
                                                            {
                                                                printf("\nHouve algum erro. Tente novamente.");
                                                            }
                                                        }
                                                        else
                                                        {
                                                            printf("\nCodigo incorreto. Tente novamente.");
                                                            option = -1;
                                                        }
                                                        break;
                                                    }

                                                    if (verify != 1)
                                                    {
                                                        option = -1;
                                                        break;
                                                    }
                                                break;

                                                case 5:
                                                    option = 14;
                                                break;
                                            }

                                        }
                                        if (option == 15) option = 5;
                                    break;

                                    case 5: // sair da conta
                                    break;
                                }
                            }
                        break;

                        case 3:
                        break;
                    }
                }

            break;

            case 4:; // sou adm

                char teste_login[15];
                char teste_senha[15];
                verify = -1;

                while(verify != 0)
                {
                    printf ("\n------------LOGIN------------\n");

                    printf("\nDigite o login de administrador: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]s", &teste_login);

                    printf("\nDigite a senha de administrador: ");
                    setbuf(stdin, NULL);
                    scanf("%[^\n]s", &teste_senha);

                    if ((strcmp(teste_login, loginADM) == 0) && strcmp(teste_senha, senhaADM) == 0) verify = 0;
                    else
                    {
                        printf ("\nLogin ou senha errados. Tente novamente!\n");
                        printf ("Digite 0 para continuar ou 1 para sair: ");
                        scanf ("%d", &verify);
                        if (verify == 0) verify = -1;
                    }
                    if (verify != 0 && verify != -1) break;
                }
                if (verify != 0) break;

                printf("\nBem-vindo, ADM!");

                while (option != 8)
                {
                    option = menu_adm();

                    switch (option)
                    {
                        case 0: // sair
                            limparCliente(lista_principal_clientes);
                            free(lista_principal_clientes);
                            limparEntregador(lista_principal_entregadores);
                            free(lista_principal_entregadores);
                            //limparRest(lista_principal_restaurantes);
                            //free(lista_principal_restaurantes);
                            
                            printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)");
                            
                            return 0;
                        break;

                        case 1: // mostrar clientes
                            mostrar_tudo_cliente (lista_principal_clientes);
                        break;

                        case 2: // mostrar entregadores
                            mostrar_tudo_entregador (lista_principal_entregadores);
                        break;

                        case 3: // mostrar restaurantes
                        break;

                        case 4: // mostrar pedidos em andamento
                            mostrarPedidosGlobais (controlePedidos, qtdPratosPedidosAndamento);
                        break;

                        case 5: // inicializar restaurantes

                        /*  restaurante teste;
                            strcpy(teste.nome, "Fast Acai");
                            strcpy(teste.email, "fast@gmail.com");
                            strcpy(teste.senha, "bem vinde");
                            inicializar_restaurante(&teste);
                            inserirInicioRest(lista_principal_restaurantes, teste);
                            mostrarListaRest(lista_principal_restaurantes);
                            pratos r;
                            strcpy(r.nome, "macarrao");
                            strcpy(r.descricao, "molho branco");
                            r.preco = 20.52;
                            inserirPratoRest(lista_principal_restaurantes, r, &teste);
                            printf("[ Cardapio ]\n");
                            mostrarCardapio(lista_principal_restaurantes, &teste);

                        */

                        limparVariavelRest(&base_rest);

                        strcpy(base_rest.nome, "Fast Acai");
                        strcpy(base_rest.email, "fast@gmail.com");
                        strcpy(base_rest.senha, "fast123");
                        strcpy(base_rest.categoria, "Acai e sorvetes");

                        inserirFimRest(lista_principal_restaurantes, &base_rest);
                        buscarRestNome(lista_principal_restaurantes, base_rest.nome, &base_rest);

                        strcpy(base_restPratos.nome, "Acai tropical");
                        strcpy(base_restPratos.descricao, "tigela 500ml");
                        base_restPratos.preco = 19.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Acai tropical");
                        strcpy(base_restPratos.descricao, "tigela 750ml");
                        base_restPratos.preco = 24.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Acai com Ninho e Morango");
                        strcpy(base_restPratos.descricao, "tigela 500ml");
                        base_restPratos.preco = 19.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Acai com Ninho e Morango");
                        strcpy(base_restPratos.descricao, "tigela 750ml");
                        base_restPratos.preco = 24.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Choco Acai");
                        strcpy(base_restPratos.descricao, "tigela 500ml");
                        base_restPratos.preco = 19.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Choco Acai");
                        strcpy(base_restPratos.descricao, "tigela 750ml");
                        base_restPratos.preco = 24.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        limpar_variavel_rest(&base_rest);

                        strcpy(base_rest.nome, "Estacao Acai");
                        strcpy(base_rest.email, "estacao@gmail.com");
                        strcpy(base_rest.senha, "estacao123");
                        strcpy(base_rest.categoria, "Acai e sorvetes");

                        inserirFimRest(lista_principal_restaurantes, &base_rest);
                        buscarRestNome(lista_principal_restaurantes, base_rest.nome, &base_rest);

                        strcpy(base_restPratos.nome, "Acai Oreo");
                        strcpy(base_restPratos.descricao, "tigela 500ml");
                        base_restPratos.preco = 22.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Acai Oreo");
                        strcpy(base_restPratos.descricao, "tigela 750ml");
                        base_restPratos.preco = 26.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Acai Tradicional");
                        strcpy(base_restPratos.descricao, "tigela 500ml");
                        base_restPratos.preco = 22.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Acai Tradicional");
                        strcpy(base_restPratos.descricao, "tigela 750ml");
                        base_restPratos.preco = 26.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Vitamina de Morango");
                        strcpy(base_restPratos.descricao, "500ml");
                        base_restPratos.preco = 22.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Vitamina de Morango");
                        strcpy(base_restPratos.descricao, "750ml");
                        base_restPratos.preco = 26.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        limpar_variavel_rest(&base_rest);

                        strcpy(base_rest.nome, "Kaisen Sushi");
                        strcpy(base_rest.email, "kaisen@gmail.com");
                        strcpy(base_rest.senha, "kaisen123");
                        strcpy(base_rest.categoria, "Comida Estrangeira");

                        inserirFimRest(lista_principal_restaurantes, &base_rest);
                        buscarRestNome(lista_principal_restaurantes, base_rest.nome, &base_rest);

                        strcpy(base_restPratos.nome, "Hot Rolls");
                        strcpy(base_restPratos.descricao, "10 pecas");
                        base_restPratos.preco = 19.50;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Sashimi");
                        strcpy(base_restPratos.descricao, "10 pecas");
                        base_restPratos.preco = 29.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Ramen");
                        strcpy(base_restPratos.descricao, "macarrao, molho de carne, ovo, carne");
                        base_restPratos.preco = 29.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        limpar_variavel_rest(&base_rest);

                        strcpy(base_rest.nome, "Mc Donalds");
                        strcpy(base_rest.email, "mc@gmail.com");
                        strcpy(base_rest.senha, "mc123");
                        strcpy(base_rest.categoria, "FastFood");

                        inserirFimRest(lista_principal_restaurantes, &base_rest);
                        buscarRestNome(lista_principal_restaurantes, base_rest.nome, &base_rest);

                        strcpy(base_restPratos.nome, "Big Mac");
                        strcpy(base_restPratos.descricao, "2 hamburguers, alface, tomate, molho maionese");
                        base_restPratos.preco = 30.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Big Tasty");
                        strcpy(base_restPratos.descricao, "hamburguer, alface, tomate, molho especial");
                        base_restPratos.preco = 40.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Nuggets");
                        strcpy(base_restPratos.descricao, "10 unidades");
                        base_restPratos.preco = 21.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        limpar_variavel_rest(&base_rest);

                        strcpy(base_rest.nome, "Burguer King");
                        strcpy(base_rest.email, "bk@gmail.com");
                        strcpy(base_rest.senha, "bk123");
                        strcpy(base_rest.categoria, "FastFood");

                        inserirFimRest(lista_principal_restaurantes, &base_rest);
                        buscarRestNome(lista_principal_restaurantes, base_rest.nome, &base_rest);

                        strcpy(base_restPratos.nome, "Stacker Duplo");
                        strcpy(base_restPratos.descricao, "1 hamburguer, bacon, cheddar, alface");
                        base_restPratos.preco = 15.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Coca Cola");
                        strcpy(base_restPratos.descricao, "bebida");
                        base_restPratos.preco = 6.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Whopper");
                        strcpy(base_restPratos.descricao, "1 hamburguer, picles, alface, tomate");
                        base_restPratos.preco = 19.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);


                        limpar_variavel_rest(&base_rest);

                        strcpy(base_rest.nome, "Casa Mexicana");
                        strcpy(base_rest.email, "mexico@gmail.com");
                        strcpy(base_rest.senha, "mexico123");
                        strcpy(base_rest.categoria, "Comida Estrangeira");

                        inserirFimRest(lista_principal_restaurantes, &base_rest);
                        buscarRestNome(lista_principal_restaurantes, base_rest.nome, &base_rest);

                        strcpy(base_restPratos.nome, "Tacos");
                        strcpy(base_restPratos.descricao, "carne moida, chips, queijo, guacamole, salsa");
                        base_restPratos.preco = 32.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Burrito");
                        strcpy(base_restPratos.descricao, "tortilha, carne moida, milho, salsa queijo");
                        base_restPratos.preco = 19.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Fanta");
                        strcpy(base_restPratos.descricao, "bebida");
                        base_restPratos.preco = 19.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        limpar_variavel_rest(&base_rest);
                        strcpy(base_rest.nome, "Porto Alegre");
                        strcpy(base_rest.email, "PA@gmail.com");
                        strcpy(base_rest.senha, "PA123");
                        strcpy(base_rest.categoria, "Pizzaria");

                        inserirFimRest(lista_principal_restaurantes, &base_rest);
                        buscarRestNome(lista_principal_restaurantes, base_rest.nome, &base_rest);

                        strcpy(base_restPratos.nome, "Frango Catupiry");
                        strcpy(base_restPratos.descricao, "Tamanho Familia");
                        base_restPratos.preco = 30.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Da Casa");
                        strcpy(base_restPratos.descricao, "Grande");
                        base_restPratos.preco = 24.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        strcpy(base_restPratos.nome, "Romeu e Julieta");
                        strcpy(base_restPratos.descricao, "Grande");
                        base_restPratos.preco = 19.99;
                        inserirPratoRest(lista_principal_restaurantes, base_restPratos, base_rest);

                        limpar_variavel_rest(&base_rest);

                        break;

                        case 6: // voltar
                        break;
                    }
                }
            break;

            case 5: // sobre
                // aqui será inserido uma mensagem completa sobre o codigo e coisas do tipo
                printf("\n----------SOBRE NOS----------\n");

                printf ("\n\nObrigado por se interessar mais sobre o processo de producao do app.");
                printf ("\nEste aplicativo foi feito para o trabalho de conclusao de disciplina da materia de Algoritmos e Estruturas de Dados 1.");
                printf ("\n\nO grupo eh composto por:\n");
                printf ("\tJean Souto Galvao Moreira @jean.soutoo        ");
                printf ("\tEster Camilly Simplicio de Freitas @esterzolas");
                printf ("\tAna Alice Cordeiro de Souza @alicecordeiro    ");
                printf ("\n                         Fernanda lalala     ");
                printf ("\n\nO objetivo do trabalho eh aplicar todos os conceitos aprendidos em sala e garantir o pleno funcionamento do aplicativo.");
                printf (" Alem disso, o tema deste aplicativo eh 'gerenciador de pedidos em restaurantes', algo como um 'ifood'.");
                printf ("\nEsperamos que tenha gostado e tenha sido uma boa experiencia. Muito obrigado! :)");
            break;
            
        }
    }

    limparCliente(lista_principal_clientes);
    free(lista_principal_clientes);
    limparEntregador(lista_principal_entregadores);
    free(lista_principal_entregadores);
    limparRest(lista_principal_restaurantes);
    free(lista_principal_restaurantes);
    
    printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)");

    return 0;
}

// FUNÇÕES EXTRAS RELACIONADAS ÀS STRUCTS EXTRAS

void copiarPedidoCpC(pedidos *A, pedidos *B) // criar possivel funcao que copiará pedido para pedido entre tipos de pedidos e tals
{
    int i;
    B->codigo = A->codigo;
    B->qtdPratosPed = A->qtdPratosPed;
    B->precoTotal = A->precoTotal;
    strcpy(B->nome_rest, A->nome_rest);

    B->pratosPed = (pratos*) malloc (A->qtdPratosPed*sizeof(pratos));

    for (i = 0; i < A->qtdPratosPed; i++)
    {
        B->pratosPed[i].preco = A->pratosPed[i].preco;
        strcpy(B->pratosPed[i].descricao, A->pratosPed[i].descricao);
        strcpy(B->pratosPed[i].nome, A->pratosPed[i].nome);
    }
}

/*pratos* copiarPpP (pratos *A, int tam)
{
    int i = 0;
    tam = 0;

    B = (pratos*) malloc (tam*sizeof(pratos));

    for (i = 0; i < tam; i++)
    {
        B[i].preco = A[i].preco;
        strcpy(B[i].nome, A[i].nome);
        strcpy(B[i].descricao, A[i].descricao);
    }

    return 
}*/

pedidosglobais* inserirControleGlobal(pedidosglobais *pg, entregador entregador_atual, pedidos pedido_atual, Cliente cliente_atual, int *qtd)
{
    (*qtd)++;
    int j = *qtd;

    if(pg == NULL) pg = (pedidosglobais*) malloc (sizeof(pedidosglobais));
    pg = (pedidosglobais*) realloc (pg, j*sizeof(pedidosglobais));

    int i = *qtd - 1;

    copiarEntregador(&entregador_atual, &pg[i].entregador_do_pedido);
    copiarPedidoCpC(&pedido_atual, &pg[i].pedido_em_andamento);
    copiarCliente(&cliente_atual, &pg[i].comprador);

    return pg;
}

pedidosglobais* removerControleGlobal(pedidosglobais *pg, int numero_pedido, int *qtd, Lista_cliente *l_cliente, Lista_entregadores *l_entregador, Lista_restaurantes *l_restaurante, float nota) // deve remover do controle, liberar entregador e adicionar aos historicos
{
    int i, rem = 0;
    pedidos temp;

    for (i = 0; i < *qtd; i++)
    {
        if (pg[i].pedido_em_andamento.codigo == numero_pedido)
        {
            rem = i;
        }
    }

    copiarPedidoCpC (&pg[rem].pedido_em_andamento, &temp);
    
    inserirPedidoHistoricoEntregador (l_entregador, pg[rem].entregador_do_pedido.codigo, temp);
    inserirPedidoHistorico (l_cliente, pg[rem].comprador.codigo, temp);
    inserirPedidoHistoricoRestNome (l_restaurante, pg[rem].pedido_em_andamento.nome_rest, temp);

    adicionarCorridaNota(l_entregador, pg[rem].entregador_do_pedido.codigo, nota); // adiciona a nota ao entregador e libera ele

    for (i = rem; i < *qtd-1; i++)
    {
        copiarCliente(&(pg[i].comprador), &(pg[i+1].comprador));
        copiarEntregador(&(pg[i].entregador_do_pedido), &(pg[i+1].entregador_do_pedido));
        copiarPedidoCpC (&(pg[i].pedido_em_andamento), &(pg[i+1].pedido_em_andamento));
    }

    (*qtd)--;
    pg = (pedidosglobais *)realloc(pg, (*qtd) * sizeof(pedidosglobais));
    return pg;
}

pedidos* buscarPedidoAndamento (pedidosglobais *pg, int qtd, int codigo_cliente, int *num_pedidos) // talvez o problema está aqui na hr de fazer o vetor em andamento // testar com um pedido só pra ver o q acontece
{
    pedidos *em_andamento;
    int i = 0;

    *num_pedidos = 0;

    em_andamento = (pedidos*) malloc (sizeof(pedidos));

    for (i = 0; i < qtd; i++)
    {
        if (pg[i].comprador.codigo == codigo_cliente)
        {
            (*num_pedidos)++;
            em_andamento = (pedidos*) realloc (em_andamento, (*num_pedidos) * sizeof(pedidos));
            copiarPedidoCpC (&(pg[i].pedido_em_andamento), &em_andamento[(*num_pedidos)-1]);
        }
    }
    return em_andamento;
}

int buscarPedidoAndamentoEntregador (pedidosglobais *pg, int qtd, int codigo_entregador, pedidos *em_andamento)
{
    int i = 0;

    for (i = 0; i < qtd; i++)
    {
        if (pg[i].entregador_do_pedido.codigo == codigo_entregador)
        {
            copiarPedidoCpC (&(pg[i].pedido_em_andamento), &(*em_andamento));
            return 1;
        }
    }
    return 0;
}

void mostrarPedidosGlobais (pedidosglobais *pg, int qtd)
{
    int i;

    for (i = 0; i < qtd; i++)
    {
        printf ("\n%d.\nNome restaurante: %s", i+1, pg[i].pedido_em_andamento.nome_rest);
        printf ("\nNome entregador: %s", pg[i].entregador_do_pedido.nome);
        printf ("\nNome cliente: %s\n", pg[i].comprador.nome);
    }
}

pratos* adicionarPratoPed (int *qtd, pratos *novo_prato_vet, pratos novo_prato)
{
    pratos *novo_prato_vet2;
    
    if (novo_prato_vet == NULL)
    {
        novo_prato_vet2 = (pratos*) malloc (sizeof (pratos));
        novo_prato_vet2[*qtd].preco = novo_prato.preco;
        strcpy (novo_prato_vet2[*qtd].nome, novo_prato.nome);
        strcpy (novo_prato_vet2[*qtd].descricao, novo_prato.descricao);
        (*qtd)++;
    }
    else 
    {
        int i = 0;
        novo_prato_vet2 = (pratos*) malloc ((*qtd+1)*sizeof(pratos));

        for (i = 0; i < *qtd; i++)
        {
            novo_prato_vet2[i].preco = novo_prato_vet[i].preco;
            strcpy (novo_prato_vet2[i].nome, novo_prato_vet[i].nome);
            strcpy (novo_prato_vet2[i].descricao, novo_prato_vet[i].descricao);
        }

        novo_prato_vet2[*qtd].preco = novo_prato.preco;
        strcpy (novo_prato_vet2[*qtd].nome, novo_prato.nome);
        strcpy (novo_prato_vet2[*qtd].descricao, novo_prato.descricao);

        (*qtd)++;
    }
    return novo_prato_vet2;
}

// funções extras

void inicializar_entregador(entregador *item) // usada ao criar um novo cadastro de entregador (zera todas as informações para evitar lixo e erros)
{
    item->corridas = 0;
    item->status = 0;
    item->rank.media = 0.0;
    item->rank.quantidade = 0;
    item->rank.total = 0;
    item->quant_pedidos = 0;
    item->historico = NULL;
}

void limpar_variavel_entregador(entregador *item) // limpa a variavel para evitar erros ao sobrepor
{
    strcpy(item->cpf, "000");
    strcpy(item->email, "000");
    strcpy(item->nome, "000");
    item->codigo = -1;
    inicializar_entregador(item);
}

void inicializar_cliente(Cliente *item) // usada ao criar um novo_cliente cadastro de entregador (zera todas as informações para evitar lixo e erros)
{
    item->gasto_total = 0;
    item->quantidade_cartoes = 0;
    item->quant_pedidos = 0;
    item->quant_enderecos = 0;
    item->historico = NULL;
    item->pagamentos = NULL;
    item->enderecos = NULL;
}

void inicializar_restaurante(restaurante *item)
{
    strcpy(item->categoria, "-");
    item->cardapio = NULL;
    item->qtdCardapio = 0;
    item->historico = NULL;
    item->qtdHistorico = 0;
    item->status = -1;
    item->pedidosPendentes = criar_filaPedidosPendentes();
}

void limpar_variavel_prato (pratos *item)
{
    strcpy(item->nome, "-");
    strcpy(item->descricao, "-");
    item->preco = -1;
}

int confirmarSenha(char *str1, char *str2)
{
    if (strlen(str1) != strlen(str2))
        return 3;

    int tam = strlen(str1);

    for (int i = 0; i <= tam; i++)
        if (str1[i] != str2[i])
            return 1;
    return 0;
}

void limpar_variavel_cliente(Cliente *item) // limpa a variavel para evitar erros ao sobrepor
{
    strcpy(item->cpf, "000");
    strcpy(item->email, "000");
    strcpy(item->nome, "000");
    strcpy(item->senha_8d, "000");
    item->codigo = -1;
    inicializar_cliente(item);
}

void limpar_variavel_rest(restaurante *item) // limpa a variavel para evitar erros ao sobrepor
{
    strcpy(item->email, "000");
    strcpy(item->nome, "000");
    strcpy(item->senha, "000");
    item->codigo = -1;
    inicializar_restaurante(item);
}

void mostrarCardapioItem (restaurante item)
{
    int i; 

    printf ("( ");
    for (i = 0; i < item.qtdCardapio; i++)
    {
        printf ("%d. {Nome do prato: %s / Descricao: %s / Valor: %.2f} ", i+1, item.cardapio[i].nome, item.cardapio[i].descricao, item.cardapio[i].preco);
    }
    printf (")");
}

// MENUS

int menu_inicial() // permite a escolha entre os diferentes usuários
{
    int op = -1;
    int i;
    do
    {
        //system ("cls");
         printf("\xDA");
    for (i = 0; i < 23; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3     Menu Inicial    \xB3\n");

    printf("\xC3");
    for (i = 0; i < 23; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3 Selecione uma opcao \xB3\n");
    printf("\xB3 1. Sou Cliente      \xB3\n");
    printf("\xB3 2. Sou Restaurante    \xB3\n");
    printf("\xB3 3. Sou Entregador     \xB3\n");
    printf("\xB3 4. Sou Administrador  \xB3\n");
    printf("\xB3 5. Sobre o app        \xB3\n");
    printf("\xB3 0. Sair               \xB3\n");

    printf("\xC0");
    for (i = 0; i < 23; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");
    printf("Opcao: \n");
        scanf("%d", &op);
        if (op < 0 || op > 5)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 5);
    return op;
}

int menu_inicial_cliente() // permite ao cliente escolher
{
    int op = -1;
    int i;
    do
    {
        //system ("cls");
        printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 23; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3 Menu Cadastro Cliente \xB3\n");

    printf("\xC3");
    for (i = 0; i < 23; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3 Selecione uma opcao   \xB3\n");
    printf("\xB3 1. Quero me cadastrar \xB3\n");
    printf("\xB3 2. Ja tenho cadastro  \xB3\n");
    printf("\xB3 3. Voltar             \xB3\n");
    printf("\xB3 0. Sair               \xB3\n");

    printf("\xC0");
    for (i = 0; i < 23; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");
    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 4)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 4);
    return op;
}

int menu_cliente() // permite ao cliente escolher após logado
{
    int op = -1;
    int i;
    do
    {
        printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 29; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3         Menu Cliente        \xB3\n");

    printf("\xC3");
    for (i = 0; i < 29; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3     Selecione uma opcao     \xB3\n");
    printf("\xB3 1. Fazer pedido             \xB3\n");
    printf("\xB3 2. Historico de pedidos     \xB3\n");
    printf("\xB3 3. Cartoes                  \xB3\n");
    printf("\xB3 4. Enderecos                \xB3\n");
    printf("\xB3 5. Confirmar entrega        \xB3\n");
    printf("\xB3 6. Configuracoes            \xB3\n");
    printf("\xB3 7. Sair da conta            \xB3\n");
    printf("\xB3 0. Sair do app              \xB3\n");

    printf("\xC0");
    for (i = 0; i < 29; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 7) printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 7);
    return op;
}

int menu_pedido_cliente() // permite ao cliente escolher após logado
{
    int op = -1;
    int i;
    do
    {
         printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 34; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3        Menu Pedido Cliente       \xB3\n");

    printf("\xC3");
    for (i = 0; i < 34; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3        Selecione uma opcao       \xB3\n");
    printf("\xB3 1. Mostrar todos os restaurantes \xB3\n");
    printf("\xB3 2. Filtrar por categoria         \xB3\n");
    printf("\xB3 3. Procurar por nome             \xB3\n");
    printf("\xB3 4. Voltar                        \xB3\n");

    printf("\xC0");
    for (i = 0; i < 34; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 1 || op > 4) printf("\nDigite uma opcao valida\n\n");
    } while (op < 1 || op > 4);
    return op;
}

int menu_config_cliente() // permite ao cliente escolher após logado
{
    int op = -1;
    int i;
    do
    {
        printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 26; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3      Configuracoes       \xB3\n");

    printf("\xC3");
    for (i = 0; i < 26; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3    Selecione uma opcao   \xB3\n");
    printf("\xB3 1. Alterar senha         \xB3\n");
    printf("\xB3 2. Alterar e-mail        \xB3\n");
    printf("\xB3 3. Mostrar dados pessoais\xB3\n");
    printf("\xB3 4. Apagar conta          \xB3\n");
    printf("\xB3 5. Voltar                \xB3\n");

    printf("\xC0");
    for (i = 0; i < 26; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 1 || op > 5) printf("\nDigite uma opcao valida\n\n");
    } while (op < 1 || op > 5);
    return op;
}

int menu_inicial_restaurante() // permite ao restaurante escolher
{
    int op = -1;
    int i;
    do
    {
        //system ("cls");
        printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 29; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3   Menu Cadastro Restaurante \xB3\n");

    printf("\xC3");
    for (i = 0; i < 29; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3 Selecione uma opcao         \xB3\n");
    printf("\xB3 1. Quero me cadastrar       \xB3\n");
    printf("\xB3 2. Ja tenho cadastro        \xB3\n");
    printf("\xB3 3. Voltar                   \xB3\n");
    printf("\xB3 0. Sair                     \xB3\n");

    printf("\xC0");
    for (i = 0; i < 29; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 3)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 3);
    return op;
}

int menu_categoria()
{
    int op = -1;
    int i;
    do
    {
        // system ("cls");
       printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 52; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3                      Categorias                    \xB3\n");

    printf("\xC3");
    for (i = 0; i < 52; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3                Selecione uma opcao                 \xB3\n");
    // Opções de categorias
    printf("\xB3 1. Comida brasileira (caipira, mineira, baiana...) \xB3\n");
    printf("\xB3 2. Comida estrangeira (japonesa, indiana...)       \xB3\n");
    printf("\xB3 3. FastFood                                        \xB3\n");
    printf("\xB3 4. Acai e sorvetes                                 \xB3\n");
    printf("\xB3 5. Padaria e cafeteria                             \xB3\n");
    printf("\xB3 6. Pizzaria                                        \xB3\n");
    printf("\xB3 7. Doces                                           \xB3\n");
    printf("\xB3 8. Fitness                                         \xB3\n");
    printf("\xB3 9. Bebidas                                         \xB3\n");
    printf("\xB3 10. Outros                                         \xB3\n");

    printf("\xC0");
    for (i = 0; i < 52; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");

        scanf("%d", &op);
        if (op < 0 || op > 10)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 10);
    return op;
}

int menu_restaurante()
{
    int op = -1;
    int i;
    do
    {
        // system ("cls");
       printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 27; i++) {
        printf("\xC4");
    }
     printf("\xBF\n");

    printf("\xB3  Menu Inicial Restaurante \xB3\n");

    printf("\xC3");
    for (i = 0; i < 27; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3   Selecione uma opcao     \xB3\n");
    printf("\xB3 1. Atualizar Cardapio     \xB3\n");
    printf("\xB3 2. Pedidos Pendentes      \xB3\n");
    printf("\xB3 3. Historico de pedidos   \xB3\n");
    printf("\xB3 4. Configuracoes          \xB3\n");
    printf("\xB3 5. Sair da conta          \xB3\n");
    printf("\xB3 0. Sair do App            \xB3\n");
  

    printf("\xC0");
    for (i = 0; i < 27; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 5)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 5);
    return op;
}

int menu_cardapio_restaurante()
{
    int op = -1;
    int i;
    do
    {
        // system ("cls");
        printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 25; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3       Menu Cardapio     \xB3\n");

    printf("\xC3");
    for (i = 0; i < 25; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3 Selecione uma opcao     \xB3\n");
    printf("\xB3 1. Mostrar Cardapio     \xB3\n");
    printf("\xB3 2. Inserir item         \xB3\n"); //item ou prato?
    printf("\xB3 3. Remover item         \xB3\n");
    printf("\xB3 4. Voltar               \xB3\n");

    printf("\xC0");
    for (i = 0; i < 25; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 4)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 4);
    return op;
}

int menu_pedidosPendentes_restaurante()
{
    int op = -1;
    int i;
    do
    {
        // system ("cls");
        printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 42; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3             Pedidos Pendentes            \xB3\n");

    printf("\xC3");
    for (i = 0; i < 42; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3        Selecione uma opcao               \xB3\n");
    printf("\xB3 1. Mostrar todos os pedidos pendentes    \xB3\n");
    printf("\xB3 2. Mostrar proximo pedido a ser executado\xB3\n");
    printf("\xB3 3. Voltar                                \xB3\n");

    printf("\xC0");
    for (i = 0; i < 42; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 3)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 3);
    return op;
}

int menu_historicoPedidos_restaurante()
{
    int op = -1;
    int i;
    do
    {
        // system ("cls");
         //mudar os nomes ne mona?
    printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 45; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3              Historico de Pedidos           \xB3\n");

    printf("\xC3");
    for (i = 0; i < 45; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3             Selecione uma opcao             \xB3\n");
    printf("\xB3 1. Todos os pedidos ja feitos no restaurante\xB3\n");
    printf("\xB3 2. Filtrar por nome do prato                \xB3\n");
    printf("\xB3 3. Mostrar pedido buscado por codigo        \xB3\n");
    printf("\xB3 4. Voltar                                   \xB3\n");

    printf("\xC0");
    for (i = 0; i < 45; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 4)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 4);
    return op;
}

int menu_configuracoes_restaurante()
{
    int op = -1;
    int i;
    do
    {
        // system ("cls");
       printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 29; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3        Configuracoes        \xB3\n");

    printf("\xC3");
    for (i = 0; i < 29; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3     Selecione uma opcao     \xB3\n");
    printf("\xB3 1. Mostrar dados pessoais   \xB3\n");
    printf("\xB3 2. Alterar codigo de acesso \xB3\n");
    printf("\xB3 3. Alterar Senha            \xB3\n");
    printf("\xB3 4. Alterar e-mail           \xB3\n");
    printf("\xB3 5. Alterar categoria        \xB3\n");
    printf("\xB3 6. Alterar status           \xB3\n");
    printf("\xB3 7. Apagar conta             \xB3\n");
    printf("\xB3 8. Voltar                   \xB3\n");

    printf("\xC0");
    for (i = 0; i < 29; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 8)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 8);
    return op;
}

int menu_adm() // permite ao adm escolher
{
    int op = -1;
    int i;
    do
    {
       printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 37; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3         Menu Administrador          \xB3\n");

    printf("\xC3");
    for (i = 0; i < 37; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3       Selecione uma opcao           \xB3\n");
    printf("\xB3 1. Mostrar lista de clientes        \xB3\n");
    printf("\xB3 2. Mostrar lista de entregadores    \xB3\n");
    printf("\xB3 3. Mostrar lista de restaurantes    \xB3\n");
    printf("\xB3 4. Mostrar pedidos em andamento     \xB3\n");
    printf("\xB3 5. Inicializar clientes             \xB3\n");
    printf("\xB3 6. Inicializar entregadores         \xB3\n");
    printf("\xB3 7. Inicializar restaurantes         \xB3\n");
    printf("\xB3 8. Sair da conta                    \xB3\n");
    printf("\xB3 0. Sair do app                      \xB3\n");

    printf("\xC0");
    for (i = 0; i < 37; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");

        scanf("%d", &op);
        if (op < 0 || op > 8)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 8);
    return op;
}

int menu_inicial_entregador() // permite ao entregador escolher
{
    int op = -1;
    int i;
    do
    {
        //system ("cls");
        printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 27; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3  Menu Cadastro Entregador \xB3\n");

    printf("\xC3");
    for (i = 0; i < 27; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3 Selecione uma opcao       \xB3\n");
    printf("\xB3 1. Quero me cadastrar     \xB3\n");
    printf("\xB3 2. Ja tenho cadastro      \xB3\n");
    printf("\xB3 3. Voltar                 \xB3\n");
    printf("\xB3 0. Sair                   \xB3\n");

    printf("\xC0");
    for (i = 0; i < 27; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 4)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 4);
    return op;
}

int menu_entregador() // permite ao entregador escolher após logar
{
    int op = -1;
    int i;
    do
    {
        //system ("cls");
         printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 34; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3         Menu Entregador          \xB3\n");

    printf("\xC3");
    for (i = 0; i < 34; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3       Selecione uma opcao        \xB3\n");
    printf("\xB3 1. Mostrar corrida atual         \xB3\n");
    printf("\xB3 2. Mostrar nota                  \xB3\n");
    printf("\xB3 3. Mostrar historico de entregas \xB3\n");
    printf("\xB3 4. Configuracoes                 \xB3\n");
    printf("\xB3 5. Sair da conta                 \xB3\n");
    printf("\xB3 0. Sair do app                   \xB3\n");

    printf("\xC0");
    for (i = 0; i < 34; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 5) printf("\nDigite uma opcao valida");
    } while (op < 0 || op > 5);
    return op;
}

int menu_config_entregador() // permite ao entregador escolher após logar
{
    int op = -1;
    int i;
    do
    {
        //system ("cls");
        printf("\n\n");
    printf("\xDA");
    for (i = 0; i < 30; i++) {
        printf("\xC4");
    }
    printf("\xBF\n");

    printf("\xB3         Configuracoes        \xB3\n");

    printf("\xC3");
    for (i = 0; i < 30; i++) {
        printf("\xC4");
    }
    printf("\xB4\n");

    printf("\xB3      Selecione uma opcao     \xB3\n");
    printf("\xB3 1. Mostrar dados pessoais    \xB3\n");
    printf("\xB3 2. Alterar codigo de acesso  \xB3\n");
    printf("\xB3 3. Alterar e-mail            \xB3\n");
    printf("\xB3 4. Apagar conta              \xB3\n");
    printf("\xB3 5. Voltar                    \xB3\n");

    printf("\xC0");
    for (i = 0; i < 30; i++) {
        printf("\xC4");
    }
    printf("\xD9\n");

    printf("Opcao: ");
        scanf("%d", &op);
        if (op < 1 || op > 5)
            printf("\nDigite uma opcao valida");
    } while (op < 1 || op > 5);
    return op;
}

   