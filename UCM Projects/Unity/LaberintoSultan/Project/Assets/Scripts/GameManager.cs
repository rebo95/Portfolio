using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class GameManager : MonoBehaviour {
	
	public static GameManager instance;

	int Energia;
	public int JoyasIni;

	public GameObject Exit;
	public GameObject Morir; 
	//variable PUBLICA que será el GameObjet al que queremos acceder (GetComponent) para activar o desactivar un Script que tiene ese GM

	public GameObject Player;
	public GameObject PanelVictoria;
	public GameObject PanelReentrada; 
	public GameObject PanelMuerte ;

	/*public bool Testeo;
	public bool Verdad;
	public bool Mentira;*/

	public Text TextJoyas;
	public Text TextJoyasPanel;
	public Text TextEnergia;

	void Start (){
		instance = this;
	}


	public void Update(){
		
	}

	//Carga de escenas, los botones llamarán al GM que cargará la escena correspondiente 

	public void Credits(){
		Application.LoadLevel ("Creditos");
	}


	public void irMenu(){
		Application.LoadLevel ("Menu");

	}


	public void Niv1(){
		Application.LoadLevel("Nivel1");
		
	}


	public void Niv2(){
		Application.LoadLevel("Nivel2");
	}



	public void Reset(){
		//nos devuelve a una posición concreta (una unidad al frente y mirando a su vector.z por delante del ponto de salida del laberinto
		Player.transform.position = Exit.transform.position + Exit.transform.forward + new Vector3 (0, -0.25f, 0f); ;
		Player.transform.rotation = Exit.transform.rotation;
		//habíamos deshabilitado el mov, lo habilitamos de nuevo.
		ActivaMovimiento ();

		//quitamos el panel
		PanelReentrada.SetActive (false);
	}

		
	public void Muerte(){
		PanelMuerte.SetActive(true);
		DesactivaMovimiento ();
		//saca panel muerte y no deja movernos 
	}


	public void ActivaMovimiento(){
		Morir.GetComponent<PlayerController>().enabled = true;
		//aciva el script PM
		//NombreVariable(tipoGO).GetComponent<>().enables = true/false
	}


	public void DesactivaMovimiento(){
		//deshabilita PM
		Morir.GetComponent<PlayerController>().enabled = false;
		
	}


	public void GUIenergía(int energía){
		// actualiza el GUI, nos muestra la energía en todo momento
		TextEnergia.text = "Energía:" + energía;
	}


	public void GUIjoyas(int joyasdentro){
		// nos imprime en pantallas (esquina sup dcha) las joyas que quedan en el laberinto, solo se actualiza cuando salimos
		TextJoyas.text = "Joyas en el laberinto: " + joyasdentro;
	}


	public void ActivaPanelReentrada(){
		PanelReentrada.SetActive (true);
	}


	public void ActivaPanelVictoria(){
		PanelVictoria.SetActive (true);
	}


	public void Contadorjoyas (int JoyasFuera, out int JoyasLaberinto){
		// y si ini GameObject.FindGameObjectsWithTag("")?
		JoyasLaberinto = JoyasIni - JoyasFuera;
		//lleva la cuenta de las joyas que quedan dentro del laberinto.
		//que son las iniciales - las del bolsillo que cuenta el PM
		//SI METEMOS MAS JOYAS DEBEMOS CAMBIAR ESTE VALOR DESDE EL EDITOR O IMPLEMENTAR FINDOBJETS
		// actualiza el GUI que aparece en el panel, actualizamos solo cuando salimos.
		TextJoyasPanel.text = "Joyas en el laberinto : " + JoyasLaberinto;
		GUIjoyas (JoyasLaberinto);
		}
}
