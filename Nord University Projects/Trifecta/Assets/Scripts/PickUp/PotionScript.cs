using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PotionScript : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            if (collision.gameObject.GetComponent<SpiritNewMovement>().enabled)
            {
                GameManager.instance.spiritRecover();
            }
            else if (collision.gameObject.GetComponent<DaughterMovement>().enabled)
            {
                GameManager.instance.daughterRecover();
            }
            else if (collision.gameObject.GetComponent<FatherNewMovement>().enabled)
            {
                GameManager.instance.fatherRecover();
            }

            this.gameObject.SetActive(false);
        }


    }
}
