#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <vector>

#ifdef __unix__
#define isWindows 0
#elif defined(_WIN32) || defined(WIN32)
#define isWindows 1

#endif

using namespace std;

#define INT_MAX 9999

const int NUM_POKEMON_TYPES = 19;
const string POKEMON_TYPES[] = {
    "-",      // 0
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

struct CityInfo {
  string name;
  int id;
  bool isHubPresent;
  Ponto posicao;
  list<edge> adj_cidades;
};

struct Pokemon {
  string nome;
  int primaryType;
  int secoundaryType;
  Ponto posicao;
};

struct Node {
  Pokemon data;
  Node *left;
  Node *right;
};

void print_menu();
void clear_terminal();
void pause();
void printPokemonTypes();

// ------- TOWN FUNCTIONS

void cadastro_cidades(CityInfo cityArray[], int n_cidades);
void find_shortest_path(CityInfo cityArray[], int num_towns,
                        Ponto userLocation);

// Town aux functions
double distancia(Ponto p1, Ponto p2);

// ------- POKEMON FUNCTIONS

void inputPokemon(Node *&root);
Node *insertPokemonNode(Node *root, Pokemon p);
Node *removePokemonNode(Node *root, string nome);
void destroyPokemonTree(Node *root);
void printPokemonInOrder(Node *root);
void printPokemonByType(Node *root);
void verify_pokemon(Node *root, string nome);
int count_pokemon_by_type(Node *root, int tipo);
int count_pokemon_in_radius(Node *root, Ponto posicao, int raio);

// Pokemon aux functions
void collectPokemons(Node *root, vector<Pokemon> &pokemons);
Node *searchPokemonInTree(Node *root, string nome);
Node *min_value_node(Node *node);

int main() {
  // Estruturas de dados
  const int NUM_TOWNS = 9;
  CityInfo cityArray[NUM_TOWNS];
  Node *pokemons = NULL;
  Ponto userLocation;

  // variaveis de leitura
  string nome;
  int tipo;
  int opc;

  // Cadastrando cidades no sistema e setando a posição do usuário
  cout << "ADMIN: Inserindo dados das cidades:\n";
  cadastro_cidades(cityArray, NUM_TOWNS);
  userLocation.x = cityArray[0].posicao.x;
  userLocation.y = cityArray[0].posicao.y;

  cout << "Ola, Treinador(a) Pokemon! Bem-vindo a sua Pokedex. Informamos "
          "que voce"
          " esta em uma area de 1000 x 1000 m².\n";

  while (true) {
    // Mensagem de boas-vindas ao treinador pokemon.
    cout << "Sua localizacao atual e (X = " << userLocation.x
         << ", Y = " << userLocation.y
         << "). Sua Pokedex possui varias funcionalidades que o auxiliarao em "
            "sua aventura. Boa caçada!\n";

    // Printa o menu para o usuário.
    print_menu();

    // Espera o usuário entrar com uma opção na Pokédex.
    cin >> opc;

    /*
      cout << "1 - Centro Pokemon mais próximo;\n"; // Nao implementada
      cout << "2 - Verificacao Pokemon;\n";
      cout << "3 - Quantidade de Pokemons (por tipo);\n";
      cout << "4 - Mostrar Pokemons;\n";
      cout << "5 - Mostrar Pokemons (por tipos);\n";
      cout << "6 - Pokemons próximos (100 m);\n";
      cout << "7 (EXTRA) - Encontrar perimetro minimoque englobe todos os "
              "pokemons em 100 m;\n"; // Nao implementada
      cout << "8 - Inserir Pokemon;\n";
      cout << "9 - Remover Pokemons;\n";
      cout << "10 - Creditos;\n";
      cout << "11 (EXTRA) - balancear árvore;\n";
    */
    switch (opc) {
    case 1:
      // Melhor rota para chegar ao centro Pokemon mais próximo
      find_shortest_path(cityArray, NUM_TOWNS, userLocation);
      break;
    case 2:
      // Verificação de um Pokemon pelo nome
      cout << "Digite o nome do Pokemon a ser verificado: ";
      cin >> nome;
      verify_pokemon(pokemons, nome);
      break;
    case 3:
      // Contabilizar a quantidade de Pokemon de cada tipo
      printPokemonTypes();
      cout << "Digite o tipo de Pokemon:";
      cin >> tipo;
      cout << "Quantidade de Pokemons do tipo " << POKEMON_TYPES[tipo] << ": "
           << count_pokemon_by_type(pokemons, tipo) << endl;
      break;
    case 4:
      // Imprimir informações dos Pokemon por ordem crescente de nome
      printPokemonInOrder(pokemons);
      break;
    case 5:
      // Imprimir Pokemon por ordem alfabética dos tipos
      printPokemonByType(pokemons);
      break;
    case 6:
      // Quantidade de Pokemon num raio de 100m
      cout << "A quantidade de Pokemon num raio de 100m e: "
           << count_pokemon_in_radius(pokemons, userLocation, 100) << endl;
      break;
    case 7:
      // Inserir Pokemon manualmente
      inputPokemon(pokemons);
      break;
    case 8:
      // Remover Pokemon pelo nome
      cout << "Digite o nome do Pokemon a ser removido: ";
      cin >> nome;
      pokemons = removePokemonNode(pokemons, nome);
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
    pause();
    clear_terminal();
  }

  destroyPokemonTree(pokemons);

  return 0;
}

//////////////////////////////////////////////////////////////////// Funções
/// para uso no código
/////////////////////////////////////////////////////////////////////////

// 1ª função - Cadastra as cityArray no sistema
void cadastro_cidades(CityInfo cityArray[], int n_cidades) {
  int num_adj, id_cidade_destino, distancia_cidade_adj;
  for (int i = 0; i < n_cidades; i++) {
    cout << "Cidade [" << i + 1 << "] \n";
    cout << "  Nome: ";
    getline(cin >> ws, cityArray[i].name);
    cout << "  Codigo: ";
    cin >> cityArray[i].id;
    cout << "  Possui hub? (0,1): ";
    cin >> cityArray[i].isHubPresent;
    cout << "  Posição ('X Y'. Ex: 200 300): ";
    cin >> cityArray[i].posicao.x;
    cin >> cityArray[i].posicao.y;
    cout << "  Número de Cidades adjacentes: ";
    cin >> num_adj;
    for (int j = 0; j < num_adj; j++) {
      cout << "    Codigo da " << j + 1 << "º cidade adjacente: ";
      cin >> id_cidade_destino;
      distancia_cidade_adj =
          distancia(cityArray[i].posicao, cityArray[j].posicao);
      cityArray[i].adj_cidades.push_back(
          {cityArray[i].id, id_cidade_destino, -1});
      cityArray[id_cidade_destino].adj_cidades.push_back(
          {id_cidade_destino, cityArray[i].id, -1});
    }
  }
  clear_terminal();
}
// 2ª função - Imprime o menu de opções para o usuário.

void print_menu() {
  cout << "1 - Centro Pokemon mais próximo;\n"; // Nao implementada
  cout << "2 - Verificacao Pokemon;\n";
  cout << "3 - Quantidade de Pokemons (por tipo);\n";
  cout << "4 - Mostrar Pokemons;\n";
  cout << "5 - Mostrar Pokemons (por tipos);\n";
  cout << "6 - Pokemons próximos (100 m);\n";
  cout << "7 (EXTRA) - Encontrar perimetro minimoque englobe todos os "
          "pokemons em 100 m;\n"; // Nao implementada
  cout << "8 - Inserir Pokemon;\n";
  cout << "9 - Remover Pokemons;\n";
  cout << "10 - Creditos;\n";
  cout << "11 (EXTRA) - balancear árvore;\n"; // proporcionar uma busca
                                              // performatica implementando
                                              // mecanismos de rotacao para
                                              // manter a(s) arvore(s)
                                              // balanceada(s)\n"; // Nao
                                              // implementada
}

void printPokemonTypes() {
  stringstream ss; 
  for (int i = 1; i < NUM_POKEMON_TYPES; i++) {
    ss << i << " - " << POKEMON_TYPES[i] << " ";
  }
  cout << "Tipos de Pokemon:\n";
  cout << "=========================== | | ===========================\n";
  printf("%s\n", ss.str().c_str());
  cout << "=========================== | | ===========================\n";

}

void clear_terminal() { cout << "\x1B[2J\x1B[H"; }
inline void pause() {
  std::string dummy;
  std::cout << "Enter to continue..." << std::endl;
  std::getline(std::cin, dummy);
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

  Node *result = searchPokemonInTree(root, nome);
  if (result != NULL)
    cout << "Pokemon " << nome << " encontrado na posicao ("
         << result->data.posicao.x << ", " << result->data.posicao.y << ")."
         << endl;
  else
    cout << "Pokemon " << nome << " nao encontrado." << endl;
}
Node *searchPokemonInTree(Node *root, string nome) {
  if (root == NULL)
    return NULL;

  if (root->data.nome == nome)
    return root;

  if (nome < root->data.nome)
    return searchPokemonInTree(root->left, nome);
  return searchPokemonInTree(root->right, nome);
}

// 5ª função - Contabilizar a quantidade de Pokemon de cada tipo
int count_pokemon_by_type(Node *root, int tipo) {
  if (root == NULL) {
    return 0;
  }

  int count = 0;
  if (root->data.primaryType == tipo || root->data.secoundaryType == tipo) {
    count = 1;
  }

  return count + count_pokemon_by_type(root->left, tipo) +
         count_pokemon_by_type(root->right, tipo);
}

// 6ª função - Imprimir informações dos Pokemon por ordem crescente de nome
void printPokemonInOrder(Node *root) {
  if (root == NULL) 
    return;
  printPokemonInOrder(root->left);
  printf("Nome: %s, Tipo 1: %s, Tipo 2: %s, Posicao: (%d, %d)\n",
         root->data.nome.c_str(), POKEMON_TYPES[root->data.primaryType].c_str(),
         POKEMON_TYPES[root->data.secoundaryType].c_str(), root->data.posicao.x,
         root->data.posicao.y);
  printPokemonInOrder(root->right);
}

// 7ª função - Im primir Pokemon por ordem alfabética dostipos
void printPokemonByType(Node *root) {
  vector<Pokemon> pokemons;
  collectPokemons(root, pokemons);

  sort(pokemons.begin(), pokemons.end(),
       [](const Pokemon &a, const Pokemon &b) {
         if (POKEMON_TYPES[a.primaryType] != POKEMON_TYPES[b.primaryType]) {
           return POKEMON_TYPES[a.primaryType] < POKEMON_TYPES[b.primaryType];
         }
         return a.nome < b.nome;
       });

  for (const Pokemon &p : pokemons) {
    printf("Nome: %s, Tipo 1: %s, Tipo 2: %s, Posicao: (%d, %d)\n",
         p.nome.c_str(), POKEMON_TYPES[p.primaryType].c_str(),
         POKEMON_TYPES[p.secoundaryType].c_str(), p.posicao.x, p.posicao.y);
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
void inputPokemon(Node *&root) {
  Pokemon p;
  cout << "Nome do Pokemon: ";
  getline(cin >> ws, p.nome);

  printPokemonTypes();

  cout << "Tipo primário: ";
  cin >> p.primaryType;

  cout << "Tipo secundário: ";
  cin >> p.secoundaryType;

  cout << "Posição (X Y)";
  cin >> p.posicao.x >> p.posicao.y;

  root = insertPokemonNode(root, p);
}

Node *insertPokemonNode(Node *root, Pokemon p) {
  if (root == NULL) {
    Node *node = new Node();
    node->data = p;
    node->left = node->right = NULL;
    return node;
  }
  if (p.nome < root->data.nome)
    root->left = insertPokemonNode(root->left, p);
  else if (p.nome > root->data.nome)
    root->right = insertPokemonNode(root->right, p);
  return root;
}

// 9ª função - Remover Pokemon pelo nome
Node *removePokemonNode(Node *root, string nome) {
  if (root == NULL)
    return root;
  if (nome < root->data.nome)
    root->left = removePokemonNode(root->left, nome);
  else if (nome > root->data.nome)
    root->right = removePokemonNode(root->right, nome);
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
    root->right = removePokemonNode(root->right, temp->data.nome);
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

void destroyPokemonTree(Node *root) {
  if (root != NULL) {
    destroyPokemonTree(root->left);
    destroyPokemonTree(root->right);
    delete root;
  }
}

double distancia(Ponto p1, Ponto p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int verificar_cidades(CityInfo *cityArray, int num_towns, Ponto userLocation) {
  for (int i = 0; i < num_towns; i++) {
    if (userLocation.x == cityArray[i].posicao.x &&
        userLocation.y == cityArray[i].posicao.y) {
      return cityArray[i].id;
    }
  }
  return -1; // Cidade não encontrada
}

/*void find_shortest_path(CityInfo *cityArray, int num_towns, Ponto
userLocation) { int start = verificar_cidades(cityArray, num_towns,
userLocation); if (start == -1) { cout << "Cidade atual nao encontrada." <<
endl; return;
  }
  list<edge> adj_cidades[num_towns];
  for (int i = 0; i < num_towns; i++) {
    for (const edge &a : cityArray[i].adj_cidades) {
      adj_cidades[i].push_back(a);
    }
  }

  int end = -1;
  int min_distance = INT_MAX;
  int min_jumps = INT_MAX;

  for (int i = 0; i < num_towns; i++) {
    if (cityArray[i].isHubPresent) {
      resposta res = shortest_path_dijkstra(adj_cidades, num_towns,
userLocation); if (res.distance < min_distance || (res.distance ==
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
  resposta res = shortest_path_dijkstra(adj_cidades, num_towns, start, end);
  cout << "Distancia: " << res.distance << endl;
  cout << "Saltos: " << res.jumps << endl;
}*/

void find_shortest_path(CityInfo cityArray[], int num_towns,
                        Ponto userLocation) {
  int start = verificar_cidades(cityArray, num_towns, userLocation);
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
    for (p = cityArray[v].adj_cidades.begin();
         p != cityArray[v].adj_cidades.end(); p++) {
      int dest = p->dest;
      int weight = p->weight;
      if (distance[dest] > distance[v] + weight) {
        distance[dest] = distance[v] + weight;
        parent[dest] = v;
      }
    }
    v = 0;
    int dist = INT_MAX;
    for (int u = 0; u < num_towns; u++) {
      if (intree[u] == false && distance[u] < dist) {
        dist = distance[u];
        v = u;
      }
    }
  }
  // return distance[end];;
}