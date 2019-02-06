using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class GameManager : MonoBehaviour {//va a llevar todos los datos del juego

	public static GameManager instance;
	public GameObject vida1, vida2, vida3, vida4, panelderrota, panelvictoria; //se definen los objetos que haran de vidas y de paneles de victoria y derrota
	int vidas = 4;//se declaran 4 vidas
	int puntos = 0;//los puntos comienzan en 0
	int muertes = 0;//el numero de muertes de los enemigos tambien se inicia en 0
	bool victoria = false;//un booleano que determina la victoria que se inicia en false
	bool derrota = false;//un booleano que determina la derrota que se inicia en false
	public int vasos;//la variable que almacena el numero de vasos vacios que hay en la escena
	public Text TextoPuntuación; //texto que marcará la puntuacion
	int a=10;//la variable de los puntos que hemos asignado al echar a un cliente del bar
	int b=1;//la variable de puntos que se consiguen a la variable asignada al recoger un vaso vacio
	void Start () {
		instance = this;
		TextoPuntuación.text="Score: " + puntos;//el marcador se inia con el texto "score" iniciada en la varible puntos que se inicia en 0

	}
	void Update(){//en cada vuelta del bucle comprueba
		if (victoria == false)//si no se ha producido la victoria 
			panelderrota.SetActive (derrota == true);//y la derrota si, entoces se activa el panel de la derrota
		if (derrota == false)// si no se ha producido la derrota
			panelvictoria.SetActive (victoria == true);//y la victoria si se ha producido entonces se activa el panel de la victoria
		vasos = GameObject.FindGameObjectsWithTag ("CervezaVacia").Length; //cada vuelta del bucle cuenta cuantos objetos hay con el tag cerveza vacia para ver el numero de vasos que hay en la escena
		if ((muertes == 10)&&(vasos==0))//si todos los enemigos se han ido del bar y no hay vasos, entonces se gana, siemore que la derrota no se haya producido
			victoria = true;//se setea la victoria a true
	}

	public void Pierde () {//el metodo de perder vidas
		if (victoria == false) 
		vidas--;
		//cada vez que se le llama se pierde una vida quitandola a la variable vidas
		vida1.SetActive (vidas >= 1);//Las vidas son o no visibles segun el valor de la variable vidas
		vida2.SetActive (vidas >= 2);
		vida3.SetActive (vidas >= 3);
		vida4.SetActive (vidas >= 4);
		if (vidas < 1) {//cuando las vidas son menores que uno la derrota activa la derrota impidiendo la victoria
			derrota = true;
		}
	}
	public void Gana(){
		muertes++;//cada vez que se llama se añade una unidad a la variable muertes 
	}

	public void PuntuacionEnemigo(){
		if (vidas < 1) {//si las vidas son menores que 1, entonces cuando se le llame, los puntos que sumaran serán 0
			a = 0;
		}
		puntos = puntos + a;//se suman los puntos
		TextoPuntuación.text="Score: "+puntos;//se escribe en pantalla
	}
	public void PuntuacionCerveza(){
		if (vidas < 1) {//si las vidas son menores que 1, entonces cuando se le llame, los puntos que sumaran serán 0
			b = 0;
		}
		puntos = puntos + b;//se suman los puntos
		TextoPuntuación.text="Score: "+puntos;//se escribe en pantalla
	}

	public void ResetGame(){
		Application.LoadLevel ("Game");//metodo para cargar la escena desde 0, está añadido a los botones de los paneles
	}
}
