using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PopUpSystem : MonoBehaviour
{
    //Hold the message text.
    public GameObject Message;

    //Message pops up when the player collides with the detection hitbox.
    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "Player")
        {
            Message.SetActive(true);
        }
    }

    //Message disappears when the player leaves the detection hitbox.
    private void OnTriggerExit(Collider other)
    {
        if(other.gameObject.tag == "Player")
        {
            Message.SetActive(false);
        }
    }
}