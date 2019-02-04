using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformVerticalMovement : MonoBehaviour {

    private Vector2 startPosition;
    private Vector2 newPosition;

    public int speed = 3;
    public int maxDistance = 2;

    void Start()
    {
        startPosition = transform.position;
        newPosition = transform.position;
    }

    void Update()
    {
        newPosition.y = startPosition.y + (maxDistance * Mathf.Sin(Time.time * speed));
        transform.position = newPosition;
        Debug.Log(maxDistance * Mathf.Sin(Time.time * speed));
    }
}
