using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class WC_EnteringBossPuzzle : MonoBehaviour {

    public string SceneName; // we have to set the scene name

    bool entryGrantet = false;

    public string NameOfTheExitObject;

    [Space]
     Image ScoreForRoom;
    public List<Sprite> Sprites = new List<Sprite>();

    [Header("UI")]
    public GameObject uiCanvus;

    public bool Tutorial = false;

    public AudioClip objectActive;
   // public AudioClip objectInteract;

    private void Start()
    {
        uiCanvus = transform.GetChild(1).gameObject;

        ScoreForRoom = uiCanvus.transform.GetChild(0).GetComponent<Image>();
        if (PlayerPrefs.GetInt(SceneName, 0) <= -1)
        {
            return;
        }
        ScoreForRoom.sprite = Sprites[PlayerPrefs.GetInt(SceneName,0)];

        if (Tutorial)
        {
            ScoreForRoom.enabled = false;
        }
    }

    void Update () {
        if (entryGrantet)
        {
            if (Input.GetButtonDown("Interact") && Time.timeScale != 0) // Currently set to E on the keyboard.
            {
                //print("YOU MAY PASS");
                GameObject.FindGameObjectWithTag("DoorNr").GetComponent<DoNotDestroy>().NameOfTheObject = NameOfTheExitObject; // set the exit object
               // GetComponent<AudioSource>().PlayOneShot(objectInteract);
                //SceneManager.LoadScene(SceneName); // load the next scene
                GetComponent<LoadScene>().LoadLevel(SceneName);

            }
            
        }
	}

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.layer == 10) // checks what layer the triggering object is and activates if it's the "Player" layer
        {
            gameObject.transform.GetChild(2).gameObject.SetActive(true);
            entryGrantet = true;
            uiCanvus.SetActive(true);
            GetComponent<AudioSource>().PlayOneShot(objectActive);
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.gameObject.layer == 10) // checks what layer the triggering object is and deactivates if it's the "Player" layer
        {
            gameObject.transform.GetChild(2).gameObject.SetActive(false);
            entryGrantet = false;
            uiCanvus.SetActive(false);

        }
    }

}

