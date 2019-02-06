using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GeneralPlayerMovement : MonoBehaviour
{
    public Animator[] animat;


    [HideInInspector]
    public int Controls = 1;

    [Header("Daughter Stats")]
    [Range(1,20)]
    public float dSpeed;

    [Header("Spirit Stats")]
    [Range(1, 20)]
    public float sSpeed;

    [Header("Wizard Stats")]
    [Range(1, 20)]
    public float wSpeed;

    float curSpeed;

    //private Rigidbody2D rb; // a relic from when we used force to move the char
    [HideInInspector]
    public bool right = true;

    // A variable for each character to enable and disable each power
    private DaughterMovement c0Script;
    private FatherNewMovement c1Script;
    private SpiritNewMovement c2Script;

    private GameManager c3Script;

    private TestSpawner c4Script;

    // A variable for the animations
    Animator anim;
    //[HideInInspector]
    [Space]
    public int characterSelected = 1;// this variable will be used for the GameManager Getter "updateHUD" to change the HUD when Control = 0
    // Variable to rotate the PlayerFirepoint
    public bool changeDir = false;

    // A variable to change the color of the Player wen he changes the character
    //private MeshRenderer render;
    SpriteRenderer sR;


    // FOR THE OTHER CONTROLS
    //int curActivChar;


    // CANVAS
    GameObject AbilityWheel;
    public Animator WheelAnimator;


    //Gravity Control
    [Header("Jumping ARK")]
    public float gFourceDown = 4;
    public float gFourceUp = 3;
    // You don't get the gravity of this var
    [HideInInspector]
    public float velY;
    Rigidbody2D rb;

    [Header("Dead Zone for movement")]
    public float movementDeadZone = 0.1f;

    [Header("Char Speed")]
    public float MoveSpeed;
    [HideInInspector]
    public float SPD;

    [Header("colliding")]
    public LayerMask layers;

    // Prevent solution, I need to think about it. Pablo
    Vector2 startPosition;

    public void ChangeMovements(int move) // change movements
    {
        Controls = move;
        this.gameObject.SendMessage("Start");
    }
    // Use this for initialization
    void Awake()
    {
        characterSelected = PlayerPrefs.GetInt("CharNr", 1);

        // get rb
        rb = GetComponent<Rigidbody2D>();

        // sR
        sR = GetComponent<SpriteRenderer>();


        // THE HUD (AbilityWheel)
        AbilityWheel = GameObject.FindGameObjectWithTag("AbilityWheel");
        if (AbilityWheel != null)
        {
            WheelAnimator = AbilityWheel.GetComponent<Animator>();
        }
        // The scripts of the other characters
        c0Script = GetComponent<DaughterMovement>();
        c1Script = GetComponent<FatherNewMovement>();
        c2Script = GetComponent<SpiritNewMovement>();

        anim = GetComponent<Animator>();

        curSpeed = dSpeed;

        changeChar(characterSelected);

        lastChar = characterSelected;

        startPosition = gameObject.transform.position;
    }
    void Update() // used to get the player input since they don't live in frames
    {
        ChangeCharacter();
    }
    // Update for physics engine
    void FixedUpdate()
    {
        MoveSpeed = Input.GetAxis("Horizontal"); // for animation

        GeneralMovement();
        GravityControl();
    }
	// General movement of the player
	private float doubtTimer;
	public GameObject doubter;
	void GeneralMovement()
	{
		if (Input.GetKeyDown("x"))
		{
			doubtTimer = 5f;
		}
		if (Input.GetKey("x"))
		{
			doubtTimer -= Time.deltaTime;
			if (doubtTimer < 0)
			{
				doubtTimer = 9999999999999999f;
				doubter.SetActive(true);
				Debug.Log("Doubt");

			}
		}
		if (Input.GetKeyUp("x"))
		{
			doubtTimer = 0f;
			doubter.SetActive(false);
		}

		if (Input.GetKeyDown("x")){
			Debug.Log("Doubt");
		}
        if (Input.GetAxis("Horizontal") != 0)
        {
            if (Input.GetAxis("Horizontal") > 0 && !right) // goes right
            {
                Flip();
                //right = true;
                sR.flipX = false;

                RaycastHit2D rightWall = Physics2D.Raycast(new Vector2(transform.position.x + 0.5f, transform.position.y + 1f), Vector2.down, 0.5f);
                Debug.DrawRay(new Vector2(transform.position.x + 0.5f, transform.position.y + 1f), new Vector2(0, -0.5f), Color.green);
                
                if (rightWall)
                {
                    if (rightWall.collider.gameObject.layer == 12 || rightWall.collider.gameObject.layer == 13)
                    {
                        return;
                    }
                }
            }
            if (Input.GetAxis("Horizontal") < 0 && right) // goes left
            {
                Flip();
                //right = false;
                sR.flipX = true;

                RaycastHit2D leftWall = Physics2D.Raycast(new Vector2(transform.position.x - 0.5f, transform.position.y + 1f), Vector2.down, 0.5f);
                Debug.DrawRay(new Vector2(transform.position.x - 0.5f, transform.position.y + 1f), new Vector2(0, -0.5f), Color.green);
                if (leftWall)
                {
                    if (leftWall.collider.gameObject.layer == 12 || leftWall.collider.gameObject.layer == 13)
                    {
                        return;
                    }
                }
                //if (c2Script.enabled)
                //{
                //    c2Script.changeShotDirecctio(-1);
                //}
            }

            if (Input.GetAxis("Horizontal") <= movementDeadZone && Input.GetAxis("Horizontal") >= -movementDeadZone)
            {
                return;
            }
            SPD = curSpeed * Input.GetAxis("Horizontal"); // set spd to the curspeed and dir the player is walking
            anim.SetFloat("X Movement", SPD); // set the animator x movement. ;) 

            transform.position = new Vector2(transform.position.x + SPD * Time.deltaTime, transform.position.y); // moving the char
        }
        else if (SPD != 0) // set things to 0 m8 ;) 
        {
            SPD = 0;
            anim.SetFloat("X Movement", SPD); // set the animator x movement. ;) 
        }
    }

    void ChangeCharacter()
    {
        // the player controls where the player change who they are by pressing X Y B on the controller || A S D on keyboard
        if (Input.GetButtonDown("Girl"))
        {
            characterSelected = 0;
            PlayerPrefs.SetInt("CharNr", characterSelected);
            changeChar(characterSelected);

            curSpeed = dSpeed;
        }
        else if (Input.GetButtonDown("Spirit"))
        {
            characterSelected = 2;
            PlayerPrefs.SetInt("CharNr", characterSelected);
            changeChar(characterSelected);

            curSpeed = sSpeed;
        }
        else if (Input.GetButtonDown("OldMan"))
        {
            characterSelected = 1;
            PlayerPrefs.SetInt("CharNr", characterSelected);
            changeChar(characterSelected);

            curSpeed = wSpeed;
        }
        if (AbilityWheel != null)
        {
            animat = AbilityWheel.GetComponentsInChildren<Animator>();
            foreach (Animator item in animat)
            {
                //print(item);
                item.SetInteger("Character", characterSelected);
            }

            //WheelAnimator.SetInteger("Character", characterSelected); // change the hud wheel
        }
        //the Switch Movement where the player changes char with LB and RB on the controller
        if (Input.GetButtonDown("RightButton"))
        {
            if (characterSelected != 2)
            {
                characterSelected += 1;
            }
            else
            {
                characterSelected = 0;
            }
            PlayerPrefs.SetInt("CharNr", characterSelected);
            changeChar(characterSelected);
        }
        if (Input.GetButtonDown("LeftButton"))
        {
            if (characterSelected != 0)
            {
                characterSelected -= 1;
            }
            else
            {
                characterSelected = 2;
            }
            PlayerPrefs.SetInt("CharNr", characterSelected);
            changeChar(characterSelected);
        }
    }
    int lastChar;
    void changeChar(int nr) // just an function made to make it clearer how the switching happens
    {
        anim.SetFloat("Char_Last", lastChar);
        anim.SetInteger("Char", nr);
        anim.SetTrigger("Char_Change");
        lastChar = nr;

        //WheelAnimator.SetFloat("Char_Last", WheelAnimator.GetInteger("Character"));
        //WheelAnimator.SetTrigger("Char_Change");

        switch (nr)
        {
            case 0: // the girl
                //anim.Play("Girl");
                c0Script.enabled = true;
                c1Script.enabled = false;
                c2Script.enabled = false;
                curSpeed = dSpeed;
                break;
            case 1: // the old man
                    //anim.Play("Wizard");
                c0Script.enabled = false;
                c1Script.enabled = true;
                c2Script.enabled = false;

                curSpeed = wSpeed;
                break;
            case 2: // the spirit
                    //anim.Play("Warrior");
                c0Script.enabled = false;
                c1Script.enabled = false;
                c2Script.enabled = true;
                curSpeed = sSpeed;
                break;
            default:
                break;
        }
        if (AbilityWheel != null)
        {
            animat = AbilityWheel.GetComponentsInChildren<Animator>();

            foreach (Animator item in animat)
            {
                item.SetInteger("Character", characterSelected);
            }

            //WheelAnimator.SetInteger("Character", characterSelected); // change the hud wheel
        }
    }
    
    void GravityControl()
    {
        velY = rb.velocity.y;
        anim.SetFloat("Y_Vel", velY); // down
        if (velY < 0) 
        {
            anim.SetBool("Jump", false);
            anim.SetBool("DoubleJump", false);
            if (velY > -20)
            {
                rb.gravityScale = gFourceDown;

            }
            else
            {
                rb.gravityScale = 0;
            }
        }
        else 
        {
            rb.gravityScale = gFourceUp;
        }
    }
    void Flip()
    {
        right = !right;
        changeDir = true;
    }


    public void touchedByEnemy(float dir, int pot)
    {
            rb.AddForce(new Vector2(-dir * 500, pot * 500));
    }

    public void Damaged()
    {
        gameObject.GetComponent<SpriteRenderer>().color = Color.red;
        Invoke("returnNormalState", 0.3f);
    }

    private void returnNormalState()
    {
        gameObject.GetComponent<SpriteRenderer>().color = Color.white;
    }


    public Vector2 getStartPosition()
    {
        return startPosition;
    }
}
