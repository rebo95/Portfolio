using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CreditsMovement : MonoBehaviour {
    StartMenuButtons sMB;
    public int vely = 100;
    public float timeToMenu = 5.0f;
	// Use this for initialization
	void Start () { 
        sMB = FindObjectOfType<StartMenuButtons>();
        Invoke("InvokeFunction", timeToMenu);

    }
	
	// Update is called once per frame
	void Update () {
        gameObject.transform.Translate(new Vector2(0.0f, vely * Time.deltaTime));
	}

    void InvokeFunction()
    {
        sMB.Starmenu();
    }
}
