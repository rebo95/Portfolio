using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class cameraLogic : MonoBehaviour {

    private GameObject player;

    public Camera cam;
    
    public Vector2 minCamPos, maxCamPos;

    public float smoothTime = 0.15f;
    private Vector2 velocity;

    public bool change = false;
    float currentPosition;

    // Use this for initialization
    void Start () {
        player = GameObject.FindGameObjectWithTag("Player");
        currentPosition = transform.position.x;

    }

    // Update is called once per frame
    void Update()
    {

        if (player.transform.position.x < minCamPos.x/*player.transform.position.x < minCamPos.x*/)
        {
            minCamPos.x -= 18 * 2;
            maxCamPos.x -= 18 * 2;
            currentPosition -= 18 * 2;
            change = true;
        }
        else if (player.transform.position.x > maxCamPos.x)
        {
            minCamPos.x += 18 * 2;
            maxCamPos.x += 18 * 2;
            currentPosition += 18 * 2;
            change = true;
        }

        if (change)
        {
            float posX = Mathf.SmoothDamp(transform.position.x, currentPosition,
                  ref velocity.x, smoothTime);
            transform.position = new Vector3(posX, transform.position.y, transform.position.z);

            if (transform.position.x < currentPosition + 0.1 && transform.position.x > currentPosition - 0.1)
                change = false;
        }


        //}

    }

    private void FixedUpdate()
    {


        //if (!change)
        //{
            //float posX = Mathf.SmoothDamp(transform.position.x, player.transform.position.x,
            //        ref velocity.x, smoothTime);
            float posY = Mathf.SmoothDamp(transform.position.y, player.transform.position.y + 7,
                ref velocity.y, smoothTime);

            transform.position = new Vector3(transform.position.x,
                //Mathf.Clamp(posX, minCamPos.x + 14, maxCamPos.x - 14),
                Mathf.Clamp(posY, minCamPos.y, maxCamPos.y),
                transform.position.z);
        //}

    }
}
