//Grupo VJ01, Aaron Reboredo Vázquez
//Grupo VJ01, Pablo Martín García

//Elemento bien situdos nos permite, haciendo uso de divide y vencerás,
//saber si en un vector de enrtada (de enteros y ordenado),existe algún 
//elemento cuyo valor coincide con su índice.
//El método va acotando el análisis del vector* a la mitad por cada comprobación que realiza, hasta llegar 
//al caso base (vector vacío, o vector unitario), es aquí donde obtenemos la solución al problema:
//en caso de obtener el ´"vector unitario" se deberá analizar esa posición y su índice, obteniendo true 
// en caso de coincidir y false en caso contrario.
//en caso de llegar al caso de vector vacío la solución es imediata, no se ha encontrado ningún valor
// que coinida con su índice.

//*esto es: utilizamos indicadores que nos acotan el análisis del vector (ini y fin), de esta manera cuando 
//nos referimos a vector unitario nos referimos a que la cantidad de valores existentes entre
//el indicador de ini y fin es único y que ambos "señalan" al mismo índice en caso de que sea vacío.

#include<iostream>
#include <vector>

using namespace std;

//FUNCIONES
bool elemento_situado(const vector<int>& v, int ini, int fin); void Entradas(int n); void answer(bool b);

int main()
{
	int numCasos;

	cin >> numCasos;
	Entradas(numCasos);
	return 0;
}

//El coste de esta función es O(log n)
bool elemento_situado(const vector<int>& v, int ini, int fin)
{
	int mit;
	mit = (ini + fin) / 2;

	if ((fin - ini) == 0)
		return false;
	else if ((fin - ini) == 1)
	{
		if (v[mit] == mit)
			return true;
		else
			return false;
	}
	else
	{
		if (v[mit] > mit)
		{
			//Buscamos a la izqda
			return elemento_situado(v, ini, mit);
		}
		else if (v[mit] < mit)
		{
			//Buscamos a la derecha
			return elemento_situado(v, mit, fin);
		}
		return true;
	}
}

void Entradas(int n)
{
	int dim;
	for (int i = 0; i < n; i++)
	{
		cin >> dim;
		vector <int> v(dim);
		for (int j = 0; j < dim; j++)
		{
			cin >> v[j];
		}
		answer(elemento_situado(v, 0, v.size()));
	}
}

void answer(bool b) {
	if (b)
		cout << "SI" << endl;
	else
		cout << "NO" << endl;
}