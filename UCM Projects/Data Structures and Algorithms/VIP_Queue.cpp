//Grupo VJ01, Aaron Reboredo V�zquez
//Grupo VJ01, Pablo Mart�n Garc�a

//Este ejercicio nos permite gestionar la cola de una discoteca en funci�n de las prioridades de los asistentes. Para ello hacemos uso de la clase ColaVip.
//todas aquellas llegadas tales que exista espacio en la discoteca entran directamente aumenando el n�mero de personas dentro.
// en caso de que el aforo est� lleno, las personas se ir�n posicionando por orden de llegada en nuestra cola, hacemos uso del m�todo nuestro m�todo push.
// en caso de que salga una persona de la discoteca, el contador de personas dentro disminuir� y se proceder� a introducir una persona de la cola en caso de haberla.
// Ahora, la selecci�n de la persona que va a entrar ir� en funci�n de las prioridades, vamos comparando en la cola las prioridades de los elementos y seleccionamos la primera
// de las mayores prioridades, es decir, el elemento con el n�mero de prioridad m�s bajo y que se encuentre antes que los equivalentes en la cola. Con pop, eliminamos ese elemento
// e incrementamos el contador de personas en la discoteca. Gestionamos el problema de esta manera hasta terminar con el n�mero de movimientos.

#include <iostream>

using namespace std;

//HEADER DE LA CLASE
template <typename T>
class colaVIP
{
private:
	//Clase Nodo
	class Nodo
	{
	public:
		int priority = 0;
		T id = 0;
		Nodo* sig = nullptr;
		Nodo(const int& p, const T& ident, Nodo* n) : priority(p), id(ident), sig(n) {}	//Constructor
	};

	size_t nelems = 0;	//N�mero de eltos de la cola

						//Punteros al primer y �ltimo nodo
	Nodo* pri = nullptr;
	Nodo* ult = nullptr;

	//Prioridades de la cola
	int prioridad = 0;

public:
	colaVIP();
	colaVIP(int p);
	~colaVIP();
	void push(const int& p, const T& ident);
	T const& front() const;
	void pop();
	bool empty() const;
	size_t size() const;
};

//CPP DE LA CLASE
template <typename T>
colaVIP<T>::colaVIP()
{
}

//Crea una cola que admite hasta p prioridades
//Este m�todo tiene un coste O(1)
template <typename T>
colaVIP<T>::colaVIP(int p)
{
	//Creamos un nodo fantasma que sea el primero de la lista
	prioridad = p;
	Nodo* fant = new Nodo(-1, -1, nullptr);
	pri = fant;
	ult = fant;
	nelems = 0;
}

template <typename T>
colaVIP<T>::~colaVIP()
{
}

//Introducimos un elemnto con su prioridad e identificador al final de la cola
//Este m�todo tiene un coste de O(1)
template <typename T>
void colaVIP<T>::push(const int& p, const T& ident)
{
	Nodo* node = new Nodo(p, ident, ult->sig);
	ult->sig = node;
	ult = node;
	nelems++;
}

//Devuelve el primer elemento, considerando prioridades
//Este m�todo tiene un coste O(n) siendo n el tama�o de la cola
template <typename T>
T const& colaVIP<T>::front() const
{
	int max_p = prioridad + 1;
	Nodo* act = pri->sig;
	Nodo* imp = nullptr;

	if (!empty())
	{

		while (act != nullptr)
		{
			if (act->priority < max_p)
			{
				max_p = act->priority;
				imp = act;
			}

			act = act->sig;
		}

	}
	else
		std::cout << "Cola vacia";

	return imp->id;
}

//Elimina el primer nodo de la lista, considerando prioridades
// el coste del m�todo es O(n + m) siendo n el numero de personas en la cola y m la distancia entre el primer elemeto y el primero de mayor prioridad.
// en el peor de los casos el elemento se encuentra al final de la cola , el coste es O(2n) -> O(n), siendo n el n�mero de elementos en la cola.
template <typename T>
void colaVIP<T>::pop()
{
	T e_id = front(); // coste O(n) donde n es el n�mero de personas en la cola 
	int i = 1;

	Nodo* act = pri->sig;
	Nodo* imp = pri;
	Nodo* ant = pri;

	if (size() == 1)
	{
		imp = act;
		pri = ant;
	}
	else
	{
		while (act->id != e_id){
		
			ant = act;
			act = act->sig;
			i++;
		}

		imp = act;

	}

	ant->sig = imp->sig;

	if(i == size())
		ult = ant;
	
	nelems--;

	//El coste de este condicional es O(m) siendo m la "distancia" desde el primer elemento de la cola hasta el deseado(que nos lo da el m�todo front) es decir, el
	//primero con mayor prioridad.


}

//Comprueba si la cola est� vac�a
//Este m�todo tiene un coste de O(1)
template <typename T>
bool colaVIP<T>::empty() const
{
	return size() == 0;
}

//Devuelve el tama�o de la cola
//Este m�todo tiene un coste de O(1)
template <typename T>
size_t colaVIP<T>::size() const
{
	return nelems;
}


//FUNCIONES A USAR EN EL PROGRAMA PRINCIPAL
void resuelve_caso(); void salida(colaVIP<int>& c);

int main()
{
	int numCasos;
	cin >> numCasos;

	for (int i = 0; i < numCasos; i++)
		resuelve_caso();

	return 0;
}

//Funci�n que resuelve un caso propuesto
//Esta funci�n tiene un coste O(m * n) siendo m la cantidad de movimientos(gente que entra y gente que sale) que se van a hacer en la cola
//y n la cantidad de gente que hay en la cola. En el peor de los casos la gente que habr� en la cola ser� equivalente al n�mero de personas (num pers en el caso de una discoteca
// de aforo 0 o numpersonas - 1 en el caso de una discoteca de aforo 1 (num pers aprox = num pers -1). De esta manera,
// el coste es O(m*n) donde m ser� el n�mero de movimientos y n el n�mero de personas.
void resuelve_caso()
{
	int p_cola, mov, aforo, pers;
	char op;
	pers = 0;	//Personas que hay dentro de la discoteca inicialmente

	cin >> p_cola >> mov >> aforo;

	colaVIP<int> cola = colaVIP<int>(p_cola);

	for (int i = 0; i < mov; i++) // repetimos m veces, siendo m el n�mero de movimientos realizados. Repetimos m veces instrucci�n de coste O(n)
	{
		cin >> op;
		
		if (op == '-')
		{
			pers--;
			if (cola.size() > 0) // condicion con coste O(1)
			{
				cola.pop(); // pop coste O(n) donde n, va a ser el tama�o de la cola en cada momento.
				pers++;
			}
		}
		else
		{
			int p, ident;
			cin >> p >> ident;
			cola.push(p, ident);

			if (pers < aforo && cola.size() > 0)
			{
				cola.pop(); // pop coste O(n) donde n, va a ser el tama�o de la cola en cada momento.
				pers++;
			}
			
		}// coste del condicional O(n)
	}

	salida(cola);
}

//Funci�n que gestiona la salida que debe devolver el programa
//Esta funci�n tiene un coste O(n) siendo n el tama�o de la cola
void salida(colaVIP<int>& c)
{
	int tam = c.size(); // size() coste O(1)

	if (tam > 0)
	{
		
		for (int i = 0; i < tam; i++) //n veces O(1), siendo n el tama�o de la cola 
		{
			cout << c.front() << " ";
			c.pop(); // pop coste O(1)
		}
				
	}		
	else
		cout << "NADIE";

	cout << endl;
}