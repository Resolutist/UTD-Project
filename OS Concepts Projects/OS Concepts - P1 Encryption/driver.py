# Command Line Argument Format Used: py program.py logFile

# Used for running the encryption and logger files from driver.
from subprocess import Popen, PIPE
import sys


class Driver:

    # Default constructor for assigning self to other methods, to pass to logger and encryption files.
    def __init__(self, logFile):

        # Using pipes to connect standard input and output for subprocess. Using -u to prevent buffered streams.
        self.log = Popen(['python', 'logger.py', logFile], stdout=PIPE, stdin=PIPE, encoding='utf8')
        self.enc = Popen(['python', 'encryption.py'], stdout=PIPE, stdin=PIPE, encoding='utf8')

        # Set variables to store the password and history list
        self.hist = []
        self.password = ''

        # Communication streams.
        self.logger_in = self.log.stdin
        self.logger_out = self.log.stdout
        self.encryption_in = self.enc.stdin
        self.encryption_out = self.enc.stdout

    def menu(self):
        while True:
            # Provide menu with numbers for selecting strings and how they are used.
            print('------------------------------MENU------------------------------')
            print('| 1. Password | 2. Encrypt | 3. Decrypt | 4. History | 5. Quit |')
            print('----------------------------------------------------------------')

            # Variable to store user input to interact with the menu.
            userChoice = input('Select a number from the list to perform: ')

            # Switch menu choice with function calls for each action.
            if userChoice == '1':
                self.setPassword()
            elif userChoice == '2':
                self.encrypt()
            elif userChoice == '3':
                self.decrypt()
            elif userChoice == '4':
                self.history()
            elif userChoice == '5':
                self.quit()
            else:
                print("Invalid input, please try again.")

    def setPassword(self):
        while True:
            newPassword = self.userOptionChoice()
            # "Set the new string as the current password in the encryption program."
            self.encryptComm("PASSKEY", newPassword)
            message = f"New password is: {newPassword}"
            # Log the new password command.
            self.logComm("PASSKEY", message)

    def encrypt(self):
        plainText = self.userOptionChoice()
        # "Send an encrypt command to the encryption program."
        cipherText = self.encryptComm("ENCRYPT", plainText)

        # Split the cipher text for output purposes.
        actionCommand = cipherText.split()
        COMMAND = actionCommand[1]

        # Format message to send to logger.
        message = f"{plainText} was encrypted to {COMMAND}"

        # Log the encryption command.
        self.logComm("ENCRYPT", message)

        # "The results should be printed to standard output and saved in the history."
        print(f"Encrypted text: {COMMAND}")
        # Connects to line 38 of encryption.py
        while COMMAND == 'Password not set.':
            self.hist.append(COMMAND)

    def decrypt(self):
        decryptText = self.userOptionChoice()

        # Send a decrypt command to the encryption program.
        decryptResult = self.encryptComm("DECRYPT", decryptText)

        # Split for output purposes.
        COMMAND = decryptResult.strip().split(1)

        # Format message to send to logger.
        message = f"{decryptText} was decrypted to {COMMAND}"

        # Log the decryption command.
        self.logComm("DECRYPT", message)

        # "The results should be printed to standard output and saved in the history."
        print(f"Decrypted text: {COMMAND}")
        self.hist.append(COMMAND)

    def history(self):
        self.userHistoryChoice()
        # Display history.
        print("History: ")
        for i, string in enumerate(self.hist):
            print(f"{i + 1}: {string}")

    def quit(self):
        # Tell encrypt and logger files to quit/stop, using \n to help with buffered streams.
        self.log.stdin.write(f"STOP Logging Stopped.\n")
        self.enc.stdin.write("QUIT\n")
        print("Program exited successfully.")

        # Kill processes.
        self.log.kill()
        self.enc.kill()
        exit()

    # "Provide the user with the option of using a string in the history or entering a new string."
    # Used for password, encrypt, and decrypt functions.
    def userOptionChoice(self):
        while True:
            string = ''
            # Provide the user to choose between using a string in history or entering a new string.
            print(f"Enter 'H' to use a string from history, or 'N' to enter a new string.")
            # Get input, truncating any spaces and setting it to capital if lowercase is inputted.
            choice = input().strip().upper()
            # Validate user input.
            if choice != 'H' and choice != 'N':
                print("Invalid input. Enter H or N.")
            elif choice == 'N':
                # Get the new string from the user.
                string = input(f"Enter the new string: ").strip().upper()
            elif choice == 'H':
                # Jump to history function.
                string = self.userHistoryChoice()
                # "Provide the user with a menu where a number can be used to select a string stored in the history."
                string = input(f"Enter a number to select a string: ").strip()
            else:
                quit(self)

            return string

    # "whenever the history is used, provide the user with a means to exit the history and enter a new string."
    def userHistoryChoice(self):
        string = None
        print("Enter a number to select a string from the history. Press E if you want to exit.")
        userChoice = input().strip()

        if userChoice.upper() == 'E':
            exit()
        else:
            # Ensure passing of a number.
            userChoice = int(userChoice)
            # String is chosen from the array based on the user's input.
            string = self.hist[userChoice - 1]

        return string

    # Methods for processing communication passes with logger.py and encryption.py.
    def logComm(self, ACTION, MESSAGE):
        for i in range(10, 0, -1):
            self.log.stdin.write(f"{ACTION} {MESSAGE} \n")
            self.log.stdin.flush()

    def encryptComm(self, ACTION, MESSAGE):
        for i in range(10, 0, -1):
            self.enc.stdin.write(f"{ACTION} {MESSAGE} \n")
            self.enc.stdin.flush()

        # Return the result of the encryption. (OIWWC for HELLO)
        return self.enc.stdout.readline().strip()


# Run the program from terminal.
if __name__ == '__main__':
    logFile = sys.argv[1]
    driver = Driver(logFile)
    driver.menu()
