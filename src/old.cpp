// Tema escolhido: Tema 01 - Pokedex

// Integrantes: Gustavo Pivoto Ambrósio
//              Yam Sol Britto Bertamini
//              Miguel Vianna Streva
//              Lucca Ribeiro Zogbi
//              João Pedro Nunes Vivas de Resende

#include <iostream>
#include <list>

using namespace std;


/**
 * 	0: NULO,
 *	1: NORMAL,
 *	2: FIGHTING,
 *	3: FLYING,
 *	4: POISON,
 *	5: GROUND,
 *	6: ROCK,
 *	7: BUG,
 *	8: GHOST,
 *	9: STEEL,
 *	10: FIRE,
 *	11: WATER,
 *	12: GRASS,
 *	13: ELECTRIC,
 *	14: PSYCHIC,
 *	15: ICE,
 *	16: DRAGON,
 *	17: DARK,
 *	18: FAIRY
*/
typedef int tipo_pokemon;


struct adj
{
	int origem;
	int destino;
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



void cadastro_cidades(struct Cidade *towns)
{

	/*
	 20 0 84 0  "Mount Silver"
	 17 1 149 179  "Pallet Town"
	 2 1 231 192  "Celadon City"
	 8 0 118 103  "Mount Moon"
	 20 0 107 173  "Cycling Road"
	 7 0 220 227  "Vermilion City"
	 2 1 285 215  "Kanto Power Plant"
	 8 0 75 99  "Safari Zone"
	 18 1 119 57  "Cinnabar Island"
	*/
	// ADJ (10)
		// 1 0
		// 1 3
		// 2 4
		// 2 5
		// 3 5
		// 4 7
		// 5 6
		// 5 7
		// 6 7
		// 7 8

	cout << "Quantas cidades deseja inserir?\n";
	int n;
	for (int i = 0; i < n; i++)
	{
		cout << "Cidade [" << i << "] \n";
		cout << "- Nome: ";
		cin >> towns[0].name;
		cout << "- Codigo: ";
		cin >> towns[0].code;
		cout << "- Possui hub? (0,1): ";
		cin >> towns[0].hub;
		cout << "Posição (Ex: '100 200'): ";
		cin >> towns[0].pos_x;
		cin >> towns[0].pos_y;
	}
	
	// Cadastro nomes cidades

	// // Cadastro cidades adjacentes
	// origem = 0;
	// destino = 1;
	// towns[origem].adj_towns.push_back({origem, destino});
	// towns[destino].adj_towns.push_back({destino, origem});

	// //cidades que tem adj (origem, destino)
	
	
	
	
	
	
	
	
	
	


	// Definindo se existe centro Pokemon na cidade ou não
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	// 

	// Definição das posições das cidades
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	// 
	*/
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