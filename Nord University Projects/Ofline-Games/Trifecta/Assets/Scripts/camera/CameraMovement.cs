using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraMovement : MonoBehaviour {

    [Header("Defult Camera Pos")]
    public float cameraHight = 2;
    public float cameraZPos = -1;

    [Header("Camera stats")]
    public float cSpeed = 2;

    public float CameraMoveTime = 0.2f;
    float cameraTimer;

    public Transform player;
    GeneralPlayerMovement GMP;

    private float aspect;
    [HideInInspector]
    public Transform CamMin;
    [HideInInspector]
    public Transform CamMax;

    public float LookDistance = 4;
    Vector3 p;

	// Use this for initialization
	void Start () {
        player = GameObject.FindGameObjectWithTag("Player").transform;
        GMP = player.GetComponent<GeneralPlayerMovement>();

        cameraTimer = CameraMoveTime;

        CamMin = GameObject.Find("CameraMin").transform;
        CamMax = GameObject.Find("CameraMax").transform;
        aspect = Camera.main.aspect;

	}
    public float asdasD;
	// Update is called once per frame
	void FixedUpdate () {

        asdasD = Input.GetAxis("RightStick");

        // Checking if player is looking up or down
        if (Input.GetAxis("RightStick") != 0)
        {
            // Timer
            if (cameraTimer <= 0)
            {
                // checks the YVal
                // stops if from happening while moving too much
                if (Input.GetAxis("RightStick") >= 0 && Input.GetAxis("Horizontal") <= 0.1 && Input.GetAxis("Horizontal") >= -0.1 && GMP.velY == 0)
                {
                    // UP
                    p = new Vector3(player.position.x, player.position.y + cameraHight + LookDistance, cameraZPos);

                    MovingTheCamera(p);

                    return;
                }
                // stops if from happening while moving too much
                else if (Input.GetAxis("RightStick") <= 0 && Input.GetAxis("Horizontal") <= 0.1 && Input.GetAxis("Horizontal") >= -0.1 && GMP.velY == 0)
                {
                    // Down
                    p = new Vector3(player.position.x, player.position.y + cameraHight - LookDistance, cameraZPos);
                    MovingTheCamera(p);

                    return;
                }
            }
            // counts down
            else
            {
                cameraTimer -= Time.deltaTime;
            }

        }
        // Resets the timer for looking up
        else if(cameraTimer != CameraMoveTime)
        {
            cameraTimer = CameraMoveTime;
        }

        // defult camera target
        p = new Vector3(player.position.x, player.position.y + cameraHight, cameraZPos);
        MovingTheCamera(p);

	}


    public void MovingTheCamera(Vector3 target)
    {
        float orthSize = Camera.main.orthographicSize;
        if(target.x < (CamMin.position.x + orthSize * aspect))
        {
            target.x = CamMin.position.x + orthSize * aspect;
        }
        else if (target.x > (CamMax.position.x - orthSize * aspect))
        {
            target.x = CamMax.position.x - orthSize * aspect;
        }
        if (target.y < (CamMin.position.y + orthSize))
        {
            target.y = CamMin.position.y + orthSize;
        }
        else if (target.y > (CamMax.position.y - orthSize))
        {
            target.y = CamMax.position.y - orthSize;
        }
        transform.position = Vector3.Lerp(transform.position, target, Vector3.Distance(transform.position, target) * cSpeed * Time.deltaTime);
            //new Vector3(player.position.x, player.position.y + cameraHight, cameraZPos);
    }
}

