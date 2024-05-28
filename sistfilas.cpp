#include <iostream>
using namespace std;

// Estrutura do nó da Fila
struct No {
    string senha;
    No* prox;
};

// Estrutura da Fila
struct Fila {
    No* ini; // início da fila
    No* fim; // fim da fila
};

Fila* criaFila() {
    Fila* f = (Fila*)malloc(sizeof(Fila)); // Aloca memória para a Fila

    if (f != NULL) {
        f->ini = f->fim = NULL;
    }

    return f;
}

void gerarSenha(Fila* f) {
    static int numeroSenha = 1; // Variável estática para controlar o número da senha
    string novaSenha = "A" + to_string(numeroSenha++);

    No* novo = (No*)malloc(sizeof(No)); // Aloca memória para o novo No

    if (novo != NULL) {
        novo->senha = novaSenha;
        novo->prox = NULL;

        if (f->fim == NULL) {
            f->ini = f->fim = novo;
        } else {
            f->fim->prox = novo;
            f->fim = novo;
        }
    }
}

string atender(Fila* f) {
    if (f->ini == NULL) {
        cout << "Fila vazia!" << endl;
        return "";
    }

    No* temp = f->ini;
    string senha = temp->senha;

    f->ini = f->ini->prox;

    if (f->ini == NULL) {
        f->fim = NULL;
    }

    free(temp); 

    return senha;
}

bool filaVazia(Fila* f) {
    return f->ini == NULL;
}

void imprimirFila(Fila* f) {
    if (filaVazia(f)) {
        cout << "Fila vazia." << endl;
        return;
    }

    No* temp = f->ini;
    while (temp != NULL) {
        cout << temp->senha << " ";
        temp = temp->prox;
    }
    cout << endl;
}

int main() {
    Fila* f = criaFila();
    char opcao;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Gerar senha\n";
        cout << "2. Atender senha\n";
        cout << "3. Sair\n";
        cout << "Escolha a opcao: ";
        cin >> opcao;

        switch (opcao) {
            case '1':
                gerarSenha(f);
                break;
            case '2':
                if (!filaVazia(f)) {
                    string senhaAtendida = atender(f);
                    cout << "Senha atendida: " << senhaAtendida << endl;
                } else {
                    cout << "Fila vazia, não há senhas para atender." << endl;
                }
                break;
            case '3':
                free(f); // Libera a memória alocada para a Fila antes de encerrar o programa
                return 0;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }

        cout << "Senhas na fila: ";
        imprimirFila(f);
    }

    return 0;
}
