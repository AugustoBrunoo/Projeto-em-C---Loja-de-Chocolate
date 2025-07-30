/*---------- Constantes do Projeto ----------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char cpf[11];
    char nome[100];
    char dataNascimento[9];
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

/*---------- Funções secundárias do programa ----------*/

int informacoesCliente (int id, int *posicaoCliente, dadosCliente clientes[]) {
    int valida;

    switch (id) {

    case 0: 
    char cpfUsuario[11];

    printf("Digite o CPF (000.000.000-0): ");
    fgets(cpfUsuario, sizeof(cpfUsuario), stdin);
    
    int valida = validarCPF(cpfUsuario); // validar CPF

    if (valida == 1) {
        // Verifica se há no banco de clientes
        int cadastrado = 0;
        
        for (int i = 0; i < posicaoCliente; i++) {
            if (clientes[i].cpf == cpfUsuario) {
                cadastrado = 1;
            }
        }

        if (cadastrado == 0) {
            char escolha;
            printf("Cliente nao cadastrado!\n");
            printf("\n\n");

            do {
                printf("Deseja cadastrar cliente (S ou N)? \n");
                scanf(" %c", escolha);
                getchar();
                escolha = toupper(escolha);

                if (escolha == 'S') {
                    informacoesCliente(1, posicaoCliente, dadosCliente clientes[]);
                } else {
                    break;
                }
            
            } while (escolha != 'S' || escolha != 'N');
            
        }
        
    }

    return 0;
    
    break;

    case 2:

    char nomeCliente[100];
        printf("Informe seu nome: ");
        fgets(nomeCliente, sizeof(nomeCliente), stdin);
        nomeCliente[strcspn(nomeCliente, "\n")] = '\0';

        valida = validarNome(nomeCliente);

        if (valida == 1) {
            clientes[posicaoCliente].nome = nomeCliente;
            return 1;
        } else {
            // int tentar = tentarNovamente();
        }

        break;

    default:
        break;
    }
}


/*---------- Funções primárias do sistema ----------*/

void cadastrarCliente(dadosCliente clientes[], int *posicaoCliente) {
    // Verificar se o cliente é cadastrado

    int verificarCadastro = informacoesCliente(0, posicaoCliente);
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

        if (escolha < 0 || escolha > 5) {
            printf("\n");
            printf("Opção inválida! Escolha uma opcao valida!");
            printf("\n\n");
        }

    } while (escolha < 0 || escolha > 5);

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
    default:
        break;
    }

    
    return 0;
}