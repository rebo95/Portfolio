using UnityEngine;
using System.Collections;

public class restringemovimiento : MonoBehaviour {
	public float xmax;
	public float xmin;

	// Use this for initialization
	void Start () {
	
	}
	
	// Update is called once per frame
	void Update () {
		transform.position = new Vector3 (Mathf.Clamp (transform.position.x, xmin, xmax),
			transform.position.y, transform.position.z);
		
	
	}
}
