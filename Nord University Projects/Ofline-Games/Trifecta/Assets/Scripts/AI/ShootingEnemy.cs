using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShootingEnemy : MonoBehaviour
{
    ObjectPooler objectPooler;

    public Transform FirePoint;
    public float fireRate = 2.0f;
    private float fireTimer;
    public bool Facing_Right;

    Animator anim;

    // Use this for initialization
    void Start()
    {
        objectPooler = ObjectPooler.instance;
        fireTimer = fireRate;

        anim = GetComponent<Animator>();

        if (!Facing_Right)
            Flip();


        StartCoroutine( Shoot()); // Start shooting
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    // Script with the shoot logic
    IEnumerator Shoot()
    {

        while (true)
        {
            yield return new WaitForSeconds(fireRate); // waiting for the fire rate
            anim.SetTrigger("Shooting"); // tell the animation to start

            // wait to spawn the bullet
            yield return new WaitForSeconds(0.5f);
            objectPooler.spawnFromPool("Turret_Enemy_Bullets", FirePoint.transform.position, FirePoint.transform.rotation);
        }


        //fireTimer -= Time.deltaTime;
        //if (fireTimer <= 0)
        //{
        //    anim.SetTrigger("Shooting");
        //    objectPooler.spawnFromPool("Turret_Enemy_Bullets", FirePoint.transform.position, FirePoint.transform.rotation);
        //    fireTimer = fireRate;
        //}

    }

    private void Flip()
    {
        transform.Rotate(0f, 180f, 0f);
    }


    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "PlayerBullet")
            Destroy(gameObject);
    }
}
