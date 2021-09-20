/*
 * Name: Irene Wang, 5005298618, Assignment 1
 * Description: This program will output to the terminal
 * an excerpt from the Constitution and Bill of Rights.
 * Input: Programmed excerpt of the Constitution following 
 * K&R style formatting guidelines.
 * Output: The excerpt will be displayed on the terminal
 * in the exact format as the example.
 */

/*
 * This is the preprocessor directive, it allows the 
 * usage of "cout" to generate output and "endl" from pre-existing code 
 * library <iostream>.
 */
#include<iostream> 

// This provides all the string capabilities to the program.
#include<string>

/*
 * This allows for the usage of "cout" and "endl" 
 * without the prefix "std::".
 */
using namespace std;

/*
 * This is the heading of the function "main".
 * "int" is a reserved word or keyword.
 */
int main()

/*
 * This is marks the beginning of the actual program,
 * the start of a function". 
 */
{
    
/*
 * "cout" is the output statement to the terminal.
 * "<<" is an insertion operator that allows output expression to be 
 * sent to a destination, in this case, "cout", or the terminal.
 * Items inside the "" sign are "strings" that evaluates to itself.
 * The semicolon signifies the end of a programming line. 
 */
    cout << "***************************************************************";
    
// "\n" is the linefeed character that inserts a new line.
    cout << "***************** \n";
    cout << "We the People of the United States, in Order to form a more ";
    cout << "perfect Union,     * \n";
    cout << "establish Justice, insure domestic Tranquility, provide for ";
    cout << "the common defence, \n";
    cout << "promote the general Welfare, and secure the Blessings of "; 
    cout << "Liberty to ourselves \n";
    cout << "and our Posterity, do ordain and establish this Constitution ";
    cout << "for the \n";

/* 
 * "endl" is the endline statement that causes the 
 * insertion point to move to the beginning of the next line.
 */ 
    cout << "United States of America. \n" << endl;

    cout << "Article. I. \n";
    cout << "Section. 1. \n" << endl;

    cout << "All legislative Powers herein granted shall be vested in a \n"; 
    cout << "Congress of the United States, which shall consist of a \n";
    cout << "Senate and House of Representatives. \n";
    cout << "... \n";
    cout << "Article. VII. \n" << endl;

    cout << "The Ratification of the Conventions of nine States, shall be ";
    cout << "sufficient \n";
    cout << "for the Establishment of this Constitution between the ";
    cout << "States \n";
    cout << "so ratifying the Same. \n" << endl;

    cout << "The U.S. Bill of Rights \n" << endl;

    cout << "Amendment I \n" << endl;

    cout << "Congress shall make no law respecting an establishment of ";
    cout << "religion, \n"; 
    cout << "or prohibiting the free exercise thereof; or abridging the ";
    cout << "freedom of speech, \n";
    cout << "or of the press; or the right of the people peaceably to ";
    cout << "assemble, \n";
    cout << "and to petition the Government for a redress of grievances. \n"; 
    cout << endl;

    cout << "Amendment II \n" << endl;

    cout << "A well regulated Militia, being necessary to the security of a ";
    cout << "free State, \n"; 
    cout << "the right of the people to keep and bear Arms, shall not be ";
    cout << "infringed.         * \n";
    cout << "***************************************************************";
    cout << "*****************" << endl;
    
//This statement is necessary at the end of program.
    return 0;

//This signals the end of the program, closes the function.
}
