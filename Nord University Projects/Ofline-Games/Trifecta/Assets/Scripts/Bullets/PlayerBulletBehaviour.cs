using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerBulletBehaviour : MonoBehaviour {

    FatherNewMovement fatherScript;
    ObjectPooler objectPooler;

	// Use this for initialization
	void Start () {
        objectPooler = ObjectPooler.instance;
	}
	

    private void OnCollisionEnter2D(Collision2D collision)
    {
        //fatherScript = collision.gameObject.GetComponent<FatherNewMovement>();

        //if (fatherScript == null)
        //    objectPooler.killGameObject(gameObject);

        if (collision.gameObject.tag != "Player")
            objectPooler.killGameObject(gameObject);

    }
}
