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
  int codigo;
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

// -------  MENU FUNCTIONS
int showMenu();
void clearScreen();
void pauseProgram();
bool handleUserOption(int opc, CityInfo cityArray[9], Ponto &userLocation, Node *&pokemons);
void welcomeMessage();

// -------  USER FUNCTIONS
void changeLocation(CityInfo cityArray[], Ponto &userLocation);

// ------- TOWN FUNCTIONS
void inputCities(CityInfo cityArray[]);
void computeEdgeDistances(CityInfo cityArray[]);
void dijkstraShortestPath(CityInfo cityArray[], Ponto &userLocation);


// Town aux functions
double calculateDistance(Ponto p1, Ponto p2);
int findIndexByID(CityInfo cityArray[], int targetCityId);
int getNearestHubIndex(CityInfo cityArray[], int distance[]);
void printPath(CityInfo cityArray[], int parent[], int nearestHubIndex, int startIndex);


// ------- POKEMON FUNCTIONS

void  inputPokemon(Node *&root, int i);
Node *insertPokemonNode(Node *&root, Pokemon p);
Node *removePokemonNode(Node *root, string nome);
void  destroyPokemonTree(Node *root);
void  printPokemonsInOrder(Node *root);
void  printPokemonsByType(Node *root);
void  isPokemonInTree(Node *root, string nome);
int   countPokemonByType(Node *root, int tipo);
int   countPokemonInRadius(Node *root, Ponto position, int raio);

// Pokemon aux functions
void  collectPokemons(Node *root, vector<Pokemon> &pokemons);
Node *searchPokemonInTree(Node *root, string nome);
Node *getSmallestNode(Node *root);
int   calculateTreeDepth(Node *root);
void printPokemonTypes();

int main() {
  // Estruturas de dados
  CityInfo cityArray[NUM_CITIES]; // Grafo de cidades
  Node *pokemons = NULL; // Pokemons: Árvore binária de busca
  Ponto userLocation;

  // Cadastrando cidades no sistema e setando a posição do usuário
  cout << "ADMIN: Inserindo dados das cidades:\n";
  inputCities(cityArray);
  userLocation.x = cityArray[0].position.x;
  userLocation.y = cityArray[0].position.y;
  clearScreen();

  // Mensagem de boas-vindas ao treinador pokemon.
  welcomeMessage();

  while (true) {
    cout << "Atualmente você se encontra na cidade " << " (X = " << userLocation.x
         << ", Y = " << userLocation.y << ").\n";
    cout << "\n\n";

    int opc = showMenu();
    clearScreen();
    if (!handleUserOption(opc, cityArray, userLocation, pokemons))
      break;
    
    pauseProgram();
    clearScreen();
  }

  destroyPokemonTree(pokemons);

  return 0;
}

void welcomeMessage();

bool handleUserOption(int opc, CityInfo cityArray[9], Ponto &userLocation,
                      Node *&pokemons) {
  // variaveis de leitura
  string nome;
  int tipo;
  int numPokemons;
  
  switch (opc) {
    case -1:
      return false;
    case 1:
      // Melhor rota para chegar ao centro Pokemon mais próximo
      dijkstraShortestPath(cityArray, userLocation);
      break;
    case 2:
      // Verificação de um Pokemon pelo nome
      cout << "Digite o nome do Pokemon a ser verificado: ";
      cin >> nome;
      isPokemonInTree(pokemons, nome);
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
        printPokemonsInOrder(pokemons);
      break;
    case 5:
      // Imprimir Pokemon por ordem alfabética dos tipos
      if (calculateTreeDepth(pokemons) == 0)
        cout << "\n\nNenhum Pokemon cadastrado.\n";
      else
        printPokemonsByType(pokemons);
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
      // Inserir Pokemons manualmente
      cout << "Quantos Pokemons deseja inserir? ";
      cin >> numPokemons;
      for (int i = 0; i < numPokemons; i++) {
        inputPokemon(pokemons, i);
      }
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
      // proporcionar uma busca performatica implementando mecanismos de rotacao
      // para manter a(s) arvore(s) balanceada(s)\n";  Nao implementada
      break;
    case 12:
      changeLocation(cityArray, userLocation); 
    default:
      cout << "Opçao invalida!" << endl;
  }
  return true;
}

//////////////////////////////////////////////////////////////////// Funções
/// para uso no código
/////////////////////////////////////////////////////////////////////////

// 1ª função - Cadastra as cityArray no sistema
void inputCities(CityInfo cityArray[]) {
  int num_adj, codigo_cidade_destino, indexDestino;
  for (int i = 0; i < NUM_CITIES; i++) {
    cityArray[i].arrayIndex = i;
    cout << "Cidade [" << i + 1 << "] \n";
    cout << "  Nome: ";
    getline(cin >> ws, cityArray[i].name);
    cout << "  Codigo: ";
    cin >> cityArray[i].codigo;
    cout << "  Possui hub? (0,1): ";
    cin >> cityArray[i].isHubPresent;
    cout << "  Posição ('X Y'. Ex: 200 300): ";
    cin >> cityArray[i].position.x;
    cin >> cityArray[i].position.y;
    cout << "  Número de Cidades adjacentes: ";
    cin >> num_adj;

    for (int j = 0; j < num_adj; j++) {
      cout << "    Codigo da " << j + 1 << "º cidade adjacente: ";
      cin >> codigo_cidade_destino;

      // Convertendo o código da cidade destino para o índice do vetor
      while (true) {
        indexDestino = findIndexByID(cityArray, codigo_cidade_destino);
        if (indexDestino != -1) break;
        cout << "    Cidade não encontrada. Digite um código válido: ";
        cin >> codigo_cidade_destino;
      }

      cityArray[i].cityEdges.push_back(
          {i, indexDestino, INT_MAX});
      cityArray[indexDestino].cityEdges.push_back(
          {indexDestino, i, INT_MAX});
    }
  }
  computeEdgeDistances(cityArray);
}

// 2ª função - Imprime o menu de opções para o usuário.

int showMenu() {
  cout << "===================== MENU =====================\n";
  cout << "[1] Encontrar o centro Pokemon mais próximo;\n";
  cout << "[2] Buscar Pokemon;\n";
  cout << "[3] Quantidade de Pokemons (por tipo);\n";
  cout << "[4] Mostrar Pokemons;\n";
  cout << "[5] Mostrar Pokemons (por ordem de tipos);\n";
  cout << "[6] Pokemons próximos (100 m);\n";
  cout << "[7] Calcular perímetro que englobe todos os pokemons em 100 m; (EXTRA) \n"; // Nao implementada
  cout << "[8] Inserir Pokemon;\n";
  cout << "[9] Remover Pokemons;\n";
  cout << "[10] Creditos;\n";
  cout << "[11] Balancear árvore; (EXTRA) \n"; // Nao implementada
  cout << "[12] Viajar para uma cidade;\n";
  cout << "[-1] Sair;\n";
  cout << "=========================== | | ================\n";
  cout << "Escolha uma opcao: ";
  int opc;
  cin >> opc;
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

// 4ª função - Verificação de um Pokemon pelo nome
void isPokemonInTree(Node *root, string nome) {

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
int pokemon_pos = 0;
void printPokemonsInOrder(Node *root) {
  if (root == NULL)
    return;
  printPokemonsInOrder(root->left);
  printf("[%d] %s (%s - %s)\n",
         pokemon_pos++, root->data.nome.c_str(), POKEMON_TYPES[root->data.primaryType].c_str(),
         POKEMON_TYPES[root->data.secoundaryType].c_str());
  printPokemonsInOrder(root->right);
}

// 7ª função - Im primir Pokemon por ordem alfabética dostipos
int sortFunction(const Pokemon &a, const Pokemon &b) {
  if (POKEMON_TYPES[a.primaryType] != POKEMON_TYPES[b.primaryType]) {
    return POKEMON_TYPES[a.primaryType] < POKEMON_TYPES[b.primaryType];
  }
  return a.nome < b.nome;
}

void printPokemonsByType(Node *root) {
  vector<Pokemon> pokemons;
  collectPokemons(root, pokemons);

  sort(pokemons.begin(), pokemons.end(), sortFunction);

  cout << "\n\n\n\n";
  cout << "===================== POKEMONS =====================\n";
  int i = 0;
  for (const Pokemon &p : pokemons) {
    printf("[%d] %s (%s - %s)\n",
           i++, p.nome.c_str(), POKEMON_TYPES[p.primaryType].c_str(),
           POKEMON_TYPES[p.secoundaryType].c_str());
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


// TODO(1): Mostrar quais sao os pokemons proximos (e posições)
// 9ª função - Inserir Pokemon manualmente
void inputPokemon(Node *&root, int i) {
  cout << "Inserindo Pokemon [" << i + 1 << "]:\n";
  Pokemon p;
  cout << "  Nome do Pokemon: ";
  getline(cin >> ws, p.nome);

  printPokemonTypes();

  cout << "  Tipo primário: ";
  cin >> p.primaryType;

  cout << "  Tipo secundário: ";
  cin >> p.secoundaryType;

  cout << "  Posição (X Y): ";
  cin >> p.position.x >> p.position.y;

  root = insertPokemonNode(root, p);
}

Node *insertPokemonNode(Node *&root, Pokemon p) {
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

void welcomeMessage()
{
  cout << "\n\n\n\n\n\n\n";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "Olá, Treinador(a) Pokemon! Bem-vindo a sua Pokedex. Informamos que "
          "voce está em uma área de 1000 x 1000 m². Sua Pokedex possui varias "
          "funcionalidades que o auxiliarão em sua aventura. Boa caçada!\n";
  cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
  cout << "\n\n";
}

int   calculateTreeDepth(Node *root) {
  if (root == NULL)
    return 0;
  return 1 + max(calculateTreeDepth(root->left), calculateTreeDepth(root->right));
}

int findIndexByID(CityInfo cityArray[], int targetCityId) {
  for (int i = 0; i < NUM_CITIES; i++)
  {
    if (cityArray[i].codigo == targetCityId)
      return i;
  }
  return -1;
}

void computeEdgeDistances(CityInfo cityArray[]) {
  // calculate and store distances of cities
  for (int i = 0; i < NUM_CITIES; i++) {
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

int verificar_cidades(CityInfo *cityArray, Ponto userLocation) {
  for (int i = 0; i < NUM_CITIES; i++) {
    if (userLocation.x == cityArray[i].position.x &&
        userLocation.y == cityArray[i].position.y) {
      return cityArray[i].arrayIndex;
    }
  }
  return -1; // Cidade não encontrada
}

void dijkstraShortestPath(CityInfo cityArray[],
                        Ponto &userLocation) {
  int start = verificar_cidades(cityArray, userLocation);
  if (start == -1) {
    cout << "Não foi possível encontrar nenhum caminho para as cidades "
            "existentes.\n";
    return;
  }

  bool intree[NUM_CITIES];
  int distance[NUM_CITIES], parent[NUM_CITIES];

  for (int u = 0; u < NUM_CITIES; u++) {
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
    for (int u = 0; u < NUM_CITIES; u++) {
      if (intree[u] == false && distance[u] < dist) {
        dist = distance[u];
        v = u;
      }
    }
  }

  // find nearest hub
  int nearestHubIndex = getNearestHubIndex(cityArray, distance);
  if (nearestHubIndex == -1) {
    cout << "Nao foi possivel encontrar um centro Pokemon.\n";
    return;
  }

    int nearestHubDistance = distance[nearestHubIndex];
    if (nearestHubDistance == 0){
        cout << "Você já está em um centro Pokemon.\n";
        return;
    }
    
    cout << "Cidade mais próxima com centro:" 
    << cityArray[nearestHubIndex].name << endl;
    cout << "Distancia: " << nearestHubDistance << endl;
    cout << "Rota: ";
    printPath(cityArray, parent, nearestHubIndex, start);

    int opc;
    cout << "Dejesa ir para o centro Pokemon mais próximo? (0,1): ";
    cin >> opc;
    if (opc == 1){
        userLocation.x = cityArray[nearestHubIndex].position.x;
        userLocation.y = cityArray[nearestHubIndex].position.y;
        cout << "Você chegou ao centro Pokemon mais próximo.\n";
    } else {
        cout << "Você optou por não ir ao centro Pokemon mais próximo.\n";
    }
    
}
          
  // find smallest value in distance array to a city with hub
int getNearestHubIndex(CityInfo cityArray[], int distance[]) {
  int smallest = INT_MAX;
  int smallestPos = -1;
  for (int j = 0; j < NUM_CITIES; j++)
  {
    if ((distance[j] < smallest) && (cityArray[j].isHubPresent)) {
      smallest = distance[j];
      smallestPos = j;
    }
  }
  return smallestPos;
}


void printPath(CityInfo cityArray[], int parent[], int nearestHubIndex, int startIndex) {

  list<int> lista;

  // Create a list all cities in the path
  int index = nearestHubIndex;
  while (index != startIndex) {
    index = parent[index];
    lista.push_front(index);
  } 

  list<int>::iterator p;
  for(p = lista.begin(); p != lista.end(); p--) {
    cout << cityArray[*p].name << " -> ";
  }
  cout << cityArray[nearestHubIndex].name << endl;
}

void changeLocation(CityInfo cityArray[], Ponto &userLocation){
  int opc;

  cout << "Escolha a cidade para onde deseja viajar:\n";
  for (int i = 0; i < NUM_CITIES; i++){
    cout << i << " - " << cityArray[i].name << "(" << cityArray[i].codigo << ")" << endl;
  }

  cout << "Digite o código da cidade: ";
  cin >> opc;
  int index = findIndexByID(cityArray, opc);
  userLocation.x = cityArray[index].position.x;
  userLocation.y = cityArray[index].position.y;
  cout << "Você chegou a cidade " << cityArray[index].name << endl;
}