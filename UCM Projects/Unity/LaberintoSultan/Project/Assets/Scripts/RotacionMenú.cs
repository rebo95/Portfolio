using UnityEngine;
using System.Collections;

public class RotacionMenú : MonoBehaviour {

	// Use this for initialization
	void Start () {
		rotando();
		
	
	}
	
	// Update is called once per frame
	void Update () {
	
	}
	public void rotando(){
		this.transform.Rotate(0, 90, 0);
		Invoke ("rotando", 1.0f);
	}
}
