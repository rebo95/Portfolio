using UnityEngine;
using System.Collections;

public class Deathzone : MonoBehaviour {//Este codigo es el de la deathzone de la izquierda de la barra

	public string taggana;

	void OnTriggerEnter2D (Collider2D other){
		Debug.Log ("Algo ha chocado");

		if (other.CompareTag (taggana)) {//si tiene este tag  se llama al metodo gana del gamemanager
			Destroy (other.gameObject);//se destuye el enemigo 
			GameManager.instance.Gana ();//se llama al metodo gana del gamemanager
			GameManager.instance.PuntuacionEnemigo ();//se llama a este para que sume los puntos que hemos asignado al enemigo
		} 

		else   {
			Destroy (other.gameObject); //si no tiene el tag se destruye
			GameManager.instance.Pierde (); //se llama al metodo pierde vida, que resta una unidad a la variable vidas y quita una vida visible

		} 
			
	}
		
}

