class Encryption:
    import sys
    # Encryption/Decryption Program using Vigenere cypher.

    # Key to be passed.
    passkey = ''

    # While loop for parsing the first word of the command, and perform actions based on the command.
    while True:
        # Get command from standard user input, and split the input, with a respective length.
        userCommand = input("Enter command:").split()
        uc = len(userCommand)

        # Assign command and passkey, and their respective lengths to variables.
        command = userCommand[0].upper()
        c = len(command)
        # upper() is applied, as the example password was in all caps.
        password = userCommand[1].upper()
        p = len(password)

        # Define the response types, and the result of encryption/decryption.
        successResponse = 'RESULT'
        failureResponse = 'ERROR'
        result = ""

        # In case the user only enters a command, or only enters a password, being the two most probable mistakes.
        if uc != 2:
            print("Must have one command and one password. Please reenter.")

        # Check for either Passkey, Encrypt, or Decrypt commands.
        if command == 'PASSKEY':
            # Assign passkey upon recognizing PASSKEY command.
            passkey = password
            print(successResponse)
        elif command == 'ENCRYPT':
            # Validate that a passkey has been created.
            if passkey == "":
                print(failureResponse, "Password not set.")
                # Let the loop continue upon failure.
                continue
            else:
                # Encryption Block via Vigenere cypher algorithm, within the bounds of the length of the password entered.
                for i in range(p):
                    # Convert cipher to a character index, adding the passkey according to the original formula. (M + K)
                    # upper() is applied, as the example password was in all caps.
                    result += chr(65 + (ord(password[i]) - 65 + ord(passkey[i % p]) - 65) % 26).upper()

                # Print result of the encryption.
                print(successResponse, result)

        elif command == 'DECRYPT':
            # Validate that a passkey has been created.
            if passkey == "":
                print(failureResponse, "Password not set.")
                # Let the loop continue upon failure.
                continue
            else:
                # Decryption Block via Vigenere cypher algorithm.
                for i in range(p):
                    # Slight difference versus encryption where we subtract the key, and don't need to subtract the ascii value. (M - K)
                    result += chr(65 + (ord(password[i]) - ord(passkey[i % p]) + 26) % 26)

                # Print result of the decryption.
                print(successResponse, result)
        # Exit the program if the user asks to quit.
        elif command == 'QUIT':
            print("Exited the program.")
            break
        else:
            # Only accept the above three commands, and break from the loop if otherwise.
            print("Invalid command, please try again.")
            break
