/*
 * Name: Irene Wang, 5005298618, Assignment 7
 * Description: This program will read in instructions from an input file
 * through file stream, create separate files through file stream, and 
 * print out shapes according to the instructions into each file.
 * Input: Text file containing instructions for shapes following 
 * "shape name, shape size, character" format.
 * Output: Separate text files each containing one specified shape
 * from the instructions, with file name indicating the shape name and
 * shape size (shapeName_shapeSize).
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

using namespace std;

// prototypes
void openInputFile( ifstream&, string, string="");
bool openOutputFile( ofstream & oFile, string fname);
void outputChar( ofstream&, int count, char l);
string createOutputFilename(  string typeString, int labelSize );
void makeArrow( ofstream& oFile, int size, char c );
void makeBracket( ofstream& oFile, int size, char c );
void makeTheta( ofstream& oFile, int size, char c );
bool readRecord ( ifstream& iFile, string& typeString, int& lSize, char& c );

// main 
// parameter is file containing specification
int main(int argc, char* argv[]){
    ifstream iFile;
    ofstream oFile;
    string ofName;
    string typeString;
    int  labelSize = 0;
    char labelChar = 0;
    int recordCount = 0;
    bool done = false;
    string passedString;

    cout << "Welcome to Arrakis Computational Support" << endl;

    if( argc > 1) 
        passedString = argv[1];

    // Open input file
    openInputFile( iFile, "Input Specification File: ", passedString );
    
    // read a record from the specification file. 
    while(true){
        
        // read a record from the file
        done = readRecord ( iFile, typeString,  labelSize, labelChar );

        // verify that it worked, if not exit.
        if ( !done ){   
            cout << "Finished processing input file" << endl;
            cout << recordCount << " Shapes Created " <<endl;
            iFile.close();
            oFile.close();
            exit(0);            
        }else{
        
            recordCount++;    
    
            // create the output filename
            ofName = createOutputFilename( typeString, labelSize );

            // open output file
            if( !openOutputFile( oFile, ofName )) {
                cout << "Output file \"" << ofName << "\" did not open" << endl;
                cout << "File \"" << ofName << "\" not generated" << endl;
            }else{
                    cout << "File \"" << ofName << "\" successfully opened" << endl;
                    if( typeString == "arrow")
                        makeArrow( oFile, labelSize, labelChar );
                    else if(typeString == "theta")
                        makeTheta( oFile, labelSize, labelChar);
                    else if( typeString == "bracket")
                        makeBracket( oFile, labelSize, labelChar );

            } 
        }
        
        // close the shape file so that we can re-use oFile variable
        oFile.close();
      }  
}

/* *******************************************************************
 * function_identifier: This function reads in the instructions from
 * the input file through input file stream.Instructions are extracted
 * from the file and stored into the three key variables "typeString", 
 * "lSize", and "c".
 * parameters: The instruction file which follows "shape type, shape
 * size, character" format opeed through input file stream.
 * return value: Returns true when the program have not reached the
 * end of file (which means there are more instructions to be read).
 * This corresponds to the (!done) condition in the main function.
 * Returns false when the program have reached the end of file (no
 * more instructions to be read). This corresponds to the else 
 * condition in the main function.
 * *******************************************************************/
bool readRecord ( ifstream& iFile, string& typeString, 
                int& lSize, char& c ){

    iFile >> typeString;
    iFile >> lSize;
    iFile >> c;

    if(!iFile.eof()){
        return true;
    }
    else{
        return false;
    }
}

/* *****************************************************************
 * function_identifier: This function creates the output file name
 * according to the homework guidelines (shapeName_shapeSize).
 * parameters: The typeString variable (shape name) and the 
 * labelSize variable (shape size) from main.
 * return value: Returns the string variable oFilename that contains
 * the output file name to main.
 * *****************************************************************/
string createOutputFilename(  string typeString, int labelSize ){
    string oFilename;

    oFilename = typeString + "_" + to_string(labelSize) + ".txt";
    return oFilename;

}

/* ******************************************************************
 * function_identifier: This function will prompt the user to type in
 * the name of the file containing the instructions that they wish to
 * open and then opens the input file through file stream.
 * parameters: The string variable "prompt" containing the prompt 
 * message, the input file stream variable "iFile", and the name of 
 * the input file (through cin). 
 * return value: Does not return any value, only opens the file.
 * ******************************************************************/
void openInputFile( ifstream& iFile, string prompt, string name ){
    
    cout << prompt;
    cin >> name;
    iFile.open(name.c_str());

}

/* ***********************************************************************
 * function_identifier: This function will create and open the output file
 * through file stream.
 * parameters: The output file stream variable "oFile" and the name of the 
 * output file "fname" (generated through createOutputFilename function).
 * return value: Always returns true. 
* ************************************************************************/
bool openOutputFile( ofstream & oFile, string fname){
        oFile.open(fname.c_str());
        return true;
}      

/* ****************************************************************************
 * function_identifier: This function will print out an arrow symbol 
 * according to the size and designated character specified in the 
 * instruction to the output file.
 * parameters: The output file stream "oFile", the size of the shape, and 
 * the character used for the shape "c".
 * return value: None, only prints out symbol to output file.
 * ****************************************************************************
    Algorithm
 1. Print out header of the file (include symbol, size, and character)
    *When width is even, width change message will be displayed
 2. Print out the width count (0-9) above the symbol through for loop
 3. Separate processing for even and odd size arrows
    *Even: 
    1)Midpoint is determined as size / 2
    2)Top portion of arrow: print out each row with gradual increase of spacing
      and character string length through for loop until midpoint is reached. 
    3)Print out extra center row
    4)Bottom portion of arrow: print out each row with gradual decrease of
      spacing and character string length through for loop and substring 
      function until size is reached.
    *Odd:
    1)Midpoint is determined as size / 2 + 1
    2)Top portion of arrow: print out each row with gradual increase of spacing
      and character string length until midpoint is reached. 
    3)Bottom portion of arrow: print out each row with gradual decrease of
      spacing and character string length until size is reached.
 4. Row count is incorporated into the arrow printing process, not in a
    separate loop like width count since it appears to the right of the 
    symbol.
* ******************************************************************************/
void makeArrow( ofstream& oFile, int size, char c ){

    int width;
    if(size % 2 == 0) //even width
        width = size - 1;
    else if(size % 2 == 1) //odd width
        width = size;
    int wCount = 0; //width count
    int wDisplay = 1; //displayed width count numbers (0-9)
    int row = 0; //row count
    int midpt = 0; //midpoint of arrow
    string str; //character display
    string spacing = " "; //increase spacing
    int cCount = 0; //character count
    int sCount = 0; //spacing count
    
    //Print out header
    oFile << "Symbol: Arrow " << "Size: " << size << " Character: '" << c 
          << "'" << endl;
    
    //Print out width change message for even size
    if(size % 2 == 0){
        oFile << "Note: Symbol size is even, width will be size-1: " 
              << width << endl;
    }
    
    //Print out width count
    oFile << "    ";
    for(wCount = 1; wCount <= width; wCount++){
            wDisplay = wCount % 10;
            oFile << wDisplay; 
    }
    oFile << endl;
    
    //Print out arrow with even size
    if(size % 2 == 0){
        midpt = size / 2;
        for(int i = 0; i < midpt; i++){
            row += 1;
            str = str + c;
            spacing = spacing + " ";
            oFile << setw(2) << row << spacing << str << endl;
        }
        //Print out extra center row
        row += 1;
        oFile << setw(2) << row << spacing << str << endl;
        
        cCount = str.length();
        sCount = spacing.length();
        for(int i = midpt + 1; i < size; i++){
            row += 1;
            cCount -= 1;
            sCount -= 1;
            oFile << setw(2) << row << spacing.substr(0,sCount)
                 << str.substr(0,cCount) << endl;
        }

    }
    
    //Print out arrow with odd size
    else if(size % 2 == 1){
        midpt = size / 2 + 1;
        for(int i = 0; i < midpt; i++){
            row += 1;
            str = str + c;
            spacing = spacing + " ";
            oFile << setw(2) << row << spacing << str << endl;
        }
        
        cCount = str.length();
        sCount = spacing.length();
        for(int i = midpt; i < size; i++){
            row += 1;
            cCount -= 1;
            sCount -= 1;
            oFile << setw(2) << row << spacing.substr(0,sCount)
                 << str.substr(0,cCount) << endl;
        }
    }

}  

/* *********************************************************************
 * function_identifier: This function will print out a bracket symbol 
 * according to the size and designated character specified in the 
 * instruction to the output file.
 * parameters: The output file stream "oFile", the size of the shape, and 
 * the character used for the shape "c".
 * return value: None, only prints out symbol to output file.
 * *********************************************************************
    Algorithm
 1. Print out header of the file (include symbol, size, width, 
    and character)
 2. Print out the width count (0-9) above the symbol through for loop
 3. Print out top part of bracket 
    *If thickness is equal to zero (0 < size < 10):
     1. Print out 1 row of specified amount of characters
    *If thickness is greater than zero;
     1. Print out "thickness" amount of rows (1,2,3 etc.) through for
        loop
 4. Print out middle part of bracket
    *If thickness is equal to zero (0 < size < 10):
     1. Print out one character per row
    *If thickness is greater than zero:
     1. Print out "thickness" amount of characters through for loop
 5. Print out bottom part of bracket
    *Same as top part of bracket
 6. Row count is incorporated into the arrow printing process, not in a
    separate loop like width count since it appears to the right of the 
    symbol.
* **********************************************************************/

void makeBracket( ofstream& oFile, int size, char c ){
    
    int width = size / 2;
    int height = size;
    int row = 0; //row count
    int thickness = size / 10; //thickness of bracket
    int wCount = 0; //width count
    int wDisplay = 1; //displayed width count numbers (0-9)
    string str; //character display
    
    //Print out header
    oFile << "Symbol: Bracket " << "Size: " << size << " Width: " 
          << width << " Character: '" << c << "'" << endl;
    
    //Print out width count
    oFile << "    ";
    for(wCount = 1; wCount <= width; wCount++){
            wDisplay = wCount % 10;
            oFile << wDisplay; 
    }

    oFile << endl;
    //Print out top part of bracket
    if(thickness > 0){
        for(int i = 0; i < thickness; i++){
            row += 1;
            oFile << setw(2) << row << "  ";
            for(int j = 0; j < width; j++){
                oFile << c;
            }
            oFile << endl;
        } 
    }
    else if(thickness == 0){
        row += 1;
        oFile << setw(2) << row << "  ";
        for(int i = 0; i < width; i++){
            oFile << c;
        }
        oFile << endl;
    } 

    //Print out middle part of bracket
        if(thickness == 0){
            
            for(int i = 0; i < (height - 2); i++){
                row += 1;
                oFile << setw(2) << row << setw(width + 2) << c << endl;
            }
        }
        else if(thickness > 0){
            for(int i = 0; i < thickness; i++){
                str  = str + c; 
            }
            for(int j = 0; j < (height - 2*thickness); j++){
                row += 1;
                oFile << setw(2) << row << setw(width + 2) << str << endl;
            }
        }

    //Print out bottom part of bracket
    if(thickness > 0){
        for(int i = 0; i < thickness; i++){
            row += 1;
            oFile << setw(2) << row << "  ";
            for(int j = 0; j < width; j++){
                oFile << c;
            }
                oFile << endl;
        } 
    }
    else if(thickness == 0){
        row += 1;
        oFile << setw(2) << row << "  ";
        for(int i = 0; i < width; i++){
            oFile << c;
        }
        oFile << endl;
    } 
        oFile << endl;

} 
/* *********************************************************************
 * function_identifier: This function will print out a theta symbol 
 * according to the size and designated character specified in the 
 * instruction to the output file.
 * parameters: The output file stream "oFile", the size of the shape, and 
 * the character used for the shape "c".
 * return value: None, only prints out symbol to output file.
 * *********************************************************************
    Algorithm
 1. Print out header of the file (include symbol, size, and character)
    *When width is even, width change message will be displayed
 2. Print out the width count (0-9) above the symbol
 3. Print out first line of theta 
    1)Run spacing loop to add appropriate number of spaces before the 
    characters (before midpoint)
    2)Print out three characters in the middle of theta as the first row
 4. Print out top part of theta through for loop
    1)Update spacing count "sCount" to length of "spacing".
    2)Subtract 2 from sCount to account for increased middle space (+2)
    3)Print out first character after "sCount" number of spaces
    4)Print out middle spacing count "msCount" number of spaces
    5)Print out second character after "msCount" number of spaces
    6)Update sCount by subtracting 1 to decrease number of spaces before
      first character
      *Spacing later fout through substring function
    7)Update msCount by adding 1 to increase number of spaces between
      first and second character
    8)For loop stops when it reaches midpoint number.
 5. Print out middle line of theta
    1)Print out "size" number of characters through for loop
 6. Print out bottom part of theta through for loop
    1)Update middle spacing count "msCount" to length of "mSpace"
    2)Add 2 to msCount to account for middle line and last line
    3)Subtract 1 to sCount to account for middle line
    4)Same as top part except sCount increases by 1 each time and 
      msCount decreases by 1 each time
 6. Print out last line of theta
    1)Reset spacing to zero spaces
    2)Run for loop to print out appropriate number of spaces before
      characters (before midpoint)
    3)Print out three characters
 7. Row count is incorporated into the arrow printing process, not in a
    separate loop like width count since it appears to the right of the 
    symbol.
* **********************************************************************/

void makeTheta( ofstream& oFile, int size, char c ){
    
    int row = 0; //row count
    int width;
    if(size % 2 == 0) //even width - convert to odd by + 1
        width = size + 1;
    else if(size % 2 == 1) //odd width
        width = size;
    int midpt = width / 2 + 1; //calculate the midpoint of width
    int wCount = 0; //width count
    int wDisplay = 1; //displayed width count numbers (0-9)
    string spacing; //spacing
    string mSpace = " "; //spacing in the middle of theta
    int sCount = 0; //spacing count
    int msCount = 0; //middle spacing count

    //Print out header
    oFile << "Symbol: Theta " << "Size: " << size << " Character: '" << c 
         << "'" << endl;
    
    //Print out width change message for even size
    if(size % 2 == 0){
        oFile << "Symbol size must be odd, Size is: " << width << endl;
    }

    //Print out width count (0-9)
    oFile << "    ";
    for(wCount = 1; wCount <= width; wCount++){
            wDisplay = wCount % 10;
            oFile << wDisplay; 
    }
    oFile << endl;

    //Print out first line of symbol (three characters in the middle).
    for(int i = 0; i < midpt; i++){
        spacing = spacing + " ";
    }
    oFile << " 1" << spacing << c << c << c << spacing << endl;

    //Print out upper part
    sCount = spacing.length();
    row = 1;
    sCount = sCount - 2;
    for(int i = 2; i < midpt; i++){
        row += 1;
        sCount -= 1;
        mSpace = mSpace + "  ";
        oFile << setw(2) << row << "  " << spacing.substr(0,sCount) << c << mSpace
             << c << endl;
    }

    //Print out middle line of characters
    row += 1;
    oFile << setw(2) << row << "  ";
    for(int i = 0; i < width; i++){
        oFile << c;
    }
    oFile << endl;

    //Print out lower part
    msCount = mSpace.length();
    msCount = msCount + 2;
    sCount = sCount - 1;
    for(int i = midpt - 2; i > 0; i--){
        row += 1;
        sCount += 1;
        msCount -= 2;
        spacing = spacing + " ";
        oFile << setw(2) << row << "  " << spacing.substr(0,sCount) << c 
             << mSpace.substr(0,msCount) << c << endl;
    }

    //Print out last line of symbol (three characters in the middle)
    row += 1;
    spacing = ""; //Spacing is reset to zero spaces.
    for(int i = 0; i < midpt; i++){
        spacing = spacing + " ";
    }
    oFile << setw(2) << row << spacing << c << c << c << spacing << endl; 
}