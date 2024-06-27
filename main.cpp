#include <iostream>
using namespace std;

// Definição da estrutura do nó da fila
struct No {
    int dado; // Dado armazenado no nó
    No *prox; // Ponteiro para o próximo nó na fila
};

// Definição da estrutura da fila
struct Fila {
    No *ini; // Ponteiro para o primeiro nó da fila
    No *fim; // Ponteiro para o último nó da fila
};

// Função para inicializar a fila
Fila* iniciarFila() {
    Fila *f = new Fila; // Aloca memória para a fila
    f->ini = NULL; // Inicializa o ponteiro de início com null
    f->fim = NULL; // Inicializa o ponteiro de fim com null
    return f; // Retorna a fila inicializada
}

// Função para verificar se a fila está vazia
bool filaVazia(Fila *f) {
    return (f->ini == NULL); // Retorna verdadeiro se o ponteiro de início for null
}

// Função para enfileirar um elemento na fila
void enfileirar(Fila *f, int valor) {
    No *novoNo = new No; // Cria um novo nó
    novoNo->dado = valor; // Atribui o valor ao dado do nó
    novoNo->prox = NULL; // Inicializa o próximo do nó como null

    if (filaVazia(f)) { // Se a fila estiver vazia
        f->ini = novoNo; // O início da fila aponta para o novo nó
    } else {
        f->fim->prox = novoNo; // Caso contrário, o próximo do último nó aponta para o novo nó
    }
    f->fim = novoNo; // Atualiza o fim da fila para o novo nó
}

// Função para desenfileirar um elemento da fila
int desenfileirar(Fila *f) {
    if (filaVazia(f)) { // Verifica se a fila está vazia
        return -1; // Retorna -1 se a fila estiver vazia
    } else {
        No *primeiroNo = f->ini; // Obtém o primeiro nó da fila
        int dadoRetornado = primeiroNo->dado; // Obtém o dado do primeiro nó
        f->ini = primeiroNo->prox; // Atualiza o início da fila para o próximo nó
        if (f->ini == NULL) { // Se o início se tornar nulo (fila ficar vazia)
            f->fim = NULL; // Atualiza o fim da fila para nulo também
        }
        delete primeiroNo; // Libera a memória do nó desenfileirado
        return dadoRetornado; // Retorna o dado do nó desenfileirado
    }
}

// Função para contar o número de elementos na fila
int contarElementos(Fila *f) {
    int quantidade = 0; // Inicializa a variável para contar os elementos
    No *noAtual = f->ini; // Começa do início da fila

    while (noAtual != NULL) { // Percorre todos os nós da fila
        quantidade++; // Incrementa o contador
        noAtual = noAtual->prox; // Move para o próximo nó
    }
    return quantidade; // Retorna a quantidade de elementos na fila
}

// Função para liberar a memória alocada para a fila
void liberarFila(Fila *f) {
    No *noAtual = f->ini; // Começa do início da fila

    while (noAtual != NULL) { // Enquanto houver nós na fila
        No *proximoNo = noAtual->prox; // Guarda o próximo nó
        delete noAtual; // Libera a memória do nó atual
        noAtual = proximoNo; // Move para o próximo nó
    }
    delete f; // Libera a memória da estrutura da fila
}

// Função principal
int main() {
    Fila *filaSenhasGeradas = iniciarFila(); // Inicializa a fila de senhas geradas
    Fila *filaSenhasAtendidas = iniciarFila(); // Inicializa a fila de senhas atendidas
    int opcao; // Variável para armazenar a opção do usuário
    int proximaSenha = 0; // Variável para controlar o número da próxima senha a ser gerada

    do {
        // Menu de opções
        cout << "Selecione uma opcao:\n";
        cout << "0. Sair\n";
        cout << "1. Gerar senha\n";
        cout << "2. Realizar atendimento\n";
        cout << "Senhas aguardando atendimento: " << contarElementos(filaSenhasGeradas) << "\n"; // Exibe a quantidade de senhas na fila de geradas
        cin >> opcao; // Lê a opção do usuário

        switch(opcao) {
            case 0:
                if (!filaVazia(filaSenhasGeradas)) { // Verifica se há senhas aguardando atendimento
                    cout << "Ainda existem senhas aguardando atendimento. Continue o atendimento antes de sair.\n"; // Mensagem de aviso
                    opcao = -1; // Para evitar sair do loop se houver senhas aguardando
                } else {
                    cout << "Quantidade de senhas atendidas: " << contarElementos(filaSenhasAtendidas) << "\n"; // Exibe a quantidade de senhas atendidas ao sair
                }
                break;
            case 1:
                proximaSenha++; // Incrementa o número da senha atual
                enfileirar(filaSenhasGeradas, proximaSenha); // Enfileira a nova senha gerada
                cout << "Senha gerada: " << proximaSenha << "\n"; // Exibe a senha gerada
                break;
            case 2:
                if (!filaVazia(filaSenhasGeradas)) { // Verifica se há senhas para atendimento
                    int senhaAtendida = desenfileirar(filaSenhasGeradas); // Desenfileira a próxima senha a ser atendida
                    enfileirar(filaSenhasAtendidas, senhaAtendida); // Enfileira a senha na fila de senhas atendidas
                    cout << "Atendendo senha: " << senhaAtendida << "\n"; // Exibe a senha que está sendo atendida
                } else {
                    cout << "Nao ha senhas para atendimento.\n"; // Mensagem de aviso se não houver senhas para atendimento
                }
                break;
            default:
                cout << "Opcao invalida. Tente novamente.\n"; // Mensagem de opção inválida
                break;
        }
    } while (opcao != 0); // Continua o loop até o usuário escolher sair

    liberarFila(filaSenhasGeradas); // Libera a memória da fila de senhas geradas
    liberarFila(filaSenhasAtendidas); // Libera a memória da fila de senhas atendidas

    return 0; // Retorna 0 para indicar que o programa terminou com sucesso
}
