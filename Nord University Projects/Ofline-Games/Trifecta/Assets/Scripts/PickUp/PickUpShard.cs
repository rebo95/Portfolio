using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PickUpShard : MonoBehaviour {

    public int ShardGain = 1;

    public int theShardNr;

    public GameObject papa;
    private void Start()
    {
        //PlayerPrefs.DeleteAll();

        if (PlayerPrefs.GetInt(SceneManager.GetActiveScene().name + theShardNr.ToString(), 0) != 0)
        {
            Destroy(papa);
        }
    }

    public void OnTriggerEnter2D(Collider2D c)
    {
        if (c.tag == "Player")
        {

            int pp = PlayerPrefs.GetInt(SceneManager.GetActiveScene().name + theShardNr.ToString(), 0);

            if (pp == 0)
            {

                PlayerPrefs.SetInt(SceneManager.GetActiveScene().name + theShardNr.ToString(), 1);
                int p = PlayerPrefs.GetInt("SoulShards", 0);
                p = p + ShardGain;
                PlayerPrefs.SetInt("SoulShards", p);
                Destroy(papa);
            }
        }

    }
}
