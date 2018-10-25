using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TriggerObject : MonoBehaviour
{
    public string colliderTag;
    public string onEnter;
    public bool enterReceiver;

    public string onExit;
    public bool exitReceiver;

    public string whileColliding;
    public bool collidingReceiver;

    private void OnTriggerEnter(Collider other)
    {
        if (colliderTag == "")
            if (enterReceiver == false)
                gameObject.SendMessage(onEnter, SendMessageOptions.DontRequireReceiver);
            else
                gameObject.SendMessage(onEnter, SendMessageOptions.RequireReceiver);
        else
            if (enterReceiver == false && other.tag == colliderTag)
                gameObject.SendMessage(onEnter, SendMessageOptions.DontRequireReceiver);
            else if (other.tag == colliderTag)
                gameObject.SendMessage(onEnter, SendMessageOptions.RequireReceiver);
    }

    private void OnTriggerExit(Collider other)
    {
        if (exitReceiver == false)
            gameObject.SendMessage(onExit, SendMessageOptions.DontRequireReceiver);
        else
            gameObject.SendMessage(onExit, SendMessageOptions.RequireReceiver);
    }

    private void OnTriggerStay(Collider other)
    {
        if (collidingReceiver == false)
            gameObject.SendMessage(whileColliding, SendMessageOptions.DontRequireReceiver);
        else
            gameObject.SendMessage(whileColliding, SendMessageOptions.RequireReceiver);
    }
}
