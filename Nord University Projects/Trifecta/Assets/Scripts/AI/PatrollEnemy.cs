using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PatrollEnemy : MonoBehaviour {

    // Use this for initialization
    public Transform viewOrigin;
    public Transform feetOrigin;
    public float viewRange;
    public float feetRange;
    public float vel;
    private Vector2 dir = new Vector2(1, 0);

    private Rigidbody2D rb;
    //private ObjectPooler objectPooler = ObjectPooler.instance;

    public int life = 3;

    public float multiplier = 0;

    //private BoxCollider2D myOwnCollider



    void Start () {
        rb = GetComponent<Rigidbody2D>();
    }
	
	// Update is called once per frame
	void Update () {

        Debug.DrawRay(viewOrigin.position, dir*viewRange);
        Debug.DrawRay(feetOrigin.position, dir * feetRange);

        RaycastHit2D viewHit = Physics2D.Raycast(viewOrigin.position, dir , viewRange);
        RaycastHit2D feetHit = Physics2D.Raycast(feetOrigin.position, dir, feetRange);

        if (viewHit)
        {
            if(viewHit) // here are going to be the conditions if we want another behaviour for the enemy it it collides with another object
            {
                Flip();
                vel = -vel;
                dir = -dir;
            }
        }

        if (!feetHit)
        {
            Flip();
            vel = -vel;
            dir = -dir;
        }

        if (viewHit)
        {
            if(viewHit.collider.gameObject.tag == "Player")
            {


                if (viewHit.collider.gameObject.GetComponent<SpiritNewMovement>().enabled)
                {
                    viewHit.collider.gameObject.GetComponent<SpiritNewMovement>().damaged();
                }
                else if (viewHit.collider.gameObject.GetComponent<DaughterMovement>().enabled)
                {
                    viewHit.collider.gameObject.GetComponent<DaughterMovement>().damaged();
                }
                else if (viewHit.collider.gameObject.GetComponent<FatherNewMovement>().enabled)
                {
                    viewHit.collider.gameObject.GetComponent<FatherNewMovement>().damaged();
                }

                viewHit.collider.gameObject.GetComponent<GeneralPlayerMovement>().touchedByEnemy(transform.localScale.x/Mathf.Abs(transform.localScale.x), 1);
                viewHit.collider.gameObject.GetComponent<GeneralPlayerMovement>().Damaged();
            }
        }
	}

    void FixedUpdate()
    {
        rb.velocity = new Vector2(vel, rb.velocity.y );
    }

    void Flip()
    {
        Vector3 objectScale = transform.localScale;
        objectScale.x = -objectScale.x;
        transform.localScale = objectScale;
    }

    private void OnCollisionEnter2D(Collision2D collision)
    {
        if(collision.gameObject.tag == "Player")
        {
            collision.gameObject.GetComponent<GeneralPlayerMovement>().touchedByEnemy(transform.localScale.x / Mathf.Abs(transform.localScale.x),2);
            collision.gameObject.GetComponent<GeneralPlayerMovement>().Damaged();

            if (collision.gameObject.GetComponent<SpiritNewMovement>().enabled)
            {
                collision.gameObject.GetComponent<SpiritNewMovement>().damaged();
            }
            else if (collision.gameObject.GetComponent<DaughterMovement>().enabled)
            {
                collision.gameObject.GetComponent<DaughterMovement>().damaged();
            }
            else if (collision.gameObject.GetComponent<FatherNewMovement>().enabled)
            {
                collision.gameObject.GetComponent<FatherNewMovement>().damaged();
            }
        }

        if(collision.gameObject.tag == "PlayerBullet")
        {
            
            life--;
            
            multiplier = collision.gameObject.transform.rotation.y;
            if (multiplier != 0)
                multiplier = -1;
            else multiplier = 1;

            rb.AddForce(new Vector2(multiplier * 3000, 200));
            Damaged();

            checkDead();
        }
    }

    private void checkDead()
    {
        if (life <= 0)
        {
            gameObject.SetActive(false);
        }
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
}
