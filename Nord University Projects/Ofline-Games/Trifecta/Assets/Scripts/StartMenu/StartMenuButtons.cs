
using UnityEngine;
using UnityEngine.SceneManagement;

public class StartMenuButtons : MonoBehaviour {

    public void GoToOpenWorld()
    {
        
        PlayerPrefs.DeleteAll();
        PlayerPrefs.SetString("LastLoadedScene", "Tutorial");
        //SceneManager.LoadScene(1);
        GetComponent<LoadScene>().LoadLevel(PlayerPrefs.GetString("LastLoadedScene"));
    }

    public void ContinueGame()
    {
        GameObject.FindGameObjectWithTag("DoorNr").GetComponent<DoNotDestroy>().NameOfTheObject = PlayerPrefs.GetString("EntryPoint", "Tutorial"); // set the exit object
        GetComponent<LoadScene>().LoadLevel(PlayerPrefs.GetString("LastLoadedScene"));
    }

    public void StartFromLevel02()
    {
        PlayerPrefs.DeleteAll();
        // set the pp
        PlayerPrefs.SetString("LastLoadedScene", "Level02"); // Set startScene.
        PlayerPrefs.SetFloat("D01", 1); // unlock WallJump


        GetComponent<LoadScene>().LoadLevel(PlayerPrefs.GetString("LastLoadedScene"));


    }

    public void Starmenu()
    {
        GetComponent<LoadScene>().LoadLevel("StartMenu");
    }
}
