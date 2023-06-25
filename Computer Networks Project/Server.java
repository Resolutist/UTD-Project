import java.io.*;
import java.net.*;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.concurrent.*;

class Server {
    private static final int PORT = 6789;

    // For logging purposes
    private static final SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    // Store client handlers
    private static final ConcurrentHashMap<String, ClientHandler> clients = new ConcurrentHashMap<>();

    public static void main(String argv[]) throws Exception {
        ServerSocket welcomeSocket = new ServerSocket(PORT);
        System.out.println("Math server started on port " + PORT);

        while (true) {
            Socket connectionSocket = welcomeSocket.accept();
            ClientHandler clientHandler = new ClientHandler(connectionSocket);
            clientHandler.start();
        }
    }

    // ClientHandler class to handle each client connection
    private static class ClientHandler extends Thread {
        private final Socket clientSocket;
        private String clientName;
        private BufferedReader input;
        private PrintWriter output;

        public ClientHandler(Socket clientSocket) {
            this.clientSocket = clientSocket;
        }

        @Override
        public void run() {
            try {
                input = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                output = new PrintWriter(clientSocket.getOutputStream(), true);

                // Check client name uniqueness and acknowledge connection
                while (true) {
                    output.println("ENTER_NAME");
                    clientName = input.readLine();

                    // Exit if the client name is null.
                    if (clientName == null) {
                        return;
                    }

                    synchronized (clients) {
                        if (clients.containsKey(clientName)) {
                            // If the name is not unique, inform the client and continue the loop.
                            output.println("NAME_NOT_UNIQUE");
                        } else {
                            // If the name is unique, add the client to the clients map and inform the client.
                            clients.put(clientName, this);
                            output.println("NAME_ACCEPTED");
                            System.out.println("Client " + clientName + " connected at " + dateFormat.format(new Date()));
                            break;
                        }
                    }
                }


                // Process client messages
                while (true) {
                    String request = input.readLine();
                    if (request == null || request.equalsIgnoreCase("exit")) {
                        break;
                    }

                    // Process and respond to math calculations
                    String[] tokens = request.split(" ");
                    if (tokens.length == 3) {
                        try {
                            double num1 = Double.parseDouble(tokens[0]);
                            String operator = tokens[1];
                            double num2 = Double.parseDouble(tokens[2]);

                            double result = 0;
                            switch (operator) {
                                case "+":
                                    result = num1 + num2;
                                    break;
                                case "-":
                                    result = num1 - num2;
                                    break;
                                case "*":
                                    result = num1 * num2;
                                    break;
                                case "/":
                                    result = num1 / num2;
                                    break;
                                default:
                                    output.println("INVALID_OPERATOR");
                                    continue;
                            }

                            System.out.println("Client " + clientName + " requested calculation: " + request);
                            output.println("RESULT " + result);
                        } catch (NumberFormatException e) {
                            output.println("INVALID_NUMBER");
                        }
                    } else {
                        output.println("INVALID_REQUEST");
                    }
                }
            } catch (IOException e) {
                System.out.println("Error handling client " + clientName + ": " + e.getMessage());
            } finally {
                closeConnection();
            }
        }

        private void closeConnection() {
            try {
                if (clientName != null) {
                    clients.remove(clientName);
                    System.out.println("Client " + clientName + " disconnected at " + dateFormat.format(new Date()));
                }
                if (output != null) {
                    output.close();
                }
                if (input != null) {
                    input.close();
                }
                if (clientSocket != null) {
                    clientSocket.close();
                }
            } catch (IOException e) {
                System.out.println("Error closing connection with client " + clientName + ": " + e.getMessage());
            }
        }
    }
}
