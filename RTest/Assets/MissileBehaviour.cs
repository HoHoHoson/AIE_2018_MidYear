using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[RequireComponent(typeof(Rigidbody))]
public class MissileBehaviour : MonoBehaviour
{
    [Range(1, 60)]
    public float timeToDespawn = 5; 
    public float Force = 10;
    public GameObject entity;

    private Collider[] missileColliders;
    private Collider[] entityColliders;

    // Use this for initialization
    void Start ()
    {
        entityColliders = entity.GetComponentsInChildren<Collider>(true);
        missileColliders = GetComponentsInChildren<Collider>(true);

        if (entityColliders != null)
        {
            foreach (Collider m in missileColliders)
                foreach (Collider e in entityColliders)
                    Physics.IgnoreCollision(e, m, true);
        }
        
        GetComponent<Rigidbody>().AddForce(transform.up * Force, ForceMode.Impulse);
	}
	
	// Update is called once per frame
	void Update ()
    {
        Destroy(gameObject, timeToDespawn);
	}
}
