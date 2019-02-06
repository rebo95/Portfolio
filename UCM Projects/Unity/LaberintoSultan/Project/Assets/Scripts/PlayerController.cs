using UnityEngine;
//using UnityEngine.UI;
using System.Collections;

public class PlayerController : MonoBehaviour {
	
	public string TagEntrada;

	public int ContadorDeJoyas= 0 ;
	public int JoyasRestantes;
	public int JoyasSacadas;
	public int Energia=100;

	public GameObject Joyac; 
	public GameObject Player;
	public GameObject Entrada;
	public GameObject Camara;
	public GameObject Camaraaerea;



	// Inicializa joyas en el laberinto y llama al GM para actualizal el GUI al comezar
	void Start () {
		JoyasRestantes = 3;
		GameManager.instance.Contadorjoyas (JoyasSacadas, out JoyasRestantes);
	}

		
	// Llama al GUI del GM para actualizar la energía que aparecerá en pantalla
	//Llama a los metodos del PC para que se puedan utilizar durante todo el juego
	void Update () {
		
		GameManager.instance.GUIenergía (Energia);
		MovementLogic (); // nos permite desplazarnos y no atravesar muros
		DejaJoya (); // nos permite soltar las joyas recogidas y su lógica
		Coge (); // nos permite coger las joyas con su lógica incluida
		InvocaCamaraAerea(); //cambio de posición de la cámara

	}

	void Coge(){
		
		//cogemos joyas bajo una condición de energía.
		if (Energia>(20*(1+ContadorDeJoyas))){
		Collider[] joyita = Physics.OverlapSphere(transform.position, 0.5f);
			//array de colliders ( la esfera del OlS tiene centro en nuestro jugador y radio 0.2f
		if (Input.GetKeyDown ("c")) {
			for (int i = 0; i < joyita.Length; i++) {//recorremos el vector buscando los colliders con tag joya
				if (joyita[i].gameObject.tag == "joya"){
					Destroy (joyita[i].gameObject);
					ContadorDeJoyas++;
						//cogemos o destruimos la joya y sumamos uno a las joyas en el bolsillo
					}
				}
			}
		}
	}


	public void InvocaCamaraAerea(){
		// activa una cámara aérea desactivando la principal
		if (Energia >= 10) {
			if (Input.GetKeyDown (KeyCode.M)) {
				Camara.SetActive (false);
				Camaraaerea.SetActive (true);
				Energia = Energia - 2;
				GameManager.instance.DesactivaMovimiento();

				Invoke("CambioDePosicion",2f);
			}
		}
	}


	void CambioDePosicion(){
		//desactiva la cámara aérea y vuelve a activar la principal.
		Camara.SetActive (true);
		Camaraaerea.SetActive (false);
		GameManager.instance.ActivaMovimiento();
	}


	void OnTriggerEnter (Collider entrada){
		
		if (entrada.CompareTag(TagEntrada)){
			//cuando salimos del laberinto llamamos al GM para que actualice el GUI
			JoyasSacadas += ContadorDeJoyas;
			// cuando sales del laberinto el PM introduce en el GM las joyas que sacas esta vez
			// ya ha ido restando las que se han sacado anteriormente 
			GameManager.instance.Contadorjoyas (JoyasSacadas,out JoyasRestantes);

			if (JoyasRestantes > 0) {
				GameManager.instance.ActivaPanelReentrada ();
				//se activa el pnael de reentrada si quedan joyas dentro del laberinto
			}

			else{
				GameManager.instance.ActivaPanelVictoria ();
				//se activa el pnael de victoria si las joyas dentro del laberinto son 0
			}
			//cuando estamos fuera del laberinto llamamos al GM que deshabilita el mov
			GameManager.instance.DesactivaMovimiento ();
			//las joyas del bolsillo ahora son 0, y recuperamos la energia 
			ContadorDeJoyas = 0;
			Energia = 100;
		}
	}

	void DejaJoya(){
		// si llevamos joyas en el bolsillo nos permite dejarlas( en este caso las creamos)
		if (ContadorDeJoyas>=1){
			if (Input.GetKeyDown (KeyCode.Space)) {
				
				Instantiate (Joyac, transform.position + new Vector3 (0.0f, 0.5f, 0.0f), transform.rotation);
				ContadorDeJoyas--;
				//creamos la joya a partir de la posición del jugador y reducuimos el contador de joyas o joyas que llevamos en el bolsillo
			} 
			//condición pedida para que suelte las joyas si tenemos poca energía.
			if (Energia < 20 * ContadorDeJoyas) {
				GameObject nuevo = Instantiate (Joyac);
				nuevo.transform.position = Player.transform.position + new Vector3 (0.0f, 0.5f, 0.0f);
				ContadorDeJoyas--;
			}
		}
	}
		

	public void GastaEnergia (){
		//si llevamos una joya resta dos, si llevamos dos resta tres, si llevamos tres resta 4
		Energia = Energia - 1 - ContadorDeJoyas;
		if (Energia <= 0) {
			GameManager.instance.Muerte();
			//si la energía llega a 0 llamamos al GM que desabilita Mov y activa el panel de muete

		}
	}

	void MovementLogic (){
		
		RaycastHit Choqueplayer;
		//nos permite movernos siempre que no tengamos un muro delante
			if (Input.GetKeyDown(KeyCode.W)) {

				if ((Physics.Raycast (transform.position, transform.TransformDirection (Vector3.forward), out Choqueplayer, 1)) 
				&& (Choqueplayer.collider.tag == TagEntrada))
				//si lo que tenemos delante es la entrada (o salida) podemos avanzar para que se ejecute el OnTrigger
					transform.Translate (new Vector3 (0.0f, 0.0f, 1.0f));
			
				//AQUI EL RAYCAST TIENE LA FORMA ABREVIADA
				else if ((Physics.Raycast (transform.position, transform.forward,out Choqueplayer, 1))
				&& (Choqueplayer.collider.tag == "fant"))
				GameManager.instance.Muerte ();
			//si lo que tenemos delante es el fantasma y avanzamos, se llama al GM que desabilita Mov y activa el panel de muete
				
				else if ((Physics.Raycast (transform.position, transform.TransformDirection (Vector3.forward),out Choqueplayer, 1)) == false) {
					transform.Translate (new Vector3 (0.0f, 0.0f, 1.0f));
					GastaEnergia ();
				//si no hay nada delante avanzamos y gastamos energía 
				}
			}

		else if (Input.GetKeyDown (KeyCode.A)) {
			this.gameObject.transform.Rotate (new Vector3 (0, -90, 0));
			
		} 

		else if (Input.GetKeyDown (KeyCode.D)) {
				this.gameObject.transform.Rotate (new Vector3 (0, 90, 0));
		}
	}

}
