using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformLogic : MonoBehaviour
{

    private GameObject player_;


    private void OnTriggerStay2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            player_ = collision.gameObject;
            player_.transform.parent = GetComponentInChildren<Transform>().transform;
        }
        //else if (collision.gameObject.tag == "Box")
        //{
        //    collision.gameObject.transform.parent = GetComponentInChildren<Transform>().transform;
        //}
    }


    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.gameObject.tag == "Player")
        {
            if (player_ != null)
            {
                player_.transform.parent = null;

            }
        }
        //else if (collision.gameObject.tag == "Box")
        //{
        //    collision.gameObject.transform.parent = null;
        //}
    }

}