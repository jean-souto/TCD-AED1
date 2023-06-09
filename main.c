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
    pedidosC pedido_em_andamento;
    Cliente comprador;
}pedidosglobais;

// funções para o gerenciador global de pedidos em andamento

void copiarPedidoCpC(pedidosC *A, pedidosC *B); // criar possivel funcao que copiará pedido para pedido entre tipos de pedidos e tals
void copiarPedidoCpE(pedidosC *A, pedidosE *B); // criar possivel funcao que copiará pedido para pedido entre tipos de pedidos e tals
void copiarPedidoCpR(pedidosC *A, pedidosR *B); // criar possivel funcao que copiará pedido para pedido entre tipos de pedidos e tals
int inserirControleGlobal(pedidosglobais *pg, entregador entregador_atual, pedidosC pedido_atual, Cliente cliente_atual, int *qtd);
int removerControleGlobal(pedidosglobais *pg, int numero_pedido, int *qtd, Lista_cliente *l_cliente, Lista_entregadores *l_entregador, float nota);
int buscarPedidoAndamento (pedidosglobais *pg, int qtd, char *nome_cliente, pedidosC *em_andamento);

// FUNÇÕES EXTRAS

int inicializar_entregador(entregador *item); // usada ao criar um novo cadastro de entregador (zera todas as informações para evitar lixo e erros)
int limpar_variavel_entregador(entregador *item); // limpa a variavel para evitar erros ao sobrepor
int inicializar_cliente(Cliente *item); // usada ao criar um novo_cliente cadastro de entregador (zera todas as informações para evitar lixo e erros)
int inicializar_restaurante(restaurante *item);
int limpar_variavel_cliente(Cliente *item); // limpa a variavel para evitar erros ao sobrepor
int limpar_variavel_rest(restaurante *item); // limpa a variavel para evitar erros ao sobrepor
void limpaBuffer();

// MENUS

int menu_inicial(); // permite a escolha entre os diferentes usuários
int menu_inicial_cliente(); // permite ao cliente escolher
int menu_cliente(); // permite ao cliente escolher após logado
int menu_inicial_restaurante(); // permite ao restaurante escolher
int menu_restaurante();
int menu_adm(); // permite ao adm escolher
int menu_inicial_entregador(); // permite ao entregador escolher
int menu_entregador(); // permite ao entregador escolher após logar

// MAIN

int main()
{
    srand(time(NULL));

    // declarações relacionadas ao gerenciador global de pedidos
    pedidosglobais *controlePedidos;
    int qtdPedidosAndamento = 0;

    // declarações relacionadas aos clientes
    Lista_cliente *lista_principal_clientes;
    Cliente logado_cliente, novo_cliente;
    Cliente esqueceu_senha_cliente, inicializados_cliente;
    cartao novo_cartao;
    endereco novo_endereco;
    pedidosC *em_andamento, novoped_pedido;

    // declarações relacionadas aos restaurantes
    Lista_restaurantes *lista_principal_restaurantes;
    restaurante novo_restaurante, login_restaurante, logado_restaurante;
    int codigo_loginR;
    pratosR novo_prato;
    char nome_prato[40];

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
    char email[40];
    char senha[15];
    char cpf[12];
    char confirmSenha[15];

    // inicializações
    lista_principal_clientes = criarCliente();
    lista_principal_entregadores = criar_lista_entregadores();
    lista_principal_restaurantes = criar_listaRestaurantes();

    // criando testes
    restaurante teste;
    strcpy(teste.nome, "Fast Acai");
    strcpy(teste.email, "fast@gmail.com");
    strcpy(teste.senha, "bem vinde");
    inicializar_restaurante(&teste);
    inserirInicioRest(lista_principal_restaurantes, teste);
    mostrarListaRest(lista_principal_restaurantes);

    strcpy(loginADM, "souADM");
    strcpy(senhaADM, "123ADM");

    inicializar_cliente (&esqueceu_senha_cliente);
    inicializar_entregador (&esqueceu_senha_entregador);
    limpar_variavel_entregador (&esqueceu_senha_entregador);

    // AQUI COMEÇA O PROGRAMA EM SI

    while (option != 0) // mantém o programa rodando até que seja escolhido sair
    {
        option = menu_inicial();

        switch (option)
        {

            case 0: // sair
                return 0;
            break;

            case 1: // sou cliente

                while (option != 3)
                {
                    option = menu_inicial_cliente();

                    switch (option)
                    {
                        case 0: // sair
                            return 0;
                        break;

                        case 1: // quero me cadastrar

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

                            printf("\nDigite sua senha (8 digitos): ");
                            setbuf(stdin, NULL);
                            scanf("%[^\n]s", novo_cliente.senha_8d);
                            inicializar_cliente(&novo_cliente);

                            if ((inserirFimCliente(lista_principal_clientes, novo_cliente)) == 0) printf("\nCadastro realizado com sucesso!\n");
                            limpar_variavel_cliente(&novo_cliente);
                            mostrar_cliente(lista_principal_clientes);
                        break;

                        case 2:; // ja tenho cadastro

                            int verify = -1;

                            while (verify != 0)
                            {
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
                                        else printf("\nAlgo deu errado. Tente novamente!");
                                    }
                                }
                                if (verify == 0) verify = 1;
                            }

                            if (verify == 5) break; // sair e voltar ao menu anterior

                            while ((option != 10) && (option != 11)) // voltar após selecionar voltar ou excluir a conta
                            {
                                option = menu_cliente();

                                switch (option) // opções do cliente após logar
                                {
                                    case 0: // sair
                                        return 0;
                                    break;

                                    case 1: // mostrar todos os restaurantes
                                        mostrar_entregador (lista_principal_entregadores);
                                        buscarEntregador (lista_principal_entregadores, &novoped_entregador);
                                        mostrar_entregador (lista_principal_entregadores);

                                        novoped_pedido.codigo = 123;
                                        novoped_pedido.precoTotal = 125.25;
                                        strcpy(novoped_pedido.nome_rest, "mariass");
                                        novoped_pedido.qtdPed = 2;
                                        novoped_pedido.ped = (pratosC*) realloc (novoped_pedido.ped, 2*sizeof(pratosC));
                                        strcpy (novoped_pedido.ped[0].nome, "teste1");
                                        strcpy (novoped_pedido.ped[0].descricao, "teste descricao 1");
                                        novoped_pedido.ped[0].preco = 50;
                                        strcpy (novoped_pedido.ped[1].nome, "teste2");
                                        strcpy (novoped_pedido.ped[1].descricao, "teste descricao 2");
                                        novoped_pedido.ped[1].preco = 75.25;
                                        inserirControleGlobal(controlePedidos, novoped_entregador, novoped_pedido, logado_cliente, qtdPedidosAndamento);
                                    break;

                                    case 2: // filtrar por categoria
                                    break;

                                    case 3: // procurar por nome
                                    break;

                                    case 4: // histórico
                                    break;

                                    case 5: // cartões (cadastrar e excluir)
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

                                    case 6: // endereços (cadastrar ou excluir)
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

                                    case 7:; // alterar senha

                                        int verify = -1;
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

                                    case 8:; // alterar email

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

                                    case 9: // procura os pedidos em andamento com o nome do cliente, se tiver algum pergunta se esta concluido e, se sim, pede a nota do entregador



                                        verify = 0;
                                        verify = buscarPedidoAndamento (controlePedidos, qtdPedidosAndamento, logado_cliente.nome, em_andamento);
                                        int i, j;

                                        if (verify == 0)
                                        {
                                            printf ("\nVoce nao possui pedidos em andamento. Esta na hora de fazer um! ");
                                        }
                                        else
                                        {
                                            printf ("\nVoce possui %d pedidos em andamento!", verify);
                                            for (i = 0; i < verify; i++)
                                            {
                                                printf ("\n%d: %s\n", i+1, em_andamento[i].nome_rest);
                                                printf ("Total: %.2f\n", em_andamento[i].precoTotal);
                                                for (j = 0; j < em_andamento[i].qtdPed; j++)
                                                {
                                                    printf ("%s: %.2f\n", em_andamento[i].ped[j].nome, em_andamento[i].ped[j].preco);
                                                }
                                            }

                                            printf ("\nAlgum dos seus pedidos chegou? Digite 1 se sim e 0 se não: ");
                                            scanf ("%d", &verify);

                                            if (verify == 1)
                                            {
                                                float nota = 0;
                                                i = 0;
                                                printf ("Digite o numero do pedido que chegou: ");
                                                scanf ("%d", &i);

                                                printf ("\nQual nota voce da para o entregador (0 - 5)? ");
                                                scanf ("%f", &nota);
                                                
                                                removerControleGlobal (controlePedidos, em_andamento[i-1].codigo, &qtdPedidosAndamento, lista_principal_clientes, lista_principal_entregadores, nota); // QUE INFERNO BUCETA CU CAPETA
                                            
                                                free(em_andamento);
                                            }
                                            else
                                            {
                                                printf ("\nTudo bem! Nao esqueca de nos avisar caso chegue.\n");
                                            }
                                        }


                                    break;

                                    case 10: // sair da conta (voltar)
                                    break;

                                    case 11: // apagar conta
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

                        if (strcmp(senha, confirmSenha) == 0) {
                            strcpy(novo_restaurante.senha, senha);
                        } else {
                            printf("Senha Incorreta!\n");
                            break;
                        }

                        inicializar_restaurante(&novo_restaurante);

                        if ((inserirFimRest(lista_principal_restaurantes, novo_restaurante)) == 0)
                        printf("\nCadastro realizado com sucesso!\n");
                        limpar_variavel_rest(&novo_restaurante);
                        mostrarListaRest(lista_principal_restaurantes);
                        break;

                    case 2:; // Ja tenho cadastro
                        int verify = -1;

                        while (verify != 0)
                        {
                            printf("\nDigite o e-mail: ");
                            setbuf(stdin, NULL);
                            scanf("%[^\n]s", &email);

                            printf("\nDigite a senha: ");
                            setbuf(stdin, NULL);
                            scanf("%[^\n]s", &senha);
                            printf("%d\n", verify);

                            verify = loginRestaurante(lista_principal_restaurantes, email, senha, &logado_restaurante);
                            printf("%d\n", verify);
                            strcpy(email, " ");
                            strcpy(senha, " ");

                            if (verify != 0)
                            {
                                printf("\nLogin ou senha invalidos. Tente novamente!\n");
                            }
                            if (verify == 0)
                            {
                                printf("\nLogin efetuado com sucesso. Bem vindos de volta, %s!\n", logado_restaurante.nome);
                                break;
                            }

                            if (verify == 0) break;

                            printf("\nTentar Novamente (Digite 0)\n"
                                   "Esqueceu a senha? (Digite 5)\n"
                                   "Voltar (Digite 6)\n");
                            scanf("%d", &verify);

                            if (verify == 6)
                                break;
                            if (verify == 5)
                            {
                                while (verify != 0)
                                {
                                    printf("\nDigite o email: ");
                                    setbuf(stdin, NULL);
                                    scanf("%[^\n]s", &email);

                                    printf("\nDigite o codigo do restaurante: ");
                                    setbuf(stdin, NULL);
                                    scanf("%[^\n]s", &codigo_loginR);

                                    verify = buscarRestEmailCodigo(lista_principal_restaurantes, email, codigo_loginR, &login_restaurante);
                                    printf("%d", verify);

                                    if (verify == 0)
                                    {
                                        verify = -1;

                                        while (verify != 0)
                                        {
                                            if (verify != 1) 
                                                printf("\nTe encontramos!");

                                            printf("\nDigite sua nova senha: "); 
                                            setbuf(stdin, NULL);
                                            scanf("%[^\n]s", &senha);

                                            printf("\nDigite sua nova senha novamente: ");
                                            setbuf(stdin, NULL);
                                            scanf("%[^\n]s", &confirmSenha);

                                            verify = alterarSenhaRest(lista_principal_restaurantes, codigo_loginR, senha, confirmSenha);

                                            if (verify == 0)
                                                printf("\nSenha alterada com sucesso! ");

                                            if (verify != 0)
                                                printf("\nSenhas diferentes. Tente novamente! ");
                                        }
                                    }
                                    else
                                        printf("\nAlgo deu errado. Tente novamente!");
                                }
                            }
                            if (verify == 0) verify = 1;
                        }

                        if (verify == 5) break; // sair e voltar ao menu anterior

                        while (option != 4)
                        {
                            option = menu_restaurante();
                            int op;
                           
                            switch (option)
                            {
                                case 0: // voltar
                                    break;

                                case 1: // atualizar cardapio

                                    while (op != 0)
                                    {
                                        //op = menu_Cardapio();

                                        switch (op)
                                        {
                                            case 0:
                                                printf("Saindo...\n");
                                                break;

                                            case 1:

                                                printf("CARDAPIO:\n");
                                                mostrarCardapio(lista_principal_restaurantes, &logado_restaurante);
                                                break;

                                            case 2:

                                                printf("Digite o nome:\n(max 40 caracteres)\n");
                                                limpaBuffer();

                                                printf("Descricao:\nEx.: Bedida, Ingredientes\n(max 100 caracteres): ");
                                                limpaBuffer();
                                                scanf("%[^\n]s", &novo_prato.descricao);

                                                printf("Entre com o preco: ");
                                                limpaBuffer();
                                                scanf("%f", &novo_prato.preco);
 
                                                if (inserirPratoRest(lista_principal_restaurantes, novo_prato, &logado_restaurante) == 0)
                                                {
                                                    printf("Item adicionado com sucesso!\n");

                                                } else {
                                                    printf("Tente Novamente\n");
                                                    break;
                                                }
                                                
                                                break;
                                            
                                            case 3:

                                                printf("Nome do prato a ser removido: ");
                                                limpaBuffer();
                                                scanf("%[^\n]s", &nome_prato);

                                                if (removerPratoRest(lista_principal_restaurantes, nome_prato, &logado_restaurante) == 0)
                                                {
                                                    printf("Item removido com sucesso!\n");
                                                }
                                                else
                                                {
                                                    printf("Item nao encontrado.\n");
                                                    break;
                                                }
                                                
                                                break;
                                                

                                            default:
                                                printf("Opcao invalida. Tente novamente.\n");
                                                break;
                                        }
                                    }

                                    break;

                                case 2: // pedidos pendentes
                                    
                                    while ((op != 0))
                                    {
                                        //op = menu_PedidosPendentes();

                                        switch (op)
                                        {
                                            case 0: // voltar
                                                break;

                                            case 1: // mostrar a fila toda
                                                break;

                                            case 2: // mostrar apenas o proximo
                                                break;

                                            default:
                                                printf("Opcao invalida. Tente novamente.\n");
                                                break;
                                        }
                                    }
                                    
                                    break;

                                case 3: // historico de pedidos
                                    /*
                                    while ((op != voltar))
                                    {
                                        op = menu_;

                                        switch (op)
                                        {
                                            case 1: // todos os pedidos ja feitos no restaurante
                                                break;

                                            case 2: // filtrar por mes
                                                break;

                                            case 3: // filtrar por semana
                                                break;

                                            case 4: // filtrar por nome do prato
                                                break;

                                            case 5: // buscar pedido por codigo
                                                break;
                                        }
                                    }
                                    */
                                    break;

                                case 4: // configuracoes
                                    /*
                                    while ((op != voltar))
                                    {
                                        op = menu_;

                                        switch (op)
                                        {
                                            case 1: // alterar codigo de acesso
                                                break;

                                            case 2: // alterar senha
                                                break;

                                            case 3: // alterar e-mail
                                                break;

                                            case 4: // sair da conta
                                                break;

                                            case 5: // apagar conta
                                                break;
                                        }
                                    }
                                    */
                                    break;       
                           }
                           
                        }
                        
                    case 3: // Voltar
                        break;

                    default:
                        break;
                    }
                }

            break;

            case 3:; // sou entregador
  
                while (option != 3) // voltar
                {
                    option = menu_inicial_entregador();
                    int verify = -1;

                    switch (option)
                    {

                        case 0: // sair
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
                                            esqueceu_senha_entregador.status = 1;
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

                            while ((option != 7) && (option != 8))
                            {
                                option = menu_entregador();

                                switch (option)
                                {
                                    case 0: // sair
                                        return 0;
                                    break;

                                    case 1: // mostrar corrida atual (pedido em andamento)

                                    break;

                                    case 2: // mostrar dados pessoais
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

                                    case 3: // mostrar nota
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

                                    case 4: // mostrar historico

                                    break;

                                    case 5: // alterar codigo de acesso // se estiver em corrida nao poderá alterar

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

                                    case 6: // alterar email
                                        
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

                                    case 7: // sair da conta
                                    break;

                                    case 8: // excluir conta // se estiver em corrida não poderá excluir

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

                printf("\nDigite o login de administrador: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]s", &teste_login);

                printf("\nDigite a senha de administrador: ");
                setbuf(stdin, NULL);
                scanf("%[^\n]s", &teste_senha);

                if ((strcmp(teste_login, loginADM) == 0) && strcmp(teste_senha, senhaADM) == 0)
                {
                    printf("\nBem-vindo, ADM!\n");

                    while (option != 9)
                    {
                        option = menu_adm();

                        switch (option)
                        {
                        }
                    }
                }
                else
                {
                   printf("\nLogin ou senha incorretos!\n");
                }

            break;

            default:
            break;
            
        }
    }

    limparCliente(lista_principal_clientes);
    free(lista_principal_clientes);
    limparEntregador(lista_principal_entregadores);
    free(lista_principal_entregadores);
    limparRest(lista_principal_restaurantes);
    free(lista_principal_restaurantes);

    return 0;
}

// FUNÇÕES EXTRAS RELACIONADAS ÀS STRUCTS EXTRAS

void copiarPedidoCpC(pedidosC *A, pedidosC *B) // criar possivel funcao que copiará pedido para pedido entre tipos de pedidos e tals
{
    int i;
    B->codigo = A->codigo;
    B->qtdPed = A->qtdPed;
    B->precoTotal = A->precoTotal;
    strcpy(B->nome_rest, A->nome_rest);

    B->ped = (pratosC *)realloc(B->ped, A->qtdPed * sizeof(pratosC));
    for (i = 0; i < A->qtdPed; i++)
    {
        B->ped[i].preco = A->ped[i].preco;
        strcpy(B->ped[i].descricao, A->ped[i].descricao);
        strcpy(B->ped[i].nome, A->ped[i].nome);
    }
}

void copiarPedidoCpE(pedidosC *A, pedidosE *B) // criar possivel funcao que copiará pedido para pedido entre tipos de pedidos e tals
{
    int i;
    B->codigo = A->codigo;
    B->qtdPed = A->qtdPed;
    B->precoTotal = A->precoTotal;
    strcpy(B->nome_rest, A->nome_rest);

    B->ped = (pratosE *)realloc(B->ped, A->qtdPed * sizeof(pratosE));
    for (i = 0; i < A->qtdPed; i++)
    {
        B->ped[i].preco = A->ped[i].preco;
        strcpy(B->ped[i].descricao, A->ped[i].descricao);
        strcpy(B->ped[i].nome, A->ped[i].nome);
    }
}

void copiarPedidoCpR(pedidosC *A, pedidosR *B) // criar possivel funcao que copiará pedido para pedido entre tipos de pedidos e tals
{
    int i;
    B->codigo = A->codigo;
    B->qtdPed = A->qtdPed;
    B->precoTotal = A->precoTotal;
    strcpy(B->nome_rest, A->nome_rest);

    B->ped = (pratosR *)realloc(B->ped, A->qtdPed * sizeof(pratosR));
    for (i = 0; i < A->qtdPed; i++)
    {
        B->ped[i].preco = A->ped[i].preco;
        strcpy(B->ped[i].descricao, A->ped[i].descricao);
        strcpy(B->ped[i].nome, A->ped[i].nome);
    }
}

int inserirControleGlobal(pedidosglobais *pg, entregador entregador_atual, pedidosC pedido_atual, Cliente cliente_atual, int *qtd)
{
    (*qtd)++;
    pg = (pedidosglobais *)realloc(pg, (*qtd) * sizeof(pedidosglobais));

    int i = (*qtd) - 1;
    copiarEntregador(&entregador_atual, &pg[i].entregador_do_pedido);
    copiarPedidoCpC(&pedido_atual, &pg[i].pedido_em_andamento);
    copiarCliente(&cliente_atual, &pg[i].comprador);

    return 0;
}

int removerControleGlobal(pedidosglobais *pg, int numero_pedido, int *qtd, Lista_cliente *l_cliente, Lista_entregadores *l_entregador, float nota) // deve remover do controle, liberar entregador e adicionar aos historicos
{
    int i, rem;
    pedidosE temp;
    pedidosR temp2;
    for (i = 0; i < *qtd; i++)
    {
        if (pg[i].pedido_em_andamento.codigo == numero_pedido)
        {
            rem = i;
        }
    }

    inserirPedidoHistorico (l_cliente, pg[rem].comprador.codigo, pg[rem].pedido_em_andamento);
    copiarPedidoCpE (&(pg[rem].pedido_em_andamento), &temp);
    inserirPedidoHistoricoEntregador (l_entregador, pg[rem].entregador_do_pedido.codigo, temp);
    copiarPedidoCpR (&(pg[rem].pedido_em_andamento), &temp2);
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
    return 0;
}

int buscarPedidoAndamento (pedidosglobais *pg, int qtd, char *nome_cliente, pedidosC *em_andamento)
{
    int i = 0;
    int num_pedidos = 0;
    for (i = 0; i < qtd; i++)
    {
        if (strcmp (pg[i].comprador.nome, nome_cliente) == 0)
        {
            num_pedidos++;
            em_andamento = (pedidosC*) realloc (em_andamento, num_pedidos * sizeof(pedidosC));
            copiarPedidoCpC (&(pg[i].pedido_em_andamento), &em_andamento[num_pedidos-1]);
        }
    }
    return num_pedidos;
}

// funções extras

int inicializar_entregador(entregador *item) // usada ao criar um novo cadastro de entregador (zera todas as informações para evitar lixo e erros)
{
    item->corridas = 0;
    item->status = 0;
    item->rank.media = 0.0;
    item->rank.quantidade = 0;
    item->rank.total = 0;
    item->quant_pedidos = 0;
    item->historico = NULL;
    return 0;
}

int limpar_variavel_entregador(entregador *item) // limpa a variavel para evitar erros ao sobrepor
{
    strcpy(item->cpf, "000");
    strcpy(item->email, "000");
    strcpy(item->nome, "000");
    item->codigo = -1;
    inicializar_entregador(item);
}

int inicializar_cliente(Cliente *item) // usada ao criar um novo_cliente cadastro de entregador (zera todas as informações para evitar lixo e erros)
{
    item->gasto_total = 0;
    item->quantidade_cartoes = 0;
    item->quant_pedidos = 0;
    item->quant_enderecos = 0;
    item->historico = NULL;
    item->pagamentos = NULL;
    item->enderecos = NULL;
    return 0;
}

int inicializar_restaurante(restaurante *item)
{
    strcpy(item->categoria, "-");
    item->cardapio = NULL;
    item->qtdCardapio = 0;
    item->historico = NULL;
    item->status = -1;
    item->pedidosPendentes = NULL;
    return 0;
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

int limpar_variavel_cliente(Cliente *item) // limpa a variavel para evitar erros ao sobrepor
{
    strcpy(item->cpf, "000");
    strcpy(item->email, "000");
    strcpy(item->nome, "000");
    strcpy(item->senha_8d, "000");
    item->codigo = -1;
    inicializar_cliente(item);
}

int limpar_variavel_rest(restaurante *item) // limpa a variavel para evitar erros ao sobrepor
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
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 4)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 4);
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
        //system ("cls");
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Mostrar todos os restaurantes\n");
        printf("2. Filtrar por categoria\n");
        printf("3. Procurar por nome\n");
        printf("4. Historico de pedidos\n");
        printf("5. Cartoes\n");
        printf("6. Enderecos\n");
        printf("7. Alterar senha\n");
        printf("8. Alterar e-mail\n");
        printf ("9. Confirmar entrega\n");
        printf("10. Sair da conta\n");
        printf("11. Apagar conta\n");
        printf("0. Sair do app\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 11)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 11);
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
        /*
        "1.Atualizar Menu\n"
        "2.Cadastrar Cliente\n"
        "3.Pedidos Pendentes\n"
        "4.Histórico"
        "5.Programa de fidelidade\n"
        "6.Voltar\n"
        ""
        */
        // system ("cls");
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Atualizar Menu\n"); //(trocar por atualizar cardapio) ir para outro menu que da opcao de add ou remover algum prato
        printf("2. Pedidos Pendentes\n"); // ir para outro menu que mostra todos os pedidos ou apenas o proximo a ser executado
        printf("3. Historico de pedidos\n"); // ir para outro menu que mostra todos os pedidos ja feitos no restaurante, talvez implementar um filtro por mes, semana, codigo e prato

        // configuracoes
        //alterar codigo de acesso 
        printf("7. Alterar senha\n");
        printf("8. Alterar e-mail\n");
        printf("9. Sair da conta\n");
        printf("10. Apagar conta\n");
        printf("0. Sair do app\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 10)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 10);
    return op;
}

int menu_adm() // permite ao adm escolher
{
    int op = -1;
    do
    {
        //system ("cls");
        printf("\n\nSelecione uma opcao: \n");
        printf("1. Mostrar lista de clientes\n");
        printf("2. Mostrar lista de entregadores\n");
        printf("3. Mostrar lista de restaurantes\n");
        printf("4. Mostrar fila de pedidos universal\n");
        printf("5. \n");
        printf("6. \n");
        printf("7. \n");
        printf("8. \n");
        printf("9. Sair da conta\n");
        printf("0. Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 9)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 9);
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
        printf("2. Mostrar dados pessoais\n");
        printf("3. Mostrar nota\n");
        printf("4. Mostrar historico de entregas\n");
        printf("5. Alterar codigo de acesso\n");
        printf("6. Alterar e-mail\n");
        printf("7. Sair da conta\n");
        printf("8. Apagar conta\n");
        printf("0. Sair do app\n");
        printf("Opcao: ");
        scanf("%d", &op);
        if (op < 0 || op > 8)
            printf("\nDigite uma opcao valida\n\n");
    } while (op < 0 || op > 8);
    return op;
}
