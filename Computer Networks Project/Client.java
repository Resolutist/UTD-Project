import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Random;

public class Client {

    private static final String[] OPERATORS = {"+", "-", "*", "/"};
    private static final Random random = new Random();

    public static void main(String[] args) {
        try (Socket socket = new Socket("localhost", 6789);
             BufferedReader input = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             PrintWriter output = new PrintWriter(socket.getOutputStream(), true);
             BufferedReader keyboard = new BufferedReader(new InputStreamReader(System.in))) {

            // Give client name during the initial attachment.
            String clientName = "";
            while (clientName.isEmpty())
            {
                System.out.print("Enter your name: ");
                clientName = keyboard.readLine();
                output.println(clientName);
            }

            // Wait for server to acknowledge successful connection.
            String response = input.readLine();
            while (response.compareTo("NAME_ACCEPTED") != 0) {
                if (response.compareTo("NAME_NOT_UNIQUE") == 0) {
                    System.out.print("Name is not unique. Please enter another name: ");
                    clientName = keyboard.readLine();
                    output.println(clientName);
                }
                response = input.readLine();
            }
            System.out.println("Successfully connected to the server.");

            // Send user-inputted math calculation requests.
            String userInput;
            do {
                // Prompt the user for a basic arithmetic expression
                System.out.print("Enter a basic arithmetic expression: ");
                userInput = keyboard.readLine();

                // Check if the user entered "exit" to terminate the connection
                if (userInput.equals("exit")) {
                    output.println("exit");
                } else {
                    // Send the arithmetic expression to the server
                    output.println(userInput);

                    // Read the server's response and display it
                    response = input.readLine();
                    System.out.println("Server response: " + response);
                }
            } while (!userInput.equals("exit")); // Continue the loop until the user enters "exit"

        } catch (IOException e)
        {
            System.out.println("Error connecting to server: " + e.getMessage());
        }
    }
}
