using UnityEngine;
using System.Collections;

public class Disparacervezas : MonoBehaviour {//script para hacer que tapper lance cerveza

	public GameObject cerveza;
	public GameObject posicionmano;


	void Update () {
		if (Input.GetKeyDown(KeyCode.Space)){ //cada vez que se lanza el espacio
			Debug.Log ("espacio pulsado" + Time.frameCount);//esto no es necesario en verdad, es solo un debug.log
			GameObject nuevo = Instantiate(cerveza);//se crea la cerveza
			nuevo.transform.position=posicionmano.transform.position;//se situa la cerveza en la posición mano del jugador
	}
}
}