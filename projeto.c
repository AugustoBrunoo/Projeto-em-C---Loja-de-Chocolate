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
        getchar();
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

    printf("Veja um resumo dos dados que serão adicionados:\n");
    printf("Nome: %s\n", clientes[*posicaoCliente].nome);
    printf("CPF: %s\n", clientes[*posicaoCliente].cpf);
    printf("Data de Nascimento: %s\n", clientes[*posicaoCliente].dataNascimento);
    printf("Telefone: %s\n", clientes[*posicaoCliente].telefone);
    
    (*posicaoCliente)++;

    printf("Cliente cadastrado com sucesso!\n");
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
        case 5:
            return;
        default:
            break;
        }

    } while (escolha < 1 || escolha > 5);
    
}

void mostrarDados(char cpf[], int* posicaoCliente, dadosCliente clientes[]) {
    char escolha;
    int posEncontrada;

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

/*---------- Funções primárias do sistema ----------*/

void cadastrarCliente(dadosCliente clientes[], int *posicaoCliente) {
    // Verificar se o cliente é cadastrado
    int valida;
    char cpfUsuario[15];  // espaço para CPF com pontos e traço
    char escolha;

    do {
        printf("Digite o CPF (000.000.000-0): ");
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
        printf("Cliente não cadastrado!\n\n");

        do {
            printf("Deseja cadastrar cliente (S ou N)? ");
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

        printf("Cliente já cadastrado ao sistema!\n");
        printf("\n\n");
        
        mostrarDados(cpfUsuario, posicaoCliente, clientes);

        return; // Implementar mais tarde
    }

}


int main() {
    dadosCliente clientes[100];
    int posicaoCliente = 0;

    int escolha;
    printf("Sistema da Loja de Chocolate!\n");
    printf("Projeto realizado em: 30/07/2025\n");
    printf("\n\n\n");

    // Estrutura de Repetição para caso o usuário digite errado
    // possa ver as opções novamente no terminal

    do {
        printf("----- | Menu | -----");
        printf("\n\n");
        printf("Escolha das opções abaixo: \n");
        printf("1 - Cadastrar Cliente\n");
        printf("2 - Buscar Cliente por CPF\n");
        printf("3 - Aniversariantes do Mês\n");
        printf("4 - Realizar Venda\n");
        printf("5 - Cancelar\n");
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
            // buscarCliente();
            break;
        case 3: 
            // aniversariantes();
            break;
        case 4:
            // realizarVenda();
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