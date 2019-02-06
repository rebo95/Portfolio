using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TestSpawner : MonoBehaviour {

    public GameObject bullet;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
        if (Input.GetKeyDown(KeyCode.U))
        {

            bullet.transform.position = new Vector2(this.transform.position.x, this.transform.position.y);
            Instantiate(bullet);
           
        }
	}
    
}
