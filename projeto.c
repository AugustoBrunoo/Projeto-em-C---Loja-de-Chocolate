/*---------- Constantes do Projeto ----------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct {
    char cpf[15];
    char nome[100];
    char dataNascimento[11];
    char telefone[50];
} dadosCliente;

/*---------- Validações ----------*/

int validarNome(char nomeCliente[]) {
    int tamanho = strlen(nomeCliente);
    for (int i = 0; i < tamanho; i++) {
        if (nomeCliente[i] == '-' || nomeCliente[i] == '_') {
            return 1;
        }
    }

    return 0;
}

int validarData(int dia, int mes, int ano) {
    if (ano < 1 || mes < 1 || mes > 12 || dia < 1) {
        return 0;
    } 

    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Ano bissexto

    if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
        diasNoMes[1] = 29;
    }

    if (dia > diasNoMes[mes - 1]) {
        return 0;
    } else {
        return 1;
    }
}

bool validarCPF(char cpf[]) {
    char copiaCPF[15];
    int tamanho = strlen(cpf);

    int j = 0;
    // Retira . e virgulas do cpf
    for (int i = 0; i < tamanho; i++) {
        if (cpf[i] == '-' || cpf[i] == '.') {
            continue;
        } else {
            copiaCPF[j] = cpf[i];
            j++;
        }
    }

    copiaCPF[j] = '\0';

    int tamanhoCopia = strlen(copiaCPF);

    if (tamanhoCopia > 11 || tamanhoCopia < 11) {
        return false;
    }

    // Se todos forem iguais

    bool todosIguais = true;

    for (int i = 1; i < 11; i++) {
        if (copiaCPF[i] != copiaCPF[0]) {
            todosIguais = false;
            break;
        }
    }

    if (todosIguais) return false;

    int cpfNum[11];
    
    for (int i = 0; i < 11; i++) {
        cpfNum[i] = copiaCPF[i] - '0';
    }
    // 1º digito verificador    

    int k = 10;
    int somaDV1 = 0;

    for (int i = 0; i < 9; i++) {
        somaDV1 += cpfNum[i] * k;
        k--;
    }
    
    int resultadoDV1 = (somaDV1 * 10) % 11;

    
    if (resultadoDV1 == 10 || resultadoDV1 == 11) {
        resultadoDV1 = 0;
    }

    if (cpfNum[9] != resultadoDV1) {
        return false;
    }

    // 2º Dígito verificador

    int somaDV2 = 0;

    k = 11;

    for (int i = 0; i < 10; i++) {
        somaDV2 += cpfNum[i] * k;
        k--;
    }

    int resultadoDV2 = (somaDV2 * 10) % 11;

    
    if (resultadoDV2 == 10 || resultadoDV2 == 11) {
        resultadoDV2 = 0;
    }
    
    if (cpfNum[10] != resultadoDV2) {
        return false;
    }
    
    return true;
}

int validarTelefone(char telefone[]) {
    int ddd[] = {
        11, 12, 13, 14, 15, 16, 17, 18, 19,     // São Paulo
        21, 22, 24,                             // Rio de Janeiro
        27, 28,                                 // Espírito Santo
        31, 32, 33, 34, 35, 37, 38,             // Minas Gerais
        41, 42, 43, 44, 45, 46,                 // Paraná
        47, 48, 49,                             // Santa Catarina
        51, 53, 54, 55,                         // Rio Grande do Sul
        61,                                     // Distrito Federal
        62, 64,                                 // Goiás
        63,                                     // Tocantins
        65, 66,                                 // Mato Grosso
        67,                                     // Mato Grosso do Sul
        68,                                     // Acre
        69,                                     // Rondônia
        71, 73, 74, 75, 77,                     // Bahia
        79,                                     // Sergipe
        81, 87,                                 // Pernambuco
        82,                                     // Alagoas
        83,                                     // Paraíba
        84,                                     // Rio Grande do Norte
        85, 88,                                 // Ceará
        86, 89,                                 // Piauí
        91, 93, 94,                             // Pará
        92, 97,                                 // Amazonas
        95,                                     // Roraima
        96,                                     // Amapá
        98, 99                                  // Maranhão
    };

    int tamanhoTel = strlen(telefone);
    char telefoneAjustado[12];

    int j = 0;
    for (int i = 0; i < tamanhoTel; i++) {
        if (isdigit(telefone[i])) {
            telefoneAjustado[j] = telefone[i];
            j++;
        }
    }

    telefoneAjustado[j] = '\0';


    if (j != 11) {
        return 0;
    }
    
    int dddUsuario = (telefoneAjustado[0] - '0') * 10 + (telefoneAjustado[1] - '0');

    for (int i = 0; i < 67; i++) {
        if (ddd[i] == dddUsuario) {
            return 1;
        }
    }
    
    return 0;
}

bool verificarCPFemBD(char cpf[], int *posicaoCliente, dadosCliente clientes[]) {
    int achou = 0;

    for (int i = 0; i < *posicaoCliente; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            achou = 1;
            break;
        }
    }

    if (achou) {
        return true;
    } else {
        return false;
    }
    
}

/*---------- Funções de Alterações ----------*/

void alterarNome(dadosCliente *cliente) {
        char nomeCadastro[100];
        int erro = 0;

        do {

        printf("Informe seu nome: ");
        fgets(nomeCadastro, sizeof(nomeCadastro), stdin);
        nomeCadastro[strcspn(nomeCadastro, "\n")] = '\0';
        
        if (validarNome(nomeCadastro)) {
            printf("Nome incorreto! Tente novamente!\n");
            erro = 1;
        } else {
            erro = 0;
        }
        
    } while (erro != 0);

    strcpy(cliente->nome, nomeCadastro);
}

void alterarDataNascimento(dadosCliente *cliente) {
    int dia, mes, ano;
    int erro;
    char dataNascimento[11];

    do {
        printf("Informe a data de nascimento (DD/MM/AAAA): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        getchar();

        if (!validarData(dia, mes, ano)) {
            printf("Data inválida! Tente novamente!\n");
            erro = 1;
        } else {
            erro = 0;
        }
    } while (erro != 0);

    sprintf(dataNascimento, "%02d/%02d/%04d", dia, mes, ano);
    strcpy(cliente->dataNascimento, dataNascimento);
}

void alterarTelefone(dadosCliente *cliente) {
    char telefoneCadastro[15];
    int erro = 0;

    do {
        printf("Informe seu celular (com DDD): ");
        fgets(telefoneCadastro, sizeof(telefoneCadastro), stdin);
        telefoneCadastro[strcspn(telefoneCadastro, "\n")] = '\0';

        if (!validarTelefone(telefoneCadastro)) {
            printf("Número inválido! Tente novamente!\n");
            erro = 1;
        } else {
            erro = 0;
        }

    } while (erro != 0);

    strcpy(cliente->telefone, telefoneCadastro);
}

/*---------- Funções secundárias do programa ----------*/

void adicionarCliente(char cpf[], int *posicaoCliente, dadosCliente clientes[]) {
    
    char nomeCadastro[100];
    char telefoneCadastro[20];
    char dataNascimento[11];
    int dia, mes, ano;

    // Outros dados

    int erro = 0;

    do {

        printf("Informe seu nome: ");
        fgets(nomeCadastro, sizeof(nomeCadastro), stdin);
        nomeCadastro[strcspn(nomeCadastro, "\n")] = '\0';
        
        if (validarNome(nomeCadastro)) {
            printf("Nome incorreto! Tente novamente!\n");
            erro = 1;
        } else {
            erro = 0;
        }
        
    } while (erro != 0);
    


    do {
        printf("Informe sua data de nascimento (DD/MM/AAAA): ");
        scanf("%d/%d/%d", &dia, &mes, &ano);
        getchar();

        if (!validarData(dia, mes, ano)) {
            printf("Data inválida! Tente novamente!\n");
            erro = 1;
        } else {
            erro = 0;
        }
    } while (erro != 0);

    sprintf(dataNascimento, "%02d/%02d/%04d", dia, mes, ano);

    do {
        printf("Informe seu celular (com DDD): ");
        fgets(telefoneCadastro, sizeof(telefoneCadastro), stdin);
        telefoneCadastro[strcspn(telefoneCadastro, "\n")] = '\0';

        if (!validarTelefone(telefoneCadastro)) {
            printf("Número inválido! Tente novamente!\n");
            erro = 1;
        } else {
            erro = 0;
        }


    } while (erro != 0);

    // Adicionando o cpf do cliente automaticamente
    strcpy(clientes[*posicaoCliente].cpf, cpf); 
    
    // Adição dos outros dados no vetor
    strcpy(clientes[*posicaoCliente].nome, nomeCadastro);
    strcpy(clientes[*posicaoCliente].dataNascimento, dataNascimento);
    strcpy(clientes[*posicaoCliente].telefone, telefoneCadastro);

    // Resumo dos dados
    printf("\n\n");

    printf("Veja um resumo dos dados que serão adicionados:\n\n");
    printf("Nome: %s\n", clientes[*posicaoCliente].nome);
    printf("CPF: %s\n", clientes[*posicaoCliente].cpf);
    printf("Data de Nascimento: %s\n", clientes[*posicaoCliente].dataNascimento);
    printf("Telefone: %s\n", clientes[*posicaoCliente].telefone);
    
    (*posicaoCliente)++;

    printf("\nCliente cadastrado com sucesso!\n\n");
}  

void alterarCadastro(int posicaoUsuario, dadosCliente clientes[]) {
    int escolha;

    do {
        printf("\n\n");

        printf("Escolha das opções abaixo: \n");
        printf("1 - Nome\n");
        printf("2 - Data de Nascimento\n");
        printf("3 - Telefone\n");
        printf("4 - Todos os dados\n");
        printf("5 - Cancelar\n");
        printf("\n");
        printf("O que voce deseja alterar? ");
        scanf("%d", &escolha);
        getchar();

        printf("\n");

        if (escolha < 1 || escolha > 5) printf("Opçao inexistente! Tente novamente!\n");

        switch (escolha) {
        case 1:
            alterarNome(&clientes[posicaoUsuario]);
            break;
        case 2:
            alterarDataNascimento(&clientes[posicaoUsuario]);
            break;
        case 3: 
            alterarTelefone(&clientes[posicaoUsuario]);
            break;
        case 4:
            alterarNome(&clientes[posicaoUsuario]);
            alterarDataNascimento(&clientes[posicaoUsuario]);
            alterarTelefone(&clientes[posicaoUsuario]);
            break;
        case 5:
            return;
        default:
            break;
        }

    } while (escolha < 1 || escolha > 5);
    
    printf("\nVeja os dados atualizados:\n");
    printf("\n");
    printf("Nome: %s\n", clientes[posicaoUsuario].nome);
    printf("CPF: %s\n", clientes[posicaoUsuario].cpf);
    printf("Data de Nascimento: %s\n", clientes[posicaoUsuario].dataNascimento);
    printf("Telefone: %s\n", clientes[posicaoUsuario].telefone);
    printf("\n\n");
    
}

void mostrarDados(char cpf[], int* posicaoCliente, dadosCliente clientes[], int id) {
    char escolha;
    int posEncontrada;
    printf("\n");
    for (int i = 0; i < *posicaoCliente; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0)  {
            printf("Cliente %d:\n", i + 1);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Data de Nascimento: %s\n", clientes[i].dataNascimento);
            printf("Telefone: %s\n", clientes[i].telefone);
            printf("\n\n");
            
            posEncontrada = i;
        }
    }
    
    if (id == 1) {

        do {
            printf("Deseja alterar algum dado desse cliente (S ou N)? ");
            scanf(" %c", &escolha);
            getchar();
            escolha = toupper(escolha);
    
            if (escolha == 'S') {
                alterarCadastro(posEncontrada, clientes);
            } else if (escolha == 'N') {
                return;
            }
    
        } while (escolha != 'S' && escolha != 'N');
    }
}

/*---------- Funções primárias do sistema ----------*/

void cadastrarCliente(dadosCliente clientes[], int *posicaoCliente) {
    // Verificar se o cliente é cadastrado
    int valida;
    char cpfUsuario[15];  // espaço para CPF com pontos e traço
    char escolha;

    do {
        printf("Digite o CPF (000.000.000-00): ");
        fgets(cpfUsuario, sizeof(cpfUsuario), stdin);
        cpfUsuario[strcspn(cpfUsuario, "\n")] = '\0';

        // Validar se o cpf é válido!
        valida = validarCPF(cpfUsuario);

        if (!valida) {
            printf("CPF Invalido, tente novamente!\n");
        }

    } while (!valida);
    
    // Se válido, verifica se o CPF é cadastrado

    bool cadastrado = verificarCPFemBD(cpfUsuario, posicaoCliente, clientes);

    if (!cadastrado) {
        printf("\nCliente não cadastrado!\n\n");

        do {
            printf("Deseja cadastrar cliente? (S/N): ");
            scanf(" %c", &escolha);
            getchar();

            escolha = toupper(escolha);

            if (escolha == 'S') {
                adicionarCliente(cpfUsuario, posicaoCliente, clientes);
            } else if (escolha == 'N') {
                return;
            }

        } while (escolha != 'S' && escolha != 'N');

    } else {
        printf("\n");
        printf("Cliente já cadastrado ao sistema!\n");
        printf("\n\n");
        
        mostrarDados(cpfUsuario, posicaoCliente, clientes, 1);
    }
}

void buscarCliente(dadosCliente clientes[], int *posicaoCliente) {
    printf("\n\n");

    if ((*posicaoCliente) == 0) {
        printf("Ainda nao ha clientes cadastrados no sistema!\n");
    } else {
        
        int valida;
        char cpfUsuario[15];  // espaço para CPF com pontos e traço
    
        do {
            printf("Digite o CPF (000.000.000-00): ");
            fgets(cpfUsuario, sizeof(cpfUsuario), stdin);
            cpfUsuario[strcspn(cpfUsuario, "\n")] = '\0';
    
            // Validar se o cpf é válido!
            valida = validarCPF(cpfUsuario);
    
            if (!valida) {
                printf("CPF Invalido, tente novamente!\n");
            }
    
            bool cadastrado = verificarCPFemBD(cpfUsuario, posicaoCliente, clientes);
    
            char escolha;
    
            if (!cadastrado) {
                printf("Cliente nao cadastrado no sistema!\n");
                printf("\n");
                do {
                    printf("Deseja cadastrar? (S ou N): ");
                    scanf(" %c", &escolha);
                    getchar();
                    escolha = toupper(escolha);
    
                    if (escolha != 'S' && escolha != 'N') {
                        printf("Escolha invalida, tente novamente!\n\n");
                    }
                } while (escolha != 'S' && escolha != 'N');
    
                if (escolha == 'S') {
                    adicionarCliente(cpfUsuario, posicaoCliente, clientes);
                }
            } else {
                mostrarDados(cpfUsuario, posicaoCliente, clientes, 1);
            }
    
        } while (!valida);
    }
}

void aniversariantes(dadosCliente clientes[], int posicaoCliente) {
    int mesEscolhido;

    if (posicaoCliente == 0) {
        printf("Nao nenhum cliente cadastrado na loja!\n");
    } else {
        do {
            printf("Digite o mes desejado: ");
            scanf("%d", &mesEscolhido);
    
            if (mesEscolhido < 1 || mesEscolhido > 12) {
                printf("O mes escolhido nao existe! Tente novamente!");
            }
    
        } while (mesEscolhido < 1 || mesEscolhido > 12);
        
        dadosCliente aniversariantesMes[posicaoCliente];
        int totalAniversariantes = 0;
    
        for (int i = 0; i < posicaoCliente; i++) {
            char mesStr[3];
            strncpy(mesStr, clientes[i].dataNascimento + 3, 2);
            mesStr[2] = '\0';
    
            int mes = atoi(mesStr); // Transforma a string em numero
    
            if (mes == mesEscolhido) {
                aniversariantesMes[totalAniversariantes] = clientes[i];
                totalAniversariantes++;
            }
        }
    
        if (totalAniversariantes == 0) {
            printf("Nenhum cliente faz aniversario este mes\n");
        }

        for (int i = 0; i < totalAniversariantes - 1; i++) {
            for (int j = 0; j < totalAniversariantes - i - 1; j++) {
                char diaStr1[3], diaStr2[3];
                
                // extrai o dia do primeiro cliente
                strncpy(diaStr1, aniversariantesMes[j].dataNascimento, 2);
                diaStr1[2] = '\0';
                int dia1 = atoi(diaStr1);

                // extrai o dia do segundo cliente
                strncpy(diaStr2, aniversariantesMes[j + 1].dataNascimento, 2);
                diaStr2[2] = '\0';
                int dia2 = atoi(diaStr2);

                if (dia1 > dia2) {
                    // troca os clientes
                    dadosCliente temp = aniversariantesMes[j];
                    aniversariantesMes[j] = aniversariantesMes[j + 1];
                    aniversariantesMes[j + 1] = temp;
                }
            }    
        }

        printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf("\n%d cliente(s) faz aniversario no mes %d:\n", totalAniversariantes, mesEscolhido);

        for (int i = 0; i < totalAniversariantes; i++) {
            char dia[3], mes[3], ano[5];

            strncpy(dia, aniversariantesMes[i].dataNascimento, 2);
            dia[2] = '\0';

            strncpy(mes, aniversariantesMes[i].dataNascimento + 3, 2);
            mes[2] = '\0';

            strncpy(ano, aniversariantesMes[i].dataNascimento + 6, 4);
            ano[4] = '\0';

            printf("\n");
            printf("Cliente %d\n", i + 1);
            printf("\n\n");
            printf("Nome: %s\n", aniversariantesMes[i].nome);
            printf("Data de Nascimento: %s/%s/%s\n", dia, mes, ano);
            printf("Telefone: %s\n", aniversariantesMes[i].telefone);
        }
        printf("\n\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    }
    printf("\n\n");
}

int buscarClienteVenda(dadosCliente clientes[], int *posicaoCliente) {
    printf("\n\n");

    int valida;
    char cpfUsuario[15];  // espaço para CPF com pontos e traço
    int flagProcurar = 0;
    int posicao = -1;

    do {
        printf("Digite o CPF (000.000.000-00): ");
        fgets(cpfUsuario, sizeof(cpfUsuario), stdin);
        cpfUsuario[strcspn(cpfUsuario, "\n")] = '\0';
    
        // Validar se o cpf é válido!
        valida = validarCPF(cpfUsuario);
    
        if (!valida) {
            printf("CPF Invalido, tente novamente!\n");
        }
        
        
    } while (!valida);
    
    bool cadastrado = verificarCPFemBD(cpfUsuario, posicaoCliente, clientes);
    
    if (!cadastrado) {
        char escolha;

        printf("Cliente nao cadastrado no sistema!\n");
        printf("\n");
        do {
            printf("Deseja cadastrar? (S ou N): ");
            scanf(" %c", &escolha);
            getchar();
            escolha = toupper(escolha);

            if (escolha != 'S' && escolha != 'N') {
                printf("Escolha invalida, tente novamente!\n\n");
            }
        } while (escolha != 'S' && escolha != 'N');

        if (escolha == 'S') {
            adicionarCliente(cpfUsuario, posicaoCliente, clientes);
            flagProcurar = 1;
        }

    } else {
        flagProcurar = 1;
    }

    if (flagProcurar == 1) {
        // Se já está cadastrado, precisamos localizar a posição
        for (int i = 0; i < *posicaoCliente; i++) {
            if (strcmp(clientes[i].cpf, cpfUsuario) == 0) {
                posicao = i;
                break;
            }
        }
    }

    return posicao;
}

int cadastrarClienteVenda(dadosCliente clientes[],int *posicaoCliente) {
    while (1) {
        // Verificar se o cliente é cadastrado
        int valida;
        char cpfUsuario[15];  // espaço para CPF com pontos e traço
        char escolha;
    
        do {
            printf("Digite o CPF (000.000.000-00): ");
            fgets(cpfUsuario, sizeof(cpfUsuario), stdin);
            cpfUsuario[strcspn(cpfUsuario, "\n")] = '\0';
    
            // Validar se o cpf é válido!
            valida = validarCPF(cpfUsuario);
    
            if (!valida) {
                printf("CPF Invalido, tente novamente!\n");
            }
    
        } while (!valida);
        
        // Se válido, verifica se o CPF é cadastrado
    
        bool cadastrado = verificarCPFemBD(cpfUsuario, posicaoCliente, clientes);
    
        if (!cadastrado) {
            getchar();
            adicionarCliente(cpfUsuario, posicaoCliente, clientes);
            return *posicaoCliente - 1;
            break;

        } else {
            printf("Já existe cliente cadastrado com esse CPF no sistema!\n");
            printf("\n");

            // mostrarDados(cpfUsuario, posicaoCliente, clientes, 2);
            printf("Tente outro CPF!\n\n");

            printf("Deseja tentar novamente? (S/N): ");
            scanf(" %c", &escolha);
            getchar();

            escolha = toupper(escolha);

            if (escolha == 'N') {
                return -1;
            }
        }
    }
}

void realizarVenda(dadosCliente clientes[], int posicao, int id) {
    char produtos[10][50] = {"ChocoDelícia", "Amargo Supremo", "Branco Neve", "Crocante Caramelo", 
    "Noir Intenso", "ChocoMenta", "ChocoCafé", "ChocoKids", "Branco Crocante", "ChocoLaranja"};

    double valorProdutos[10] = {9.90, 12.50, 10.00, 11.75, 13.90, 10.50, 12.00, 8.50, 11.00, 10.00};

    char flagContinuar = 0;
    double valorAPagar = 0;
    
    double carrinhoValorCliente[100]; // Vai até 100 produtos
    char carrinhoProdutos[10][50];
    int posCarrinho = 0;
    int unidadesProduto[100];

    if (id != -1) {
        printf("Ola, %s!\n", clientes[posicao].nome);
        printf("Voce tem 20%% de desconto no final da compra!\n");
    }

    do {
        int escolha;
        int quantidadeChoco;
        printf("\n\n");
        printf("Chocolates disponiveis:\n\n");
        printf("Nome do Chocolate      Tipo de Chocolate     Preço (R$)\n");
        printf("----------------------------------------------------------\n");
        printf("1. ChocoDelícia         Ao Leite              R$  9.90\n");
        printf("2. Amargo Supremo       Amargo                R$ 12.50\n");
        printf("3. Branco Neve          Branco                R$ 10.00\n");
        printf("4. Crocante Caramelo    Ao Leite              R$ 11.75\n");
        printf("5. Noir Intenso         Amargo                R$ 13.90\n");
        printf("6. ChocoMenta           Menta                 R$ 10.50\n");
        printf("7. ChocoCafé            Café                  R$ 12.00\n");
        printf("8. ChocoKids            Ao Leite              R$  8.50\n");
        printf("9. Branco Crocante      Branco                R$ 11.00\n");
        printf("10. ChocoLaranja        Laranja               R$ 10.90\n");
        printf("----------------------------------------------------------\n");

        do {
            printf("Escolha um chocolate (Digite o numero relacionado a ele): ");
            scanf("%d", &escolha);

            if (escolha < 1 || escolha > 10) {
                printf("\a");
                printf("Produto inexistente, escolha novamente!\n");
            }

        } while (escolha < 1 || escolha > 10);

        do {
            printf("Deseja adquirir quantas unidades? ");
            scanf("%d", &quantidadeChoco);
        } while (quantidadeChoco <= 0);
        
        
        carrinhoValorCliente[posCarrinho] = quantidadeChoco * valorProdutos[escolha - 1];
        strcpy(carrinhoProdutos[posCarrinho], produtos[escolha - 1]);
        unidadesProduto[posCarrinho] = quantidadeChoco;

        do {
            printf("Deseja comprar mais algum chocolate? (S/N): ");
            scanf(" %c", &flagContinuar);
            
            flagContinuar = toupper(flagContinuar);

            if (flagContinuar != 'S' && flagContinuar != 'N') {
                printf("Opcao invalida! Tente novamente!\n");
            }
            
        } while (flagContinuar != 'S' && flagContinuar != 'N');
        
        posCarrinho++; 

    } while (flagContinuar == 'S');

    printf("\n\n");

    printf("Total do Carrinho:\n");
    
    for (int i = 0; i < posCarrinho; i++) {
        printf("%s  - %d unidades  - R$ %.2f\n", carrinhoProdutos[i], unidadesProduto[i], carrinhoValorCliente[i]);
        valorAPagar += carrinhoValorCliente[i];
    }
    
    printf("\n");
    printf("----------------------------------------\n");
    printf("Total a Pagar:\n");

    if (id == -1) {
        printf("R$ %.2f\n", valorAPagar);
    } else {
        printf("R$ %.2f - (20%% de desconto) = R$ %.2f\n", valorAPagar, valorAPagar - (valorAPagar * 0.20));
    }

    printf("\n\n");
}

void pre_venda(dadosCliente clientes[], int *posicaoCliente) {
    char escolha;
    int posClienteRegistrado;

    do {
        printf("\n");
        printf("O cliente tem cadastro no sistema? (S/N): ");
        scanf(" %c", &escolha);
        getchar();

        escolha = toupper(escolha);

        if (escolha != 'S' && escolha != 'N') {
            printf("Opcao Invalida! Tente Novamente!\n");
        }

    } while (escolha != 'S' && escolha != 'N');

    if (escolha == 'N') {
        char escolhaCadastro;

        do {
            printf("\nDeseja se cadastrar na loja e aproveitar benefícios?\n");
            printf("Vantagem: 20%% de desconto na sua compra final!\n");
            printf("Deseja realizar o cadastro agora? (S/N): ");

            scanf(" %c", &escolhaCadastro);
            escolhaCadastro = toupper(escolhaCadastro);

            getchar();

            if (escolhaCadastro != 'S' && escolhaCadastro != 'N') {
                printf("Opcao Invalida! Tente Novamente!\n");
            }

        } while (escolhaCadastro != 'S' && escolhaCadastro != 'N');

        if (escolhaCadastro == 'S') {
            int resultadoCadastro = cadastrarClienteVenda(clientes, posicaoCliente);

            if (resultadoCadastro != -1) {
                realizarVenda(clientes, resultadoCadastro, 1);
            }

            // e se for -1? (Nao achar)
        } else {
            realizarVenda(clientes, 0, -1);
        }

    } else {   
        posClienteRegistrado = buscarClienteVenda(clientes, posicaoCliente);

        if (posClienteRegistrado == -1) {
            realizarVenda(clientes, posClienteRegistrado, -1);
        } else {
            realizarVenda(clientes, posClienteRegistrado, 1);
        }
    }
}

int main() {
    dadosCliente clientes[100];
    int posicaoCliente = 0;

    int escolha;
    printf("\n");
    printf("Sistema da Loja de Chocolate!\n");
    printf("Projeto realizado em: 30/07/2025\n");
    printf("\n\n");

    // Estrutura de Repetição para caso o usuário digite errado
    // possa ver as opções novamente no terminal

    do {
        printf("--------- | Menu | ---------");
        printf("\n\n");
        printf("Escolha das opções abaixo:\n\n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Buscar Cliente por CPF\n");
        printf("3 - Aniversariantes do Mês\n");
        printf("4 - Realizar Venda\n");
        printf("5 - Encerrar programa\n");
        printf("\n");
        printf("Digite a escolha desejada: ");
        scanf("%d", &escolha);
        getchar();

        if (escolha < 0 || escolha > 5) {
            printf("\n");
            printf("Opção inválida! Escolha uma opcao valida!");
            printf("\n\n");
            continue;
        }

        switch (escolha) {
        case 1:
            cadastrarCliente(clientes, &posicaoCliente);
            break;
        case 2:
            buscarCliente(clientes, &posicaoCliente);
            break;
        case 3: 
            aniversariantes(clientes, posicaoCliente);
            break;
        case 4:
            pre_venda(clientes, &posicaoCliente);
            break;
        case 5:
            printf("\n\n");
            printf("Programa encerrado com sucesso!\n\n");
            break;
        default:
            break;
        }

    } while (escolha != 5);


    
    return 0;
}