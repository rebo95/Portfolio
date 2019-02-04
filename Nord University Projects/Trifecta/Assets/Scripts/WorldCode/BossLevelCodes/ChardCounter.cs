using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class ChardCounter : MonoBehaviour {

    public int StartShards;
    public int curShardCount;

    public GameObject ChardNrObject;
    Text ChardNrText;

    GeneralPlayerMovement GPM;
    int curChar = 4;

    //UI for 0 shards
    public GameObject shardUI;

    // UIForAbillityWheel
    //SpriteRenderer One;
    //SpriteRenderer Ten;
    public Image SwapNumbers;

    [Header("Images for UI nr")]
    public List<Sprite> Numbers = new List<Sprite>();

    bool outOfSwitches = false;

    // Use this for initialization
    void Start () {

        transform.GetChild(0).GetComponent<Canvas>().worldCamera = GameObject.FindGameObjectWithTag("MainCamera").GetComponent<Camera>();

        curShardCount = StartShards;

        GPM = GameObject.FindGameObjectWithTag("Player").GetComponent<GeneralPlayerMovement>();

        curChar = GPM.characterSelected;


        // assign one and ten
        GameObject HolderOfSpritRenderer = GameObject.FindGameObjectWithTag("AbilityWheel").transform.GetChild(0).gameObject;
        //One = HolderOfSpritRenderer.transform.GetChild(0).GetComponent<SpriteRenderer>();
        //Ten = HolderOfSpritRenderer.transform.GetChild(1).GetComponent<SpriteRenderer>();
        // assign the nr
        UpdateNumbers(curShardCount);
    }
	
	// Update is called once per frame
	void FixedUpdate () {

        if (curChar != GPM.characterSelected) // checks if the player have a new char activ
        {
            curChar = GPM.characterSelected;
            curShardCount -= 1;


            if (curShardCount <= -1)
            {
                outOfSwitches = true;
                // Disable everything!!!
                GPM.enabled = false; // turns off the GPM
                Time.timeScale = 0; // Time set to 0
                shardUI.SetActive(true); // activate the ui
                return;
            }

            // assign in the ui
            UpdateNumbers(curShardCount);
        }

    }

    public void UpdateNumbers(int switches)
    {

        // find the rounded nrs for the ui images
        //int one = switches - (switches / 10) * 10;
        //int ten = switches / 10;
        // set the up images
        //One.sprite = Numbers[one];
        //Ten.sprite = Numbers[ten];
        SwapNumbers.sprite = Numbers[switches];

    }

    public void Update()
    {
        if (outOfSwitches)
        {
            if (Input.anyKeyDown)
            {
                RestartScene();
            }
        }
    }

    public void RestartScene()
    {
        // activate everything
        Time.timeScale = 1;
        GPM.enabled = true;

        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }


}
