using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PersistentSceneScript : MonoBehaviour {


    void Awake() // only happens when the object is in the scene from before
    {
        GameObject[] theObject;
        theObject = GameObject.FindGameObjectsWithTag("DoNotDestroy"); // find all the objects

        DontDestroyOnLoad(this.gameObject); // don't destroy this object

        if (theObject.Length != 0) // check if theres more then one object
        {
            for (int i = 0; i < theObject.Length; i++)
            {
                if (i == 0)
                {
                    // just checks if its the first object of the list
                }
                else
                {
                    Destroy(theObject[i]);// destroy everything else

                }
            }
        }
    }
}
