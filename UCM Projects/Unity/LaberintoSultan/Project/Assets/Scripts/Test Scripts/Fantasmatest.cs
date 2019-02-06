using UnityEngine;
using System.Collections;

public class Fantasmatest : MonoBehaviour {

	//public string tagplayer;
	public float velfant;
	void Start () {
		movimiento ();
	}


	void Update(){

	}

	void movimiento (){
		RaycastHit choca;

		transform.Rotate (0, 270, 0);

		while ((Physics.Raycast (transform.position, transform.TransformDirection (Vector3.forward),out choca, 1))) {
			if ((choca.collider.tag == "Player"))
				Debug.Log("El player ha muerto");

			transform.Rotate (0, 90, 0);
		}

		transform.Translate (0.0f, 0.0f, 1.0f);
		Invoke ("movimiento", velfant);
	}


}