#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string TIPOS_POKEMON[] = {
    "N/A",      // 0
    "NORMAL",   // 1
    "FIGHTING", // 2
    "FLYING",   // 3
    "POISON",   // 4
    "GROUND",   // 5
    "ROCK",     // 6
    "BUG",      // 7
    "GHOST",    // 8
    "STEEL",    // 9
    "FIRE",     // 10
    "WATER",    // 11
    "GRASS",    // 12
    "ELECTRIC", // 13
    "PSYCHIC",  // 14
    "ICE",      // 15
    "DRAGON",   // 16
    "DARK",     // 17
    "FAIRY",    // 18
};


struct Ponto {
    int x;
    int y;
};

struct adj {
    int origem;
    int destino;
    int peso;
};

struct Cidade {
    string name;
    int code;
    bool hub;
    list<adj> adj_towns;
    Ponto posicao;
};

struct Pokemon {
    string nome;
    int tipos[2];
    Ponto posicao;
};

struct Node {
    Pokemon data;
    Node* left;
    Node* right;
};

void print_menu();
void print_types();
Node* insert(Node* root, Pokemon p);
Node* search(Node* root, string nome);
Node* remove(Node* root, string nome);
Node* min_value_node(Node* node);
void in_order(Node* root);
void free_tree(Node* root);
void read_pokemon(Node*& root);
void verificar_pokemon(Node* root, string nome);
void show_pokemon_by_type(Node* root);
int count_pokemon_by_type(Node* root, int tipo);

void cadastro_cidades(struct Cidade* towns);

void collectPokemons(Node* root, vector<Pokemon>& pokemons);

int main() {
    // Estruturas de dados
    Cidade towns[9];
    Node* pokemons = nullptr;
    Ponto posicao_usuario = {1,1};
    
    // variaveis de leitura
    string nome;
    int tipo;
    int opc;

    while (true) {
        
        // Mensagem de boas-vindas ao treinador pokemon.
        cout << "Olá, Treinador de Pokémon! Bem-vindo à sua Pokédex. Informamos que você está em uma área de 1000 x 1000 m². Sua localização atual é (X =?, Y = ?). Sua Pokédex possui várias funcionalidades que o auxiliarão em sua aventura. Boa caçada!";

        // Printa o menu para o usuário.
        print_menu();

        // Espera o usuário entrar com uma opção na Pokédex.
        cin >> opc;
        
        switch (opc) {
            case 1:
                // Melhor rota para chegar ao centro Pokemon mais próximo

                break;
            case 2:
                // Verificação de um Pokemon pelo nome
                cout << "Digite o nome do Pokemon a ser verificado: ";
                cin >> nome;
                verificar_pokemon(pokemons, nome);
                break;
            case 3:
                // Contabilizar a quantidade de Pokemon de cada tipo
                cout << "Digite o tipo de Pokemon (0-NULO, 1-NORMAL, ..., 18-FAIRY): ";
                cin >> tipo;
                cout << "Quantidade de Pokemons do tipo " << TIPOS_POKEMON[tipo] << ": " << count_pokemon_by_type(pokemons, tipo) << endl;
                break;
            case 4:
                // Imprimir informações dos Pokemon por ordem crescente de nome
                in_order(pokemons);
                break;
            case 5:
                // Imprimir Pokemon por ordem alfabética dos tipos
                show_pokemon_by_type(pokemons);
                break;
            case 6:
                // Quantidade de Pokemon num raio de 100m
                
                cout << "A quantidade de Pokemon num raio de 100m é: " << pokemon_raio100(pokemons, posicao_usuario);
                break;
            case 7:
                // Inserir Pokemon manualmente
                read_pokemon(pokemons);
                break;
            case 8:
                // Remover Pokemon pelo nome
                cout << "Digite o nome do Pokemon a ser removido: ";
                cin >> nome;
                pokemons = remove(pokemons, nome);
                break;
            case 9:
                // Créditos do trabalho
                cout << "Integrantes: Gustavo Pivoto Ambrósio, Yam Sol Britto Bertamini, Miguel Vianna Streva, Lucca Ribeiro Zogbi, João Pedro Nunes Vivas de Resende" << endl;
                break;
            default:
                cout << "Opção inválida!" << endl;
        }
    }

    free_tree(pokemons);
    return 0;
}

void print_menu() {
    cout << "(nao implm.)1 - Melhor rota para chegar ao centro Pokemon mais próximo \n";
    cout << "2 - Verificação de um Pokemon pelo nome\n";
    cout << "3 - Contabilizar a quantidade de Pokemon de cada tipo\n";
    cout << "4 - Imprimir informações dos Pokemon por ordem crescente de nome\n";
    cout << "5 - Imprimir Pokemons por ordem alfabética dos tipos\n";
    cout << "6 - Quantidade de Pokemon num raio de 100m\n";
    cout << "7 - Inserir Pokemon manualmente\n";
    cout << "8 - Remover Pokemon pelo nome\n";
    cout << "9 - Créditos do trabalho\n";
}

void print_types() {
    cout << "+-------------------------------------------\n";
    cout << "||\n";
    cout << "||\n";
    cout << "||\n";
    cout << "||\n";
    cout << "||\n";
    cout << "||\n";
    cout << "||\n";
    cout << "+-------------------------------------------\n";
}

Node* insert(Node* root, Pokemon p) {
    if (root == nullptr) {
        Node* node = new Node();
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

Node* search(Node* root, string nome) {
    if (root == nullptr || root->data.nome == nome)
        return root;
    if (nome < root->data.nome)
        return search(root->left, nome);
    return search(root->right, nome);
}

Node* remove(Node* root, string nome) {
    if (root == nullptr) return root;
    if (nome < root->data.nome)
        root->left = remove(root->left, nome);
    else if (nome > root->data.nome)
        root->right = remove(root->right, nome);
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = min_value_node(root->right);
        root->data = temp->data;
        root->right = remove(root->right, temp->data.nome);
    }
    return root;
}

Node* min_value_node(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

void in_order(Node* root) {
    if (root != nullptr) {
        in_order(root->left);
        cout << "Nome: " << root->data.nome 
             << ", Tipo 1: " << TIPOS_POKEMON[root->data.tipos[0]] 
             << ", Tipo 2: " << TIPOS_POKEMON[root->data.tipos[1]] 
             << ", Posição: (" << root->data.posicao.x << ", " << root->data.posicao.y << ")" 
             << endl;
        in_order(root->right);
    }
}

void free_tree(Node* root) {
    if (root != nullptr) {
        free_tree(root->left);
        free_tree(root->right);
        delete root;
    }
}

void verificar_pokemon(Node* root, string nome) {
    Node* result = search(root, nome);
    if (result != nullptr)
        cout << "Pokemon " << nome << " encontrado na posição (" << result->data.posicao.x << ", " << result->data.posicao.y << ")." << endl;
    else
        cout << "Pokemon " << nome << " não encontrado." << endl;
}

void read_pokemon(Node*& root) {
    Pokemon p;

    cout << "Digite o nome do Pokemon: ";
    cin >> p.nome;

    cout << "Digite o tipo primário do Pokemon (0-NULO, 1-NORMAL, ..., 18-FAIRY): ";
    cin >> p.tipos[0];

    cout << "Digite o tipo secundário do Pokemon (0-NULO, 1-NORMAL, ..., 18-FAIRY): ";
    cin >> p.tipos[1];

    cout << "Digite a posição x do Pokemon: ";
    cin >> p.posicao.x;

    cout << "Digite a posição y do Pokemon: ";
    cin >> p.posicao.y;

    root = insert(root, p);
}

int pokemon_raio100(Node*& pokemons, Ponto posicao_jogador){

    if(pokemons != NULL){
        pokemon_raio100(pokemons->left, posicao_jogador);
        // if(pokemons->data)
        pokemon_raio100(pokemons->right, posicao_jogador);
        
    }
}

void collectPokemons(Node* root, vector<Pokemon>& pokemons) {
    if (root == nullptr) {
        return;
    }
    collectPokemons(root->left, pokemons);
    pokemons.push_back(root->data);
    collectPokemons(root->right, pokemons);
}

void show_pokemon_by_type(Node* root) {
    vector<Pokemon> pokemons;
    collectPokemons(root, pokemons);

    sort(pokemons.begin(), pokemons.end(), [](const Pokemon& a, const Pokemon& b) {
        if (TIPOS_POKEMON[a.tipos[0]] != TIPOS_POKEMON[b.tipos[0]]) {
            return TIPOS_POKEMON[a.tipos[0]] < TIPOS_POKEMON[b.tipos[0]];
        }
        return a.nome < b.nome;
    });

    for (const Pokemon& p : pokemons) {
        cout << "Nome: " << p.nome 
             << ", Tipo 1: " << TIPOS_POKEMON[p.tipos[0]] 
             << ", Tipo 2: " << TIPOS_POKEMON[p.tipos[1]] 
             << ", Posição: (" << p.posicao.x << ", " << p.posicao.y << ")" 
             << endl;
    }
}

int count_pokemon_by_type(Node* root, int tipo) {
    if (root == nullptr) {
        return 0;
    }

    int count = 0;
    if (root->data.tipos[0] == tipo || root->data.tipos[1] == tipo) {
        count = 1;
    }

    return count + count_pokemon_by_type(root->left, tipo) + count_pokemon_by_type(root->right, tipo);
}

void cadastro_cidades(Cidade* towns) {
	cout << "Quantas cidades deseja inserir? ";
	int num_cidades, num_adj, cidade_destino;
	for (int i = 0; i < num_cidades; i++) {
		cout << "Cidade [" << i << "] \n";
		cout << "- Nome: ";
		cin >> towns[i].name;
		cout << "- Codigo: ";
		cin >> towns[i].code;
		cout << "- Possui hub? (0,1): ";
		cin >> towns[i].hub;
		cout << "- Posição (Ex: '100 200'): ";
		cin >> towns[i].posicao.x;
		cin >> towns[i].posicao.y;

		cout << "- Número de Cidades adjacentes: ";
		cin >> num_adj;
		for (int j = 0; j < num_adj; j++) {
			cin >> cidade_destino;
			towns[i].adj_towns.push_back({towns[i].code,cidade_destino});
		}
		
	}
}

