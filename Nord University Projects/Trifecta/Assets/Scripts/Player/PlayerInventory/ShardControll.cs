using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ShardControll : MonoBehaviour {

    public int SoulShards;

    public bool RemovePP = false;

    Animator playerAnimator;

    [Header("should be assigned in the prefab")]
    public SpriteRenderer NrOne;
    public SpriteRenderer NrTen;

    public Canvas Canvas;

    [Header("Images for the numbers")]
    public List<Sprite> Numbers = new List<Sprite>();

    private void Start()
    {
        //PlayerPrefs.SetInt("SoulShards",57);

        playerAnimator = GameObject.FindGameObjectWithTag("Player").GetComponent<Animator>();

        Canvas.worldCamera = Camera.main; // set the camera

        if (RemovePP) // for play testing you can remove the soulshard count with this bool activ
        {
            PlayerPrefs.DeleteKey("SoulShards");
        }

        UpdateNumbers();


    }

    private void FixedUpdate()
    {
        UpdateNumbers();
    }

    public void UpdateNumbers () {
        SoulShards = PlayerPrefs.GetInt("SoulShards", 0);

        //playerAnimator.SetFloat("RemainingSwitches", SoulShards);

        // find the rounded nrs for the ui images
        int one = SoulShards - (SoulShards / 10) * 10;
        int ten = SoulShards/10;
        // set the up images
        NrOne.sprite = Numbers[one];
        NrTen.sprite = Numbers[ten];

    }

}
