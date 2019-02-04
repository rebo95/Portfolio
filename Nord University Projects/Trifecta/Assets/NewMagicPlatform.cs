using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NewMagicPlatform : MonoBehaviour {

    private SpiritNewMovement player;
    private GameObject playerObject;

     List <BoxCollider2D> colision = new List<BoxCollider2D>();

    public char magicPlatformType = 'A'; // A default value // if it is A it will begin banish
                                         //B in case of platforms that start on the scene
                                         

     List<Animator> Ani = new List<Animator>();
    Animator[] children;
    // Use this for initialization
    void Start()
    {
        playerObject = GameObject.FindGameObjectWithTag("Player");
        player = playerObject.GetComponent<SpiritNewMovement>();


        //view = GetComponent<SpriteRenderer>();

        children = transform.GetComponentsInChildren<Animator>();

        for (int i = 0; i < children.Length; i++)
        {
            Ani.Add(children[i]);
            colision.Add(transform.GetChild(i).GetComponent<BoxCollider2D>());
        }


        if (magicPlatformType == 'A')
        {

            for (int i = 0; i < children.Length; i++)
            {
                Ani[i].SetBool("SwapBox", false);

                colision[i].enabled = false;

            }

        }
        else
        {
            for (int i = 0; i < children.Length; i++)
            {
                Ani[i].SetBool("SwapBox", true);
                colision[i].enabled = true;

            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (player.activatePlatform)
        {
            if (magicPlatformType == 'A') // if player activate the power 'A' platforms will apear
            {                                                           //'B' platforms will banish

                for (int i = 0; i < children.Length; i++)
                {
                    Ani[i].SetBool("SwapBox", true);

                    colision[i].enabled = true;
                }
            }
            else
            {

                for (int i = 0; i < children.Length; i++)
                {
                    Ani[i].SetBool("SwapBox", false);
                    colision[i].enabled = false;

                }
            }
        }
        else
        {
            if (magicPlatformType == 'A') // if player desactivate the power 'A' platforms will banish
            {                                                               //'B' platforms will apear


                for (int i = 0; i < children.Length; i++)
                {
                    Ani[i].SetBool("SwapBox", false);

                    colision[i].enabled = false;

                }
            }
            else
            {
                for (int i = 0; i < children.Length; i++)
                {
                    Ani[i].SetBool("SwapBox", true);

                    colision[i].enabled = true;


                }
            }
        }
    }
}


