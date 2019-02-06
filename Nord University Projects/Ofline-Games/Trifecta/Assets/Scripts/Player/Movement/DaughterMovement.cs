using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DaughterMovement : MonoBehaviour
{
    [Header("Jump Stats")]
    [Range(10f,40f)]
    public float jumpSpeed = 20;

    [Header("Jump without ground")]
    [Range(10f, 40f)]
    public float DoubleJumpSpeed = 12;

    public int airJumpCount = 1;
    int curAirJumpCount;

    // Getting varables
    Rigidbody2D rb;
    Animator anim;
    SpriteRenderer SR;

    // Checking if it's grounded
    [Space]
    public bool isGrounded = false;

    [Header("Raycasts")]
    public float hightOfTheRaycast = 0.2f;
    public float widthOfTheRaycast = 0.15f;
     LayerMask JumpableLayers;

    [Space]
    public float yVel;

    [Space]
    public float coyoteTime = 0.2f;
    float curCoyoteTime;
    bool jumping = false;

    [Header("Wall Jump")]
    public bool wallJump = false;
    public float PushFromTheWall = 10;
    public float PushUpFromTheWall = 15;
    public float wallStcik = 6;
    public float wallSlide = -8;
    public bool doubleJumpAfterWall = true;

    public int dauhgterLife = 100;



    public void Start()
    {
        JumpableLayers = LayerMask.GetMask("Ground", "WallJump", "Default");
        
        // setting vars
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
        SR = GetComponent<SpriteRenderer>();

        // setting abilities
        GiveAbbility();
    }

    float curVel;

    public void GiveAbbility()
    {
        if (!wallJump)
        {
            if (PlayerPrefs.GetInt("D01", 0) == 1)
            {
                wallJump = true;
            }
        }
    }

    public void Update()
    {
        if (wallJump)
        {
            // checks if the player is in the air
            if (!isGrounded)
            {
                // raycasts to check for walls

                RaycastHit2D rightcheck = Physics2D.Raycast(new Vector2(transform.position.x + 0.4f, transform.position.y + 1),
                    Vector2.right, 0.1f);

                Debug.DrawRay(new Vector2(transform.position.x + 0.4f, transform.position.y + 1),
                    new Vector2(0.1f, 0), Color.cyan);

                RaycastHit2D leftcheck = Physics2D.Raycast(new Vector2(transform.position.x - 0.4f, transform.position.y + 1),
                Vector2.right, -0.1f);

                Debug.DrawRay(new Vector2(transform.position.x - 0.4f, transform.position.y + 1),
                    new Vector2(-0.1f, 0), Color.cyan);

                if (leftcheck)
                {
                    if (leftcheck.collider.gameObject.layer == 13)
                    {
                        SR.flipX = false;

                        // animator bool
                        anim.SetBool("WallSlide", true);

                        if (Input.GetButtonDown("Jump"))
                        {
                            anim.SetTrigger("Jump");
                            print("PLAYER Wall JUMPED");
                            //PAO.Jump = true;
                            jumping = true;

                            if (doubleJumpAfterWall)
                            {
                                curAirJumpCount = airJumpCount;
                            }

                            rb.velocity = new Vector2(PushFromTheWall, PushUpFromTheWall);
                            
                            
                            return;
                        }
                        else if (rb.velocity.y < -2)// slide
                        {
                            rb.velocity = new Vector2(-wallStcik, wallSlide);
                            // animator bool
                            anim.SetBool("WallSlide", true);
                        }
                    }
                    else
                    {
                        // animator bool
                        anim.SetBool("WallSlide", false);
                    }
                }

                if (rightcheck)
                {
                    if (rightcheck.collider.gameObject.layer == 13)
                    {
                        SR.flipX = true;

                        anim.SetBool("WallSlide", true);
                        if (Input.GetButtonDown("Jump"))
                        {
                            anim.SetTrigger("Jump");

                            //PAO.Jump = true;
                            jumping = true;


                            if (doubleJumpAfterWall)
                            {
                                curAirJumpCount = airJumpCount;
                            }

                            rb.velocity = new Vector2(-PushFromTheWall, PushUpFromTheWall);

                            return;
                        }
                        else if (rb.velocity.y < -2)// slide
                        {
                            rb.velocity = new Vector2(wallStcik, wallSlide);
                            anim.SetBool("WallSlide", true);

                        }
                    }
                    else
                    {
                        // animator bool
                        anim.SetBool("WallSlide", false);
                    }// wall slide animator
                }// check tyhe wall on the right side

                if (!rightcheck && !leftcheck)
                {
                    anim.SetBool("WallSlide", false);
                }
            }// check if player is grounded

        }// Check if wall jumping is Activ

        GroundCheck();

        //coyote time
        if (isGrounded)
        {
            curAirJumpCount = airJumpCount;
            curCoyoteTime = coyoteTime;
            jumped = false;

            
        }

        else if (!isGrounded && curCoyoteTime > 0)
        {
            Jump(true);
            curCoyoteTime -= Time.deltaTime;
            return;
        }



        Jump(false);


    }

    bool jumped;
    public void Jump(bool Coyoty)
    {
        // THE JUMP SIGNAL
        if (Input.GetButtonDown("Jump"))
        {
            // COYOTY TIME JUMP
            if (curAirJumpCount != 0 && Coyoty && !jumped)
            {
                jumped = true;

                // PLAY THE ANIMATION
                anim.SetTrigger("Jump");

                // ACTIVTE THE JUMP
                rb.velocity = Vector2.up * jumpSpeed;

                curCoyoteTime = 0;

            }

            // SINGLE JUMP AKA GROUND JUMP
            else if (curAirJumpCount >= 0 && isGrounded && !jumped)
            {
                jumped = true;

                // PLAY THE ANIMATION
                anim.SetTrigger("Jump");

                // ACTIVTE THE JUMP
                rb.velocity = Vector2.up * jumpSpeed;
            }


            // DOUBLE JUMP AKA AIR JUMP
            else if (curAirJumpCount != 0)
            {
                // REMOVE A AIR JUMP
                curAirJumpCount -= 1;

                // PLAY THE ANIMATION
                anim.SetTrigger("DoubleJump");

                // ACTIVTE THE JUMP
                rb.velocity = Vector2.up * DoubleJumpSpeed;
            }
            
        }
        

        if (false)
        {
            //// Jumping
            //if (Input.GetButtonUp("Jump") && jumping == true)// && curAirTime > 0) // jump over
            //{
            //    curAirTime = 0;
            //    rb.velocity = new Vector2(rb.velocity.x, rb.velocity.y / 4);

            //    jumping = false;

            //}
            //else if (Input.GetButtonDown("Jump") && curCoyoteTime > 0) // take Off
            //{
            //    jumping = true;
            //    curCoyoteTime = 0;

            //    curVel = jumpSpeed; // set the vel

            //    rb.velocity = new Vector2(rb.velocity.x, curVel); // add the starting force

            //    curAirTime = airTime; // set how long the button press will be for

            //    anim.SetTrigger("Jump");
            //    print("PLAYER JUMPED");

            //    return;
            //}
            //else if (Input.GetButton("Jump") && curAirTime > 0) // In The Air
            //{
            //    curAirTime -= Time.deltaTime;

            //    curVel = curVel - Time.deltaTime * 20;

            //    rb.velocity = new Vector2(rb.velocity.x, curVel);
            //    //anim.SetBool("Jump", false);
            //    //anim.SetBool("DoubleJump", false);


            //    return;
            //}
            ////////////////////////////////////////////////////////// X2!!!!
            //if (Input.GetButtonDown("Jump") && curAirJumpCount > 0) // checks if the player tries to jump in the air
            //{
            //    curAirJumpCount -= 1;

            //    jumping = true;

            //    curVel = DoubleJumpSpeed; // set the vel

            //    rb.velocity = new Vector2(rb.velocity.x, curVel); // add the starting force

            //    curAirTime = DoubleJumpAirTime; // set how long the button press will be for

            //    anim.SetTrigger("DoubleJump");



            //}
        } // old jumps
    }

    

    public void FixedUpdate()
    {
        yVel = rb.velocity.y;

    }

    public void GroundCheck()
    {
        // check if player is grounded 
        RaycastHit2D hitRight = Physics2D.Raycast(new Vector2(transform.position.x, transform.position.y - hightOfTheRaycast), new Vector2(1, 0), widthOfTheRaycast, JumpableLayers/*Ignores the player layer*/);
        RaycastHit2D hitLeft = Physics2D.Raycast(new Vector2(transform.position.x, transform.position.y - hightOfTheRaycast), new Vector2(-1, 0), widthOfTheRaycast, JumpableLayers/*Ignores the player layer*/);


        

        if (hitLeft || hitRight)
        {
            Debug.DrawRay(new Vector2(transform.position.x, transform.position.y - hightOfTheRaycast), new Vector2(widthOfTheRaycast, 0), Color.green);
            Debug.DrawRay(new Vector2(transform.position.x, transform.position.y - hightOfTheRaycast), new Vector2(-widthOfTheRaycast, 0), Color.green);

            isGrounded = true;
            anim.SetBool("isGrounded", true);
            anim.SetBool("WallSlide", false);

        }
        else if (isGrounded)
        {

            isGrounded = false;
            anim.SetBool("isGrounded", false);

        }
    }

    private void OnEnable()
    {
        curCoyoteTime = 0;
        if (GameManager.instance != null)
            GameManager.instance.EnableDaughterLife();
    }

    public void damaged()
    {
        //dauhgterLife -= 5;
        GameManager.instance.daughterDamage();
    }

}