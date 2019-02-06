using UnityEngine;
using System.Collections;

public class Credits : MonoBehaviour {
	public int vely;
	//public float time;
	// Use this for initialization
	void Start () {
		Invoke ("voyamenu", 10.0f); 
	}
	
	// Update is called once per frame
	void Update () {
		this.transform.Translate (0, vely * Time.deltaTime, 0);
	}

	void voyamenu(){
		GameManager.instance.irMenu ();
	}


}
