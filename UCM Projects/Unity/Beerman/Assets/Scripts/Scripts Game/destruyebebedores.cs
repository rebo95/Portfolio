using UnityEngine;
using System.Collections;

public class destruyebebedores : MonoBehaviour {//Igual que el Deathzone
	public string tagpierde;

	void OnTriggerEnter2D (Collider2D other){
		Debug.Log ("Algo ha chocado");

		if (other.CompareTag (tagpierde)) {
			Destroy (other.gameObject);
			GameManager.instance.Pierde ();
		} 

	}
}
