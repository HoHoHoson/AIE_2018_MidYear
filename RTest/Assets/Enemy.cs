using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class Enemy : MonoBehaviour
{
    public float speed = 0;
    public GameObject target;

    private Vector3 dir;
    // Use this for initialization
    void Start()
    {
        //target = GameObject.Find("Player");
    }

    // Update is called once per frame
    void Update()
    {
        dir = target.transform.position - transform.position;
        dir = dir.normalized;
        GetComponent<Rigidbody>().AddForce(dir * speed * Time.deltaTime, ForceMode.Impulse);
    }

    public void Die()
    {
        Destroy(gameObject);
    }
}
