using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Menu_AnyKeyDisable : MonoBehaviour {

	void OnEnable () {
        //StartCoroutine(Disable());
	}

    //IEnumerator Disable()
    //{
        
    //    while (true)
    //    {
    //        if (Input.anyKeyDown)
    //        {
    //            this.gameObject.SetActive(false);
    //        }
    //    }

    //}

    private void Update()
    {
        if (Input.anyKeyDown)
        {
            Debug.Log("Any key pressed!");
            this.gameObject.SetActive(false);
        }
    }

}
