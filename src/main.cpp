#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// #ifdef __unix__
// #define isWindows 0
// #elif defined(_WIN32) || defined(WIN32)
// #define isWindows 1
// #endif


#define INT_MAX 9999
#define NUM_POKEMON_TYPES 19
#define NUM_CITIES 9

const string POKEMON_TYPES[] = {
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

struct CityInfo {
  int arrayIndex;
  string name;
  int id;
  bool isHubPresent;
  Ponto position;
  list<edge> cityEdges;
};

struct Pokemon {
  string nome;
  int primaryType;
  int secoundaryType;
  Ponto position;
};

struct Node {
  Pokemon data;
  Node *left;
  Node *right;
};

int showMenu();
void clearScreen();
void pauseProgram();
void printPokemonTypes();
void handleUserOption(int opc, CityInfo cityArray[9], Ponto &userLocation, Node *&pokemons);

// ------- TOWN FUNCTIONS

void registerCities(CityInfo cityArray[], int n_cidades);
void computeEdgeDistances(CityInfo cityArray[], int n_cidades);
void findShortestRoute(CityInfo cityArray[], int num_towns, Ponto userLocation);

// Town aux functions
double calculateDistance(Ponto p1, Ponto p2);
int    findIndexByID(CityInfo cityArray[], int targetCityId);

// ------- POKEMON FUNCTIONS

void  inputPokemon(Node *&root);
Node *insertPokemonNode(Node *root, Pokemon p);
Node *removePokemonNode(Node *root, string nome);
void  destroyPokemonTree(Node *root);
void  printPokemonInOrder(Node *root);
void  printPokemonByType(Node *root);
void  verifyPokemon(Node *root, string nome);
int   countPokemonByType(Node *root, int tipo);
int   countPokemonInRadius(Node *root, Ponto position, int raio);

// Pokemon aux functions
void  collectPokemons(Node *root, vector<Pokemon> &pokemons);
Node *searchPokemonInTree(Node *root, string nome);
Node *getSmallestNode(Node *root);
int   calculateTreeDepth(Node *root);

int main() {
  // Estruturas de dados
  CityInfo cityArray[NUM_CITIES]; // Grafo de cidades
  Node *pokemons = NULL; // Pokemons: Árvore binária de busca
  Ponto userLocation;

  // Cadastrando cidades no sistema e setando a posição do usuário
  cout << "ADMIN: Inserindo dados das cidades:\n";
  registerCities(cityArray, NUM_CITIES);
  userLocation.x = cityArray[0].position.x;
  userLocation.y = cityArray[0].position.y;
  clearScreen();

  // Mensagem de boas-vindas ao treinador pokemon.
  cout << "\n\n\n\n\n\n\n";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "Olá, Treinador(a) Pokemon! Bem-vindo a sua Pokedex. Informamos que "
          "voce está em uma área de 1000 x 1000 m². Sua Pokedex possui varias "
          "funcionalidades que o auxiliarão em sua aventura. Boa caçada!\n";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "\n\n";

  while (true) {
    cout << "Sua localização atual é (X = " << userLocation.x
         << ", Y = " << userLocation.y << ").\n";
    cout << "\n\n";

    int opc = showMenu();
    clearScreen();
    handleUserOption(opc, cityArray, userLocation, pokemons);

    pauseProgram();
    clearScreen();
  }

  destroyPokemonTree(pokemons);

  return 0;
}

void handleUserOption(int opc, CityInfo cityArray[9], Ponto &userLocation, Node *&pokemons) {
  // variaveis de leitura
  string nome;
  int tipo;

  switch (opc) {
  case 1:
    // Melhor rota para chegar ao centro Pokemon mais próximo
    findShortestRoute(cityArray, NUM_CITIES, userLocation);
    break;
  case 2:
    // Verificação de um Pokemon pelo nome
    cout << "Digite o nome do Pokemon a ser verificado: ";
    cin >> nome;
    verifyPokemon(pokemons, nome);
    break;
  case 3:
    // Contabilizar a quantidade de Pokemon de cada tipo
    printPokemonTypes();
    cout << "Digite o tipo de Pokemon:";
    cin >> tipo;
    cout << "\n\nQuantidade de Pokemons do tipo " << POKEMON_TYPES[tipo] << ": "
         << countPokemonByType(pokemons, tipo) << endl;
    break;
  case 4:
    // Imprimir informações dos Pokemon por ordem crescente de nome
    if (calculateTreeDepth(pokemons) == 0)
      cout << "\n\nNenhum Pokemon cadastrado.\n";
    else
      printPokemonInOrder(pokemons);
    break;
  case 5:
    // Imprimir Pokemon por ordem alfabética dos tipos
    if (calculateTreeDepth(pokemons) == 0)
      cout << "\n\nNenhum Pokemon cadastrado.\n";
    else
      printPokemonByType(pokemons);
    break;
  case 6:
    // Quantidade de Pokemon num raio de 100m
    cout << "A quantidade de Pokemon num raio de 100m é: "
         << countPokemonInRadius(pokemons, userLocation, 100) << endl;
    break;
  case 7:
    cout << "7 (EXTRA) - Calcular perímetro mínimo - Nao implementada\n";
    break;
  case 8:
    // Inserir Pokemon manualmente
    inputPokemon(pokemons);
    break;
  case 9:
    // Remover Pokemon pelo nome
    cout << "Digite o nome do Pokemon a ser removido: ";
    cin >> nome;
    pokemons = removePokemonNode(pokemons, nome);
    break;
  case 10:
    // Créditos do trabalho
    cout << "Integrantes:\n  Gustavo Pivoto Ambrosio,\n  Yam Sol Britto "
            "Bertamini,\n"
            "  Miguel Vianna Streva,\n  Lucca Ribeiro Zogbi,\n  Joao Pedro "
            "Nunes Vivas de Resende\n";
    break;
  case 11:
    cout << "11 (EXTRA) - Balancear árvore - Nao implementada\n";
    break;
  default:
    cout << "Opçao invalida!" << endl;
  }
}

//////////////////////////////////////////////////////////////////// Funções
/// para uso no código
/////////////////////////////////////////////////////////////////////////

// 1ª função - Cadastra as cityArray no sistema
void registerCities(CityInfo cityArray[], int n_cidades) {
  int num_adj, id_cidade_destino, index;
  for (int i = 0; i < n_cidades; i++) {
    cityArray[i].arrayIndex = i;
    cout << "Cidade [" << i + 1 << "] \n";
    cout << "  Nome: ";
    getline(cin >> ws, cityArray[i].name);
    cout << "  Codigo: ";
    cin >> cityArray[i].id;
    cout << "  Possui hub? (0,1): ";
    cin >> cityArray[i].isHubPresent;
    cout << "  Posição ('X Y'. Ex: 200 300): ";
    cin >> cityArray[i].position.x;
    cin >> cityArray[i].position.y;
    cout << "  Número de Cidades adjacentes: ";
    cin >> num_adj;

    for (int j = 0; j < num_adj; j++) {
      cout << "    Codigo da " << j + 1 << "º cidade adjacente: ";
      cin >> id_cidade_destino;

      // Verifica se o código da cidade destino é válido
      while ((index = findIndexByID(cityArray, id_cidade_destino)) == -1) {
        cout << "    Cidade não encontrada. Digite um código válido: ";
        cin >> id_cidade_destino;
      }

      cityArray[i].cityEdges.push_back(
          {cityArray[i].id, id_cidade_destino, INT_MAX});
      cityArray[index].cityEdges.push_back(
          {id_cidade_destino, cityArray[i].id, INT_MAX});
    }
  }
  computeEdgeDistances(cityArray, n_cidades);
}

// 2ª função - Imprime o menu de opções para o usuário.

int showMenu() {
  int opc;
  cout << "===================== MENU =====================\n";
  cout << "1 - Ir para centro Pokemon mais próximo;\n"; // Nao implementada
  cout << "2 - Verificacao Pokemon;\n";
  cout << "3 - Quantidade de Pokemons (por tipo);\n";
  cout << "4 - Mostrar Pokemons;\n";
  cout << "5 - Mostrar Pokemons (por tipos);\n";
  cout << "6 - Pokemons próximos (100 m);\n";
  cout << "7 (EXTRA) - Calcular perímetro mínimo que englobe todos os "
          "pokemons em 100 m;\n"; // Nao implementada
  cout << "8 - Inserir Pokemon;\n";
  cout << "9 - Remover Pokemons;\n";
  cout << "10 - Creditos;\n";
  cout << "11 (EXTRA) - Balancear árvore;\n"; // proporcionar uma busca
                                              // performatica implementando
                                              // mecanismos de rotacao para
                                              // manter a(s) arvore(s)
                                              // balanceada(s)\n"; // Nao
                                              // implementada
  cout << "Escolha uma opcao: ";
  cin >> opc;
  cout << "=========================== | | ===========================\n";
  return opc;
}

void printPokemonTypes() {
  cout << "===================== Tipos de Pokemon =====================\n";
  for (int i = 0; i < NUM_POKEMON_TYPES;) {
    for (int j = 0; j < 5; j++) {
      if (i < NUM_POKEMON_TYPES) {
        if (i < 10)
          cout << '0';
        cout << i << ": " << POKEMON_TYPES[i++] << " ";
      }
    }
    cout << endl;
  }
  cout << "=========================== | | ===========================\n";
}

void clearScreen() { cout << "\x1B[2J\x1B[H"; }
inline void pauseProgram() {
  cout << "\n\n-----------------------------\n";
  cout << "  Press Enter to continue...\n";
  cout << "-----------------------------\n";
  cin.ignore();
  cin.get();
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
void verifyPokemon(Node *root, string nome) {

  Node *result = searchPokemonInTree(root, nome);
  if (result != NULL)
    cout << "\nPokemon " << nome << " encontrado na posicao ("
         << result->data.position.x << ", " << result->data.position.y << ")."
         << endl;
  else
    cout << "\nPokemon " << nome << " nao encontrado." << endl;
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
int countPokemonByType(Node *root, int tipo) {
  if (root == NULL) {
    return 0;
  }

  int count = 0;
  if (root->data.primaryType == tipo || root->data.secoundaryType == tipo) {
    count = 1;
  }

  return count + countPokemonByType(root->left, tipo) +
         countPokemonByType(root->right, tipo);
}

// 6ª função - Imprimir informações dos Pokemon por ordem crescente de nome
void printPokemonInOrder(Node *root) {
  if (root == NULL)
    return;
  printPokemonInOrder(root->left);
  printf("Nome: %s, Tipo 1: %s, Tipo 2: %s, Posicao: (%d, %d)\n",
         root->data.nome.c_str(), POKEMON_TYPES[root->data.primaryType].c_str(),
         POKEMON_TYPES[root->data.secoundaryType].c_str(),
         root->data.position.x, root->data.position.y);
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
           POKEMON_TYPES[p.secoundaryType].c_str(), p.position.x, p.position.y);
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
int countPokemonInRadius(Node *root, Ponto position, int raio) {
  if (root == NULL) {
    return 0;
  }

  int count = 0;
  if (calculateDistance(root->data.position, position) <= raio) {
    count++;
  }

  return count + countPokemonInRadius(root->left, position, raio) +
         countPokemonInRadius(root->right, position, raio);
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

  cout << "Posição (X Y): ";
  cin >> p.position.x >> p.position.y;

  root = insertPokemonNode(root, p);
}

Node *insertPokemonNode(Node *root, Pokemon p) {
  if (root == NULL) {
    Node *root = new Node();
    root->data = p;
    root->left = root->right = NULL;
    return root;
  }
  if (p.nome < root->data.nome)
    root->left = insertPokemonNode(root->left, p);
  else if (p.nome > root->data.nome)
    root->right = insertPokemonNode(root->right, p);
  return root;
}

// 10ª função - Remover Pokemon pelo nome
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
    Node *temp = getSmallestNode(root->right);
    root->data = temp->data;
    root->right = removePokemonNode(root->right, temp->data.nome);
  }
  return root;
}

Node *getSmallestNode(Node *root) {
  Node *current = root;
  while (current && current->left != NULL)
    current = current->left;
  return current;
}

//////////////////////////////////////////////////////////////////// Funções
/// auxiliares
/////////////////////////////////////////////////////////////////////////

int   calculateTreeDepth(Node *root) {
  if (root == NULL)
    return 0;
  return 1 + max(calculateTreeDepth(root->left), calculateTreeDepth(root->right));
}

int findIndexByID(CityInfo cityArray[], int targetCityId) {
  for (int i = 0; i < NUM_CITIES; i++)
  {
    if (cityArray[i].id == targetCityId)
      return i;
  }
  return -1;
}

void computeEdgeDistances(CityInfo cityArray[], int n_cidades) {
  // calculate and store distances of cities
  for (int i = 0; i < n_cidades; i++) {
    for (edge &e : cityArray[i].cityEdges) {
      e.weight = calculateDistance(cityArray[i].position, cityArray[e.dest].position);
    }
  }
}

void destroyPokemonTree(Node *root) {
  if (root != NULL) {
    destroyPokemonTree(root->left);
    destroyPokemonTree(root->right);
    delete root;
  }
}

double calculateDistance(Ponto p1, Ponto p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

int verificar_cidades(CityInfo *cityArray, int num_towns, Ponto userLocation) {
  for (int i = 0; i < num_towns; i++) {
    if (userLocation.x == cityArray[i].position.x &&
        userLocation.y == cityArray[i].position.y) {
      return cityArray[i].id;
    }
  }
  return -1; // Cidade não encontrada
}

/*void findShortestRoute(CityInfo *cityArray, int num_towns, Ponto
userLocation) { int start = verificar_cidades(cityArray, num_towns,
userLocation); if (start == -1) { cout << "Cidade atual nao encontrada." <<
endl; return;
  }
  list<edge> cityEdges[num_towns];
  for (int i = 0; i < num_towns; i++) {
    for (const edge &a : cityArray[i].cityEdges) {
      cityEdges[i].push_back(a);
    }
  }

  int end = -1;
  int min_distance = INT_MAX;
  int min_jumps = INT_MAX;

  for (int i = 0; i < num_towns; i++) {
    if (cityArray[i].isHubPresent) {
      resposta res = shortest_path_dijkstra(cityEdges, num_towns,
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
  resposta res = shortest_path_dijkstra(cityEdges, num_towns, start, end);
  cout << "Distancia: " << res.distance << endl;
  cout << "Saltos: " << res.jumps << endl;
}*/

void findShortestRoute(CityInfo cityArray[], int num_towns,
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
    for (p = cityArray[v].cityEdges.begin(); p != cityArray[v].cityEdges.end();
         p++) {
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