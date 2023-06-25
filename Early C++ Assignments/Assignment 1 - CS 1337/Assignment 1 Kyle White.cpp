//CS 1337.001 Assignment 1
//8/31/20
//Kyle White
//In short, this program reads in 10 matrixes from a file 6 valid and 4 invalid, takes the values from its vertical additive symmetry, sort it and then displays the data...
//9/2/20 Fixed bug that gave numbers practically infinite decimals.
//9/2/20 Bug still exists that doesn't read in the first number of a matrix, and doing so the entire system. Have yet to solve it.

//Header Files.
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdio.h>

using namespace std;

//Function Prototypes.
bool readMatrix(float [][20], unsigned&, unsigned&, ifstream&);
void displayMatrix(float [][20], unsigned, unsigned);
void displayCalcMatrixSums(float[][20], unsigned, unsigned, float[20]);
void symmetryCheckMatrix(float[], unsigned, unsigned);
void sortMatrixRows(float[][20], unsigned, unsigned);

int main()
{
     unsigned numRows, numColumns;
     float matrix[20][20], columnSum[20];

     //Condition the stream to show decimal point.
     cout << setprecision(3) << showpoint << fixed;
     //Open the file.
     ifstream matrixFile;
     matrixFile.open("matrixes.txt");
     string fileNameInput;

     matrixFile >> fileNameInput;

        if(matrixFile.fail())
        {
            cout << "The file" << fileNameInput << "could not be opened. Press enter to continue and try again." << endl; cin.ignore(); cin.get();
        }

    do
    {
        //If we get the true values back from the readMatrix function, then the loop finishes.
        if(readMatrix(matrix, numRows, numColumns, matrixFile))
            break;

        cout << "Input: " << endl;
        //Function calls that pass appropriate variables.
            displayMatrix(matrix, numRows, numColumns);
            displayCalcMatrixSums(matrix, numRows, numColumns, columnSum);
            symmetryCheckMatrix(columnSum, numColumns, numRows);
            sortMatrixRows(matrix, numColumns, numRows);
        cout << "Sorted:" << endl;
            displayMatrix(matrix, numRows, numColumns);
        cout << endl;
        cout << "Press enter to continue." << endl; cin.ignore(); cin.get();


     } while(true);

     return 0;
}
//Function to bring back numRows and numColumns if read, and send the change to matrixFile back as a reference.
bool readMatrix(float matrix[][20], unsigned& numRows, unsigned& numColumns, ifstream& matrixFile)
{
//If there is nothing else to read at the end of the file, return true boolean value.
    if(!(matrixFile >> numRows))
        return true;
    //If it doesn't return true, read the rest of the data.
    matrixFile >> numColumns;

    //Local Array Data
    for(unsigned int i = 0; i < numRows; i++)
    {
        for(unsigned int j = 0; j < numColumns; j++)
            matrixFile >> matrix[i][j];
    }
    //Return false to indicate that there is more data in the file.
    return false;
}

void displayCalcMatrixSums(float matrix[][20], unsigned numRows, unsigned numColumns, float columnSum[20])
{
    for(unsigned j = 0; j < numColumns; j++)
        columnSum[j] = 0;
    for(unsigned j = 0; j < numColumns; j++)
    {
        for(unsigned i = 0; i < numRows; i++)
            columnSum[j] += matrix[i][j];
    }

    cout << "Sums: " << endl;
    for(unsigned j = 0; j < numColumns; j++)
        cout << setw(12) << columnSum[j];
    cout << endl << endl;

    return;
}

void symmetryCheckMatrix(float columnSum[], unsigned numColumns, unsigned numRows)
{
    cout << "Does the matrix have VAS?" << endl;

    //Divide numColumns by two in case of an odd number, and to check for symmetry.
    for(unsigned int j = 0; j < numColumns / 2; j++)
    {
        float leftColumnSum = 0, rightColumnSum = 0;
        //Holds the sum of the values in left and right.
        leftColumnSum += columnSum[j];
        rightColumnSum += columnSum[numColumns - j - 1];

        if(leftColumnSum != rightColumnSum)
        {
            cout << "No." << endl;
            return;
        }
    }
    cout << "Yes." << endl;

    return;
}

void sortMatrixRows(float matrix[][20], unsigned numColumns, unsigned numRows)
{
    //Bubble sorting.
    for(unsigned int i = 0; i < numRows; i++)
    {
        for(unsigned int j = 0; j < numColumns - 1; j++)
            for(unsigned int k = 0; k < (numColumns - j - 1); k++)
                if(matrix[i][k] > matrix[i][k + 1])
                {
                    float temp = matrix[i][k];
                    matrix[i][k] = matrix[i][k + 1];
                    matrix[i][k + 1] = temp;
                }
    }
}
//numRows and numColumns are passed by value instead, since they aren't going back to main.
void displayMatrix(float matrix[][20], unsigned numRows, unsigned numColumns)
{
    for(unsigned int i = 0; i < numRows; i++)
    {
        for(unsigned int j = 0; j < numColumns; j++)
            cout << setw(12) << matrix[i][j];
        cout << endl;
    }
}













