using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class MissileBehaviour : MonoBehaviour
{
    [Range(1, 60)]
    public float timeToDespawn = 5; 
    public float Force = 10;

	// Use this for initialization
	void Start ()
    {
        GetComponent<Rigidbody>().AddForce(transform.up * Force, ForceMode.Impulse);
	}
	
	// Update is called once per frame
	void Update ()
    {
        Destroy(gameObject, timeToDespawn);
	}
}
