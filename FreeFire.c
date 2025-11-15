#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

#define MAX_ITENS 10
#define MAX_NOME 50
#define MAX_TIPO 30

// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
typedef enum {
    POR_NOME,
    POR_TIPO,
    POR_PRIORIDADE
} CriterioOrdenacao;

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
Item mochila[MAX_ITENS];
int numItens = 0;
int comparacoes = 0;
bool ordenadaPorNome = false;

// Protótipos das funções
void limparTela();
void exibirMenu();
void inserirItem();
void removerItem();
void listarItens();
void buscaSequencialPorNome();
void menuDeOrdenacao();
void insertionSort(CriterioOrdenacao criterio);
void buscaBinariaPorNome();

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela() {
    for (int i = 0; i < 30; i++) {
        printf("\n");
    }
}

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu() {
    printf("\n========================================\n");
    printf("   🔫🎒 MOCHILA FREE FIRE 🎒🔫\n");
    printf("========================================\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Buscar item por nome (busca sequencial)\n");
    printf("5. Ordenar itens\n");
    printf("6. Busca binária por nome\n");
    printf("0. Sair\n");
    printf("========================================\n");
    if (ordenadaPorNome) {
        printf("Status: Mochila ordenada por nome ✓\n");
    } else {
        printf("Status: Mochila não ordenada por nome\n");
    }
    printf("========================================\n");
    printf("Escolha uma opção: ");
}

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("\n❌ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n--- Adicionar Item ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", mochila[numItens].nome);

    printf("Tipo: ");
    scanf(" %[^\n]", mochila[numItens].tipo);

    printf("Quantidade: ");
    scanf("%d", &mochila[numItens].quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &mochila[numItens].prioridade);

    // Validação da prioridade
    if (mochila[numItens].prioridade < 1 || mochila[numItens].prioridade > 5) {
        printf("⚠️ Prioridade inválida! Definindo como 3 (padrão).\n");
        mochila[numItens].prioridade = 3;
    }

    numItens++;
    ordenadaPorNome = false; // Após inserir, a mochila não está mais ordenada por nome
    printf("\n✅ Item adicionado com sucesso!\n");
}

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem() {
    if (numItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }

    char nomeBusca[MAX_NOME];
    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    scanf(" %[^\n]", nomeBusca);

    int indice = -1;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("\n❌ Item não encontrado!\n");
        return;
    }

    // Reorganiza o vetor removendo o item encontrado
    for (int i = indice; i < numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    numItens--;
    ordenadaPorNome = false; // Após remover, a mochila não está mais ordenada por nome
    printf("\n✅ Item removido com sucesso!\n");
}

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens() {
    if (numItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para listar.\n");
        return;
    }

    printf("\n--- Lista de Itens na Mochila ---\n");
    printf("+--------------------------------------------------------+----------+------------+\n");
    printf("| %-50s | %-8s | %-10s |\n", "Nome", "Tipo", "Quantidade");
    printf("+--------------------------------------------------------+----------+------------+\n");

    for (int i = 0; i < numItens; i++) {
        printf("| %-50s | %-8s | %-10d |\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade);
    }

    printf("+--------------------------------------------------------+----------+------------+\n");
    printf("\nTotal de itens: %d\n", numItens);
}

// buscaSequencialPorNome():
// Realiza busca sequencial por nome (Nível Aventureiro).
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscaSequencialPorNome() {
    if (numItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }

    char nomeBusca[MAX_NOME];
    printf("\n--- Buscar Item por Nome (Busca Sequencial) ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    bool encontrado = false;
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = true;
            printf("\n✅ Item encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Prioridade: %d\n", mochila[i].prioridade);
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item não encontrado!\n");
    }
}

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuDeOrdenacao() {
    if (numItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para ordenar.\n");
        return;
    }

    if (numItens == 1) {
        printf("\n⚠️ Apenas um item na mochila. Não é necessário ordenar.\n");
        return;
    }

    int opcao;
    CriterioOrdenacao criterio;

    printf("\n--- Ordenar Itens ---\n");
    printf("Escolha o critério de ordenação:\n");
    printf("1. Por nome (ordem alfabética)\n");
    printf("2. Por tipo (ordem alfabética)\n");
    printf("3. Por prioridade (maior para menor)\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            criterio = POR_NOME;
            break;
        case 2:
            criterio = POR_TIPO;
            break;
        case 3:
            criterio = POR_PRIORIDADE;
            break;
        default:
            printf("\n❌ Opção inválida!\n");
            return;
    }

    insertionSort(criterio);
    printf("\n✅ Mochila ordenada com sucesso!\n");
    printf("📊 Comparações realizadas: %d\n", comparacoes);

    if (criterio == POR_NOME) {
        ordenadaPorNome = true;
    } else {
        ordenadaPorNome = false;
    }
}

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0;
    Item chave;
    int j;

    for (int i = 1; i < numItens; i++) {
        chave = mochila[i];
        j = i - 1;

        bool deveTrocar = false;

        while (j >= 0) {
            comparacoes++;
            switch (criterio) {
                case POR_NOME:
                    if (strcmp(mochila[j].nome, chave.nome) > 0) {
                        deveTrocar = true;
                    }
                    break;
                case POR_TIPO:
                    if (strcmp(mochila[j].tipo, chave.tipo) > 0) {
                        deveTrocar = true;
                    }
                    break;
                case POR_PRIORIDADE:
                    if (mochila[j].prioridade < chave.prioridade) {
                        deveTrocar = true;
                    }
                    break;
            }

            if (deveTrocar) {
                mochila[j + 1] = mochila[j];
                j--;
                deveTrocar = false;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
}

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscaBinariaPorNome() {
    if (numItens == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }

    if (!ordenadaPorNome) {
        printf("\n⚠️ A mochila precisa estar ordenada por nome para realizar busca binária!\n");
        printf("Deseja ordenar agora? (1 = Sim, 0 = Não): ");
        int opcao;
        scanf("%d", &opcao);
        if (opcao == 1) {
            insertionSort(POR_NOME);
            ordenadaPorNome = true;
            printf("✅ Mochila ordenada por nome!\n");
        } else {
            printf("❌ Busca binária cancelada.\n");
            return;
        }
    }

    char nomeBusca[MAX_NOME];
    printf("\n--- Busca Binária por Nome ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    int esquerda = 0;
    int direita = numItens - 1;
    int comparacoesBusca = 0;
    bool encontrado = false;
    int indice = -1;

    while (esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        comparacoesBusca++;
        int resultado = strcmp(mochila[meio].nome, nomeBusca);

        if (resultado == 0) {
            encontrado = true;
            indice = meio;
            break;
        } else if (resultado < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }

    if (encontrado) {
        printf("\n✅ Item encontrado!\n");
        printf("Nome: %s\n", mochila[indice].nome);
        printf("Tipo: %s\n", mochila[indice].tipo);
        printf("Quantidade: %d\n", mochila[indice].quantidade);
        printf("Prioridade: %d\n", mochila[indice].prioridade);
        printf("📊 Comparações na busca: %d\n", comparacoesBusca);
    } else {
        printf("\n❌ Item não encontrado!\n");
        printf("📊 Comparações na busca: %d\n", comparacoesBusca);
    }
}

int main() {
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Buscar item por nome (busca sequencial)
    // 5. Ordenar os itens por critério (nome, tipo, prioridade)
    // 6. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.

    int opcao;

    printf("🔫🎒 Bem-vindo ao Desafio Código da Ilha – Edição Free Fire! 🎒🔫\n");
    printf("Nível: MESTRE\n\n");

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscaSequencialPorNome();
                break;
            case 5:
                menuDeOrdenacao();
                break;
            case 6:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("\n👋 Obrigado por usar a Mochila Free Fire! Boa sorte na ilha! 🏝️\n");
                break;
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
                break;
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar();
            getchar();
        }

    } while (opcao != 0);

    return 0;
}
