// Tema escolhido: Tema 01 - Pokedex

// Integrantes: Gustavo Pivoto Ambrósio
//              Yam Sol Britto Bertamini
//              Miguel Vianna Streva
//              Lucca Ribeiro Zogbi
//              João Pedro Nunes Vivas de Resende

#include <iostream>
#include <list>

using namespace std;

enum tipo_pokemon
{
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

struct adj
{
	int origem;
	int destino;
	int peso;
};

struct Cidade
{
	int code;
	string name;
	bool hub;
	list<adj> adj_towns; 
	int pos_x;
	int pos_y;
};

struct Pokemon
{
	string nome;
	tipo_pokemon tipo[2];
	// int codigo;
	int pos_x;
	int pos_y;
};

int const N_CIDADES = 9;
int const N_POKEMONS = 50;

void cadastro_cidades(struct Cidade *towns);
void cadastro_pokemons(Pokemon *pokemons);
void print_menu();

int main()
{
	int MAPA[300][300];
	Cidade towns[9];
	Pokemon pokemons[50];
	int opc;

	// Cadastrar informações
	cadastro_cidades(towns);
	cadastro_pokemons(pokemons);

	// Menu
	print_menu();
	cin >> opc;

	return 0;
}

void cadastro_pokemons(Pokemon pokemons[])
{
	pokemons[0]  = {"Bulbasaur", {GRASS, POISON}, 166, 42};
	pokemons[1]  = {"Ivysaur", {GRASS, POISON},  248, 89};
	pokemons[2]  = {"Venusaur", {GRASS, POISON},  25, 286};
	pokemons[3]  = {"Charmander", {FIRE, NULO},  280, 299};
	pokemons[4]  = {"Charmeleon", {FIRE, NULO},  87, 299};
	pokemons[5]  = {"Charizard", {FIRE, FLYING},  276, 49};
	pokemons[6]  = {"Squirtle", {WATER, NULO},  219, 190};
	pokemons[7]  = {"Wartortle", {WATER, NULO},  47, 109};
	pokemons[8]  = {"Blastoise", {WATER, NULO},  168, 35};
	pokemons[9]  = {"Caterpie", {BUG, NULO},  100, 21};
	pokemons[10] = {"Metapod", {BUG, NULO},  170, 163};
	pokemons[11] = {"Butterfree", {BUG, FLYING},  45, 280};
	pokemons[12] = {"Weedle", {BUG, POISON},  204, 112};
	pokemons[13] = {"Kakuna", {BUG, POISON},  178, 28};
	pokemons[14] = {"Beedrill", {BUG, POISON},  41, 123};
	pokemons[15] = {"Pidgey", {NORMAL, FLYING},  153, 190};
	pokemons[16] = {"Pidgeotto", {NORMAL, FLYING},  71, 255};
	pokemons[17] = {"Pidgeot", {NORMAL, FLYING},  177, 229};
	pokemons[18] = {"Rattata", {NORMAL, NULO},  78, 293};
	pokemons[19] = {"Raticate", {NORMAL, NULO},  236, 45};
	pokemons[20] = {"Spearow", {NORMAL, FLYING},  27, 264};
	pokemons[21] = {"Fearow", {NORMAL, FLYING},  88, 171};
	pokemons[22] = {"Ekans", {POISON, NULO},  186, 119};
	pokemons[23] = {"Arbok", {POISON, NULO},  75, 60};
	pokemons[24] = {"Pikachu", {ELECTRIC, NULO},  248, 222};
	pokemons[25] = {"Raichu", {ELECTRIC, NULO},  276, 262};
	pokemons[26] = {"Sandshrew", {GROUND, NULO},  73, 57};
	pokemons[27] = {"Sandslash", {GROUND, NULO},  176, 198};
	pokemons[28] = {"Nidoran", {POISON, NULO},  267, 83};
	pokemons[29] = {"Nidorina", {POISON, NULO},  164, 98};
	pokemons[30] = {"Nidoqueen", {POISON, GROUND},  68, 94};
	pokemons[31] = {"Nidoran", {POISON, NULO},  65, 30};
	pokemons[32] = {"Nidorino", {POISON, NULO},  251, 235};
	pokemons[33] = {"Nidoking", {POISON, GROUND},  144, 187};
	pokemons[34] = {"Clefairy", {FAIRY, NULO},  175, 274};
	pokemons[35] = {"Clefable", {FAIRY, NULO},  43, 116};
	pokemons[36] = {"Vulpix", {FIRE, NULO},  48, 120};
	pokemons[37] = {"Ninetales", {FIRE, NULO},  140, 2};
	pokemons[38] = {"Jigglypuff", {NORMAL, FAIRY},  38, 292};
	pokemons[39] = {"Wigglytuff", {NORMAL, FAIRY},  22, 298};
	pokemons[40] = {"Zubat", {POISON, FLYING},  275, 86};
	pokemons[41] = {"Golbat", {POISON, FLYING},  132, 237};
	pokemons[42] = {"Oddish", {GRASS, POISON},  280, 251};
	pokemons[43] = {"Gloom", {GRASS, POISON},  67, 40};
	pokemons[44] = {"Vileplume", {GRASS, POISON},  112, 151};
	pokemons[45] = {"Paras", {BUG, GRASS},  93, 68};
	pokemons[46] = {"Parasect", {BUG, GRASS},  63, 13};
	pokemons[47] = {"Venonat", {BUG, POISON},  38, 297};
	pokemons[48] = {"Venomoth", {BUG, POISON},  132, 178};
	pokemons[49] = {"Diglett", {GROUND, NULO},  219, 164};
}

void cadastro_cidades(struct Cidade *towns)
{
	// Cadastro códigos
	for (int i = 0; i < N_CIDADES; i++)
		towns[i].code = i;

	// Cadastro nomes cidades
	towns[0].name = "Mount Silver";
	towns[1].name = "Pallet Town";
	towns[2].name = "Celadon City";
	towns[3].name = "Mount Moon";
	towns[4].name = "Cycling Road";
	towns[5].name = "Vermilion City";
	towns[6].name = "Kanto Power Plant";
	towns[7].name = "Safari Zone";
	towns[8].name = "Cinnabar Island";

	// Cadastro cidades adjacentes

	towns[0].adj_towns.push_back({1, 0, 87});
	towns[1].adj_towns.push_back({1, 0, 87});
	towns[1].adj_towns.push_back({1, 3, 45});
	towns[2].adj_towns.push_back({2, 4, 136});
	towns[2].adj_towns.push_back({2, 5, 34});
	towns[3].adj_towns.push_back({3, 1, 45});
	towns[3].adj_towns.push_back({3, 5, 96});
	towns[4].adj_towns.push_back({4, 2, 136});
	towns[4].adj_towns.push_back({4, 7, 104});
	towns[5].adj_towns.push_back({5, 2, 34});
	towns[5].adj_towns.push_back({5, 3, 96});
	towns[5].adj_towns.push_back({5, 6, 64});
	towns[5].adj_towns.push_back({5, 7, 142});
	towns[6].adj_towns.push_back({6, 5, 64});
	towns[6].adj_towns.push_back({6, 7, 59});
	towns[7].adj_towns.push_back({7, 4, 104});
	towns[7].adj_towns.push_back({7, 5, 142});
	towns[7].adj_towns.push_back({7, 6, 59});
	towns[7].adj_towns.push_back({7, 8, 121});
	towns[8].adj_towns.push_back({8, 7, 121});

	// Definindo se existe centro Pokemon na cidade ou não
	towns[0].hub = 0;
	towns[1].hub = 1;
	towns[2].hub = 1;
	towns[3].hub = 0;
	towns[4].hub = 0;
	towns[5].hub = 0;
	towns[6].hub = 1;
	towns[7].hub = 0;
	towns[8].hub = 1;

	// Definição das posições das cidades
	towns[0].pos_x = 84;
	towns[0].pos_y = 0;
	towns[1].pos_x = 149;
	towns[1].pos_y = 179;
	towns[2].pos_x = 231;
	towns[2].pos_y = 192;
	towns[3].pos_x = 118;
	towns[3].pos_y = 103;
	towns[4].pos_x = 107;
	towns[4].pos_y = 173;
	towns[5].pos_x = 220;
	towns[5].pos_y = 227;
	towns[6].pos_x = 285;
	towns[6].pos_y = 215;
	towns[7].pos_x = 75;
	towns[7].pos_y = 99;
	towns[8].pos_x = 119;
	towns[8].pos_y = 57;

	return;
}

void print_menu()
{
	cout << "######################################################################################################################################" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm------mmmmmm      mmmmmm      mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmmmmmm    mmmmmmmmmmmmmmmm--------mmmm        mmmm        mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmm   ::::::  mmmmmmmmmmmmm--------mmmm        mmmm        mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmm   ::::::::::   mmmmmmmmmmm------mmmmmm      mmmmmm      mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmm  ::::::::::::::  mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmm  ::::::::::::::  mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmm  ::::::::::::::  mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmm  ::::::::::::  mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##############################################" << endl;
	cout << "mmmmmm    ::::::::    mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmm   ::::::   mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmmmmmm    mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm####mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmm                                                                                                                      		   " << endl;
	cout << "		                Bem-vindo a sua Pokedex, (Nome do usuario da pokedex)! O que gostaria de fazer ou saber?              		   " << endl;
	cout << "mmmmmmmm                                                                                                                              " << endl;
	cout << "mmmmmmmm   1. Melhor rota para chegar ao centro Pokemon mais proximo;                                                                 " << endl;
	cout << "mmmmmmmm                                                                                                                              " << endl;
	cout << "mmmmmmmm   2. Verificacao de um Pokemon pelo nome;                                                                                    " << endl;
	cout << "mmmmmmmm                                                                                                                              " << endl;
	cout << "mmmmmmmm   3. Contabilizar a quantidade de Pokemon de cada tipo;                                                                     " << endl;
	cout << "mmmmmmmm                                                                                                                              " << endl;
	cout << "mmmmmmmm   4. Imprimir informacoes dos Pokemon por ordem crescente de nome;                                                          " << endl;
	cout << "mmmmmmmm                                                                                                                              " << endl;
	cout << "mmmmmmmm   5. Imprimir Pokemon por ordem alfabettica dos tipos;                                                                       " << endl;
	cout << "mmmmmmmm                                                                                                                              " << endl;
	cout << "mmmmmmmm   6. Quantidade de Pokemon num raio de 100m;                                                                                " << endl;
	cout << "mmmmmmmm                                                                                                                              " << endl;
	cout << "mmmmmmmm                                                                                                                              " << endl;
	cout << "mmmmmmmm                                                                                                                              " << endl;
	cout << "mmmmmmmm                                               7. Creditos do trabalho                                                        " << endl;
	cout << "mmmmmmmm                                                                                                                              " << endl;
	cout << "mmmmmmmm     mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm     mmmmmm##" << endl;
	cout << "mmmmmmmm     \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\     mmmmmm##" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmm##########mmmmmmmmmmmm##############################################mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm.##.mmmmmmmmm##" << endl;
	cout << "mmmmmmmmmm######mmmmmmmmmmmmmm##############################################mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm.....##.....mmmmm##" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##############################################mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm.##########.mmmmm##" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##############################################mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm.....##.....mmmmm##" << endl;
	cout << "mmmmmmmmmm######mmmmmmmmmmmmmm##############################################mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm.##.mmmmmmmmm##" << endl;
	cout << "mmmmmmmm##########mmmmmmmmmmmm##############################################mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm....mmmmmmmmm##" << endl;
	cout << "mmmmmmmm##########mmmmmmmmmmmm##############################################mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmmmm######mmmmmmmmmmmmmm##############################################mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##############################################mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm##" << endl;
	cout << "######################################################################################################################################" << endl;
}