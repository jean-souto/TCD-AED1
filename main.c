//BIBLIOTECAS, TADs E DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "entregador.h"
#include "cliente.h"

//FUNÇÕES EXTRAS
int inicializar_cliente (Cliente *item) // usada ao criar um novo cadastro de entregador (zera todas as informações para evitar lixo e erros) 
{
    item->valor_gasto = 0;
    item->quantidade_cartoes = 0;
    item->quant_pedidos = 0;
    item->quant_enderecos = 0;
    item->historico = NULL;
    item->pagamentos = NULL;
    item->enderecos = NULL;
    return 0;
}

int limpar_logado (Cliente *item)
{
    strcpy(item->cpf, "000");
    strcpy(item->email, "000");
    strcpy(item->nome, "000");
    strcpy(item->senha_8d, "000");
    item->codigo = -1;
    inicializar_cliente(item);
}

int menu1()
{
    int op = -1;
    printf ("Bem vindo!\n");
    do
    {
        printf ("\nSelecione uma opcao: \n");
        printf ("1. Sou cliente\n");
        printf ("2. Sou restaurante\n");
        printf ("3. Sou entregador\n");
        printf ("4. Sou administrador\n");
        printf ("0. Sair\n");
        printf ("Opcao: ");
        scanf ("%d", &op);
        if (op < 0 || op > 4) printf ("\nDigite uma opcao valida\n\n");
    }while (op < 0 || op > 4);
    return op;
}

int menu2()
{
    int op = -1;
    do
    {
        printf ("\nSelecione uma opcao: \n");
        printf ("1. Quero me cadastrar\n");
        printf ("2. Ja tenho cadastro\n");
        printf ("3. Voltar\n");
        printf ("0. Sair\n");
        printf ("Opcao: ");
        scanf ("%d", &op);
        if (op < 0 || op > 4) printf ("\nDigite uma opcao valida\n\n");
    }while (op < 0 || op > 4);
    return op;
}

int menu3()
{
    int op = -1;
    do
    {
        printf ("\nSelecione uma opcao: \n");
        printf ("1. Mostrar todos os restaurantes\n");
        printf ("2. Filtrar por categoria\n");
        printf ("3. Procurar por nome\n");
        printf ("4. Historico de pedidos\n");
        printf ("5. Cartoes\n");
        printf ("6. Enderecos\n");
        printf ("7. Alterar senha\n");
        printf ("8. Alterar e-mail\n");
        printf ("9. Sair da conta\n");
        printf ("10. Apagar conta\n");
        printf ("0. Sair do app\n");
        printf ("Opcao: ");
        scanf ("%d", &op);
        if (op < 0 || op > 10) printf ("\nDigite uma opcao valida\n\n");
    }while (op < 0 || op > 10);
    return op;
}

int menu4() // do adm
{
    int op = -1;
    do
    {
        printf ("\nSelecione uma opcao: \n");
        printf ("1. Mostrar lista de clientes\n");
        printf ("2. Mostrar lista de entregadores\n");
        printf ("3. Mostrar lista de restaurantes\n");
        printf ("4. Mostrar fila de pedidos universal\n");
        printf ("5. \n");
        printf ("6. \n");
        printf ("7. \n");
        printf ("8. \n");
        printf ("9. Sair da conta\n");
        printf ("0. Sair\n");
        printf ("Opcao: ");
        scanf ("%d", &op);
        if (op < 0 || op > 9) printf ("\nDigite uma opcao valida\n\n");
    }while (op < 0 || op > 9);
    return op;
}

// MAIN

int main ()
{
    srand(time(NULL));

    // declarações relacionadas aos clientes
    Lista_cliente *lista_principal_clientes;
    Cliente logado, esqueceu_senha;
    Cliente novo, inicializados;
    char email[40];
    char senha[15];
    char cpf[12];
    cartao novo_cartao;
    endereco novo_endereco;

    // declarações adm
    char loginADM[15];
    char senhaADM[15];

    // declarações gerais
    int option = -1;

    // inicializações

    lista_principal_clientes = criarCliente();

    strcpy (loginADM, "souADM");
    strcpy (senhaADM, "123ADM");

    inicializar_cliente(&esqueceu_senha);

    /*strcpy (inicializados.nome, "Alan da Silva");
    strcpy (inicializados.cpf, "145756984121");
    strcpy (inicializados.email, "alan@gmail.com");
    strcpy (inicializados.senha_8d, "12345678");
    inicializar_cliente(&inicializados);
    inserirInicioCliente(lista_principal_clientes, inicializados);*/

    while (option != 0)
    {
        option = menu1();

        switch (option)
        {

            case 0: // sair
            return 0;
            break;

            case 1: // sou cliente

                while (option != 3)
                {
                    option = menu2();

                    switch (option) 
                    {
                        case 0: // sair
                        return 0;
                        break;

                        case 1: // quero me cadastrar

                        printf ("Muito bem! Vamos realizar seu cadastro: \n");
                        
                        printf ("\nDigite seu nome: ");
                        setbuf (stdin, NULL);
                        scanf ("%[^\n]s", novo.nome);

                        printf ("\nDigite seu e-mail: ");
                        setbuf (stdin, NULL);
                        scanf ("%[^\n]s", novo.email);
                        
                        printf ("\nDigite seu CPF (somente numeros): ");
                        setbuf (stdin, NULL);
                        scanf ("%[^\n]s", novo.cpf);
                        
                        printf ("\nDigite sua senha (8 digitos): ");
                        setbuf (stdin, NULL);
                        scanf ("%[^\n]s", novo.senha_8d);
                        inicializar_cliente(&novo);

                        if ((inserirInicioCliente (lista_principal_clientes, novo)) == 0) printf ("\nCadastro realizado com sucesso!\n");
                        // mostrar_cliente(lista_principal_clientes);
                        break;

                        case 2: ; // ja tenho cadastro
                            
                            int verify = -1;
                            
                            while (verify != 0)
                            {
                                printf ("\nDigite 5 para voltar ou 6 se esqueceu a senha ou 0 para logar: ");
                                scanf ("%d", &verify);

                                if (verify == 5) break;
                                if (verify == 6)
                                {
                                    while (verify != 0)
                                    {
                                        printf ("\nDigite seu email: ");
                                        setbuf (stdin, NULL);
                                        scanf ("%[^\n]s", &email);

                                        printf ("\nDigite seu CPF: ");
                                        setbuf (stdin, NULL);
                                        scanf ("%[^\n]s", &cpf);

                                        verify = buscarClienteEmailCPF(lista_principal_clientes, &(*email), &(*cpf), &esqueceu_senha);

                                        if (verify == 0)
                                        {
                                            verify = -1;
                                            char senha1[15];
                                            char senha2[15];

                                            while (verify != 0)
                                            {
                                                if (verify != 1) printf ("\nTe encontramos!");
                                                printf ("\nDigite sua nova senha: ");
                                                setbuf (stdin, NULL);
                                                scanf ("%[^\n]s", &senha1);

                                                printf ("\nDigite sua nova senha novamente: ");
                                                setbuf (stdin, NULL);
                                                scanf ("%[^\n]s", &senha2);

                                                verify = alterarSenha(lista_principal_clientes, esqueceu_senha.codigo, senha1, senha2);

                                                if (verify == 0) printf ("Senha alterada com sucesso!");
                                                if (verify != 0) printf ("Senhas diferentes. Tente novamente!");
                                            }
                                        } else printf ("\nAlgo deu errado. Tente novamente!");
                                    }

                                }

                                printf ("\nDigite seu e-mail: ");
                                setbuf (stdin, NULL);
                                scanf ("%[^\n]s", &email);

                                printf ("\nDigite sua senha: ");
                                setbuf (stdin, NULL);
                                scanf ("%[^\n]s", &senha);

                                verify = loginCliente(lista_principal_clientes, &(*email), &(*senha), &logado);

                                if (verify != 0)
                                {
                                    printf ("\nLogin ou senha invalidos. Tente novamente!\n");
                                }

                                if (verify == 0)
                                {
                                    printf ("\nLogin efetuado com sucesso. Bem vindo(a) de volta, %s!\n", logado.nome);
                                }
                            }

                            if (verify == 5) break;

                            while ((option != 9) && (option != 10))
                            {
                                option = menu3();

                                switch (option) // opções do cliente após logar
                                {
                                    case 0: // sair
                                        return 0;
                                    break;

                                    case 1: // mostrar todos os restaurantes
                                    break;

                                    case 2: // filtrar por categoria
                                    break;

                                    case 3: //procurar por nome
                                    break;

                                    case 4: // histórico
                                    break;

                                    case 5: // cartões
                                        printf ("\nVoce possui os seguintes cartoes cadastrados: \n");
                                        buscarItemCliente (lista_principal_clientes, logado.codigo, &logado);
                                        mostrar_pagamentos (logado);
                                        printf ("\nVoce deseja: ");
                                        printf ("\n1. Cadastrar novo cartao");
                                        printf ("\n2. Excluir cartao");
                                        printf ("\n3. Voltar\n");
                                        scanf ("%d", &option);

                                        if (option == 1)
                                        {
                                            int temp = -1; 
                                            printf ("\n\nVamos la!\n");
                                            
                                            printf ("\nDigite o numero do cartao(sem espacos): ");
                                            setbuf (stdin, NULL);
                                            scanf ("%[^\n]s", novo_cartao.numero);
                                            
                                            printf ("\nDigite a data de validade (MMAA): ");
                                            setbuf (stdin, NULL);
                                            scanf ("%[^\n]s", novo_cartao.validade);

                                            printf ("\nDigite o CVV: ");
                                            setbuf (stdin, NULL);
                                            scanf ("%d", &novo_cartao.cvv);
                                                
                                            do 
                                            {
                                                printf ("\nO cartao eh de: \n1. Debito\n2.Credito\n");
                                                scanf ("%d", &temp);
                                            }while (temp < 1 || temp > 2);

                                            if (temp == 1) strcpy (novo_cartao.tipo, "Debito"); else strcpy (novo_cartao.tipo, "Credito");

                                            temp = inserirCartaoCliente(lista_principal_clientes, logado.codigo, novo_cartao);
                                            
                                            if (temp == 0) printf ("\nCadastro realizado com sucesso!"); else printf ("\nAlgum erro inesperado aconteceu. Tente novamente!");
                                        }

                                        if (option == 2)
                                        {
                                            int temp = -1;

                                            printf ("Digite qual o cartao que voce quer excluir (1, 2, 3...): ");
                                            scanf ("%d", &temp);

                                            temp = removerCartaoCliente(lista_principal_clientes, logado.codigo, temp);

                                            if (temp == 0) printf ("\nExcluido com sucesso!"); else printf ("\nAlgum erro inesperado aconteceu. Tente novamente!");
                                        }
                                    break;

                                    case 6: // endereços
                                        printf ("\nVoce possui os seguintes enderecos cadastrados: \n");
                                        buscarItemCliente (lista_principal_clientes, logado.codigo, &logado);
                                        mostrar_enderecos (logado);
                                        printf ("\nVoce deseja: ");
                                        printf ("\n1. Cadastrar novo endereco");
                                        printf ("\n2. Excluir endereco");
                                        printf ("\n3. Voltar\n");
                                        scanf ("%d", &option);

                                        if (option == 1)
                                        {
                                            int temp = -1; 
                                            printf ("\n\nVamos la!\n");
                                            
                                            printf ("\nDigite a rua: ");
                                            setbuf (stdin, NULL);
                                            scanf ("%[^\n]s", novo_endereco.rua);

                                            printf ("\nDigite o numero: ");
                                            setbuf (stdin, NULL);
                                            scanf ("%[^\n]s", novo_endereco.numero);

                                            printf ("\nDigite o CEP: ");
                                            setbuf (stdin, NULL);
                                            scanf ("%[^\n]s", novo_endereco.cep);

                                            temp = inserirEnderecoCliente(lista_principal_clientes, logado.codigo, novo_endereco);
                                            
                                            if (temp == 0) printf ("\nCadastro realizado com sucesso!"); else printf ("\nAlgum erro inesperado aconteceu. Tente novamente!");
                                        }

                                        if (option == 2)
                                        {
                                            int temp = -1;

                                            printf ("Digite qual o endereco que voce quer excluir (1, 2, 3...): ");
                                            scanf ("%d", &temp);

                                            temp = removerEnderecoCliente(lista_principal_clientes, logado.codigo, temp);

                                            if (temp == 0) printf ("\nExcluido com sucesso!"); else printf ("\nAlgum erro inesperado aconteceu. Tente novamente!");
                                        }
                                    break;

                                    case 7:; // alterar senha

                                        int verify = -1;
                                        char senha_atual[15];
                                        
                                        while (verify != 0)
                                        {
                                            printf ("\nDigite sua senha atual: ");
                                            setbuf(stdin, NULL);
                                            scanf ("%[^\n]s", &senha_atual);

                                            verify = strcmp(logado.senha_8d, senha_atual);

                                            if (verify != 0) 
                                            {
                                                printf ("\nSenha atual incorreta! Digite 1 para continuar ou 2 para voltar: ");
                                                scanf ("%d", &verify);
                                            }

                                            if (verify == 2) break;
                                        }

                                        if (verify == 2) break;
                                        
                                        verify = -1;
                                        
                                        while (verify != 0)
                                        {
                                            char senha1[15]; 
                                            char senha2[15];

                                            printf ("\nDigite sua nova senha: ");
                                            setbuf (stdin, NULL);
                                            scanf ("%[^\n]s", &senha1);

                                            printf ("\nDigite sua nova senha novamente: ");
                                            setbuf (stdin, NULL);
                                            scanf ("%[^\n]s", &senha2);

                                            verify = alterarSenha(lista_principal_clientes, logado.codigo, senha1, senha2);

                                            if (verify == 0) 
                                            {
                                                printf ("\nSenha alterada com sucesso!\n");
                                                buscarItemCliente (lista_principal_clientes, logado.codigo, &logado);
                                            }
                                            if (verify != 0) printf ("\nSenhas diferentes. Tente novamente!\n");
                                        }

                                    break;

                                    case 8:; // alterar email

                                        verify = -1;
                                        
                                        while (verify != 0)
                                        {
                                            printf ("\nDigite sua senha atual: ");
                                            setbuf(stdin, NULL);
                                            scanf ("%[^\n]s", &senha_atual);

                                            verify = strcmp(logado.senha_8d, senha_atual);

                                            if (verify != 0) 
                                            {
                                                printf ("\nSenha atual incorreta! Digite 1 para continuar ou 2 para voltar: ");
                                                scanf ("%d", &verify);
                                            }

                                            if (verify == 2) break;
                                        }

                                        if (verify == 2) break;
                                        
                                        verify = -1;
                                        
                                        char novo_email[40]; 

                                        printf ("\nDigite seu novo e-mail: ");
                                        setbuf (stdin, NULL);
                                        scanf ("%[^\n]s", &novo_email);

                                        verify = alterarEmail(lista_principal_clientes, logado.codigo, novo_email);

                                        if (verify == 0)
                                        {
                                            printf ("\nE-mail alterado com sucesso!\n");
                                            buscarItemCliente(lista_principal_clientes, logado.codigo, &logado);
                                        }
                                        if (verify != 0) printf ("\nAlgo deu errado. Tente novamente!\n");
                                        
                                    break;

                                    case 9: // sair da conta (voltar)
                                    break;

                                    case 10: // apagar conta
                                        printf ("\nVoce esta prestes a apagar sua conta e tudo que esta contido nela. Voce tem certeza? ");
                                        printf ("\nDigite 1 para sim e 2 para nao: ");
                                        scanf ("%d", &verify);
                        
                                        if (verify == 1)
                                        {
                                            printf ("\nMuito bem. Digite sua senha: ");
                                            setbuf(stdin, NULL);
                                            scanf ("%[^\n]s", &senha_atual);

                                            verify = strcmp(logado.senha_8d, senha_atual);

                                            if (verify == 0)
                                            {
                                                verify = removerItemCliente(lista_principal_clientes, logado.codigo);

                                                if (verify == 0)
                                                {
                                                    printf ("\nFoi um prazer ter voce conosco! Sua conta foi excluida com sucesso.");
                                                    limpar_logado(&logado);
                                                }
                                                else
                                                {
                                                    printf ("\nHouve algum erro. Tente novamente.");
                                                }
                                            }
                                            else
                                            {
                                                printf ("\nSenha incorreta. Tente novamente.");
                                            }
                                            break;
                                        }

                                        if (verify == 2)
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

            break;

            case 3: // sou entregador 

            break;

            case 4:; // sou adm

                char teste_login[15];
                char teste_senha[15];

                printf ("\nDigite o login de administrador: ");
                setbuf(stdin, NULL);
                scanf ("%[^\n]s", &teste_login);

                printf ("\nDigite a senha de administrador: ");
                setbuf(stdin, NULL);
                scanf ("%[^\n]s", &teste_senha);

                if ((strcmp(teste_login, loginADM) == 0) && strcmp(teste_senha, senhaADM) == 0) 
                {
                    printf ("\nBem-vindo, ADM!\n");

                    while (option != 9)
                    {
                        option = menu4();

                        switch (option)
                        {

                        }
                    }
                }
                else
                {
                    printf ("\nLogin ou senha incorretos!\n");
                }

            break;

            default:
            break;
        }
    }

    limparCliente(lista_principal_clientes);
    free(lista_principal_clientes);
    
    return 0;
}