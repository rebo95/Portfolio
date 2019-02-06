using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Trigger_Dialogue : MonoBehaviour {

    private GameObject player;
    public Text floatingText;
    private GameObject TextBackground;
    public DialogColor_Class[] dialogueList;

	// Use this for initialization
	void Start () {
        //Getting references
        player = GameObject.FindGameObjectWithTag("Player");
        floatingText = player.transform.GetChild(0).transform.GetChild(1).GetComponent<Text>();
        TextBackground = player.transform.GetChild(0).transform.GetChild(0).gameObject;
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        //Starting coroutine on trigger enter.
        if(collision.tag == "Player")
        {
            StartCoroutine("DisplayTexts");
        }
    }
    
    //Coroutine for displaying messages in the trigger's public strings one at a time with a delay.
    IEnumerator DisplayTexts()
    {
        gameObject.GetComponent<BoxCollider2D>().enabled = false;
        foreach(DialogColor_Class message in dialogueList)
        {
            TextBackground.SetActive(true);
            floatingText.text = message.text;
            switch (message.talker)
            {
                case DialogColor_Class.WhoTalking.Anya:
                    Color anyaColor = new Color();
                    //Copy desired color with hex string after the "#"
                    ColorUtility.TryParseHtmlString("#D41515", out anyaColor);
                    floatingText.color = anyaColor;
                    
                    break;
                case DialogColor_Class.WhoTalking.Brumund:
                    floatingText.color = Color.green;
                    break;
                case DialogColor_Class.WhoTalking.Viraya:
                    Color virayaColor = new Color();
                    //Copy desired color with hex string after the "#"
                    ColorUtility.TryParseHtmlString("#71009A", out virayaColor);
                    floatingText.color = virayaColor;
                    break;
                default:
                    break;
            }
            yield return new WaitForSeconds(5);
        }
        
        yield return null;
        //Reset floating text over player and destroy trigger.
        floatingText.text = "";
        TextBackground.SetActive(false);
        Destroy(gameObject);

    }

    // Update is called once per frame
    void Update () {
		
	}
}
