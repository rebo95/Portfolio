using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoxAttachement : MonoBehaviour {

    Transform oldParentTransform = null;


    private void OnCollisionStay2D(Collision2D collision)
    {
        if (gameObject.transform.parent != null)
            oldParentTransform = gameObject.transform.parent;

        if (collision.gameObject.tag != "Player")
            gameObject.transform.parent = collision.gameObject.transform;
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
            gameObject.transform.parent = oldParentTransform;
    }

}
