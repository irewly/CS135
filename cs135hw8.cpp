/*
 * Name: Irene Wang, 5005298618, Assignment 8
 * Description: This program will open a user-specified input Run Length Encoded
 * file using file stream. The input file will then be stored into an array which
 * is then used to decompress the file through various functions. The decompressed
 * file is then printed to a user-specified output file to generate an image.
 * Input: Run Length Encoded input file containing numbers following
 * "# of character, ASCII value" format.
 * Output: Decompressed output file containing character symbols encoded in the 
 * RLE file (to generate an image).
 */

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int ARRAY_SIZE = 20000; // Maximum array size

void processFile( ifstream& in, ofstream& of );
void processBuffer( ofstream& of, int b[],  int size );
void openInputFile( ifstream& iFile, string promptString, string name );
void openOutputFile( ofstream& oFile, string promptString, string name);
void getBuffer( ifstream& in , int& count, int b[] );

int main(int argc, char * argv[])
{
    string iName;
    string oName;
    ifstream iFile;
    ofstream oFile;
    
    switch( argc ){
        case 3:
            oName = argv[2];

        case 2:
            iName = argv[1];

    }
            

    // Open the file that contains the Archimedean solid types and edge length
    // openInputFile function only called when user did not input additional 
    // argc after "./a.out". 
    // Error message keep prompting user until input file is opened successfully
    if(argc == 1){
        openInputFile( iFile, "Enter input data filename: ", iName  );
    }
    else{
        iFile.open(iName.c_str());
        while(iFile.fail()){
            cout << "Input file: \"" << iName << "\" did not open" << endl;
            cout << "Enter input data filename: ";
            cin >> iName;
            iFile.open(iName.c_str());
        }
    }

    // Open output decompressed file
    // openInputFile function only called when user did not input third argument
    // Error message keep prompting user until output file is opened successfully
    if(argc < 3){
        openOutputFile( oFile, "Output filename: ", oName);
    }
    else{
        oFile.open(oName.c_str());
        while(oFile.fail()){
            cout << "Output file: \"" << oName << "\" did not open" << endl;
            cout << "Output filename: ";
            cin >> oName;
            oFile.open(oName.c_str());
        }
    }

    // Read the input data file of types and edge lengths into the arrays types
    // and edge  
    processFile( iFile, oFile );

    oFile.close();

}

/* ***********************************************************************
 * function_identifier: This function will declare and initialize integer
 * array b[] with a size of "ARRAY_SIZE" (20000). It will also declare
 * and initialize the integer variables count and size (which are 
 * essentially the same value for different functions). The do while loop
 * will run once before checking to see if the count is 0 (which 
 * shouldn't be the case until the getBuffer is done reading). It calls
 * getBuffer first to store the integer values from the input file to the
 * array and obtain the location of the values in the array through 
 * "count". The if statement checks to see if "count" equals 0 (which 
 * means end of file and no need to run processBuffer). If not, function
 * processBuffer is called to convert the integer values into characters
 * and print out the decompressed message to the output file. The loop
 * stops when getBuffer resets "count" to 0 which signifies end of file
 * or exceeding array size.
 * parameters: The input file stream variable "in" and the output file
 * stream variable "of".
 * return value: None, void function.
 * ***********************************************************************/

void processFile( ifstream& in, ofstream& of ){
    
    int b[ARRAY_SIZE];
    int count = 0;
    int size = 0;
    do{
        getBuffer(in, count, b);
        if(count != 0){
            processBuffer(of, b, count);
        }
    }while(count != 0);

}    

/* ***********************************************************************
 * function_identifier: This function will obtain the array location of 
 * variable "repetition" (# of characters) and "c" (character converted
 * from ASCII value) through "count" from getBuffer (here changed to
 * "size"). Since "count" increases by 1 everytime it reads in an integer
 * value from the input file, to track back the first integer stored in
 * the array (which contains "repetition"), the array location is
 * determined by "size - 2", which for the first one would be stored in
 * b[2 - 2] or b[0]. To track back the second integer stored in the array 
 * (which contains "c"), the array location is determined by"size - 1", or 
 * 1 after the first integer, in this case, b[2 - 1] or b[1]. "Repetition"
 * is then used in the for loop to determine how many times "c" will be 
 * printed to the output file. "c" is converted from the ASCII value 
 * stored in the array to character.
 * parameters: The output file stream variable "of", integer arrray b[],
 * and the size of the array (previously stored as "count").
 * return value: None, void function.
 * ***********************************************************************/

void processBuffer( ofstream& of, int b[],  int size ){
    int repetition = b[size - 2];
    char c = b[size - 1];

    for(int i = 0; i < repetition; i ++){
        of << c;
    }
}

/* ***********************************************************************
 * function_identifier: This function will open the input file through 
 * file stream. If the input file fails to open, error message will be 
 * displayed and user will be prompted to try again until file opens
 * successfully.
 * parameters: The input file stream variable "iFile", the input file
 * name prompt, and the name of the file.
 * return value: None, void function.
 * ***********************************************************************/

void openInputFile( ifstream& iFile, string promptString, string name )
{
    cout << promptString;
    cin >> name;
    iFile.open(name.c_str());
    while(iFile.fail()){
        cout << "Input file: \"" << name << "\" did not open" << endl;
        cout << promptString;
        cin >> name;
        iFile.open(name.c_str());
    }
}

/* ***********************************************************************
 * function_identifier: This function will create and open the output file
 * through file stream. If the output file fails to open, error message 
 * will be displayed and user will be prompted to try again until file 
 * opens successfully.
 * parameters: The output file stream variable "oFile", the output file 
 * name prompt, and the name of the output file.
 * return value: None, void function. 
 * ***********************************************************************/

void openOutputFile( ofstream& oFile, string promptString, string name)
{
    cout << promptString;
    cin >> name;
    oFile.open(name.c_str());
    while(oFile.fail()){
        cout << "Output file: \"" << name << "\" did not open" << endl;
        cout << promptString;
        cin >> name;
        oFile.open(name.c_str());
    }
}

/* ***********************************************************************
 * function_identifier: This function will read in the integer content 
 * within the RLE compressed file and store them in integer array b[].
 * The size or "count" of the array increase by 1 everytime a new integer
 * is stored in the array. When the size of the array reaches the max
 * (indicated by ARRAY_SIZE) or program reaches end of input file, "count"
 * is reset to zero to signify the while loop in processFile to stop.
 * parameters: Input file stream "in", pass by reference integer variable
 * "count" (or size of array), integer array b[].
 * return value: None, void function.
 * ***********************************************************************/

void getBuffer( ifstream& in , int& count, int b[] ){
    int content = 0;
    in >> content;

    b[count] = content;
    count ++;
    in >> content;
    b[count] = content;
    count ++;
    
    if(count > ARRAY_SIZE || in.eof()){
        count = 0;
    }
}