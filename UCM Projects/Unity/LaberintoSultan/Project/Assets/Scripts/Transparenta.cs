using UnityEngine;
using System.Collections;

public class Transparenta : MonoBehaviour {

	//accedemos al render del GO al que queremos variarle la opacidad.

	public Renderer r;
	//el GO empieza siendo opaco
	bool AlgoEnMedio=false;

	void Update () {
		// creamos una variable de color que podemos modificar 
		Color c = r.material.color;
		//lógica de la transparencia.
		//si 

		if (AlgoEnMedio) {
			// si hay algo en medio llamamos al método que va a hacer transparente al que se interpone (muro)
			Transparentamuro (ref c, ref r);
		}

		else {
			//si no hay nada en medio, la opacidad es 1 (opaco) y se la asocia al rener.
			c.a = 1f;
			r.material.color = c;
		}

		//cuando salimos del condicional (no hay nada en medio) queremos que el bool vuelva a su estado inicial, porque si no, se quedaría en true ( translucido )
		AlgoEnMedio = false;

	}
	public void Transparentamuro(ref Color c, ref Renderer r){
		// cuando lo llamamos cambia la opacidad y la pone a 0.5 en este caso (translúcido)
		//y se la aocia al render del GO que se interponía
		c.a = 0.5f;
		r.material.color = c;
	}
	void ActivaTransparencia(){
		AlgoEnMedio = true;
		//esto va asociado al script SmoothCamera, si algo se intermpone entre el elemento que lleva ese Script (Mcamera) y otro (JUGADOR)
		//se llamará a este método. Activa el bool AlgoEnMedio a true que regirá nuestra lógica
	}
}
