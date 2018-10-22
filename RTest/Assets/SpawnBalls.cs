using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnBalls : MonoBehaviour {
    [Range(0.5f, 100.0f)]
    public float spawnRate = 1;
    public GameObject spawnItem;

    private float timer = 0;
	// Use this for initialization
	void Start () {

	}
	
	// Update is called once per frame
	void Update ()
    {
        timer += Time.deltaTime;
		if (timer >= spawnRate)
        {
            timer = 0;
            Instantiate(spawnItem, gameObject.transform);
        }
    }
}
