using UnityEngine;
using System.Collections;

public class PlayerControllerTest : MonoBehaviour {
	int energia =100;
	int contadordeJoyas=0, joyassacadas;
	public GameObject Joya, Player, Exit;
	public string tagentrada;
	// Use this for initialization
	
	// Update is called once per frame
	void Update () {
		movementLogic ();
		coge ();
		dejajoya ();
		Reset ();
	}
	void movementLogic (){
		RaycastHit choqueplayer;

		if (Input.GetKeyDown(KeyCode.W)) {
			if ((Physics.Raycast (transform.position, transform.TransformDirection (Vector3.forward), out choqueplayer, 1))
			    && (choqueplayer.collider.tag == tagentrada))
				transform.Translate (new Vector3 (0.0f, 0.0f, 1.0f));
			else if ((Physics.Raycast (transform.position, transform.forward, out choqueplayer, 1))
			         && (choqueplayer.collider.tag == "fant"))
				Debug.Log ("Te has chocado con el fantasma");
			else if ((Physics.Raycast (transform.position, transform.TransformDirection (Vector3.forward), 1)) == false) {
				transform.Translate (new Vector3 (0.0f, 0.0f, 1.0f));
				energia = energia - (1 + contadordeJoyas);
			}

		}
		else if (Input.GetKeyDown ("a")) {
			this.gameObject.transform.Rotate (new Vector3 (0, -90, 0));
		} 
		else if (Input.GetKeyDown ("d")) {
			this.gameObject.transform.Rotate (new Vector3 (0, 90, 0));
		}
	}
	void coge(){
		int i;
		if (energia>(20*(1+contadordeJoyas))){
			Collider[] joyita = Physics.OverlapSphere(transform.position, 0.7f);
			if (Input.GetKeyDown ("c")) {
				for (i = 0; i < joyita.Length; i++) {
					if (joyita[i].gameObject.tag == "joya" ){
						Destroy (joyita[i].gameObject);
						contadordeJoyas++;
					}
				}
			}
		}
	}
	void dejajoya(){
		if (contadordeJoyas>=1){
			if (Input.GetKeyDown (KeyCode.Space)) {

				Instantiate (Joya, transform.position + new Vector3 (0.0f, 0.5f, 0.0f), transform.rotation);
				contadordeJoyas--;
			} 

			if (energia < 20 * contadordeJoyas) {
				GameObject nuevo = Instantiate (Joya);
				nuevo.transform.position = Player.transform.position + new Vector3 (0.0f, 0.5f, 0.0f);
				contadordeJoyas--;
			}
		}
	}
	void Reset(){
		if (Input.GetKeyDown(KeyCode.P)){
			joyassacadas += contadordeJoyas;
			Player.transform.position = Exit.transform.position + Exit.transform.forward + new Vector3 (0, -0.25f, 0f); ;
			Player.transform.rotation = Exit.transform.rotation;
			contadordeJoyas = 0;
			energia = 100;
		}
	}
	void OnTriggerEnter (Collider entrada){

		if (entrada.CompareTag(tagentrada)){

			joyassacadas += contadordeJoyas;
			Player.transform.position = Exit.transform.position + Exit.transform.forward + new Vector3 (0, -0.25f, 0f); ;
			Player.transform.rotation = Exit.transform.rotation;
			contadordeJoyas = 0;
			energia = 100;

}
	}
}
