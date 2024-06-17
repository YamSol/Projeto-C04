#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

#define INT_MAX 9999

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

struct edge {
  int orig;
  int dest;
  int weight;
};

struct Cidade {
  string name;
  int id;
  bool isHubPresent;
  Ponto posicao;
  list<edge> adj_towns;
};

struct Pokemon {
  string nome;
  int tipos[2];
  Ponto posicao;
};

struct Node {
  Pokemon data;
  Node *left;
  Node *right;
};

void print_menu();

// ------- TOWN FUNCTIONS

void cadastro_cidades(Cidade towns[]);
void find_shortest_path(Cidade towns[], int num_towns, Ponto posicao_usuario);

// Town aux functions
double distancia(Ponto p1, Ponto p2);

// ------- POKEMON FUNCTIONS

void read_pokemon(Node *&root);
Node *insert_pokemon_in_tree(Node *root, Pokemon p);
Node *remove_pokemon_from_tree(Node *root, string nome);
void free_pokemon_tree(Node *root);
void show_pokemon_in_order(Node *root);
void show_pokemon_by_type(Node *root);
void verify_pokemon(Node *root, string nome);
int count_pokemon_by_type(Node *root, int tipo);
int count_pokemon_in_radius(Node *root, Ponto posicao, int raio);

// Pokemon aux functions
void collectPokemons(Node *root, vector<Pokemon> &pokemons);
Node *search_pokemon_in_tree(Node *root, string nome);
Node *min_value_node(Node *node);


int main() {
  // Estruturas de dados
  Cidade towns[9];
  Node *pokemons = NULL;
  Ponto posicao_usuario = {0, 0};

  // variaveis de leitura
  string nome;
  int tipo;
  int opc;
  int quantidade_pokemons_raio = 0;

  // Cadastrando cidades no sistema e setando a posição do usuário
  cadastro_cidades(towns);
  posicao_usuario.x = towns[0].posicao.x;
  posicao_usuario.y = towns[0].posicao.y;

  while (true) {
    // Mensagem de boas-vindas ao treinador pokemon.
    printf("Ola, Treinador(a) Pokemon! Bem-vindo a sua Pokedex. Informamos que voce esta \
     em uma area de 1000 x 1000 m². Sua localizacao atual e (X = %d, Y = \
     %d). Sua Pokedex possui varias funcionalidades que o auxiliarao em sua \
     aventura. Boa caçada!",
        posicao_usuario.x, posicao_usuario.y);

    // Printa o menu para o usuário.
    print_menu();

    // Espera o usuário entrar com uma opção na Pokédex.
    cin >> opc;

    switch (opc) {
    case 1:
      // Melhor rota para chegar ao centro Pokemon mais próximo
      find_shortest_path(towns, 9, posicao_usuario);
      break;
    case 2:
      // Verificação de um Pokemon pelo nome
      cout << "Digite o nome do Pokemon a ser verificado: ";
      cin >> nome;
      verify_pokemon(pokemons, nome);
      break;
    case 3:
      // Contabilizar a quantidade de Pokemon de cada tipo
      cout << "Digite o tipo de Pokemon (0-NULO, 1-NORMAL, ..., 18-FAIRY): ";
      cin >> tipo;
      cout << "Quantidade de Pokemons do tipo " << TIPOS_POKEMON[tipo] << ": "
           << count_pokemon_by_type(pokemons, tipo) << endl;
      break;
    case 4:
      // Imprimir informações dos Pokemon por ordem crescente de nome
      show_pokemon_in_order(pokemons);
      break;
    case 5:
      // Imprimir Pokemon por ordem alfabética dos tipos
      show_pokemon_by_type(pokemons);
      break;
    case 6:
      // Quantidade de Pokemon num raio de 100m
      cout << "A quantidade de Pokemon num raio de 100m e: "
           << count_pokemon_in_radius(pokemons, posicao_usuario, 100) << endl;
      break;
    case 7:
      // Inserir Pokemon manualmente
      read_pokemon(pokemons);
      break;
    case 8:
      // Remover Pokemon pelo nome
      cout << "Digite o nome do Pokemon a ser removido: ";
      cin >> nome;
      pokemons = remove_pokemon_from_tree(pokemons, nome);
      break;
    case 9:
      // Créditos do trabalho
      cout << "Integrantes: Gustavo Pivoto Ambrosio, Yam Sol Britto Bertamini, "
              "Miguel Vianna Streva, Lucca Ribeiro Zogbi, Joao Pedro Nunes "
              "Vivas de Resende"
           << endl;
      break;
    default:
      cout << "Opçao invalida!" << endl;
    }
  }

  free_pokemon_tree(pokemons);

  return 0;
}



//////////////////////////////////////////////////////////////////// Funções
/// para uso no código
/////////////////////////////////////////////////////////////////////////

// 1ª função - Cadastra as cidades no sistema
void cadastro_cidades(Cidade towns[]) {
  int num_adj, id_cidade_destino, distancia_cidade_adj;
  for (int i = 0; i < 9; i++) {
    cout << "Cidade [" << i << "] \n";
    cout << "- Nome: ";
    cin >> towns[i].name;
    cout << "- Codigo: ";
    cin >> towns[i].id;
    cout << "- Possui hub? (0,1): ";
    cin >> towns[i].isHubPresent;
    cout << "- Posição (Ex: '100 200'): ";
    cin >> towns[i].posicao.x;
    cin >> towns[i].posicao.y;
    cout << "- Numero de Cidades adjacentes: ";
    cin >> num_adj;
    for (int j = 0; j < num_adj; j++) {
      cin >> id_cidade_destino;
      distancia_cidade_adj = distancia(towns[i].posicao, towns[j].posicao);
      towns[i].adj_towns.push_back(
          {towns[i].id, id_cidade_destino, distancia_cidade_adj});
    }
  }
}
// 2ª função - Imprime o menu de opções para o usuário.
void print_menu() {
  cout << "1 - Melhor rota para chegar ao centro Pokemon mais proximo"
       << endl;                                              // Nao implementada
  cout << "2 - Verificacao de um Pokemon pelo nome" << endl; // Implementada
  cout << "3 - Contabilizar a quantidade de Pokemons de cada tipo"
       << endl; // Implementada
  cout << "4 - Imprimir informações dos Pokemons por ordem crescente de nome"
       << endl; // Implementada
  cout << "5 - Imprimir Pokemons por ordem alfabetica dos tipos"
       << endl; // Implementada
  cout << "6 - Quantidade de Pokemons num raio de 100m"
       << endl; // Nao implementada
  cout << "7 (EXTRA) - Encontrar um perimetro minimo para englobar todos os "
          "pokemons que estao dentro do raio de 100 metros da Pokedex"
       << endl;
  cout << "8 - Inserir Pokemons manualmente" << endl; // Implementada
  cout << "9 - Remover Pokemons pelo nome" << endl;   // Implementada
  cout << "10 - Creditos do trabalho" << endl;        // Implementada
  cout << "11 (EXTRA) - proporcionar uma busca performatica implementando "
          "mecanismos de rotacao para manter a(s) arvore(s) balanceada(s)"
       << endl;
}

// // 3ª função - Melhor rota para chegar ao centro Pokemon mais próximo
// resposta shortest_path_dijkstra(list<edge> edge[], int vertices, int start,
//                                 int end) {
//   bool intree[vertices];
//   int distance[vertices], parent[vertices], saltos[vertices];

//   for (int u = 0; u < vertices; u++) {
//     intree[u] = false;
//     distance[u] = INT_MAX;
//     parent[u] = -1;
//     saltos[u] = INT_MAX;
//   }
//   distance[start] = 0;
//   saltos[start] = 0;
//   int v = start;
//   while (intree[v] == false) {
//     intree[v] = true;
//     list<edge>::iterator p;
//     for (p = edge[v].begin(); p != edge[v].end(); p++) {
//       int dest = p->dest;
//       int weight = p->custo;
//       if (distance[dest] > distance[v] + weight) {
//         distance[dest] = distance[v] + weight;
//         parent[dest] = v;
//         saltos[dest] = saltos[v] + 1;
//       }
//     }
//     v = 0;
//     int dist = INT_MAX;
//     for (int u = 0; u < vertices; u++) {
//       if (intree[u] == false && distance[u] < dist) {
//         dist = distance[u];
//         v = u;
//       }
//     }
//   }
//   return {distance[end], saltos[end]};
// }

// 4ª função - Verificação de um Pokemon pelo nome
void verify_pokemon(Node *root, string nome) {

  Node *result = search_pokemon_in_tree(root, nome);
  if (result != NULL)
    cout << "Pokemon " << nome << " encontrado na posicao ("
         << result->data.posicao.x << ", " << result->data.posicao.y << ")."
         << endl;
  else
    cout << "Pokemon " << nome << " nao encontrado." << endl;
}
Node *search_pokemon_in_tree(Node *root, string nome) {
  if (root == NULL || root->data.nome == nome)
    return root;
  if (nome < root->data.nome)
    return search_pokemon_in_tree(root->left, nome);
  return search_pokemon_in_tree(root->right, nome);
}

// 5ª função - Contabilizar a quantidade de Pokemon de cada tipo
int count_pokemon_by_type(Node *root, int tipo) {
  if (root == NULL) {
    return 0;
  }

  int count = 0;
  if (root->data.tipos[0] == tipo || root->data.tipos[1] == tipo) {
    count = 1;
  }

  return count + count_pokemon_by_type(root->left, tipo) +
         count_pokemon_by_type(root->right, tipo);
}

// 6ª função - Imprimir informações dos Pokemon por ordem crescente de nome
void show_pokemon_in_order(Node *root) {
  if (root != NULL) {
    show_pokemon_in_order(root->left);
    cout << "Nome: " << root->data.nome
         << ", Tipo 1: " << TIPOS_POKEMON[root->data.tipos[0]]
         << ", Tipo 2: " << TIPOS_POKEMON[root->data.tipos[1]] << ", Posicao: ("
         << root->data.posicao.x << ", " << root->data.posicao.y << ")" << endl;
    show_pokemon_in_order(root->right);
  }
}

// 7ª função - Imprimir Pokemon por ordem alfabética dos tipos
void show_pokemon_by_type(Node *root) {
  vector<Pokemon> pokemons;
  collectPokemons(root, pokemons);

  sort(pokemons.begin(), pokemons.end(),
       [](const Pokemon &a, const Pokemon &b) {
         if (TIPOS_POKEMON[a.tipos[0]] != TIPOS_POKEMON[b.tipos[0]]) {
           return TIPOS_POKEMON[a.tipos[0]] < TIPOS_POKEMON[b.tipos[0]];
         }
         return a.nome < b.nome;
       });

  for (const Pokemon &p : pokemons) {
    cout << "Nome: " << p.nome << ", Tipo 1: " << TIPOS_POKEMON[p.tipos[0]]
         << ", Tipo 2: " << TIPOS_POKEMON[p.tipos[1]] << ", Posicao: ("
         << p.posicao.x << ", " << p.posicao.y << ")" << endl;
  }
}
void collectPokemons(Node *root, vector<Pokemon> &pokemons) {
  if (root == NULL) {
    return;
  }
  collectPokemons(root->left, pokemons);
  pokemons.push_back(root->data);
  collectPokemons(root->right, pokemons);
}

// 8ª função - Quantidade de Pokemon num raio de 100 metros
int count_pokemon_in_radius(Node *root, Ponto posicao, int raio) {
  if (root == NULL) {
    return 0;
  }

  int count = 0;
  if (distancia(root->data.posicao, posicao) <= raio) {
    count++;
  }

  return count + count_pokemon_in_radius(root->left, posicao, raio) +
         count_pokemon_in_radius(root->right, posicao, raio);
}

// 9ª função - Inserir Pokemon manualmente
void read_pokemon(Node *&root) {
  Pokemon p;

  cout << "Digite o nome do Pokemon: ";
  cin >> p.nome;

  cout << "Digite o tipo primario do Pokemon (0-NULO, 1-NORMAL, ..., "
          "18-FAIRY): ";
  cin >> p.tipos[0];

  cout << "Digite o tipo secundario do Pokemon (0-NULO, 1-NORMAL, ..., "
          "18-FAIRY): ";
  cin >> p.tipos[1];

  cout << "Digite a posicao x do Pokemon: ";
  cin >> p.posicao.x;

  cout << "Digite a posicao y do Pokemon: ";
  cin >> p.posicao.y;

  root = insert_pokemon_in_tree(root, p);
}

Node *insert_pokemon_in_tree(Node *root, Pokemon p) {
  if (root == NULL) {
    Node *node = new Node();
    node->data = p;
    node->left = node->right = NULL;
    return node;
  }
  if (p.nome < root->data.nome)
    root->left = insert_pokemon_in_tree(root->left, p);
  else if (p.nome > root->data.nome)
    root->right = insert_pokemon_in_tree(root->right, p);
  return root;
}

// 9ª função - Remover Pokemon pelo nome
Node *remove_pokemon_from_tree(Node *root, string nome) {
  if (root == NULL)
    return root;
  if (nome < root->data.nome)
    root->left = remove_pokemon_from_tree(root->left, nome);
  else if (nome > root->data.nome)
    root->right = remove_pokemon_from_tree(root->right, nome);
  else {
    if (root->left == NULL) {
      Node *temp = root->right;
      delete root;
      return temp;
    } else if (root->right == NULL) {
      Node *temp = root->left;
      delete root;
      return temp;
    }
    Node *temp = min_value_node(root->right);
    root->data = temp->data;
    root->right = remove_pokemon_from_tree(root->right, temp->data.nome);
  }
  return root;
}

Node *min_value_node(Node *node) {
  Node *current = node;
  while (current && current->left != NULL)
    current = current->left;
  return current;
}

//////////////////////////////////////////////////////////////////// Funções
/// auxiliares
/////////////////////////////////////////////////////////////////////////

void free_pokemon_tree(Node *root) {
  if (root != NULL) {
    free_pokemon_tree(root->left);
    free_pokemon_tree(root->right);
    delete root;
  }
}

double distancia(Ponto p1, Ponto p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int verificar_cidades(Cidade *towns, int num_towns, Ponto posicao_usuario) {
  for (int i = 0; i < num_towns; i++) {
    if (posicao_usuario.x == towns[i].posicao.x &&
        posicao_usuario.y == towns[i].posicao.y) {
      return towns[i].id;
    }
  }
  return -1; // Cidade não encontrada
}

/*void find_shortest_path(Cidade *towns, int num_towns, Ponto posicao_usuario) {
  int start = verificar_cidades(towns, num_towns, posicao_usuario);
  if (start == -1) {
    cout << "Cidade atual nao encontrada." << endl;
    return;
  }
  list<edge> adj_towns[num_towns];
  for (int i = 0; i < num_towns; i++) {
    for (const edge &a : towns[i].adj_towns) {
      adj_towns[i].push_back(a);
    }
  }

  int end = -1;
  int min_distance = INT_MAX;
  int min_jumps = INT_MAX;

  for (int i = 0; i < num_towns; i++) {
    if (towns[i].isHubPresent) {
      resposta res = shortest_path_dijkstra(adj_towns, num_towns,
posicao_usuario); if (res.distance < min_distance || (res.distance ==
min_distance && res.jumps < min_jumps)) { min_distance = res.distance; min_jumps
= res.jumps; end = i;
      }
    }
  }

  if (end == -1) {
    cout << "Nao foi possivel encontrar um centro Pokemon." << endl;
    return;
  }

  cout << "Melhor rota para chegar ao centro Pokemon mais proximo:" << endl;
  resposta res = shortest_path_dijkstra(adj_towns, num_towns, start, end);
  cout << "Distancia: " << res.distance << endl;
  cout << "Saltos: " << res.jumps << endl;
}*/

void find_shortest_path(Cidade towns[], int num_towns, Ponto posicao_usuario) {
  int start = verificar_cidades(towns, num_towns, posicao_usuario);
  if (start == -1) {
    cout << "Não foi possível encontrar nenhum caminho para as cidades "
            "existentes.\n";
    return;
  }

  bool intree[num_towns];
  int distance[num_towns], parent[num_towns];

  for (int u = 0; u < num_towns; u++) {
    intree[u] = false;
    distance[u] = INT_MAX;
    parent[u] = -1;
  }

  distance[start] = 0;
  int v = start;
  while (intree[v] == false) {
    intree[v] = true;
    list<edge>::iterator p;
    for (p = towns[v].adj_towns.begin(); p != towns[v].adj_towns.end(); p++) {
      int dest = p->dest;
      int weight = p->weight;
      if (distance[dest] > distance[v] + weight) {
        distance[dest] = distance[v] + weight;
        parent[dest] = v;
      }
    }
    v = 0;
    int dist = INT_MAX, poder = 0;
    for (int u = 0; u < num_towns; u++) {
      if (intree[u] == false && distance[u] < dist) {
        dist = distance[u];
        v = u;
      }
    }
  }
  // return distance[v];;
}