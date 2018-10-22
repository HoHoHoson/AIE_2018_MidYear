using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RandomScript : MonoBehaviour {
    [Range(1, 9000), Tooltip("aesrtfyghujik")]
    public float force = 10.0f;
    public float turnForce = 180.0f;
    [Range(0.5f, 9000)]
    public float fireRate = 0;
    public GameObject prefabMissile;

    private GameObject firePos;
    private float timer = 0;
    // Use this for initialization
    void Start ()
    {
        firePos = GameObject.Find("Muzzle");
        Debug.Assert(firePos);
    }
	
	// Update is called once per frame
	void Update ()
    {
        timer += Time.deltaTime;

        if (Input.GetKey(KeyCode.W))
            GetComponent<Rigidbody>().AddForce(transform.forward * force * Time.deltaTime, ForceMode.Impulse);
           
        if (Input.GetKey(KeyCode.S))
            GetComponent<Rigidbody>().AddForce(transform.forward * -force * Time.deltaTime, ForceMode.Impulse);

        if (Input.GetKey(KeyCode.D))
            GetComponent<Rigidbody>().AddTorque(transform.up * turnForce * Time.deltaTime, ForceMode.Impulse);
        
        if (Input.GetKey(KeyCode.A))
            GetComponent<Rigidbody>().AddTorque(transform.up * -turnForce * Time.deltaTime, ForceMode.Impulse);

        if (Input.GetKey(KeyCode.Space) && timer >= fireRate)
        {
            Quaternion r = firePos.transform.rotation;
            Vector3 pos = firePos.transform.position;
            pos += firePos.transform.up * 2.5f;

            GameObject obj = Instantiate(prefabMissile, pos,  r);
            timer = 0;
        }
    }       
}
