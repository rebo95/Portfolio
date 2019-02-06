using UnityEngine;
using System.Collections;

public class Cayendosevasos : MonoBehaviour {//Es el codigo para cuando un vaso vacío cae por el lado de la barra del camarero sin que este lo coja

	public string tag;//tag que tiene que tener el objeto que entra para que ocurra la accion

	void OnTriggerEnter2D (Collider2D other){//metodo de colision
		Debug.Log ("Algo ha chocado");
		if (other.CompareTag (tag)) {
			Destroy (other.gameObject);//se destruye el objeto que tiene el tag
			GameManager.instance.Pierde ();//Se llama la metodo del gamemanager que hace perder una vida
		}
	}
}
