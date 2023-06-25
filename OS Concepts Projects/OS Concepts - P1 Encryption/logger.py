# Import for receiving the log file from terminal.
import sys

class Logger:

    # Define the current time to pass into the log file.
    # Imports.
    from datetime import datetime
    from datetime import date

    # Defining time.
    now = datetime.now()
    # Defining date.
    today = date.today()

    # Format the date in YYYY-MM-DD, and store in variable.
    date = today.strftime("%Y-%m-%d")

    # Format the time in HH:MM, and store in variable.
    time = now.strftime("%H:%M")

    # Open the file to append to, accepting the commandline argument as the name of the log file.
    logFile = open(sys.argv[1], 'a')

    # Write the start-up message to the file each time the program is run.
    print(date, time, "[START] Logging Started.", file=logFile)

    # "Accept log messages via standard input until it receives "QUIT"."
    logMessage = input("Enter a command: ")
    ACTION = input().split()[0]
    MESSAGE = input().split(ACTION, 1)[-1]

    # Loop for recognizing QUIT, but sending input to file until then.
    while ACTION != 'QUIT':
        print(date, time, ("["+ACTION+"]"+MESSAGE), file=logFile)

    # Log stop message before closing the file and exiting.
    print(date, time, "[STOP] Logging Stopped.", file=logFile)
    logFile.close()
    exit()