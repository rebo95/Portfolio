//Grupo VJ01, Aaron Reboredo Vázquez
//Grupo VJ01, Pablo Martín García

//n_reinas nos permite situar un número n de reinas en un tablero de n x n de tal manera que puedan
//coexistir, sin comerse en una supuesta siguiente jugada de ajedrez.
//utilizando vuelta atrás exploramos las casillas desde la ultima columna hacia la izda
// y desde la última fila de cada coluna haca arriba , viendo en cada caso si podemos situarlas en la posición
//analizada. En el caso de usar la mejora "marcado y desmarcado", por cada reina colocada se "marcan"
// en vectores de diagonales y filas, las posiciones en las que la reina situada actualmente comería 
//a una futura reina, de tal manera que, a la hora de colocar la siguiente, esas sean ya, posiciones prohibidas.


#include <vector>
#include <iostream>

using namespace std;

//Declaración de funciones
void n_reinas(vector<int>& sol, int k, vector<bool>& filas, vector<bool>& d_asc, vector<bool>& d_desc);
bool es_solucion(vector<int>& sol, int k, vector<bool>& filas, vector<bool>& d_asc, vector<bool>& d_desc);
bool es_completable(vector<int>& sol, int k, vector<bool>& filas, vector<bool>& d_asc, vector<bool>& d_desc);
bool no_ataca(vector<int>& sol, int k, vector<bool>& filas, vector<bool>& d_asc, vector<bool>& d_desc);
int diag_desc(int x, int y, int tam); int diag_asc(int x, int y); void procesar_solucion(vector<int>& sol, int k);

int numSols;	//Variable para contabilizar el nº de soluciones

int main()
{
	int numCasos, tam;
	cin >> numCasos;
	for (int i = 0; i < numCasos; i++)
	{
		cin >> tam;
		vector<int> prueba(tam);
		vector<bool> filas(tam);
		vector<bool> d_asc((tam * 2) - 1);
		vector<bool> d_desc((tam * 2) - 1);

		numSols = 0;
		n_reinas(prueba, 0, filas, d_asc, d_desc);
		cout << numSols << endl;
	}

	return 0;
}

//El coste de la función n_reinas es cuadrático O(n^2)
void n_reinas(vector<int>& sol, int k, vector<bool>& filas, vector<bool>& d_asc, vector<bool>& d_desc)
{
	for (int c = 0; c < sol.size(); c++)
	{
		sol[k] = c;

		if (es_solucion(sol, k, filas, d_asc, d_desc))
			procesar_solucion(sol, k);
		else if (es_completable(sol, k, filas, d_asc, d_desc))
		{
			filas[sol[k]] = true;
			d_asc[diag_asc(k, c)] = true;
			d_desc[diag_desc(k, c, sol.size())] = true;

			n_reinas(sol, k + 1, filas, d_asc, d_desc);

			filas[sol[k]] = false;
			d_asc[diag_asc(k, c)] = false;
			d_desc[diag_desc(k, c, sol.size())] = false;
		}
	}
}

void procesar_solucion(vector<int>& sol, int k)
{
	numSols++;
}

int diag_desc(int x, int y, int tam)
{
	int num = x - y;

	if (num < 0)
		num = -num + (tam - 1);

	return num;
}

int diag_asc(int x, int y)
{
	return x + y;
}

//El coste de esta función es constante O(1)
bool no_ataca(vector<int>& sol, int k, vector<bool>& filas, vector<bool>& d_asc, vector<bool>& d_desc)
{
	bool b = false;

	if (!filas[sol[k]] && !d_asc[diag_asc(k, sol[k])] && !d_desc[diag_desc(k, sol[k], sol.size())])
		b = true;

	return b;
}

//El coste de esta función es constante O(1)
bool es_completable(vector<int>& sol, int k, vector<bool>& filas, vector<bool>& d_asc, vector<bool>& d_desc)
{
	bool b = false;

	if (k < sol.size() - 1 && no_ataca(sol, k, filas, d_asc, d_desc))
		b = true;

	return b;
}

//El coste de esta función es constante O(1)
bool es_solucion(vector<int>& sol, int k, vector<bool>& filas, vector<bool>& d_asc, vector<bool>& d_desc)
{
	bool b = false;

	if (k == sol.size() - 1 && no_ataca(sol, k, filas, d_asc, d_desc))
		b = true;

	return b;
}