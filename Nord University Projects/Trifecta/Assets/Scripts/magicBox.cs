using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class magicBox : MonoBehaviour
{
    private SpiritNewMovement player;
    private GameObject playerObject;

    private BoxCollider2D colision;
    private SpriteRenderer view;

    public char magicPlatformType = 'A'; // A default value // if it is A it will begin banish
                                         //B in case of platforms that start on the scene

    // Use this for initialization
    void Start()
    {
        playerObject = GameObject.FindGameObjectWithTag("Player");
        player = playerObject.GetComponent<SpiritNewMovement>();

        colision = GetComponent<BoxCollider2D>();
        view = GetComponent<SpriteRenderer>();

        if (magicPlatformType == 'A')
        {
            colision.enabled = false;
            view.enabled = false;
        }
        else
        {
            colision.enabled = true;
            view.enabled = true;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (player.activatePlatform)
        {

            if (magicPlatformType == 'A') // if player activate the power 'A' platforms will apear
            {                                                           //'B' platforms will banish

                colision.enabled = true;
                view.enabled = true;
            }
            else
            {
                colision.enabled = false;
                view.enabled = false;
            }
        }
        else
        {
            if (magicPlatformType == 'A') // if player desactivate the power 'A' platforms will banish
            {                                                               //'B' platforms will apear
                colision.enabled = false;
                view.enabled = false;
            }
            else
            {
                colision.enabled = true;
                view.enabled = true;
            }
        }
    }
}
