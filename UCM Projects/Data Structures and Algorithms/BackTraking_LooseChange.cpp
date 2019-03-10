//Aaron Reboredo Vázquez
//Pablo Martín García
#include <iostream>
#include <vector>

using namespace std;

//Declaración funciones
void quita_calderilla(vector<int>& sol, vector<int>& cantidades, int k, int a, int m);
bool es_solucion(int k, int a);
bool es_completable(int a);
void procesar_solucion();
void compara_sol(int num);


//Variables globales
int valores[8] = { 1, 2, 5, 10, 20, 50, 100, 200 };
vector<int> sol = { 0, 0, 0, 0, 0, 0, 0, 0 };
int numMonedas = 0;
int precio = 0;

int main()
{
	vector<int> cantidades(8);
	int numCasos;
	int a = 0;
	int num_monedas = 0;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++)
	{
		cin >> precio;
		for (int j = 0; j < 8; j++)
			cin >> cantidades[j];
		quita_calderilla(sol, cantidades, 0, a, num_monedas);
		procesar_solucion();
		cout << endl;
	}

	return 0;
}

//El coste de esta función es O(n^8)
void quita_calderilla(vector<int>& sol, vector<int>& cantidades, int k, int a, int num_monedas)
{
	for (int c = 0; c <= cantidades[k]; c++)
	{
		sol[k] = c;
		if (c > 0)
		{
			a += valores[k];
			num_monedas++;
		}

		if (es_solucion(k, a))
			compara_sol(num_monedas);
		else if (es_completable(a) && k <= 6)
			quita_calderilla(sol, cantidades, k + 1, a, num_monedas);
	}

}

//El coste de esta función es constante O(1)
bool es_completable(int a)
{
	bool b = false;
	if (a < precio)
		b = true;

	return b;
}

//El coste de esta función es constante O(1)
bool es_solucion(int k, int a)
{
	bool b = false;
	if (a == precio)
		b = true;

	return b;
}

//El coste de esta función es constante O(1)
void procesar_solucion()
{
	if (numMonedas == 0)
		cout << "IMPOSIBLE";
	else
		cout << numMonedas;

	numMonedas = 0;
}

//El coste de esta función es constante O(1)
void compara_sol(int num)
{
	if (num > numMonedas)
		numMonedas = num;
}

