using UnityEngine;
using System.Collections;

public class MovimientoBebedores : MonoBehaviour {
	float velx = 0.75f; 
	public float dir = 0 ;
	public string tag;
	//public string tag2;
	public GameObject cervezavacia;
	public GameObject manocliente; //iniciamos la variables y la cerveza que se crea y donde (la mano)

	void Update () {
		transform.Translate (new Vector3 (velx * dir * Time.deltaTime, 0.0f, 0.0f)); //Se mueve 
		Invoke ("OnTriggerEnter2D", 0.0f);//e invoca el triggerenter
		}
	public void OnTriggerEnter2D (Collider2D other){
		if ((other.CompareTag (tag))&&(dir>0)) { //si lo que choca tiene el tag correcto y el cliente se mueve a la derecha entra
			Destroy (other.gameObject); //se destruye la cerveza
			velx=1.25f; 	//cambiamos la velocidad y la direccion a la opuesta
			dir = -1f;
			Invoke ("Bebiendo", 2.0f); //se invoca el bebiendo donde el cliente se queda quieto
			}
		}
		
	public void lanzavasos (){
		GameObject nuevo = Instantiate (cervezavacia); 
		nuevo.transform.position = manocliente.transform.position; //creamos la cerveza vacia
		velx=0.75f;  //la velocidad y sentido vuelven a ser las originales
		dir=1;
	}
	public void Bebiendo (){
		velx= 0 ;//la velocidad es 0
		Invoke ("lanzavasos", 2.0f);//se invoca al lanzavasos
	}
	//public void OnTriggerEnter2D1 (Collider2D other){
		//if ((other.CompareTag (tag2))&&(dir>0)) { //si lo que choca tiene el tag correcto y el cliente se mueve a la derecha entra
			//this.velx= 0.0f; 	//cambiamos la velocidad y la direccion a la opuesta
		//}	
	}



