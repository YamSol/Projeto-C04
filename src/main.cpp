// Tema escolhido: Tema 01 - Pokedex

// Integrantes: Gustavo Pivoto Ambrósio
//              Yam Sol Britto Bertamini
//              Miguel Vianna Streva
//              Lucca Ribeiro Zogbi
//              João Pedro Nunes Vivas de Resende

#include <iostream>
#include <list>
#include <string>

using namespace std;

enum tipo_pokemon {
    NULO = 0,
    NORMAL,
    FIGHTING,
    FLYING,
    POISON,
    GROUND,
    ROCK,
    BUG,
    GHOST,
    STEEL,
    FIRE,
    WATER,
    GRASS,
    ELECTRIC,
    PSYCHIC,
    ICE,
    DRAGON,
    DARK,
    FAIRY
};

struct adj {
    int origem;
    int destino;
    int peso;
};

struct Cidade {
    int code;
    string name;
    bool hub;
    list<adj> adj_towns;
    int pos_x;
    int pos_y;
};

struct Pokemon {
    string nome;
    tipo_pokemon tipo[2];
    int pos_x;
    int pos_y;
};

struct TreeNode {
    Pokemon data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* insert(TreeNode* root, Pokemon p);
TreeNode* search(TreeNode* root, string nome);
TreeNode* remove(TreeNode* root, string nome);
TreeNode* minValueNode(TreeNode* node);
void inorder(TreeNode* root);
void freeTree(TreeNode* root);

const int N_CIDADES = 9;

void cadastro_cidades(struct Cidade* towns);
void inserir_pokemon(TreeNode*& root);
void print_menu();
void verificar_pokemon(TreeNode* root, string nome);

int main() {
    Cidade towns[9];
    int opc;
    string nome;

    cadastro_cidades(towns);

    TreeNode* root = nullptr;

    while (true) {
        print_menu();
        cin >> opc;
        switch (opc) {
            case 1:
                // Melhor rota para chegar ao centro Pokemon mais próximo
                
                break;
            case 2:
                // Verificação de um Pokemon pelo nome
                cout << "Digite o nome do Pokemon: ";
                cin >> nome;
                verificar_pokemon(root, nome);
                break;
            case 3:
                // Contabilizar a quantidade de Pokemon de cada tipo
                cout << "Digite o tipo do Pokemon para saber quantos tem: ";
                break;
            case 4:
                // Imprimir informações dos Pokemon por ordem crescente de nome
                inorder(root);
                break;
            case 5:
                // Imprimir Pokemon por ordem alfabética dos tipos
                break;
            case 6:
                // Quantidade de Pokemon num raio de 100m
                break;
            case 7:
                // Inserir Pokemon manualmente
                inserir_pokemon(root);
                break;
            case 8:
                // Remover Pokemon pelo nome
                cout << "Digite o nome do Pokemon a ser removido: ";
                cin >> nome;
                root = remove(root, nome);
                break;
            case 9:
                // Créditos do trabalho
                cout << "Integrantes: Gustavo Pivoto Ambrósio, Yam Sol Britto Bertamini, Miguel Vianna Streva, Lucca Ribeiro Zogbi, João Pedro Nunes Vivas de Resende" << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    }

    freeTree(root);

    return 0;
}

void cadastro_cidades(Cidade* towns) {
    (void)towns;
}

TreeNode* insert(TreeNode* root, Pokemon p) {
    if (root == nullptr) {
        TreeNode* node = new TreeNode();
        node->data = p;
        node->left = node->right = nullptr;
        return node;
    }
    if (p.nome < root->data.nome)
        root->left = insert(root->left, p);
    else if (p.nome > root->data.nome)
        root->right = insert(root->right, p);
    return root;
}

TreeNode* search(TreeNode* root, string nome) {
    if (root == nullptr || root->data.nome == nome)
        return root;
    if (nome < root->data.nome)
        return search(root->left, nome);
    return search(root->right, nome);
}

TreeNode* remove(TreeNode* root, string nome) {
    if (root == nullptr) return root;
    if (nome < root->data.nome)
        root->left = remove(root->left, nome);
    else if (nome > root->data.nome)
        root->right = remove(root->right, nome);
    else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }
        TreeNode* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = remove(root->right, temp->data.nome);
    }
    return root;
}

TreeNode* minValueNode(TreeNode* node) {
    TreeNode* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

void inorder(TreeNode* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data.nome << endl;
        inorder(root->right);
    }
}

void freeTree(TreeNode* root) {
    if (root != nullptr) {
        freeTree(root->left);
        freeTree(root->right);
        delete root;
    }
}

void verificar_pokemon(TreeNode* root, string nome) {
    TreeNode* result = search(root, nome);
    if (result != nullptr)
        cout << "Pokemon " << nome << " encontrado na posição (" << result->data.pos_x << ", " << result->data.pos_y << ")." << endl;
    else
        cout << "Pokemon " << nome << " não encontrado." << endl;
}

void inserir_pokemon(TreeNode*& root) {
    Pokemon p;
    int tipo1_int, tipo2_int;

    cout << "Digite o nome do Pokemon: ";
    cin >> p.nome;

    cout << "Digite o tipo primário do Pokemon (0-NULO, 1-NORMAL, ..., 18-FAIRY): ";
    cin >> tipo1_int;
    p.tipo[0] = static_cast<tipo_pokemon>(tipo1_int);

    cout << "Digite o tipo secundário do Pokemon (0-NULO, 1-NORMAL, ..., 18-FAIRY): ";
    cin >> tipo2_int;
    p.tipo[1] = static_cast<tipo_pokemon>(tipo2_int);

    cout << "Digite a posição x do Pokemon: ";
    cin >> p.pos_x;

    cout << "Digite a posição y do Pokemon: ";
    cin >> p.pos_y;

    root = insert(root, p);
}

void print_menu() {
    cout << "1 - Melhor rota para chegar ao centro Pokemon mais próximo" << endl;
    cout << "2 - Verificação de um Pokemon pelo nome" << endl;
    cout << "3 - Contabilizar a quantidade de Pokemon de cada tipo" << endl;
    cout << "4 - Imprimir informações dos Pokemon por ordem crescente de nome" << endl;
    cout << "5 - Imprimir Pokemon por ordem alfabética dos tipos" << endl;
    cout << "6 - Quantidade de Pokemon num raio de 100m" << endl;
    cout << "7 - Inserir Pokemon manualmente" << endl;
    cout << "8 - Remover Pokemon pelo nome" << endl;
    cout << "9 - Créditos do trabalho" << endl;
}