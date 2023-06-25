using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovePlayer : MonoBehaviour
{
    //Variables for all the components that will determine the player's movement physics.
    [Header("Movement")]
    public float moveSpeed;

    public float groundDrag;

    public float jumpForce, jumpCooldown, airTime;
    bool readyToJump;

    [Header("Keybinds")]
    public KeyCode jumpKey = KeyCode.Space;

    [Header("Ground Check")]
    public float playerHeight;

    //Mask to not let the player game object fall through the world.
    public LayerMask whatIsGround;
    bool grounded;

    //Connects the camera's and player's orientations.
    public Transform orientation;

    //Keyboard input holders.
    float horizontalInput;
    float verticalInput;
    Vector3 moveDirection;

    //Rigidbody component.
    Rigidbody rb;

    //Assignment of Rigidbody component to the script.
    private void Start()
    {
        rb = GetComponent<Rigidbody>();
        rb.freezeRotation = true;

        readyToJump = true;
    }

    //Update the ground each time the player moves.
    private void Update()
    {
        grounded = Physics.Raycast(transform.position, Vector3.down, playerHeight * 0.5f + 0.2f, whatIsGround);

        //Functions called between each play.
        MyInput();
        SpeedControl();

        //Check if there is ground for ground drag component, and update the ground each time the player moves.
        if (grounded)
            rb.drag = groundDrag;
        else
            rb.drag = 0;
    }

    private void FixedUpdate()
    {
        PlayerMovement();
    }

    //Function for determining specifics of keyboard inputs and how the interact with the ground when moving or jumping.
    private void MyInput()
    {
        horizontalInput = Input.GetAxisRaw("Horizontal");
        verticalInput = Input.GetAxisRaw("Vertical");

        if(Input.GetKey(jumpKey) && readyToJump && grounded)
        {
            readyToJump = false;

            Jump();

            //Preventing a continuous jump when using jump key.
            Invoke(nameof(ResetJump), jumpCooldown);
        }
    }

    //Function for determining the player's general movemment interactions with rigidbody.
    private void PlayerMovement()
    {
        //Calculate the direction and which way the player is facing. 
        moveDirection = orientation.forward * verticalInput + orientation.right * horizontalInput;

        //Add force to rigidbody whether the player is grounded or in mid-air.
        if(grounded)
            rb.AddForce(moveDirection.normalized * moveSpeed * 10f, ForceMode.Force);

        else if(!grounded)
            rb.AddForce(moveDirection.normalized * moveSpeed * 10f * airTime, ForceMode.Force);
    }

    private void SpeedControl()
    {
        Vector3 flatVel = new Vector3(rb.velocity.x, 0f, rb.velocity.z);
        Vector3 limitedVel;

        //Equalize and limit player's movement speed for a constant amount.
        if (flatVel.magnitude > moveSpeed)
        {
            limitedVel = flatVel.normalized * moveSpeed;
            rb.velocity = new Vector3(limitedVel.x, rb.velocity.y, limitedVel.z);
        }

    }

    //Determine our jump speed and force values.
    private void Jump()
    {
        rb.velocity = new Vector3(rb.velocity.x, 0f, rb.velocity.z);
        rb.AddForce(transform.up * jumpForce, ForceMode.Impulse);
    }

    //Once jump cooldown is finished, we are ready to jump.
    private void ResetJump()
    {
        readyToJump = true;
    }
}