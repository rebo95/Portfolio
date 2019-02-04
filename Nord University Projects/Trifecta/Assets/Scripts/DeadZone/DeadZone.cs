using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DeadZone : MonoBehaviour {

    ObjectPooler objectPooler;

    GameObject respawnGo;
    Vector2 respawnPos;

	// Use this for initialization
	void Start () {
        objectPooler = ObjectPooler.instance;
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    private void OnTriggerEnter2D(Collider2D collision)
    {
        respawnGo = collision.gameObject;
        objectPooler.killGameObject(respawnGo);

        Box boxScript = collision.gameObject.GetComponent<Box>();
        GeneralPlayerMovement playerScript = collision.gameObject.GetComponent<GeneralPlayerMovement>();

        if (boxScript != null)
        {
            respawnPos = boxScript.getStartPosition();
            objectPooler.spawnSpecificFromPool(respawnGo, respawnPos, respawnGo.transform.rotation);
        }
        if (playerScript != null)
        {
            //respawnPos = playerScript.getStartPosition();
            //objectPooler.spawnSpecificFromPool(respawnGo, respawnPos, respawnGo.transform.rotation);
            GameManager.instance.instaKill();
        }
       
    }
}
