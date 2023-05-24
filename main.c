//BIBLIOTECAS, TADs E DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "entregador.h"
#include "cliente.h"

//FUNÇÕES EXTRAS
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
        printf ("0. Sair\n");
        printf ("Opcao: ");
        scanf ("%d", &op);
        if (op < 0 || op > 3) printf ("\nDigite uma opcao valida\n\n");
    }while (op < 0 || op > 3);
    return op;
}

int menu2()
{
    int op = -1;
    do
    {
        printf ("\nSelecione uma opcao: \n");
        printf ("1. Quero me cadastrar\n");
        printf ("2. Já tenho cadastro\n");
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
        printf ("4. Histórico de pedidos\n");
        printf ("5. Cartões\n");
        printf ("6. Endereços\n");
        printf ("7. Alterar e-mail\n");
        printf ("8. Alterar senha\n");
        printf ("9. Sair da conta\n");
        printf ("0. Sair do app\n");
        printf ("Opcao: ");
        scanf ("%d", &op);
        if (op < 0 || op > 8) printf ("\nDigite uma opcao valida\n\n");
    }while (op < 0 || op > 8);
    return op;
}

// MAIN

int main ()
{
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    // declarações relacionadas aos clientes
    Lista_cliente *lista_principal_clientes;
    Cliente logado;
    Cliente novo, inicializados;
    char email[40];
    char senha[9];
    cartao novo_cartao;

    // declarações gerais
    int option = -1;

    lista_principal_clientes = criarCliente();

    // inicializações

    strcpy (inicializados.nome, "Alan da Silva");
    strcpy (inicializados.cpf, "145756984121");
    strcpy (inicializados.email, "alansilva123@gmail.com");
    strcpy (inicializados.senha_8d, "12345678");
    inicializar_cliente(&inicializados);
    inserirInicioCliente(lista_principal_clientes, inicializados);

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
                        
                        printf ("\nDigite seu CPF (somente números): ");
                        setbuf (stdin, NULL);
                        scanf ("%[^\n]s", novo.cpf);
                        
                        printf ("\nDigite sua senha (8 dígitos): ");
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
                                printf ("\nDigite seu email: ");
                                setbuf (stdin, NULL);
                                scanf ("%[^\n]s", &email);

                                printf ("\nDigite sua senha: ");
                                setbuf (stdin, NULL);
                                scanf ("%[^\n]s", &senha);

                                verify = loginCliente(lista_principal_clientes, &(*email), &(*senha), &logado);

                                if (verify != 0)
                                {
                                    printf ("\nLogin ou senha inválidos. Tente novamente!\n");
                                }

                                if (verify == 0)
                                {
                                    printf ("\nLogin efetuado com sucesso. Bem vindo(a) de volta %s!\n", logado.nome);
                                }
                            }

                            while (option != 9)
                            {
                                option = menu3();

                                switch (option)
                                {
                                    case 0:
                                        return 0;
                                    break;

                                    case 5: 
                                        printf ("\nVocê possui os seguintes cartões cadastrados: \n");
                                        buscarItemCliente (lista_principal_clientes, logado.codigo, &logado);
                                        mostrar_pagamentos (logado);
                                        printf ("\nVocê deseja cadastrar um novo cartão? ");
                                        printf ("\n1. Sim");
                                        printf ("\n2. Voltar\n");
                                        scanf ("%d", &option);

                                        if (option == 1)
                                        {
                                            int temp = -1; 
                                            printf ("\n\nVamos lá!\n");
                                            
                                            printf ("\nDigite o número do cartão(sem espaços): ");
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
                                                printf ("\nO cartão é de: \n1. Débito\n2.Crédito\n");
                                                scanf ("%d", &temp);
                                            }while (temp < 1 || temp > 2);

                                            if (temp == 1) strcpy (novo_cartao.tipo, "Débito"); else strcpy (novo_cartao.tipo, "Crédito");

                                            temp = inserirCartaoCliente(lista_principal_clientes, logado.codigo, novo_cartao);
                                            
                                            if (temp == 0) printf ("\nCadastro realizado com sucesso!"); else printf ("\nAlgum erro inesperado aconteceu. Tente novamente!");
                                        }
                                    break;

                                    case 9:
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
        }
    }
    return 0;
}