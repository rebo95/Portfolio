using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Trigger_Tutorial_OpenLevel : MonoBehaviour
{

    public Sprite tutorialToSHow;
    private GameObject tutBox;
    private Button tutBoxButton;
    public GameObject UIToAnimate;


    bool boxOpen = false;
    // Use this for initialization

    void Start()
    {
        //Trigger is finding references in the canvas to store, then deactivating the tutorial box. There must be Canvas_Menu prefab in the scene hierarchy.
        tutBox = GameObject.FindGameObjectWithTag("Canvas_Main").transform.GetChild(3).gameObject;
        //tutBoxButton = tutBox.transform.GetChild(0).GetComponent<Button>();
        tutBox.SetActive(false);

    }

    //When player enters trigger
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.tag == "Player")
        {
            if (PlayerPrefs.GetInt("TriggerTutorialOpenLevel", 0) == 0)
            {
                PlayerPrefs.SetInt("TriggerTutorialOpenLevel", 1);

                //Activates tutorial box and displays text as input from trigger gameObject in inspector. Stops time.
                tutBox.SetActive(true);
                //tutBox.GetComponent<Image>().sprite = tutorialToSHow;
                //Adds button functionality to the button in the tutorial box.
                //tutBoxButton.onClick.AddListener(OKbutton);
                boxOpen = true;
                Time.timeScale = 0;
            }

        }
    }

    //Button function in tutorial box.
    public void OKbutton()
    {
        //Deactivate tutorial box and resume time.
        tutBox.SetActive(false);
        Time.timeScale = 1;
        //UIToAnimate.SetActive(true);
        //Destroy the trigger from the scene.
        Destroy(gameObject);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.anyKeyDown && boxOpen)
        {
            OKbutton();
        }
    }
}

