using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBulletBehaviour : MonoBehaviour {

    ObjectPooler objectPooler;

	// Use this for initialization
	void Start () {
        objectPooler = ObjectPooler.instance;
	}


    private void OnCollisionEnter2D(Collision2D collision)
    {
        // Damage logic
        if (collision.gameObject.tag == "Player")
        {
            if(transform.rotation.y == 0)
            {
                collision.gameObject.GetComponent<GeneralPlayerMovement>().touchedByEnemy(-1, 2);
            }
            else
                collision.gameObject.GetComponent<GeneralPlayerMovement>().touchedByEnemy(1, 2);
            //collision.gameObject.GetComponent<GeneralPlayerMovement>().touchedByEnemy(transform.localScale.x / Mathf.Abs(transform.localScale.x), 2);
            collision.gameObject.GetComponent<GeneralPlayerMovement>().Damaged();

            if (collision.gameObject.GetComponent<SpiritNewMovement>().enabled)
            {
                collision.gameObject.GetComponent<SpiritNewMovement>().damaged();
            }
            else if (collision.gameObject.GetComponent<DaughterMovement>().enabled)
            {
                collision.gameObject.GetComponent<DaughterMovement>().damaged();
            }
            else if (collision.gameObject.GetComponent<FatherNewMovement>().enabled)
            {
                collision.gameObject.GetComponent<FatherNewMovement>().damaged();
            }
        }

        // Deactivating the object
        objectPooler.killGameObject(gameObject);
    }
}
