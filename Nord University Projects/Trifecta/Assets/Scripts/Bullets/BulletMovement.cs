using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletMovement : MonoBehaviour, IPooledObject {

    ObjectPooler objectPooler;
    public float speed = 5f;
    Rigidbody2D rb;

    // Use this for initialization
    public void OnObjectSpawn ()
    {
        objectPooler = ObjectPooler.instance;
        rb = gameObject.GetComponent<Rigidbody2D>();
        rb.velocity = transform.right * speed;
	}
}
