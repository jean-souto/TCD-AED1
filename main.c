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
pedidosglobais* inserirControleGlobal(pedidosglobais *pg, entregador entregador_atual, pedidos pedido_atual, Cliente cliente_atual, int *qtd);
pedidosglobais* removerControleGlobal(pedidosglobais *pg, int numero_pedido, int *qtd, Lista_cliente *l_cliente, Lista_entregadores *l_entregador, float nota);
pedidos* buscarPedidoAndamento (pedidosglobais *pg, int qtd, int codigo_cliente, int *num_pedidos);
int buscarPedidoAndamentoEntregador (pedidosglobais *pg, int qtd, int codigo_entregador, pedidos *em_andamento);
void mostrarPedidosGlobais (pedidosglobais *pg, int qtd);

// FUNÇÕES EXTRAS

void inicializar_entregador(entregador *item); // usada ao criar um novo cadastro de entregador (zera todas as informações para evitar lixo e erros)
void limpar_variavel_entregador(entregador *item); // limpa a variavel para evitar erros ao sobrepor
void inicializar_cliente(Cliente *item); // usada ao criar um novo_cliente cadastro de entregador (zera todas as informações para evitar lixo e erros)
void inicializar_restaurante(restaurante *item);
void limpar_variavel_cliente(Cliente *item); // limpa a variavel para evitar erros ao sobrepor
void limpar_variavel_rest(restaurante *item); // limpa a variavel para evitar erros ao sobrepor
void limpar_variavel_prato(pratos *item);
void limpaBuffer();

// MENUS

int menu_inicial(); // permite a escolha entre os diferentes usuários
int menu_inicial_cliente(); // permite ao cliente escolher
int menu_cliente(); // permite ao cliente escolher após logado
int menu_pedido_cliente(); // permite ao cliente escolher após logado
int menu_config_cliente(); // permite ao cliente escolher após logado
int menu_inicial_restaurante(); // permite ao restaurante escolher
int menu_restaurante();
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

    // declarações relacionadas aos clientes
    Lista_cliente *lista_principal_clientes;
    Cliente logado_cliente, novo_cliente;
    Cliente esqueceu_senha_cliente, inicializados_cliente;
    cartao novo_cartao;
    endereco novo_endereco;
    pedidos *em_andamento, novoped_pedido;

    // declarações relacionadas aos restaurantes
    Lista_restaurantes *lista_principal_restaurantes;
    restaurante novo_restaurante, logado_restaurante;
    restaurante login_restaurante, inicializados_restaurante;
    restaurante fazer_pedido_rest;
    int codigo_loginR;
    pratos novo_prato;
    char nome_prato[40];
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
    fila_pedidosPendentes = criar_filaPedidosPendentes();

    inicializar_cliente (&esqueceu_senha_cliente);
    inicializar_entregador (&esqueceu_senha_entregador);
    inicializar_entregador (&novoped_entregador);
    limpar_variavel_entregador (&esqueceu_senha_entregador);
    inicializar_restaurante(&login_restaurante);
    limparVariavelRest(&fazer_pedido_rest);

    // criando testes
    
    
    /*restaurante teste;
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

    restaurante retorno;
    int a = buscarRestEmail(lista_principal_restaurantes, teste.email, &retorno);
    if (!a)
    {
        mostrarCardapio(lista_principal_restaurantes, &retorno);
    }*/
    

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
                
                printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)");
                
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

                            printf ("Esperamos que sua experiencia tenha sido positiva. Volte sempre e muito obrigado! :)");
                            
                            return 0;
                        break;

                        case 1:; // quero me cadastrar
                            int i = 0;

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
                            limpar_variavel_cliente(&novo_cliente);
                            mostrar_cliente(lista_principal_clientes);
                        break;

                        case 2:; // ja tenho cadastro

                            verify = -1;

                            while (verify != 0)
                            {
                                printf ("\n----------LOGIN----------\n");
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
                                }
                                if (verify == 0)
                                {
                                    printf("\nLogin efetuado com sucesso. Bem vindo(a) de volta, %s!\n", logado_cliente.nome);
                                    break;
                                }

                                if (verify == 0) break;

                                printf("\nDigite 5 para voltar ou 6 se esqueceu a senha ou 0 para logar: ");
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
                                            printf("\nDigite 1 para continuar ou 0 para sair: ");
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

                                                    while (verify != 0)
                                                    {
                                                        printf ("\nAqui estao todos os restaurantes disponiveis: \n");
                                                        mostrarListaRest (lista_principal_restaurantes);

                                                        printf ("\nDigite 0 para voltar ou 1 para acessar algum restaurante: ");
                                                        scanf ("%d", &verify);

                                                        if (verify != 0)
                                                        {
                                                            printf ("\nDigite qual o numero do restaurante que voce deseja visualizar: ");
                                                            scanf ("%d", &verify);
                                                            verify--; // verify = verify - 1

                                                            verify = buscarRestPos(lista_principal_restaurantes, verify, &fazer_pedido_rest);
                                                            printf ("aaaaa %d ", verify);
                                                            printf ("%s", fazer_pedido_rest.nome);
                                                            printf ("   %s   ", fazer_pedido_rest.cardapio[0].nome);
                                                            //mostrarCardapioItem (fazer_pedido_rest);
                                                        }
                                                    }
                                                
                                                    // conferir se tá funcionando e então fazer uma forma de buscar o restaurante X para fazer o pedido
                                        
                                                break;

                                                case 2: // filtrar por categoria
                                                    mostrar_entregador (lista_principal_entregadores);
                                                    buscarEntregador (lista_principal_entregadores, &novoped_entregador);
                                                    mostrar_entregador (lista_principal_entregadores);

                                                    novoped_pedido.codigo = 456;
                                                    novoped_pedido.precoTotal = 100.25;
                                                    strcpy(novoped_pedido.nome_rest, "fernandaas");
                                                    novoped_pedido.qtdPratosPed = 3;
                                                    novoped_pedido.pratosPed = (pratos*) malloc (3*sizeof(pratos));
                                                    strcpy (novoped_pedido.pratosPed[0].nome, "teste1");
                                                    strcpy (novoped_pedido.pratosPed[0].descricao, "teste descricao 1");
                                                    novoped_pedido.pratosPed[0].preco = 30;
                                                    strcpy (novoped_pedido.pratosPed[1].nome, "teste2");
                                                    strcpy (novoped_pedido.pratosPed[1].descricao, "teste descricao 2");
                                                    novoped_pedido.pratosPed[1].preco = 30.25;
                                                    strcpy (novoped_pedido.pratosPed[2].nome, "teste3");
                                                    strcpy (novoped_pedido.pratosPed[2].descricao, "teste descricao 3");
                                                    novoped_pedido.pratosPed[2].preco = 40;

                                                    controlePedidos = inserirControleGlobal(controlePedidos, novoped_entregador, novoped_pedido, logado_cliente, &qtdPratosPedidosAndamento);
                                                    limpar_variavel_entregador (&novoped_entregador);
                                                    inicializar_entregador (&novoped_entregador);
                                                break;

                                                case 3: // procurar por nome
                                                break;

                                                case 4: // voltar
                                                break;
                                            }
                                        }
                                    break;

                                    case 2: // histórico
                                        buscarItemCliente (lista_principal_clientes, logado_cliente.codigo, &logado_cliente);
                                        printf ("\nAqui estao seus ultimos pedidos: \n");
                                        mostrar_pedidos (logado_cliente);
                                    break;

                                    case 3: // cartões (cadastrar e excluir)
                                        printf("\nVoce possui os seguintes cartoes cadastrados: \n");
                                        buscarItemCliente(lista_principal_clientes, logado_cliente.codigo, &logado_cliente);
                                        mostrar_pagamentos(logado_cliente);
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

                                            if (temp == 0) printf("\nCadastro realizado com sucesso!");
                                            else printf("\nAlgum erro inesperado aconteceu. Tente novamente!");
                                        }

                                        if (option == 2)
                                        {
                                            int temp = -1;

                                            printf("Digite qual o cartao que voce quer excluir (1, 2, 3...): ");
                                            scanf("%d", &temp);

                                            temp = removerCartaoCliente(lista_principal_clientes, logado_cliente.codigo, temp);

                                            if (temp == 0) printf("\nExcluido com sucesso!");
                                            else printf("\nAlgum erro inesperado aconteceu. Tente novamente!");
                                        }
                                    break;

                                    case 4: // endereços (cadastrar ou excluir)
                                        printf("\nVoce possui os seguintes enderecos cadastrados: \n");

                                        buscarItemCliente(lista_principal_clientes, logado_cliente.codigo, &logado_cliente);
                                        mostrar_enderecos(logado_cliente);

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
                                        }

                                        if (option == 2)
                                        {
                                            int temp = -1;

                                            printf("Digite qual o endereco que voce quer excluir (1, 2, 3...): ");
                                            scanf("%d", &temp);

                                            temp = removerEnderecoCliente(lista_principal_clientes, logado_cliente.codigo, temp);

                                            if (temp == 0) printf("\nExcluido com sucesso!");
                                            else printf("\nAlgum erro inesperado aconteceu. Tente novamente!");
                                        }
                                    break;

                                    case 5: // pedidos em andamento cliente
                                        verify = 0;

                                        int nun_ped = 0;

                                        em_andamento = buscarPedidoAndamento (controlePedidos, qtdPratosPedidosAndamento, logado_cliente.codigo, &nun_ped); // problema está aqui quando tem mais de um pedido para a mesma pessoa
                                        
                                        int i, j;

                                        if (nun_ped == 0)
                                        {
                                            printf ("\nVoce nao possui pedidos em andamento. Esta na hora de fazer um! ");
                                            free(em_andamento);
                                        }
                                        else
                                        {
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

                                            printf ("\nAlgum dos seus pedidos chegou? Digite 1 se sim e 0 se nao: ");
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

                                                printf ("\nQual nota voce da para o entregador (0 - 5)? ");
                                                scanf ("%f", &nota);

                                                controlePedidos = removerControleGlobal(controlePedidos, i, &qtdPratosPedidosAndamento, lista_principal_clientes, lista_principal_entregadores, nota);

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
                                                            printf("\nSenha atual incorreta! Digite 1 para continuar ou 2 para voltar: ");
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
                                mostrarListaRest(lista_principal_restaurantes);
                                printf("\nDigite ate duas categorias que o restaurante se encaixa:\n"
                                       "separe as duas por '/' (max 30 digitos)\n" // colocar cinza
                                       "Ex.: Acai e Sorvetes\nComida Japonesa/ Doces\n"); // colocar cinza
                                setbuf(stdin, NULL);
                                scanf("%[^\n]s", categoria);

                                if (alterarCategoria(lista_principal_restaurantes, novo_restaurante.codigo, categoria, &novo_restaurante) == 0)
                                {
                                    printf("\nCadastro realizado com sucesso!\n");
                                    //salvarListaRest(lista_principal_restaurantes);
                                    printf("MEU PERFIL\n");
                                    mostrarRestaurante(&novo_restaurante);
                                } else
                                    printf("Algo deu errado! Tente Novamente\n");
                            } else 
                                printf("Algo deu errado! Tente Novamente\n");
                            
                            limpar_variavel_rest(&novo_restaurante);
                            mostrarListaRest(lista_principal_restaurantes); // tirar dps
                        break;

                    case 2:; // Ja tenho cadastro
                        verify = -1;

                        while (verify != 0)
                        {
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

                            printf("\nTentar Novamente (Digite 0)\n"
                                   "Voltar (Digite 5)\n"
                                   "Esqueceu a senha? (Digite 6)\n");
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

                                    limpaBuffer();
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
                                        printf("\nDigite 1 para continuar ou 0 para sair: ");
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
                                                buscarRestCodigo (lista_principal_restaurantes, logado_restaurante.codigo, &logado_restaurante);
                                                printf("CARDAPIO:\n");
                                                mostrarCardapio(lista_principal_restaurantes, logado_restaurante);
                                            break;

                                            case 2:

                                                printf("Digite o nome:\n(max 40 caracteres)\n");
                                                limpaBuffer();
                                                scanf("%[^\n]s", novo_prato.nome);

                                                printf("Descricao:\nEx.: Bedida, Ingredientes\n(max 100 caracteres):\n");
                                                limpaBuffer();
                                                scanf("%[^\n]s", novo_prato.descricao);

                                                printf("Entre com o preco: ");
                                                limpaBuffer();
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

                                                printf("Nome do prato a ser removido: ");
                                                limpaBuffer();
                                                scanf("%[^\n]s", &nome_prato);

                                                printf("Preco do prato a ser removido: ");
                                                limpaBuffer();
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
                                                    printf("PEDIDOS PENDENTES\n");
                                                    mostrarPedidosPendentes(logado_restaurante.pedidosPendentes);
                                                }
                                                else
                                                    printf("Nao ha pedidos pendentes por enquanto... ;)\n");

                                            break;

                                            case 2: // mostrar apenas o proximo
                                                if (filaVazia(logado_restaurante.pedidosPendentes) != EMPTY_QUEUE)
                                                {
                                                    printf("PROXIMO PEDIDO\n");
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

                                    while ((option != 5) && (option != 15))
                                    {
                                        option = menu_historicoPedidos_restaurante();

                                        switch (option)
                                        {

                                            case 1: // todos os pedidos ja feitos no restaurante

                                                if (buscarRestCodigo(lista_principal_restaurantes, logado_restaurante.codigo, &logado_restaurante) == 0)
                                                {
                                                    if (logado_restaurante.historico != NULL)
                                                    {
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
                                                        limpaBuffer();
                                                        scanf("%[^\n]s", &nome_prato);

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
                                                        limpaBuffer();
                                                        scanf("%d", &codigo_pedido);
                                                       
                                                        printf("Aqui esta o pedido com codigo %d\n", codigo_pedido);
                                                        mostrarPedidoPorCodigo(&logado_restaurante, codigo_pedido);                                   
                                                    }
                                                    else
                                                        printf("%s ainda nao tem pedidos concluidos\n", logado_restaurante.nome);
                                                }
                                            break;

                                            case 4: // filtrar por preco total (menor que, maior que e exato)

                                                /*
                                                if (buscarRestCodigo(lista_principal_restaurantes, logado_restaurante.codigo, &logado_restaurante) == 0)
                                                {
                                                    if (logado_restaurante.historico != NULL)
                                                    {
                                                        printf("Entre com o preco do pedido: ");
                                                        limpaBuffer();
                                                        scanf("%d", &precoTotal_pedido);

                                                        printf("Deseja ver pedidos com precos maiores, menores ou iguais: ");
                                                        limpaBuffer();
                                                        scanf("%[^\n]s", &nome_prato);

                                                        printf("Aqui esta o pedido com codigo %d\n", codigo_pedido);
                                                        mostrarPedidoPorCodigo(&logado_restaurante, codigo_pedido);
                                                    }
                                                    else
                                                        printf("%s ainda nao tem pedidos concluidos\n", logado_restaurante.nome);
                                                }
                                                */

                                            break;

                                            case 5:
                                            option = 15;
                                            break;
                                        }
                                    }

                                break;
                                

                                case 4: // configuracoes

                                    while ((option != 7) && (option != 17))
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

                                            printf("\nDigite sua nova categoria: ");
                                            setbuf(stdin, NULL);
                                            scanf("%[^\n]s", &categoria);

                                            verify = alterarCategoria(lista_principal_restaurantes, logado_restaurante.codigo, categoria, &logado_restaurante);

                                            if (verify == 0)
                                            {
                                                printf("\nCategoria alterada com sucesso!\n");
                                            }
                                            if (verify != 0)
                                                printf("\nAlgo deu errado. Tente novamente!\n");

                                            break;

                                            case 6: // apagar conta

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

                                            case 7: // voltar
                                            option = 17;
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

                            if ((inserirFimEntregador(lista_principal_entregadores, novo_entregador, &cod_novo)) == 0) printf("\nCadastro realizado com sucesso! Bem vindo, %s! Seu novo codigo de acesso eh: %d.", novo_entregador.nome, cod_novo);
                            limpar_variavel_entregador(&novo_entregador);

                        break;

                        case 2: // login entregador

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

                                if (verify == 0) break;
                                
                                printf("\nDigite 5 para voltar, 6 se esqueceu o codigo de acesso e 0 para continuar: ");
                                scanf("%d", &verify);

                                if (verify == 5) break;
                                if (verify == 6) // preciso fazer verificação de status == 1 ou == 0
                                {
                                    while (verify != 0)
                                    {
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
                                        
                                        pedidos em_andamento_entregador;
                                        int i;
                                        
                                        verify = 0;

                                        verify = buscarPedidoAndamentoEntregador (controlePedidos, qtdPratosPedidosAndamento, logado_entregador.codigo, &em_andamento_entregador);

                                        if (verify == 0)
                                        {
                                            printf ("\nVoce nao esta em uma corrida atualmente! ");
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

                        case 5: // inicializar clientes
                        break;

                        case 6: // inicializar entregadores
                        break;

                        case 7: // inicializar restaurante
                        break;

                        case 8: // voltar
                        break;
                    }
                }
            break;

            case 5: // sobre
                // aqui será inserido uma mensagem completa sobre o codigo e coisas do tipo
                printf ("\n\nObrigado por se interessar mais sobre o processo de producao do app.");
                printf ("\nEste aplicativo foi feito para o trabalho de conclusao de disciplina da materia de Algoritmos e Estruturas de Dados 1.");
                printf ("\n\nO grupo eh composto por:");
                printf (" Jean Souto Galvao Moreira @jean.soutoo");
                printf ("\n                         Ester Camilly lalala");
                printf ("\n                         Alice lalala");
                printf ("\n                         Fernanda lalala");
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

pedidosglobais* removerControleGlobal(pedidosglobais *pg, int numero_pedido, int *qtd, Lista_cliente *l_cliente, Lista_entregadores *l_entregador, float nota) // deve remover do controle, liberar entregador e adicionar aos historicos
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
    
    //copiarPedidoCpR (&(pg[rem].pedido_em_andamento), &temp2);
    // inserir no historico do restaurante aqui 

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

void limpaBuffer()
{
    char meuchar;
    while ((meuchar = getchar()) != EOF && meuchar != '\n');
}

// MENUS

int menu_inicial() // permite a escolha entre os diferentes usuários
{
    int op = -1;
    do
    {
        //system ("cls");
        printf("\nBem vindo!\n");
        printf("\nSelecione uma opcao: \n");
        printf("1. Sou cliente\n");
        printf("2. Sou restaurante\n");
        printf("3. Sou entregador\n");
        printf("4. Sou administrador\n");
        printf("5. Sobre o app\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 5)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 5);
    return op;
}

int menu_inicial_cliente() // permite ao cliente escolher
{
    int op = -1;
    do
    {
        //system ("cls");
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Quero me cadastrar\n");
        printf("2. Ja tenho cadastro\n");
        printf("3. Voltar\n");
        printf("0. Sair\n");
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
    do
    {
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Fazer pedido\n");
        printf("2. Historico de pedidos\n");
        printf("3. Cartoes\n");
        printf("4. Enderecos\n");
        printf("5. Confirmar entrega\n");
        printf("6. Configuracoes\n");
        printf("7. Sair da conta\n");
        printf("0. Sair do app\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 7) printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 7);
    return op;
}

int menu_pedido_cliente() // permite ao cliente escolher após logado
{
    int op = -1;
    do
    {
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Mostrar todos os restaurantes\n");
        printf("2. Filtrar por categoria\n");
        printf("3. Procurar por nome\n");
        printf("4. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 1 || op > 4) printf("\nDigite uma opcao valida\n\n");
    } while (op < 1 || op > 4);
    return op;
}

int menu_config_cliente() // permite ao cliente escolher após logado
{
    int op = -1;
    do
    {
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Alterar senha\n");
        printf("2. Alterar e-mail\n");
        printf("3. Mostrar dados pessoais\n");
        printf("4. Apagar conta\n");
        printf("5. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 1 || op > 5) printf("\nDigite uma opcao valida\n\n");
    } while (op < 1 || op > 5);
    return op;
}

int menu_inicial_restaurante() // permite ao restaurante escolher
{
    int op = -1;
    do
    {
        //system ("cls");
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Quero me cadastrar\n");
        printf("2. Ja tenho cadastro\n");
        printf("3. Voltar\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 3)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 3);
    return op;
}

int menu_restaurante()
{
    int op = -1;
    do
    {
        // system ("cls");
        printf("\n\nSelecione uma opcao: \n"
               "1. Atualizar Cardapio\n"
               "2. Pedidos Pendentes\n"
               "3. Historico de Pedidos\n"
               "4. Configuracoes\n"
               "5. Sair da Conta\n"
               "0. Sair do App\n"); // segue para o menu de configuracoes
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
    do
    {
        // system ("cls");
        printf("\n\nSelecione uma opcao: \n"
               "1. Mostrar Cardapio\n"
               "2. Inserir Prato\n"
               "3. Remover Prato\n"
               "4. Voltar\n"); 
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
    do
    {
        // system ("cls");
        printf("\n\nSelecione uma opcao: \n"
               "1. Mostrar todos os pedidos pendentes\n"
               "2. Mostrar proximo pedido a ser executado\n"
               "3. Voltar\n");
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
    do
    {
        // system ("cls");
        printf("\n\nSelecione uma opcao: \n"
               "1. todos os pedidos ja feitos no restaurante\n"
               "2. filtrar por nome do prato\n"
               "3. mostrar pedido buscado por codigo\n"
               "4. filtrar por preco total (menor que, maior que e exato)\n"
               "5. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 5)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 5);
    return op;
}

int menu_configuracoes_restaurante()
{
    int op = -1;
    do
    {
        // system ("cls");
        printf("\n\nSelecione uma opcao: \n"
               "1. mostrar dados pessoais\n"
               "2. alterar codigo de acesso\n"
               "3. alterar senha\n"
               "4. alterar e-mail\n"
               "5. alterar categoria\n"
               "6. apagar conta\n"
               "7. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 7)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 7);
    return op;
}

int menu_adm() // permite ao adm escolher
{
    int op = -1;
    do
    {
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Mostrar lista de clientes\n");
        printf("2. Mostrar lista de entregadores\n");
        printf("3. Mostrar lista de restaurantes\n");
        printf("4. Mostrar pedidos em andamento\n");
        printf("5. Inicializar clientes\n");
        printf("6. Inicializar entregadores\n");
        printf("7. Inicializar restaurantes\n");
        printf("8. Sair da conta\n");
        printf("0. Sair do app\n");
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
    do
    {
        //system ("cls");
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Quero me cadastrar\n");
        printf("2. Ja tenho cadastro\n");
        printf("3. Voltar\n");
        printf("0. Sair\n");
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
    do
    {
        //system ("cls");
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Mostrar corrida atual\n");
        printf("2. Mostrar nota\n");
        printf("3. Mostrar historico de entregas\n");
        printf("4. Configuracoes\n");
        printf("5. Sair da conta\n");
        printf("0. Sair do app\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 5) printf("\nDigite uma opcao valida");
    } while (op < 0 || op > 5);
    return op;
}

int menu_config_entregador() // permite ao entregador escolher após logar
{
    int op = -1;
    do
    {
        //system ("cls");
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Mostrar dados pessoais\n");
        printf("2. Alterar codigo de acesso\n");
        printf("3. Alterar e-mail\n");
        printf("4. Apagar conta\n");
        printf("5. Voltar\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 1 || op > 5)
            printf("\nDigite uma opcao valida");
    } while (op < 1 || op > 5);
    return op;
}
