//Grupo VJ01, Aaron Reboredo V�zquez
//Grupo VJ01, Pablo Mart�n Garc�a

//Elemento bien situdos nos permite, haciendo uso de divide y vencer�s,
//saber si en un vector de enrtada (de enteros y ordenado),existe alg�n 
//elemento cuyo valor coincide con su �ndice.
//El m�todo va acotando el an�lisis del vector* a la mitad por cada comprobaci�n que realiza, hasta llegar 
//al caso base (vector vac�o, o vector unitario), es aqu� donde obtenemos la soluci�n al problema:
//en caso de obtener el �"vector unitario" se deber� analizar esa posici�n y su �ndice, obteniendo true 
// en caso de coincidir y false en caso contrario.
//en caso de llegar al caso de vector vac�o la soluci�n es imediata, no se ha encontrado ning�n valor
// que coinida con su �ndice.

//*esto es: utilizamos indicadores que nos acotan el an�lisis del vector (ini y fin), de esta manera cuando 
//nos referimos a vector unitario nos referimos a que la cantidad de valores existentes entre
//el indicador de ini y fin es �nico y que ambos "se�alan" al mismo �ndice en caso de que sea vac�o.

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

//El coste de esta funci�n es O(log n)
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