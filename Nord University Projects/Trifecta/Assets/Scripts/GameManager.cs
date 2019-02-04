using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour {

    public static GameManager instance;

    public int daughterlife = 6;
    public int fatherLife = 6;
    public int spiritLife = 6;

    public GameObject SpiritLifeContainer;
    public GameObject DaughterLifeContainer;
    public GameObject FatherLifeContainer;

    public GameObject youDie;

    public bool testingLifeResotore = false;
    public int testInitialLifes = 6;
    public bool testRecoveLive = false;


    public List<Image> wizzardList;
    private Stack<Image> lifesWizzardStack;
    private Stack<Image> lifesWizzardStackLost;
    //private Stack<Image> lifesStackLost;

    public List<Image> daughterdList;
    private Stack<Image> lifesDaughterStack;
    private Stack<Image> lifesDaughterStackLost;

    public List<Image> spiritList;
    private Stack<Image> lifesSpiritStack;
    private Stack<Image> lifesSpiritStackLost;

    // This manages the current character the player is using
    //int currentCharacter = 0;



    private void Awake()
    {
        instance = this;
        
    }

    void Start()
    {

        daughterlife = PlayerPrefs.GetInt("daughterLife", daughterlife);
        spiritLife = PlayerPrefs.GetInt("spiritLife", spiritLife);
        fatherLife = PlayerPrefs.GetInt("fatherLife", fatherLife);

        lifesWizzardStack = new Stack<Image>();
        lifesWizzardStackLost = new Stack<Image>();

        lifesSpiritStack = new Stack<Image>();
        lifesSpiritStackLost = new Stack<Image>();

        lifesDaughterStack = new Stack<Image>();
        lifesDaughterStackLost = new Stack<Image>();

        stackFiller();


        //get the current lifes sved between scenes


        //canvasAnimator = canvasCharacterImage.GetComponent<Animator>();
        ////abilitySelected.text = "Choosen Character " + currentCharacter;
        ////abilityExplanation.text = "Daughter can Jump by pressing 'Z'"; Maybe for monday 17/09/18 will be useful to use this
        //abilitySelected.text = "";
        //abilityExplanation.text = "";

        //if (youWin != null)
        //{
        //    youWin.enabled = false;

        //}
        //stackFiller();

        youDie.SetActive(false);
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetButtonDown("Restart"))
        {
            Time.timeScale = 1;
            //SceneManager.LoadScene(SceneManager.GetActiveScene().name);
            GetComponent<LoadScene>().LoadLevel(SceneManager.GetActiveScene().name);
        }

        if (testingLifeResotore) {
            testingRestoreLifes();
        }

        if (testRecoveLive)
        {
            recoverFatherLifes();
            testRecoveLive = false;
        }
    }
    public void missionComplete()
    {
        //if (youWin != null)
        //{
        //    youWin.enabled = true;

        //}
    }

    public void updateHUD(int nr) //change the image showed on the HUD
    {

        //switch (nr)
        //{
        //    case 0: // change to the girl
        //        canvasAnimator.Play("HUDGirl");
        //        break;
         
        //    case 1: // change to the warrior 
        //        canvasAnimator.Play("HUDWarrior");
        //        break;
        //    case 2://cahnge to the wizarld
        //        canvasAnimator.Play("HUDwizard");
        //        break;

        //}

    }

    void printCharacterInfo()
    {
        //string name;
        //string explanation;

        //switch (currentCharacter)
        //{
        //    case 0:
        //        name = "Daughter";
        //        explanation = "Daughter can Jump by pressing 'Z'";
        //        break;
        //    case 1:
        //        name = "Spirit of the forest";
        //        explanation = "Spirit of the forest can move heavy blocks by pressing 'Z'";
        //        break;
        //    case 2:
        //        name = "Father";
        //        explanation = "Father can reveal the darkest secrets by pressing 'Z'";
        //        break;
        //    default:
        //        name = "No character selected correctly";
        //        explanation = "Daughter can Jump by pressing 'Z'";
        //        break;
        //}

        //abilitySelected.text = "Choosen Character: " + name;
        //abilityExplanation.text = explanation;
    }
    
    private void checkLifes()
    {
        if (fatherLife <=0 || daughterlife <=0 || spiritLife <=0)
        {
            testingRestoreLifes();
            youDie.SetActive(true);
            Time.timeScale = 0.0f;
        }
    }

    public void fatherDamage()
    {
        //damaged();
        fatherLife--;
        updateFatherLife();
        checkLifes();
        PlayerPrefs.SetInt("fatherLife", fatherLife);
    }

    public void daughterDamage()
    {
        daughterlife--;
        updateDaughterLife();
        checkLifes();
        PlayerPrefs.SetInt("daughterLife", daughterlife);
    }

    public void spiritDamage()
    {
        spiritLife--;
        updateSpiritLife();
        checkLifes();
        PlayerPrefs.SetInt("spiritLife", spiritLife);
    }

    public void fatherRecover()
    {
        if (fatherLife<testInitialLifes) {
            fatherLife++;
            giveFatherALife();
            PlayerPrefs.SetInt("fatherLife", fatherLife);
        }
    }

    public void daughterRecover()
    {
        if (daughterlife < testInitialLifes)
        {
            daughterlife++;
            giveDaughterALife();
            PlayerPrefs.SetInt("daughterLife", daughterlife);
        }
    }

    public void spiritRecover()
    {
        if (spiritLife<testInitialLifes) {
            spiritLife++;
            giveSpiritALife();

            PlayerPrefs.SetInt("spiritLife", spiritLife);
        }
    }


    private void giveFatherALife()
    {
        Image heart;
        heart = lifesWizzardStackLost.Peek();
        heart.enabled = true;
        lifesWizzardStackLost.Pop();
        lifesWizzardStack.Push(heart);
    }

    private void giveDaughterALife()
    {
        Image heart;
        heart = lifesDaughterStackLost.Peek();
        heart.enabled = true;
        lifesDaughterStackLost.Pop();
        lifesDaughterStack.Push(heart);
    }

    private void giveSpiritALife()
    {
        Image heart;
        heart = lifesSpiritStackLost.Peek();
        heart.enabled = true;
        lifesSpiritStackLost.Pop();
        lifesSpiritStack.Push(heart);
    }

    void testingRestoreLifes()
    {
        fatherLife = spiritLife = daughterlife = testInitialLifes;
        PlayerPrefs.SetInt("fatherLife", fatherLife);
        PlayerPrefs.SetInt("daughterLife", daughterlife);
        PlayerPrefs.SetInt("spiritLife", spiritLife);
        testingLifeResotore = false;
    }


    private void stackFiller()
    {
        currentFatherLife();
        currentSpiritLife();
        currentDaughterLife();
        ////int size = wizzardList.Count;
        //////for (int i = 0; i < size; i++)
        //////{
        //////    lifesWizzardStack.Push(wizzardList[i]);
        //////}

        //////wizzardList.Clear();


        ////size = daughterdList.Count;
        ////for (int i = 0; i < size; i++)
        ////{
        ////    lifesDaughterStack.Push(daughterdList[i]);
        ////}

        ////daughterdList.Clear();



        ////size = spiritList.Count;
        ////for (int i = 0; i < size; i++)
        ////{
        ////    lifesSpiritStack.Push(spiritList[i]);
        ////}

        ////spiritList.Clear();
    }

    void updateFatherLife()
    {
        Image heart;
        heart = lifesWizzardStack.Peek();
        heart.enabled = false;
        lifesWizzardStack.Pop();
        lifesWizzardStackLost.Push(heart);
    }

    void updateDaughterLife()
    {
        Image heart;
        heart = lifesDaughterStack.Peek();
        heart.enabled = false;
        lifesDaughterStack.Pop();
        lifesDaughterStackLost.Push(heart);
    }


    void updateSpiritLife()
    {
        Image heart;
        heart = lifesSpiritStack.Peek();
        heart.enabled = false;
        lifesSpiritStack.Pop();
        lifesSpiritStackLost.Push(heart);
    }

    void recoverFatherLifes() {
        Image heart;
        heart = lifesWizzardStackLost.Peek();
        heart.enabled = true;
        lifesWizzardStackLost.Pop();
        lifesWizzardStack.Push(heart);
    }

    public void EnableDaughterLife()
    {
        //SpiritLifeContainer.SetActive(false);
        //DaughterLifeContainer.SetActive(true);
        //FatherLifeContainer.SetActive(false);
    }

    public void EnableFatherLife()
    {
        //SpiritLifeContainer.SetActive(false);
        //DaughterLifeContainer.SetActive(false);
        //FatherLifeContainer.SetActive(true);
    }

    public void EnableSpiritLife()
    {
        //SpiritLifeContainer.SetActive(true);
        //DaughterLifeContainer.SetActive(false);
        //FatherLifeContainer.SetActive(false);
    }

    public void resetScene2()
    {
        Time.timeScale = 1;
        SceneManager.LoadScene("Level02");
    }

    void currentFatherLife()
    {
        for (int i = 0; i < fatherLife; i++)
        {
            wizzardList[i].enabled = true;
            lifesWizzardStack.Push(wizzardList[i]);
        }

        for (int i = fatherLife; i<testInitialLifes; i++) {

            wizzardList[i].enabled = false;
            lifesWizzardStackLost.Push(wizzardList[i]);
        }
        wizzardList.Clear();
    }

    void currentDaughterLife()
    {
        for (int i = 0; i < daughterlife; i++)
        {
            daughterdList[i].enabled = true;
            lifesDaughterStack.Push(daughterdList[i]);
        }

        for (int i = daughterlife; i < testInitialLifes; i++)
        {

            daughterdList[i].enabled = false;
            lifesDaughterStackLost.Push(daughterdList[i]);
        }
        daughterdList.Clear();
    }

    void currentSpiritLife()
    {
        for (int i = 0; i < spiritLife; i++)
        {
            spiritList[i].enabled = true;
            lifesSpiritStack.Push(spiritList[i]);
        }

        for (int i = spiritLife; i < testInitialLifes; i++)
        {
            spiritList[i].enabled = false;
            lifesSpiritStackLost.Push(spiritList[i]);
        }
        spiritList.Clear();
    }


    public void instaKill()
    {
        fatherLife = 0;
        checkLifes();
    }


}
