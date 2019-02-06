using UnityEngine;
using System.Collections;

public class MovimientoJoya : MonoBehaviour {

	// Use this for initialization
	public float vely;
	public float refresco;

	void Start () {
		movi();
	}

	// Update is called once per frame
	void Update () {
		transform.Translate (new Vector3 (0.0f, vely * Time.deltaTime, 0.0f));

	}
		//si hacemos que la parte visual sea un hijo de un padre que respete los ejes globales ya estaría,
		// hace el movimiento de sube y baja de la forma que queremos.

	public void movi(){
		
		vely = -vely;
		Invoke ("movi", refresco);
	}

}
