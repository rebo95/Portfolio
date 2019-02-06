using UnityEngine;
using System.Collections;

public class Recogiendovasos : MonoBehaviour {

	public string tag;

	void OnTriggerEnter2D (Collider2D other){//se utiliza para detectar que el jugador recoge una cerveza vacia
		Debug.Log ("Algo ha chocado");
		if (other.CompareTag (tag)) {//al chocar si tiene el tag acordado
			Destroy (other.gameObject);//se destruye la cerveza vacia
			GameManager.instance.PuntuacionCerveza ();//se llama a la suma de puntos asignada a la cerveza
		}
	}
}
