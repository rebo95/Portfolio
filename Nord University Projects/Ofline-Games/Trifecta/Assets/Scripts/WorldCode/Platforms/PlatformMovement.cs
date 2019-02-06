using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformMovement : MonoBehaviour {

    private Vector2 initialPosition;
    public float movementDistance;

    public int movementVelocity = 1;
    private int movementDirection = 1;
    public bool activate;

    public char movementKind = 'v'; // it will be v for vertical movement and h for horizontal movement
     
	// Use this for initialization
	void Start () {
        initialPosition = this.transform.position;

        if (movementVelocity >= 0)
            movementDirection = 1;
        else
            movementDirection = -1;


        activate = false;
	}


    void OnTriggerEnter2D(Collider2D collision)
    {
        
        if(collision.gameObject.tag == "BulletKey")
        {
            activate = !activate;
        }
    }

    // Update is called once per frame
    void FixedUpdate () {

        if (activate)
        {
            if (movementKind == 'v')
            {
                if (movementDirection == 1)
                {
                    if (transform.position.y < initialPosition.y + movementDirection * movementDistance)
                    {
                        float newPosY = transform.position.y + movementVelocity * 0.01f;
                        transform.position = new Vector2(transform.position.x, newPosY);
                    }
                }
                else
                {
                    if (transform.position.y > initialPosition.y + movementDirection * movementDistance)
                    {
                        float newPosY = transform.position.y + movementVelocity * 0.01f;
                        transform.position = new Vector2(transform.position.x, newPosY);
                    }
                }
            }
            else if (movementKind == 'h')
            {
                if (movementDirection == 1)
                {
                    if (transform.position.x < initialPosition.x + movementDirection * movementDistance)
                    {
                        float newPosX = transform.position.x + movementVelocity * 0.01f;
                        transform.position = new Vector2(newPosX, transform.position.y);
                    }
                }else
                {
                    if (transform.position.x > initialPosition.x + movementDirection * movementDistance)
                    {
                        float newPosX = transform.position.x + movementVelocity * 0.01f;
                        transform.position = new Vector2(newPosX, transform.position.y);
                    }
                }

            }
        }
        else
        {
            if (movementKind == 'v')
            {
                if (movementDirection == 1)
                {
                    if (transform.position.y > initialPosition.y)
                    {
                        float newPosY = transform.position.y - movementVelocity * 0.01f;
                        transform.position = new Vector2(transform.position.x, newPosY);
                    }
                }
                else {
                    if (transform.position.y < initialPosition.y)
                    {
                        float newPosY = transform.position.y - movementVelocity * 0.01f;
                        transform.position = new Vector2(transform.position.x, newPosY);
                    }
                }
            }
            else if (movementKind == 'h') {
                if (movementDirection == 1)
                {
                    if (transform.position.x > initialPosition.x)
                    {
                        float newPosX = transform.position.x - movementVelocity * 0.01f;
                        transform.position = new Vector2(newPosX, transform.position.y);
                    }
                }
                else {
                    if (transform.position.x < initialPosition.x)
                    {
                        float newPosX = transform.position.x - movementVelocity * 0.01f;
                        transform.position = new Vector2(newPosX, transform.position.y);
                    }
                }
            }
        }
	}
}
