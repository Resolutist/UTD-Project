using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveCamera : MonoBehaviour
{
    //Hold the camera position.
    public Transform cameraPosition;

    //Update the position each time the camera is moved.
    private void Update()
    {
        transform.position = cameraPosition.position;
    }
}