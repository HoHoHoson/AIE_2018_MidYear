using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RandomScript : MonoBehaviour {
    [Range(1.0f, 500.0f), Tooltip("This is a tooltip")]
    public float force = 10.0f;
    [Range(1.0f, 360.0f)]
    public float turnDegrees = 180.0f;
    [Range(0.5f, 10.0f)]
    public float fireRate = 0;
    public GameObject prefabMissile;

    private GameObject firePos;
    private float timer = 0;
    // Use this for initialization
    void Start ()
    {
        firePos = transform.GetChild(0).gameObject;
        Debug.Assert(firePos);
    }
	
	// Update is called once per frame
	void Update ()
    {
        var rb = GetComponent<Rigidbody>();
        timer += Time.deltaTime;

        if (Input.GetKey(KeyCode.W))
            rb.velocity += gameObject.transform.forward * force * Time.deltaTime;
           
        if (Input.GetKey(KeyCode.S))
            rb.velocity += gameObject.transform.forward * -force * Time.deltaTime;

        if (Input.GetKey(KeyCode.D))
            rb.angularVelocity += new Vector3(0, turnDegrees * Time.deltaTime, 0);

        if (Input.GetKey(KeyCode.A))
            rb.angularVelocity += new Vector3(0, -turnDegrees * Time.deltaTime, 0);

        if (Input.GetKey(KeyCode.LeftArrow))
            rb.angularVelocity += new Vector3(0, turnDegrees * Time.deltaTime, 0);

        if (Input.GetKey(KeyCode.RightArrow))
            rb.angularVelocity += new Vector3(0, -turnDegrees * Time.deltaTime, 0);

        if (Input.GetKey(KeyCode.Space) && timer >= fireRate)
        {
            Quaternion r = firePos.transform.rotation;
            Vector3 pos = firePos.transform.position;
            r *= Quaternion.Euler(90, 0, 0);
            //pos += firePos.transform.up * 2.5f;
            
            Instantiate(prefabMissile, pos,  r);
            timer = 0;
        }
    }       
}
