using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Shrine_OpenLevel : MonoBehaviour {

    private GameObject Rune01;
    private GameObject Rune02;
    private GameObject Rune03;
    private GameObject GodHaze;

    public bool upgradeReady = false;

    public bool PlayerInRange = false;
    public bool InteractionButtonPressed;

    public Sprite toolTiptoShow;
    private GameObject toolTip;
    private bool AbilityUnlocked = false;

    [Space]
    public int NumbersOfShrines = 3;
    // unlock abilities
    [Header("Ability unlock")]
    public string PowerUnlockID = "X";

    [Space]
    public string PlayerPref = "Level01_Progress";

    // Use this for initialization
    void Start ()
    {
        Rune01 = gameObject.transform.GetChild(0).gameObject;   
        Rune02 = gameObject.transform.GetChild(1).gameObject;       
        Rune03 = gameObject.transform.GetChild(2).gameObject;     
        GodHaze = gameObject.transform.GetChild(3).gameObject;
        toolTip = gameObject.transform.GetChild(4).gameObject;
        toolTip.SetActive(false);

        if (PlayerPrefs.GetInt(PlayerPref, 0) == 0)
        {
            Rune01.SetActive(false);
            Rune02.SetActive(false);
            Rune03.SetActive(false);
            GodHaze.SetActive(false);
        }
        if(PlayerPrefs.GetInt(PlayerPref, 0) == 1)
        {
            Rune01.SetActive(true);
            Rune02.SetActive(false);
            Rune03.SetActive(false);
            GodHaze.SetActive(false);
        }
        if(PlayerPrefs.GetInt(PlayerPref, 0) == 2)
        {
            Rune01.SetActive(true);
            Rune02.SetActive(true);
            Rune03.SetActive(false);
            GodHaze.SetActive(false);
        }
        if (PlayerPrefs.GetInt(PlayerPref, 0) == NumbersOfShrines)
        {
            Rune01.SetActive(true);
            Rune02.SetActive(true);
            Rune03.SetActive(true);
            GodHaze.SetActive(true);
            upgradeReady = true;
            gameObject.transform.GetChild(5).transform.GetComponent<AudioSource>().Play();
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.tag == "Player")
        {
            PlayerInRange = true;
            if(AbilityUnlocked == true)
            {
                toolTip.SetActive(true);
            }
            if (PlayerPrefs.GetInt(PowerUnlockID, 0) == 0 && upgradeReady == true)
            {
                gameObject.transform.GetChild(6).gameObject.SetActive(true);
                GetComponent<AudioSource>().Play();
                gameObject.transform.GetChild(5).gameObject.SetActive(true);
            }
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            PlayerInRange = false;
            gameObject.transform.GetChild(6).gameObject.SetActive(false);
            toolTip.SetActive(false);
            gameObject.transform.GetChild(5).gameObject.SetActive(false);
        }
    }



    // Update is called once per frame
    void Update ()
    {

        if (PlayerInRange == true && Input.GetButtonDown("Interact") && upgradeReady == true)
        {
            //unlock
            if (PowerUnlockID != "X")
            {


                PlayerPrefs.SetInt(PowerUnlockID, 1);
                GameObject p = GameObject.FindGameObjectWithTag("Player");
                p.SendMessage("GiveAbbility");
                AbilityUnlocked = true;
                toolTip.SetActive(true);
                toolTip.GetComponent<SpriteRenderer>().sprite = toolTiptoShow;
            }

        }

    }
}
