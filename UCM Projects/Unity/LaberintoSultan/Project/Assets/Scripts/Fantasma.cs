using UnityEngine;
using System.Collections;

public class Fantasma : MonoBehaviour {

	public GameObject Jugador; 
	public float VelFant;
	int i; //utilizamos una variable contador para evitar que en caso de encerrar al fantasma entre tres muros y el jugador no entre en un bucle infinito

	void Start () {
		i = 0;
		//llamamos al comienzo al metodo que hace que se mueva el fantasma
		Movimiento ();
	}


	void Update(){
	}

	void Movimiento (){
		RaycastHit Choca;
		i = 0;
		// giramos siempre a la izquierda, si hay algo...
		transform.Rotate (0, 270, 0);

		while ((Physics.Raycast (transform.position, transform.TransformDirection (Vector3.forward),out Choca, 1))) {
					if ((Choca.collider.tag == "Player"))
						GameManager.instance.Muerte ();
			//...si es el jugador, el GM desabilita Mov y activa el panel de muete
			//ve que hay algo delante y gira sobre si mismo.
					transform.Rotate (0, 90, 0);
			i++;
			if (i >7)
				break;

		}
		 //cuando no hay nada, avanzamos hacia adelante y se reinvoca el método para seguir moviéndose 

		transform.Translate (0.0f, 0.0f, 1.0f);
		Invoke ("Movimiento", VelFant);
	}

}