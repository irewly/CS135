/*
 * Name: Irene Wang, 5005298618, Assignment 6
 * Description: This program will allow the user to either decipher an
 * encrypted message in an existing file or encrypt a message in an
 * existing file with security through obscurity. The whole process 
 * occurs outside the terminal through file streams (in/out).
 * Input: Decipher: The encrypted message file (input.txt).
 * Encrypt: The message itself (input.txt).
 * Output: Decipher: The message itself stored in a new file (output.txt).
 * Encrypt: The encrypted message stored in a new file (output.txt).
 */

#include<iostream>
#include<fstream> //Used for file streams.
#include<time.h> //Time used as seed for random character generation.
#include<cstdlib> //Used random generation & alpha to integer convertion.
#include<iomanip> //Input/Output manipulator.

using namespace std;

//Main function allows for commandline operations (0 & 1).
int main(int argc, char **argv){
   
    //This statement confirms that the program is running.
    cout << "Filestream Assignment 6" << endl;
   
    /* 
     * The program only runs when the argument count is equal
     * to 2 (which means the user have put an additional command after
     * ./a.out).
     */
    if(argc == 2){
        
        /* 
         * The integer variable "command" is converted from the user's
         * character input (alpha). This is then used to determine which
         * if statement to run. 
         */
        int command = 0;
        command = atoi(argv[1]);
        
        //The first if statement runs the program that deciphers the encrypted
        //message. It runs when the user put a "0" after ./a.out.
        if(command == 0){
           
            //"fin" is the file containing the encrypted message, in this
            //case it is the file "input.txt".
            ifstream fin;
            fin.open("input.txt");
            //The strings inside the fin file are refered to as the string
            //variable "word".
            string word;
            
            //"fout" is the file that will be created to contain the deciphered
            //message, in this case the file "output.txt" will be created.
            ofstream fout;
            fout.open("output.txt");
            
            //This while loop runs to feed the strings, or "word"s, inside the
            //fin file into the program.
            while(fin >> word){
                
                //Since jarjar is the keyword before the actual messsage content,
                //this if statement runs when the loop discovers the word "jarjar".
                if(word == "jarjar"){
                    
                    //This statement makes the program take in the word after
                    //"jarjar". This word is the one that is part of the actual message.
                    fin >> word;
                    
                    /* 
                     * However, to make things even more complicated, the program needs to 
                     * ignore the word "jarjar" if it appears by itself at the end of the 
                     * encrypted message or if "jarjar" is followed by another "jarjar". 
                     * Since "jarjar" is only the keyword and not part of the actual message,
                     * this if statement ensures that the word only gets printed out into the
                     * output file if the word itself is not "jarjar".
                     */
                    if(word != "jarjar"){
                        
                        //The fout statement allows "word" to be printed out to the output file. 
                        //The space after "word" is used to separate the words.
                        fout << word << " ";
                    }
                }
            }
            
            //These two statements close the input and output files.
            fin.close();
            fout.close();
        }
    
        //The second if statement runs the program that encrypts the actual
        //message. It runs when the user put a "1" after ./a.out.
        if(command == 1){
            
            /*
             * Since the encryption by obscurity requires random generation of 
             * characters (letters), the linux time is used as the seed for
             * random generation.
             */
            srand(time(NULL));
            
            //"fin" is the file containing the actual message, in this
            //case it is the file "input.txt".
            ifstream fin;
            fin.open("input.txt");
            //Instead of "word", this time the string variable "message" will
            //be used to represent and feed the strings inside the input file.
            string message;

            //"fout" is the file that will be created to contain the encrypted
            //message, in this case the file "output.txt" will be created.
            ofstream fout;
            fout.open("output.txt");

            //This while loop runs to feed the strings, or "message"s, inside the
            //input file into the program.
            while(fin >> message){
                
                /* The for loop runs to generate the series of random strings used
                 * to encrypt before "jarjar" and the message word. 
                 * The integer variable "sNumber" is used to determine the number of 
                 * strings that appear before "jarjar" and the message word. 
                 * The range is determined by rand() modulus range plus starting number.
                 * This is set so that 5-10 strings will be randomly generated. 
                 * The for loop terminates when the random number of strings have been generated
                 * (in a count down fashion).
                 */
                for (int sNumber = rand() % 6 + 5; sNumber > 0; sNumber--){
                    
                    /*
                     * The nested for loop runs to generate the individual strings themselves. 
                     * The integer variable "sLength" is used to determine the number of 
                     * characters inside the string. The range is set so that the strings are
                     * 4-10 characters long. The loop terminates when the number of characters
                     * in the string have been met.
                     */
                    for(int sLength = rand() % 7 + 4; sLength > 0; sLength--){
                        
                        /* 
                         * The integer variable "letter" is used to randomly generate the 
                         * actual letters inside the random string. "Letter" have a range 
                         * of 26 to account for the 26 letters of the alphabet. 
                         */
                        int letter = rand() % 26;
                        /* 
                         * The character variable "character" starts at "97", which is the 
                         * ASCII value for the lowercase letter "a". Depending on the value
                         * generated by "letter", "character" changes to cover the range of 
                         * letters from a through z. For example, if "letter" have a value
                         * of "1", then the character generated would be "b" since b has
                         * an ASCII value of 98 (97 + 1).
                         */
                        char character = 97 + letter;
                        //The "character"s generated then fout to the output.txt file. 
                        fout << character;  
                    }
                    
                    //The space is used to separate the randomly generated strings.
                    fout << " ";
                }
                
                //This is where the keyword "jarjar" and the actual message word are inserted
                //after the random string encryption.
                fout << "jarjar " << message << " ";
            }
            
            /*
             * After the while loop is done encrypting the  message, the random string 
             * generating for loop runs again after the last message word to complete 
             * the encrypted file by generating a series of random strings at the end 
             * of the file. 
             */
            for (int sNumber = rand() % 6 + 5; sNumber > 0; sNumber--){
                for(int sLength = rand() % 7 + 4; sLength > 0; sLength--){
                    int letter = rand() % 26;
                    char character = 97 + letter;
                    fout << character;  
                }
                fout << " ";
            }
            
            //The keyword "jarjar" is used as per instruction examples to signify the
            //end of the file as the last word in the file.
            fout << "jarjar";
            
            //These two statements close the input and output files.
            fin.close();
            fout.close();
        }
    }
    
    cout << endl;
    return 0;
}