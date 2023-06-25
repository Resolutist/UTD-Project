using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerCam : MonoBehaviour
{
    
    //Essentially connects the camera's and player's orientations.
    public Transform orientation;

    //Amount of roation that determines the sensitivity.
    float xRotation;
    float yRotation;

    //Values to adjust sensitivity for x and y axis'.
    public float sensX;
    public float sensY;

    //Function on start:
    private void Start()
    {
        //Ensure that the cursor will always be in the middle
        Cursor.lockState = CursorLockMode.Locked;
        //Make Unity Cursor invisible.
        Cursor.visible = false;
    }

    //Function for updating all the values in between each start of the game.
    private void Update()
    {
        //Determine the coordinates of the mouse input on the plane of the game.
        float mouseX = Input.GetAxisRaw("Mouse X") * Time.deltaTime * sensX;
        float mouseY = Input.GetAxisRaw("Mouse Y") * Time.deltaTime * sensY;

        //Staple for how Unity handles inputs by lining up accurate input values.
        yRotation += mouseX;
        xRotation -= mouseY;

        //Lock up and down movement by 90 degrees each.
        xRotation = Mathf.Clamp(xRotation, -90f, 90f);

        //Rotation orientations for both camera and player.
        transform.rotation = Quaternion.Euler(xRotation, yRotation, 0);
        orientation.rotation = Quaternion.Euler(0, yRotation, 0);
    }
}