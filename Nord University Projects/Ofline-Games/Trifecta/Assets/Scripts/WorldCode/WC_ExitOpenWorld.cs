using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class WC_ExitOpenWorld : MonoBehaviour {

    public string SceneName; // we have to set the scene name

    bool entryGrantet = false;

    public string NameOfTheExitObject;

    public int EntryCost;

    [Header("need to be assigned but should already be in the prefab")]
    public Text TheUIText;
    public GameObject UiCanvas;
    [Space]
    public Sprite Open;

    public bool Entry = true;
    private void Start()
    {
        if (PlayerPrefs.GetInt(SceneName, 0) == 1) // change the sprite to be open
        {
            GetComponent<SpriteRenderer>().sprite = Open;
        }
    }

    void Update () {
        if (entryGrantet)
        {
            if (Input.GetButtonDown("Interact") && Time.timeScale != 0) // Currently set to E on the keyboard.
            {
                if (PlayerPrefs.GetInt(SceneName,0) == 1)
                {
                    //print("YOU MAY PASS");
                    GameObject.FindGameObjectWithTag("DoorNr").GetComponent<DoNotDestroy>().NameOfTheObject = NameOfTheExitObject; // set the exit object

                    EntryToNextScene();
                    return;
                }

                if (PlayerPrefs.GetInt("SoulShards", 0) >= EntryCost)
                {
                    PlayerPrefs.SetInt(SceneName, 1);

                    int cur = PlayerPrefs.GetInt("SoulShards", 0);
                    cur -= EntryCost;
                    PlayerPrefs.SetInt("SoulShards", cur);

                    //print("YOU MAY PASS");
                    GameObject.FindGameObjectWithTag("DoorNr").GetComponent<DoNotDestroy>().NameOfTheObject = NameOfTheExitObject; // set the exit object
                    EntryToNextScene();


                }
            }            
        }
	}

    void EntryToNextScene()
    {
        //SceneManager.LoadScene(SceneName); // load the next scene
        GetComponent<LoadScene>().LoadLevel(SceneName);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.layer == 10) // checks what layer the triggering object is and activates if it's the "Player" layer
        {
            entryGrantet = true;
            gameObject.transform.GetChild(3).gameObject.SetActive(true);

            if (PlayerPrefs.GetInt(SceneName, 0) == 0)
            {
                if (Entry)
                {
                    UiCanvas.SetActive(true);
                    TheUIText.text = "Cost:  " + EntryCost.ToString();
                }

            }

        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.gameObject.layer == 10) // checks what layer the triggering object is and deactivates if it's the "Player" layer
        {
            if (Entry)
            {
            gameObject.transform.GetChild(3).gameObject.SetActive(false);
            entryGrantet = false;

            UiCanvas.SetActive(false);

            }
        }
    }

}

