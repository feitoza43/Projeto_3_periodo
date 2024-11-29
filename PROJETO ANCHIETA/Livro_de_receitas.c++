#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Estrutura que representa uma receita
typedef struct Receita {
    char nome[50];          
    char ingredientes[1000]; 
    char preparo[1000];      
    struct Receita *prox;   
} Receita;


Receita* criarReceita(char nome[], char ingredientes[], char preparo[]) {
    
    Receita* nova = (Receita*)malloc(sizeof(Receita));
    if (!nova) { 
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }
    // Copia os dados para a nova estrutura
    strcpy(nova->nome, nome);
    strcpy(nova->ingredientes, ingredientes);
    strcpy(nova->preparo, preparo);
    nova->prox = NULL; 
    return nova;
}


void adicionarReceitas(Receita** lista) {
    char nome[50], ingrediente[100], ingredientes[1000] = "", preparo[1000];
    char continuarIngrediente, continuarReceita;

    do {
        
        printf("Digite o nome da receita: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0'; 

        
        printf("Agora, insira os ingredientes um por vez.\n");
        do {
            printf("Digite um ingrediente: ");
            fgets(ingrediente, sizeof(ingrediente), stdin);
            ingrediente[strcspn(ingrediente, "\n")] = '\0'; // Remove o '\n'

            // Adiciona o ingrediente à lista de ingredientes
            strcat(ingredientes, "- "); 
            strcat(ingredientes, ingrediente);
            strcat(ingredientes, "\n");

            
            printf("Deseja adicionar outro ingrediente? (s/n): ");
            scanf(" %c", &continuarIngrediente);
            getchar(); 
        } while (continuarIngrediente == 's' || continuarIngrediente == 'S');

       
        printf("Digite o modo de preparo da receita:\n");
        fgets(preparo, sizeof(preparo), stdin);
        preparo[strcspn(preparo, "\n")] = '\0'; 

        // Cria uma nova receita e a adiciona ao início da lista
        Receita* nova = criarReceita(nome, ingredientes, preparo);
        nova->prox = *lista;
        *lista = nova;

        // Confirmação da adição
        printf("Receita '%s' adicionada!\n", nome);

        
        printf("Deseja adicionar outra receita? (s/n): ");
        scanf(" %c", &continuarReceita);
        getchar(); // Limpa o buffer do teclado

        // Reseta os ingredientes para a próxima receita
        strcpy(ingredientes, "");
    } while (continuarReceita == 's' || continuarReceita == 'S');
}

// Função para listar todas as receitas
void listarReceitas(Receita* lista) {
    if (!lista) { 
        printf("Nenhuma receita cadastrada.\n");
        return;
    }
    while (lista) { 
        printf("\n--- %s ---\n", lista->nome);
        printf("Ingredientes:\n%s\n", lista->ingredientes);
        printf("Modo de preparo:\n%s\n", lista->preparo);
        lista = lista->prox;
    }
}

void buscarReceita(Receita* lista, char nome[]) {
    while (lista) { 
        if (strcmp(lista->nome, nome) == 0) { 
            printf("\n--- Receita: %s ---\n", lista->nome);
            printf("Ingredientes:\n%s\n", lista->ingredientes);
            printf("Modo de preparo:\n%s\n", lista->preparo);
            return; 
        }
        lista = lista->prox;
    }
    printf("Receita '%s' não encontrada.\n", nome);
}

// Função para remover uma receita pelo nome
void removerReceita(Receita** lista, char nome[]) {
    Receita* atual = *lista, *anterior = NULL;
    while (atual) { 
        if (strcmp(atual->nome, nome) == 0) { 
            if (!anterior) *lista = atual->prox; 
            else anterior->prox = atual->prox; // Remove do meio ou do final
            free(atual); 
            printf("Receita '%s' removida!\n", nome);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Receita '%s' não encontrada.\n", nome);
}

// Função para salvar receitas em um arquivo binário
void salvarReceitas(Receita* lista) {
    FILE* arquivo = fopen("receitas.dat", "wb");
    if (!arquivo) { 
        printf("Erro ao salvar receitas.\n");
        return;
    }
    while (lista) { // Escreve cada receita no arquivo
        fwrite(lista, sizeof(Receita), 1, arquivo);
        lista = lista->prox;
    }
    fclose(arquivo); 
    printf("Receitas salvas com sucesso!\n");
}

// Função para carregar receitas de um arquivo binário
void carregarReceitas(Receita** lista) {
    FILE* arquivo = fopen("receitas.dat", "rb");
    if (!arquivo) { 
        printf("Nenhum arquivo de receitas encontrado.\n");
        return;
    }
    Receita temp;
    while (fread(&temp, sizeof(Receita), 1, arquivo) == 1) { // Lê do arquivo
        Receita* nova = criarReceita(temp.nome, temp.ingredientes, temp.preparo);
        nova->prox = *lista;
        *lista = nova;
    }
    fclose(arquivo); 
    printf("Receitas carregadas com sucesso!\n");
}
void milho(Receita){
    printf("");}


// Exibe o menu principal
void menu() {
    printf("\n===== Caderno de Receitas =====\n");
    printf("1. Adicionar receita\n");
    printf("2. Listar receitas\n");
    printf("3. Buscar receita\n");
    printf("4. Remover receita\n");
    printf("5. Sair\n");
    printf("6. buscar milho\n");
    printf("Escolha uma opcao: ");
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese"); 
    Receita* lista = NULL; // Inicializa a lista como vazia
    int opcao;
    char nome[50];

    carregarReceitas(&lista); 

    do {
        menu(); // Exibe o menu
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                adicionarReceitas(&lista); 
                break;
            case 2:
                listarReceitas(lista); 
                break;
            case 3:
                printf("Digite o nome da receita para buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                buscarReceita(lista, nome); 
                break;
            case 4:
                printf("Digite o nome da receita para remover: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                removerReceita(&lista, nome); 
                break;
            case 5:
                printf("Salvando receitas e saindo...\n");
                salvarReceitas(lista); 
                break;
            case 6:
                milho(Receita);
            default:
                printf("opcao inválida. Tente novamente.\n");
        }
    } while (opcao != 5);

    // Libera a memória alocada
    while (lista) {
        Receita* temp = lista;
        lista = lista->prox;
        free(temp);
    }

    return 0;
}
