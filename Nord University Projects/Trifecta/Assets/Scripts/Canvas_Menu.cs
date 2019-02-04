using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Canvas_Menu : MonoBehaviour {

    public bool isPaused;
    public GameObject Menu;
    public GameObject OptionsMenu;

    //This script is a preliminary script for handling menus in the game. Please update with more efficient code if you can.
	
	void Start () {
        //Find neccessary gameobjects (menu items) at start of scene. Need a reference to them to be able to activate/deactivate.
        Menu = gameObject.transform.GetChild(0).gameObject;
        OptionsMenu = gameObject.transform.GetChild(1).gameObject;
        //Deactivate Menu items at start of scene.
        Menu.SetActive(false);
        OptionsMenu.SetActive(false);

        isPaused = false;
	}
    
    //Button function that resumes the game. Same as if pressing escape key.
    public void Resume()
    {
        Debug.Log("Resume button was pressed!");
        isPaused = false;
        Time.timeScale = 1;
        Debug.Log("Time.timeScale: " + Time.timeScale);
        //Activate the menu options.
        Menu.SetActive(false);
    }
    //Button function for restarting the scene/level.
    public void Restart()
    {
        Time.timeScale = 1;
        var currentScene = SceneManager.GetActiveScene().name;
        SceneManager.LoadScene(currentScene);     
    }
    //Button function for opening the options menu
    public void Options()
    {
        OptionsMenu.SetActive(true);
    }
    //Button function for quiting the application.
    public void Quit()
    {
        Application.Quit();
    }
    
    //We need to update the 2 "Input" buttons in Options to select a controller scheme and go back to Menu!
    public void Input1()
    {
        print("1");

        //Code for selecting the input 1 here.
        GameObject player = GameObject.FindGameObjectWithTag("Player");
        GeneralPlayerMovement gpm = player.GetComponent<GeneralPlayerMovement>();
        gpm.ChangeMovements(0);
    }
    public void Input2()
    {
        print("2");
        //Code for selecting the input 2 here.
        GameObject player = GameObject.FindGameObjectWithTag("Player");
        GeneralPlayerMovement gpm = player.GetComponent<GeneralPlayerMovement>();
        gpm.ChangeMovements(1);

    }


    void Update () {

        
        if (Input.GetButtonDown("Cancel") ) //"Cancel" is Unity talk for "Escape" button
        {
            //These two "if" statements allow the user to pause/unpuase the game just by pressing "Escape" key on the keyboard. Find similar input for controller.
            if (isPaused == false)
            {
                Debug.Log("Escape key was pressed!");
                isPaused = true;
                Time.timeScale = 0;
                Debug.Log("Time.timeScale: " + Time.timeScale);
                //Activate the menu options.
                Menu.SetActive(true);
            }
            else if (isPaused == true)
            {
                Debug.Log("Escape key was pressed!");
                isPaused = false;
                Time.timeScale = 1;
                Debug.Log("Time.timeScale: " + Time.timeScale);
                //Activate the menu options.
                Menu.SetActive(false);
            }
        }

	}
}
