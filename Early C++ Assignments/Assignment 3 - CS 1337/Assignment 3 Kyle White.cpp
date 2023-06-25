/*This program simulates how software operates within a satellite,
and will use macros to simulate the input and output channels from a file.
And then when the input data performs a request, the program performs a basic summary analysis
for the information given to the ground channel.*/
//CS 1336 Assignment 3
//9/30/20
//By: Kyle White

#include <iostream> //Needed for cout.
#include <string> //Needed for string values.
#include <iomanip> //Needed for setprecision, etc.
#include <fstream> //Needed to open and close files.
#include <stdint.h> //Allows _t int types.
#include <cstdlib> //Needed for exit function.
#include <stdio.h> //For pausing the screen.

using namespace std;

//Enumerated class containing reference variables for the first switch statement.
enum class MESSAGE_ID{STATUS_INFORMATION_MESSAGE = 1, EXPERIMENT_INFORMATION_MESSAGE = 2, SEND_SUMMARY_MESSAGE = 3};
MESSAGE_ID messageID;

//Enumerated class containing non defined reference variables for the second switch statement.
enum InformationType{STATUS_INFORMATION, EXPERIMENT_INFORMATION, EMPTY};

//Satellite contains two types of information: Status and Experiment.

//Satellite status information contains temperature and voltage.
struct StatusInformation
{
    float temperature; //Code Blocks would not accept any _t type besides int.
    float voltage; //But we still needed a floating point type, so picked float since it's smaller than double.
};

//Experiment information contains the below two pieces of data.
struct ExperimentInformation
{
    //Both count data types must be uint16_t.
    uint16_t radiationCount;
    uint16_t latchupEventsCount;
};

//Use a union to hold both SI and EI in the minimum amount of memory.
union MasterUnion
{
    StatusInformation statusInformation;
    ExperimentInformation experimentInformation;
};
/*Master information is held in a struct with an
enumerated discriminator that indicates the type
of info held in the union that is contained in the
master structure.*/
struct MasterInformation
{
    //Two fields that are structures that represent the SI and IE data.
    InformationType infoType;
    MasterUnion masterUnion;
};

int main()
{
    #define GroundStationOutputChannel cout

    const uint8_t ARRAY_DATA_STORAGE_SIZE = 5;

    ifstream telemetryInputAntennaReceiverChannel;
    string TELEMETRY_RECEIVER_INPUT_CHANNEL;
    //Master structure will be stored in an array in the satellite memory.
    MasterInformation infoStoredArray[ARRAY_DATA_STORAGE_SIZE];
    uint8_t entryPositionIndex = 0;
    MasterInformation masterInformation;

    telemetryInputAntennaReceiverChannel >> TELEMETRY_RECEIVER_INPUT_CHANNEL;

    //Open the file.
    telemetryInputAntennaReceiverChannel.open("inputDataAntenna.txt");
        //invalid file name, or the file doesn't exist.
        if(telemetryInputAntennaReceiverChannel.fail())
        {
            cout << "File " << TELEMETRY_RECEIVER_INPUT_CHANNEL << " could not be opened!" << endl;
            //Pause the screen.
            cout << "Press enter key to continue..."; cin.ignore(); cin.get();
            exit(EXIT_FAILURE);
        }
        //Values are represented as real numbers with one decimal place.
    GroundStationOutputChannel << setprecision(1) << fixed << showpoint;

        for(uint8_t index = 0; index < ARRAY_DATA_STORAGE_SIZE; index++)
        {
            //Initialize the array i to empty for a clean input.
            infoStoredArray[index].infoType = EMPTY;

        uint16_t val;
        //While loop that validates a number is being recognized from the file to be used in the switch statement, whether 1, 2 or 3.
        while(telemetryInputAntennaReceiverChannel >> val)
        {
            messageID = MESSAGE_ID(val);
            //The switch statement identifies which number from 1 to 3 in the file, and sets the value to what number was received.
        switch(messageID)
        {
            //If a 1 is read from the file, the next two lines will contain appropriate listing.
        case MESSAGE_ID::STATUS_INFORMATION_MESSAGE:
                //Set to status so that we know what type we are using.
                masterInformation.infoType = STATUS_INFORMATION;
                //Read the data into the temperature and voltage values.
                telemetryInputAntennaReceiverChannel >>
                //Loading the master union with the status information.
                masterInformation.masterUnion.statusInformation.temperature >>
                masterInformation.masterUnion.statusInformation.voltage;
                //Put the information into the array.
                infoStoredArray[entryPositionIndex] = masterInformation;

                //Conditional Operator that adjusts the position of the value i to either 4 or 0, then increment it to be the next position.
                entryPositionIndex = (entryPositionIndex == 4) ? 0 : ++entryPositionIndex;
            break;

            //If a 2 is read from the file, the next two lines will contain appropriate listing.
            case MESSAGE_ID::EXPERIMENT_INFORMATION_MESSAGE:
                //Set status.
                masterInformation.infoType = EXPERIMENT_INFORMATION;
                //Read the data into the radiation and latchup values.
                telemetryInputAntennaReceiverChannel >>
                //Members of the EI data structure.
                masterInformation.masterUnion.experimentInformation.radiationCount >>
                masterInformation.masterUnion.experimentInformation.latchupEventsCount;
                //Put the information into the array.
                infoStoredArray[entryPositionIndex] = masterInformation;

                //Conditional Operator that adjusts the position of the value index to either 4 or 0, then increment it to be the next position.
                entryPositionIndex = (entryPositionIndex == 4) ? 0 : ++entryPositionIndex;
            break;

            //If a 3 is read, the program must send information to the ground station.
            case MESSAGE_ID::SEND_SUMMARY_MESSAGE:
                //summary information
                float maxTemperature = -50, minTemperature = 212,
                        maxVoltage = 0.0, minVoltage = 100.0;

                //Counting variables across the array.
                uint16_t totalRadiationCount = 0,
                totalLatchupEventCount = 0,
                infoSICount = 0,
                infoEICount = 0;

            for(uint8_t index = 0; index < ARRAY_DATA_STORAGE_SIZE; index++)
            {
                //
                switch(infoStoredArray[index].infoType)
                {
                    case STATUS_INFORMATION:
                        //Display information that the ground station received on its status info, and store in array.
                        GroundStationOutputChannel <<
                        "Temperature: " <<
                        infoStoredArray[index].masterUnion.statusInformation.temperature << endl <<
                        "Voltage: " <<
                        infoStoredArray[index].masterUnion.statusInformation.voltage << endl << endl;
                        //Increment the counter variable to display the proper number of satellite records received.
                        infoSICount++;

                        //Set the minimum and maximum summary info.
                        if(maxTemperature < infoStoredArray[index].masterUnion.statusInformation.temperature)
                            maxTemperature = infoStoredArray[index].masterUnion.statusInformation.temperature;

                        if(minTemperature > infoStoredArray[index].masterUnion.statusInformation.temperature)
                            minTemperature = infoStoredArray[index].masterUnion.statusInformation.temperature;

                        if(maxVoltage < infoStoredArray[index].masterUnion.statusInformation.voltage)
                            maxVoltage = infoStoredArray[index].masterUnion.statusInformation.voltage;

                        if(minVoltage > infoStoredArray[index].masterUnion.statusInformation.voltage)
                            minVoltage = infoStoredArray[index].masterUnion.statusInformation.voltage;
                    break;

                    case EXPERIMENT_INFORMATION:
                        //Display information that the ground station received on its experimental info, and store in array.
                        GroundStationOutputChannel <<
                        "Radiation Count: " <<
                        infoStoredArray[index].masterUnion.experimentInformation.radiationCount << endl <<
                        "Latchup Event Count: " <<
                        infoStoredArray[index].masterUnion.experimentInformation.latchupEventsCount << endl << endl;
                        //Increment the counter variable to display the proper number of experimental records received.
                        infoEICount++;

                        //Add whatever values that were stored in the array previously to the total count of the variable.
                        totalRadiationCount += infoStoredArray[index].masterUnion.experimentInformation.radiationCount;
                        totalLatchupEventCount += infoStoredArray[index].masterUnion.experimentInformation.latchupEventsCount;
                    break;

                    case EMPTY:

                    break;
                }
            }
        //Display information sent to the ground station from the file.
        GroundStationOutputChannel <<
        "Summary Information" << endl <<
        "-------------------" << endl <<
        "Number of Satellite Information Records: " << infoSICount << endl <<
        "Number of Experiment Information Records: " << infoEICount << endl <<
        "Total Radiation Count: " << totalRadiationCount << endl <<
        "Total Latchup Event Count: " << totalLatchupEventCount << endl <<
        "Maximum Temperature: " << maxTemperature << endl <<
        "Minimum Temperature: " << minTemperature << endl <<
        "Maximum Voltage: " << maxVoltage << endl <<
        "Minimum Voltage: " << minVoltage << endl << endl;;

        //Pause the screen.
        cout << "Press the enter key to continue..."; cin.ignore(); cin.get();
            }
        }
    }
    //Finally, close the file.
    telemetryInputAntennaReceiverChannel.close();

    return(EXIT_SUCCESS);
}
