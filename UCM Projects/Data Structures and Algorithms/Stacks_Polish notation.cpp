//Grupo VJ01, Aaron Reboredo V�zquez
//Grupo VJ01, Pablo Mart�n Garc�a

//este programa nos permite, mediante el uso de pilas, resolver el problema de la notaci�n polaca: consiste en ir introduciendo los operandos en la pila y operarlos de dos en dos una vez
//leemos un operador, en este caso, desapilamos los dos elementos que encabezan la pila y los tratamos en funci�n del operador, introducimos el resultado en la pila, y seguimos
//con el proceso, introducimos operando, y al leer el nuevo operador desapilamos nuevamente los dos elementos que residen en la pila, el �ltimo operando introducido y el
//resultado de la anterior operaci�n.


#include <iostream>
#include <string>
#include <stack>

using namespace std;

//DECLARACI�N DE FUNCIONES
void clear_stack(stack <int>& s); void resuelve_caso(stack <int>& p, int numOp, int& resultado); void asigna_op(stack <int>& p, int& op1, int&op2);

int main()
{
	stack<int> pila;
	int numCasos, numOperandos;
	numCasos = numOperandos = 0;

	cin >> numCasos;

	for (int i = 0; i < numCasos; i++)
	{
		int resultado = 0;
		cin >> numOperandos;
		
		resuelve_caso(pila, numOperandos, resultado);		
		cout << resultado << endl;
	}

	clear_stack(pila);
	return 0;
}

//El coste de esta funci�n es O(n) siendo n el numOp(el n�mero de operandos + operadores que tiene el caso a resolver, o lo que es lo mismo, la longitud de la expresion a evaluar)
void resuelve_caso(stack <int>& p, int numOp, int& resultado)
{
	int j;
	int op1, op2;
	if (numOp > 1)
	{
		string s;
		getline(cin, s);
		
		for (j = 1; j < s.size(); j++)
		{

			if (s[j] == '-')
			{
				asigna_op(p, op1, op2); // m�todo coste O(1)
				resultado = op1 - op2;
				p.push(resultado); //push coste O(1)
			}
			else if (s[j] == '+')
			{
				asigna_op(p, op1, op2);
				resultado = op1 + op2;
				p.push(resultado);
			}
			else
				p.push(s[j] - 48);		
		}
	}
	else
	{
		cin >> resultado;
		p.push(resultado);
	}

}

//El coste de esta funci�n es constante O(1)
void asigna_op(stack <int>& p, int& op1, int&op2)
{
	op2 = p.top();
	p.pop(); // pop coste 0(1)
	op1 = p.top();
	p.pop();
}

//El coste de esta funci�n es O(n) siendo n el tama�o de la pila(n�mero de elementos que tiene)
void clear_stack(stack <int>& s)
{
	int stack_size = s.size();

	for (int k = 0; k < stack_size; k++)
		s.pop();	//coste O(1) repetida n veces, doce n es size es el tama�o de la pila
}