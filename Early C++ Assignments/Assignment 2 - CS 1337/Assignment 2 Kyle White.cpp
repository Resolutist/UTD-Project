//CS 1337 Assignment 2
//9/16/20
//By: Kyle White
/*This function organizes any array of data less than 10, into numerical order by using pointers to
change the values of the pointers in another array that has pointers into the original data set.
*/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iomanip>

using namespace std;

//Function Prototypes.
void SwapIntPtr(int, int);
bool ReadDataArray(ifstream&, int&, int[], int*[]);
void SortArray(int*[], int);
void DisplayDataArray(int[], int);
void DisplayPointerArray(int*[], int);

int main()
{
    int maxElements = 0; // Counter

    int dataArray[10]; //Holds the max value for how many numbers the array should take from.
    int *pointerArray[10];
    //Open the file.
    ifstream arrayTextFile;
    arrayTextFile.open("arrayData.txt");
    string fileNameInput;

    arrayTextFile >> fileNameInput;

    if (arrayTextFile.fail())
    {
        cout << "File " << fileNameInput << "could not be opened!" << endl;
        //Pause the screen so the display can be read.
        cout << "Press any key to continue..." << cin.ignore(); cin.get();
        exit(0);
    }

    while(!ReadDataArray(arrayTextFile, maxElements, dataArray, pointerArray))
    {
        //Function Calls.
        SortArray(pointerArray, maxElements);
        DisplayPointerArray(pointerArray, maxElements);
        DisplayDataArray(dataArray, maxElements);
        //Pause the screen again so the display can be read.
        cout << endl << "Press any key to continue..."; cin.ignore(); cin.get();
        cout << endl;
    }
    arrayTextFile.close();

    return 0;
}
//Function that swaps values of two argument pointers into int values.
void SwapIntPtr(int *&a, int *&b)
{
    int *c = a;
    a = b;
    b = c;
}
//Read data from file. While loop to end function if file does
bool ReadDataArray(ifstream &arrayTextFile, int &maxElements, int dataArray[], int *pointerArray[])
{
    //If there is nothing else to read at the end of the file, return true boolean value.
    while(!(arrayTextFile >> maxElements))
    {
        return true;
    }
    for(int i = 0; i < maxElements; i++)
    {
        arrayTextFile >> dataArray[i];
        pointerArray[i] = &dataArray[i];
    }
    //Return false to indicate that there is more data in the file.
    return false;
}
//Function for bubble sorting algorithm, but for only pointerArray.
void SortArray(int *pointerArray[], int maxElements)
{
    for(int i = 0; i < maxElements; i++)
        for(int j = i + 1; j < maxElements; j++)
           if(*pointerArray[j] < *pointerArray[i])
                //We swap pointers if the value in the right element is smaller than the left in the array.
                SwapIntPtr(pointerArray[j], pointerArray[i]);
}
//Function for displaying the original array format.
void DisplayDataArray(int dataArray[], int maxElements)
{
    cout << "Now displaying data in original order" << endl;
        for(int i = 0; i < maxElements; i++)
        //10 numbers per line in a 6 space field.
            cout << dataArray[i] << setw(6);
                cout << endl;
}
//Function for displaying the fixed array format.
void DisplayPointerArray(int *pointerArray[], int maxElements)
{
    cout << "Now displaying data in sorted order" << endl;
        for(int i = 0; i < maxElements; i++)
        //10 numbers per line in a 6 byte field.
            cout << *pointerArray[i] << setw(6);
                cout << endl;
}




