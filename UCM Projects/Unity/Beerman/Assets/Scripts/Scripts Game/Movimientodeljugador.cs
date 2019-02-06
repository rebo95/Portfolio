using UnityEngine;
using System.Collections;

public class Movimientodeljugador : MonoBehaviour {

	// Use this for initialization
	public GameObject barra1; 
	public GameObject barra2;
	public GameObject barra3; 
	public GameObject barra4;//se declaran las cuatro posiciones del jugador como empty objects
	double cont = 1;//la variable que contabiliza la posición

	void Update ()//se comprueba cada vez que se recorre el bucle
	{
		if (Input.GetKeyDown (KeyCode.UpArrow))
			cont--;//si pulsamos la flecha hacia arriba se resta una unidad al contador
		if (Input.GetKeyDown (KeyCode.DownArrow))
			cont++;//si pulsamos la flecha hacia abajo se suma una unidad al contador
			if (cont > 4)
				cont = 1;//si esa variable es mayor que 4 se setea a 1 para que el movimiento sea ciclico
			if (cont < 1)
			cont = 4;//si esa variable es menor que 1 se setea a 4 para que el movimiento sea ciclico
			else if (cont == 1)
				transform.position = barra1.transform.position;//relaciona cada posible valor de la variable que controla la posición con un objeto que será una posición
			else if (cont == 2)
				transform.position = barra2.transform.position;//relaciona cada posible valor de la variable que controla la posición con un objeto que será una posición
			else if (cont == 3)
				transform.position = barra3.transform.position;//relaciona cada posible valor de la variable que controla la posición con un objeto que será una posición
			else if (cont == 4)
				transform.position = barra4.transform.position;//relaciona cada posible valor de la variable que controla la posición con un objeto que será una posición


		}
	}

