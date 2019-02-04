using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class LoadScene : MonoBehaviour {

    public Canvas LoadingCanvas;
     Image LoadingImage;


    public void LoadLevel(string SceneName)
    {
        Canvas LC = Instantiate(LoadingCanvas);
        LC.worldCamera = Camera.main;
        LoadingImage = LC.transform.GetChild(0).GetChild(0).GetChild(1).GetComponent<Image>();


        StartCoroutine(LoadAsync(SceneName));

    }

    IEnumerator LoadAsync(string SceneName)
    {
        PlayerPrefs.SetString("LastLoadedScene", SceneName);

        AsyncOperation AO =
            SceneManager.LoadSceneAsync(PlayerPrefs.GetString("LastLoadedScene"));

        while (!AO.isDone)
        {
            float progress = Mathf.Clamp01(AO.progress / 0.9f);
            // Update your progress
            LoadingImage.fillAmount = progress;

            yield return null;
        }
    }
}
