using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpiritNewMovement : MonoBehaviour
{

    public int spiritLife = 100;

    [Header("Jump Stats")]
    [Range(10,40)]
    public float jumpSpeed = 20;


    // Getting varables
    Rigidbody2D rb;
    Animator anim;

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

    // magic
    [Header("Magic")]
    public bool MovePatform = false;

    [Space]
    public bool activatePlatform;


    public GameObject magicBulletKey;

    public float bulletVelX;
    public float bulletVelY;

    //public bool right = true;

    private GeneralPlayerMovement gpm;


    public bool OnMovablePlatform = false;

    public GameObject rspawner;
    public GameObject lspawner;
    public GameObject downSpawner;


    private void Start()
    {
        OnMovablePlatform = false;

        JumpableLayers = LayerMask.GetMask("Ground", "WallJump", "Default");

        // setting vars
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();

        gpm = GetComponent<GeneralPlayerMovement>();

        // setting abilities
        GiveAbbility();
    }

    float curVel;


    public void Update()
    {
        GroundCheck();
        MagicPower();




        //coyote time
        if (isGrounded)
        {
            curCoyoteTime = coyoteTime;

            // ready to jump again
            jumped = false;

            Jump(false);
        }

        else if (!isGrounded && curCoyoteTime > 0)
        {
            Jump(true);

            curCoyoteTime -= Time.deltaTime;
        }

        



        if (Input.GetButtonDown("AbilityB 02") && MovePatform)
        {
            anim.SetTrigger("Attack");

            //magicBulletKey.transform.position = new Vector2(this.transform.position.x, this.transform.position.y + 1);

            //bulletScript = magicBulletKey.GetComponent<BulletKey>();

            if (!OnMovablePlatform)
            {

                //float bulletVelX_ = 5.0f;
                if (!gpm.right)//will shoot to the left.
                {
                    ObjectPooler.instance.spawnFromPool("BulletKey", lspawner.transform.position, lspawner.transform.rotation);
                }
                //    bulletVelX_ = -bulletVelX;
                else //will shoot to the right.
                {
                    ObjectPooler.instance.spawnFromPool("BulletKey", rspawner.transform.position, rspawner.transform.rotation);
                   
                } /*bulletVelX_ = bulletVelX;*/

                    //bulletScript.SetVelY(0);
                    //bulletScript.SetVelX(bulletVelX_);

                    
                //ObjectPooler.instance.spawnFromPool("BulletKey", lspawner.transform.position, lspawner.transform.rotation);
            }
            else
            { 
                ObjectPooler.instance.spawnFromPool("BulletKey", downSpawner.transform.position, downSpawner.transform.rotation);
            }

            //Instantiate(magicBulletKey);
        }
    }


    public void GiveAbbility()
    {
        if (!MovePatform)
        {
            if (PlayerPrefs.GetInt("S01", 0) == 1)
            {
                MovePatform = true;
            }
        }
    }

    bool jumped;

    public void Jump(bool Coyoty)
    {
        // THE JUMP SIGNAL
        if (Input.GetButtonDown("Jump"))
        {
            // COYOTY TIME JUMP
            if (Coyoty && !jumped)
            {
                jumped = true;

                // PLAY THE ANIMATION
                anim.SetTrigger("Jump");

                // ACTIVTE THE JUMP
                rb.velocity = Vector2.up * jumpSpeed;

                curCoyoteTime = 0;

            }

            // SINGLE JUMP AKA GROUND JUMP
            else if (isGrounded && !jumped)
            {
                jumped = true;

                // PLAY THE ANIMATION
                anim.SetTrigger("Jump");

                // ACTIVTE THE JUMP
                rb.velocity = Vector2.up * jumpSpeed;
            }
        }
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
            isGrounded = true;
            anim.SetBool("isGrounded", true);


            Debug.DrawRay(new Vector2(transform.position.x, transform.position.y - hightOfTheRaycast), new Vector2(widthOfTheRaycast, 0), Color.green);
            Debug.DrawRay(new Vector2(transform.position.x, transform.position.y - hightOfTheRaycast), new Vector2(-widthOfTheRaycast, 0), Color.green);

        }
        else if (isGrounded)
        {
            isGrounded = false;
            anim.SetBool("isGrounded", false);
        }
    }


    /// MAGIC POWERS

    void MagicPower()
    {

        if (Input.GetButtonDown("AbilityB 01"))
        {
            anim.SetTrigger("GrowMagic");
            if (!activatePlatform)
                activatePlatform = true;
            else
                activatePlatform = false;
        }


    }

    private void OnEnable()
    {
        curCoyoteTime = 0;
        if (GameManager.instance != null)
        GameManager.instance.EnableSpiritLife();
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "MovablePlatform")
            OnMovablePlatform = true;
    }

    private void OnCollisionExit2D(Collision2D collision)
    {
        if(collision.gameObject.tag == "MovablePlatform")
            OnMovablePlatform = false;
    }

    public void damaged() {
        //spiritLife -= 5;
        GameManager.instance.spiritDamage();
    }


}
