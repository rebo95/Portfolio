using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraResizer : MonoBehaviour {

    CameraMovement CM;
    GameObject cView;

    Transform Min;
    Transform Max;
	// Use this for initialization
	void Start () {
        cView = GameObject.FindGameObjectWithTag("MainCamera");
        CM = cView.GetComponent<CameraMovement>();
        Min = transform.GetChild(0);
        Max = transform.GetChild(1);
    }

    private void OnTriggerStay2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            CM.CamMin = Min;
            CM.CamMax = Max;
        }

    }
}
