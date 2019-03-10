//Grupo VJ01, Aaron Reboredo Vázquez
//Grupo VJ01, Pablo Martín García


// el problema consiste en ampliar la clase bintree con el fin de poder organizar árboles binarios de las formas inorden, postorden , preorden y por niveles.
// con la entrada primeramente creamos el árbol haciendo uso de las constructoras de la clase bintree, de manera recursiva vamos construyendolo. Si nos encontramos un 0
// construimos un nodo vacío, si no seguimos profundizando en el arbol, la recursión termina cuando ya no quedan árboles no vacíos por explorar. Así con las invocaciones
// a la segunda constructora de bintree vamos construyendo los diferentes árboles con sus dos hijos, que serán a su vez hijos derechos o izquierdos de árboles anteriores
// en la recursión.

// en cuanto al propósito del ejercicio tenemos cuatro problemas. Los tres primeros tienen naturaleza recursiva, van explorando el árbol construido en el orden correcto:
// todos ellos introducen los elementos del arbor en un vector solución en el orden que nosotros queremos en cada caso

//preorden: procesamos la raiz del arbol, recorremos el hijo izdo en preorden y luego el hijo derecho en preorden 
//inorden: recorremos el hijo izdo en inorden, procesamos la raiz, recorremos el hijo derecho en inorden 
//postorden: recorremos el hijo izquierdo en postorden , recorremos el hijo izquierdo en postorden y procesamos la raiz.
 // en lostres casos el hecho de procesar la raiz implica hacer un push del valor de la raiz en el vector solución en cada caso y punto de la iteración

// en el caso de el resultado por niveles, haremos uso de una cola, clase queue.
// esto nos permite recorrer el árbol de un amanera cómoda e ir almacenando los valores en la cola en el orden que nosotros queremos a posteriori en el vector solucion
// tomamos la primera raiz, y la llevamos a la cola, a posteriori hacemos lo mismo con sus hijos izquierdo y derecho, pasamos el priomer elemento de la cola al vector solución
// y introducimos en la cola los valores de los hijso izquierdo y derecho del próximo elemento en la misma, que es el hijo izquierdo de la raiz anterior y valor recién sacado
// de la cola. seguimos haciendo lo mismo hasta que no queden más elementos en la cola ( cuando un elemento no tenga hijos no habrá entradas en la cola y esta no incrementará
// su tamaño. Este procedimiento nos permite ir situando en la cola los elementos por niveles e ir explorando el árbol de la manera correcta, de izquierda a derecha y por niveles.

// los elementos privados se encargarán de hacer todo el trabajo y los públicos únicamente invocarán a estos métodos privados, devolviendo el vector solución.

#include <stdexcept> // domain_error
#include <algorithm> // max
#include <memory>    // shared_ptr, make_shared
#include <iomanip>   // setw
#include <iostream>  // endl
#include <queue>
using namespace std;





template <typename T>
class bintree {
private:
	const int TREE_INDENTATION = 4;

	/*
	Nodo que almacena internamente el elemento (de tipo T)
	y dos 'punteros compartidos', uno al hijo izquierdo y al hijo derecho.
	*/
	class Nodo; // Declaración adelantada para poder definir Link
	using Link = shared_ptr<Nodo>; // Alias de tipo

	class Nodo {
	public:
		Link izq;
		T elem;
		Link der;

		Nodo(const T& elem) : izq(nullptr), elem(elem), der(nullptr) {}
		Nodo(Link izq, const T& elem, Link der) : izq(izq), elem(elem), der(der) {}
	};

	// puntero a la raíz
	Link raiz;

	// constructora privada a partir de un puntero a Nodo
	// Para construir los árboles generados por left() y right()
	bintree(Link r) : raiz(r) {} // O(1)

								 // Muestra por 'out' una representación del árbol
								 // Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph_rec(ostream & out, int indent, Link raiz) const { // O(n), donde 'n' es el número de nodos alcanzables desde 'raiz'
		if (raiz != nullptr) {
			graph_rec(out, indent + TREE_INDENTATION, raiz->der);
			out << setw(indent) << " " << raiz->elem << endl;
			graph_rec(out, indent + TREE_INDENTATION, raiz->izq);
		}
	}




	// coste O(n) donde n es el número de elementos (nodos) que tiene el árbol binario
	//preorden: procesamos la raiz del arbol, recorremos el hijo izdo en preorden y luego el hijo derecho en preorden 
	void preorder_rec(const Link& raiz, vector<T>& vec) const {
		//m�todo que recorre el arbol en preorden, esto es :
		//raiz , hijo izdo preo, hijo dcho preo
		if (raiz != nullptr) {
			vec.push_back(raiz->elem);
			preorder_rec(raiz->izq, vec);
			preorder_rec(raiz->der, vec);
		}
	}

	// coste O(n) donde n es el número de elementos (nodos) que tiene el árbol binario
	//inorden: recorremos el hijo izdo en inorden, procesamos la raiz, recorremos el hijo derecho en inorden 
	void inorder_rec(const Link& raiz, vector<T>& vec) const {
		//recorrido inorden, la raiz in b�squeda , izdo in - raiz - dcho in
		if (raiz != nullptr) {
			inorder_rec(raiz->izq, vec);
			vec.push_back(raiz->elem);// costeO(1)
			inorder_rec(raiz->der, vec);
		}
	}


	// coste O(n) donde n es el número de elementos (nodos) que tiene el árbol binario
	//postorden: recorremos el hijo izquierdo en postorden , recorremos el hijo izquierdo en postorden y procesamos la raiz.
	void postorder_rec(const Link& raiz, vector<T>& vec) const {
		//recorrido postorden , la raiz post-b�squeda , izdo post - dcho - raiz post
		if (raiz != nullptr) {
			postorder_rec(raiz->izq, vec);
			postorder_rec(raiz->der, vec);
			vec.push_back(raiz->elem);
		}
	}


	// coste O(n) donde n es el número de elementos (nodos) que tiene el árbol binario
	// hacemos uso de la cola para poder ir recorriendo el arbol y almacenando los elementos de los arboles en el orden correcto 
	void niveles_mej(const Link& raiz,vector<T>& vec) const {
		queue<Link> cola;
		// se trata de ir metiendo derecho e izdo a la cola, pero izdo y dcho de aquellos que se van metiendo 
		if (raiz != nullptr)
			cola.push(raiz);//si el primero es null, ya no lo mete y cola queda empty... no entramos en el bucle 

		while (!cola.empty()) { // en la cola almacenaremos el número de elementos que tiene el arbol binario

			if (cola.front()->izq != nullptr)// coste front O(1)
				cola.push(cola.front()->izq); //coste push O(1)
			if (cola.front()->der != nullptr)
				cola.push(cola.front()->der); // miramos los hijos derechos e izquierdo del elemento en cabecera y los introducimos en la cola.
			//comprobamos que los hijos de la cabecera de la cola ( el próximo elemento que ocupará su lugar en el vector solucion son no nulos
			vec.push_back(cola.front()->elem);
			cola.pop();
		}
	}


public:
	// constructor de árbol vacío
	bintree() : raiz(nullptr) {} // O(1)

								 // constructor de árbol hoja
	bintree(const T& elem) : raiz(make_shared<Nodo>(elem)) {} // O(1)

															  // constructor de árbol con 2 hijos
	bintree(const bintree<T>& izq, const T& elem, const bintree<T>& der) : // O(1)
		raiz(make_shared<Nodo>(izq.raiz, elem, der.raiz)) {}

	// valor en la raíz (si existe)
	const T& root() const { // O(1)
		if (empty()) {
			throw std::domain_error("No hay raiz en arbol vacio");
		}
		else {
			return raiz->elem;
		}
	}

	// hijo izquierdo (si existe)
	bintree<T> left() const { // O(1)
		return bintree(raiz->izq);
	}

	// hijo derecho (si existe)
	bintree<T> right() const { // O(1)
		return bintree(raiz->der);
	}

	// saber si el árbol es vacío 
	bool empty() const { // O(1)
		return (raiz == nullptr);
	}

	// altura del árbol
	size_t height() const { // O(n), donde 'n' es el número de nodos en el árbol
		if (empty()) {
			return 0;
		}
		else {
			size_t hl = left().height();
			size_t hr = right().height();
			return max<size_t>(hl, hr) + 1;
		}
	}

	// Muestra por 'out' una representación del árbol
	// Adaptado de "ADTs, DataStructures, and Problem Solving with C++", Larry Nyhoff, Person, 2015
	void graph(ostream & out) const { // O(n), donde 'n' es el número de nodos en el árbol
		out << "==== Tree =====" << endl;
		graph_rec(out, 0, raiz);
		out << "===============" << endl;
	}

	// los siguientes métodos públicos invocarán a los privados, que hacen el trabajo
	// coste O(n) donde n es el número de elementos (nodos) que tiene el árbol binario, invocamos a método con coste O(n)
	vector<T> preorder() const {//nos devuelve un vector pero le damos un arbol
		vector<T> vec;
		preorder_rec(raiz, vec);
		return vec;
	}

	// coste O(n) donde n es el número de elementos (nodos) que tiene el árbol binario, invocamos a método con coste O(n)
	vector<T> inorder() const {
		vector<T> vec;
		inorder_rec(raiz, vec);
		return vec;
	}

	// coste O(n) donde n es el número de elementos (nodos) que tiene el árbol binario, invocamos a método con coste O(n)
	vector<T> postorder() const {
		vector<T> vec;
		postorder_rec(raiz, vec);
		return vec;
	}

	/	// coste O(n) donde n es el número de elementos (nodos) que tiene el árbol binario, invocamos a método con coste O(n)
	vector<T> levels_imp() const {
		vector<T> vec;
		niveles_mej(raiz, vec);
		return vec;
	}

};

bintree<int> construye();
void solucion(bintree<int>& arbol);

int main() {

	int numCasos;
	cin >> numCasos;
	for (int i = 0; i < numCasos; i++) {
		bintree<int> arbol = construye();
		solucion(arbol);
	}

	return 0;
}

bintree<int> construye() {
	int raiz;
	cin >> raiz;
	//hacemos el an�lisis se esa primera lectura
	if (raiz == 0) {//devuelve un �rbol vac�o, ergo debemos llamar a la constructora del arbol vac�o
		return bintree<int>();
	}
	else {//quiere decir quetenemos un �rbol no vac�o , es decir, tenemos que leer hijo dcho e izdo

		bintree<int> arborlIzquierdo = construye();
		bintree<int> arbolDerecho = construye();

		return bintree<int>(arborlIzquierdo, raiz, arbolDerecho);
	}
}

// el coste de la solución equivale de sumar los costes de todas las invicaciones a los métodos de coste O(n), seería O(4n), es decir, O(n) 
// donde n es el número de elementos (nodos) que tiene el árbol binario
void solucion(bintree<int>& arbol) {

	int it = arbol.preorder().size();// coste size O(n)
	vector<int> solucion(it);

	solucion = arbol.preorder();
	for (int i = 0; i < it; i++)
		cout << solucion[i] << " ";
	cout << endl;

	solucion = arbol.inorder();
	for (int i = 0; i < it; i++)
		cout << solucion[i] << " ";
	cout << endl;

	solucion = arbol.postorder();
	for (int i = 0; i < it; i++)
		cout << solucion[i] << " ";
	cout << endl;

	solucion = arbol.levels_imp();
	for (int i = 0; i <it; i++)
		cout << solucion[i] << " ";
	cout << endl;
	cout << "==" << endl;
}