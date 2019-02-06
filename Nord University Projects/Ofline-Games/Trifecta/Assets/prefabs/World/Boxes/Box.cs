using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Box : MonoBehaviour {

    Vector2 startPosition;

	// Use this for initialization
	void Start () {
        startPosition = gameObject.transform.position;	
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public Vector2 getStartPosition()
    {
        return startPosition;
    }
}
