using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyableBlock : MonoBehaviour {

    public int shotsNedded = 2;
	// Use this for initialization
	void Start () {
	}
	
	// Update is called once per frame
	void Update () {
		
	}
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "PlayerBullet")
        {
            shotsNedded--;
            checkLife();
        }
    }

    private void checkLife()
    {
        if (shotsNedded <= 0)
        {
            ObjectPooler.instance.killGameObject(gameObject);
        }
    }
}
