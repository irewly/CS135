/*
 * Name: Irene Wang, 5005298618, Assignment 3
 * Description: This program will let the user to run either a calculator
 * or a anime club admission quiz.
 * Input: The user will first choose either calculator or quiz.
 * Calculator: first and second number, and the operation
 * that the user wishes to perform with those numbers.
 * Quiz: The user will input a series of answers to the 
 * displayed questions.
 * Output: The program will either run calculator or quiz based on user's
 * first input.
 * Calculator: The program will perform the operations that the user chose
 * to do with the two numbers and display the answer in the terminal.
 * Quiz: The program will calculate the user's score based on their inputs
 * to the quiz questions and then display one of three messages in the
 * terminal to inform the user whether they are accepted, banned, or 
 * made the club president.
 */

#include<iostream>
#include<string>
#include<cmath>

using namespace std;

int main(){
    
    //All of the variables used are defined here.

    //The string variable "choice" stores the user's choice of either 
    //calculator or quiz.
    string choice;
    
    //The string variable "operation" stores the user's choice of 
    //operation to perform with the two numbers they inputed.
    string operation;
    //The double variable "first" stores the first number that the
    //user inputed with the calculator program. 
    float first = 0;
    //The double variable "second" stores the second number that the
    //user inputed with the calculator program.
    float second = 0;

    //The integer variable "score" stores the user's test score
    //based on their answers to the quiz questions.
    int score = 0;
    //The string variable "answer" is used to store the user's
    //response to each quiz question.
    string answer;
    
    /* 
     * This initial prompt asks the user to choose the program they
     * would like to run. Their answer is then stored in the 
     * "choice" variable to enable different if else statments 
     * corresponding to each program.
     */
    cout << "Enter Which Program You Wish To Run:" << endl;
    cout << "A: Calculator" << endl;
    cout << "Q: Quiz" << endl;
    cin >> choice;
    
    /*
     * If the user types in the letter "A" (here stored as string)
     * then the corresponding if statement for the calculator 
     * program will run. The cout statemnt of "Running Calculator"
     * will inform the user that the calculator is currently running.
     */
    if(choice == "A"){
        cout << "\nRunning Calculator" << endl;
        /*
         * The cout statements will prompt the user to input two
         * numbers which are then stored inside the "first" and "second"
         * variable and used for later operations.
         */
        cout << "Enter First Number: ";
        cin >> first;
        cout << "Enter Second Number: ";
        cin >> second;
        /* 
         * The following cout statement provides the user with a list of 
         * different operations they can perform with the two numbers that
         * they previously inputed, as well as the corresponding letters
         * they need to input in order to perform the operation. The
         * letter they typed in here will be stored in the "operation"
         * variable used to run the corresponding if else statements.
         */
        cout << "Enter operation to perform from list: \n"
                "A: Addition \n"
                "S: Subtraction \n"
                "M: Multiplication \n"
                "D: Division \n"
                "P: Power \n"
                "C: Comparison \n"
                "O: Modulus \n" << endl;
        cin >> operation;
        /*
         * The following if and else if statements denote to each of 
         * the above operations. Depending on the user's input, 
         * different operations will be performed with the previously 
         * stored values for the "first" and "second" variables. 
         * There are exceptions for dividing by zero and zero to the
         * negative power, in which case a special message will appear
         * and the program will abort.
         * 
         * If the user inputed something that is not any of the above 
         * letters, the else statement for changing the sign of the 
         * first number will be run. 
         */
        if(operation == "A"){
            cout << "The Answer to Life is: " << first + second << endl;
        }
        else if(operation == "S"){
            cout << "The Answer to Life is: " << first - second << endl;
        }
        else if(operation == "M"){
            cout << "The Answer to Life is: " << first * second << endl;
        }
        else if(operation == "D"){
            if(second == 0){
                cout << "Division by Zero Detected. Aborting!" << endl;
                return -1;
            }
            else{
                cout << "The Answer to Life is: " << first / second << endl;
            }
        }
        else if(operation == "P"){
            if(first == 0 && second < 0 ){
                cout << "Division by Zero Detected. Aborting!" << endl;
                return -1;
            }
            else{
            cout << "The Answer to Life is: " << pow(first, second) << endl;
            }
        }
        else if(operation == "C"){
            if(first < second){
                cout << first << " is less than " << second << endl;
            }
            else if(first > second){
                cout << first << " is greater than " << second << endl;
            }
            else{
                cout << first << " is equal to " << second << endl;
            }
        }
        else if(operation == "O"){
            if(second == 0){
                cout << "The second number of modular operation cannot be 0. "
                        "Aborting!" << endl;
                return -1;
            }
            else{
                cout << "The Answer to Life is: " << int(first) % int(second) << endl;
            }
        }
        else{
            cout << "The Answer to Life is: " << -first << endl;
        }   
    }
    
    /* 
     * If the user types in the letter "Q" (here stored as string)
     * then the corresponding else if statement for the quiz program will run. 
     * The cout statemnt of "Running Quiz"will inform the user that the 
     * quiz program is currently running.
     * The user will then be greeted with information and instructions
     * for the Automated Anime Club Test along with the first question.
     */
    else if(choice == "Q"){
        cout << "Running Quiz" << endl;
        cout << "Hello there, Welcome to the Automated Anime Club Test," << endl;
        cout << "Please Answer each Question with a Y for Yes, and N for No.\n"; 
        cout << endl;
        /* 
         * The user's input for each question will be stored in the "answer"
         * string variable. This variable is then used to determine the 
         * corresponding if statement to be run. Depending on the answer,
         * the if statement either adds, subtracts, or keeps the current 
         * quiz score (initialized as 0). If the user inputs anything that
         * is not "Y" or "N" ("U/W" for the last question), the else statement
         * will run and no change is made to their score.
         * The quiz score is stored in the integer variable "score" to keep 
         * track and used to determine the final outcome of the quiz.
         */
        cout << "Do you agree that Japanese animation are nothing more than "
                "cartoons?" << endl;
        cin >> answer;
        if(answer == "Y"){
            score = score - 5;
        }
        else if(answer == "N"){
            score = score + 5;
        }
        else{
            score = score + 0;
        }
        
        cout << "Can you tell when people are speaking Japanese? ";
        cin >> answer;
        if(answer == "Y"){
            score = score + 5;
        }
        else if(answer == "N"){
            score = score - 5;
        }
        else{
            score = score + 0;
        }
        
        cout << "Do you hate body pillows? ";
        cin >> answer;
        if(answer == "Y"){
            score = score - 5;
        }
        else if(answer == "N"){
            score = score + 5;
        }
        else{
            score = score + 0;
        }
        
        cout << "Have you seen the toothbrush scene? ";
        cin >> answer;
        if(answer == "Y"){
            score = score + 5;
        }
        else if(answer == "N"){
            score = score - 5;
        }
        else{
            score = score + 0;
        }
        
        //The following two questions do not affect the user's score in any way.
        cout << "Did you ever hear the tragedy of Darth Plagueis The Wise? ";
        cin >> answer;
        if(answer == "Y"){
            score = score + 0;
        }
        else if(answer == "N"){
            score = score - 0;
        }
        else{
            score = score + 0;
        }
        cout << endl;
        cout << 
                "I thought not. It's not a story the Jedi would tell you. It's a Sith\n"
                "legend. Darth Plagueis was a Dark Lord of the Sith, so powerful and\n"
                "so wise he could use the Force to influence the midichlorians to\n"
                "create life... He had such a knowledge of the dark side that he could\n"
                "even keep the ones he cared about from dying. The dark side of the\n"
                "Force is a pathway to many abilities some consider to be unnatural.\n"
                "He became so powerful... the only thing he was afraid of was losing\n"
                "his power, which eventually, of course, he did. Unfortunately, he\n" 
                "taught his apprentice everything he knew, then his apprentice killed\n"
                "him in his sleep. It's ironic he could save others from death, but\n"
                "not himself." << endl;
        cout << endl;
        cout << "Is it possible to learn this power? ";
        cin >> answer;
        if(answer == "Y"){
            score = score + 0;
        }
        else if(answer == "N"){
            score = score - 0;
        }
        else{
            score = score + 0;
        }
        
        cout << "Do you own anything imported from Japan excluding Cameras and\n"
                "watches? ";
        cin >> answer;
        if(answer == "Y"){
            score = score + 5;
        }
        else if(answer == "N"){
            score = score - 5;
        }
        else{
            score = score + 0;
        }
        
        cout << "Do you use or watch “bleach” ? Answer U for use, W for watch) ";
        cin >> answer;
        if(answer == "U"){
            score = score - 5;
        }
        else if(answer == "W"){
            score = score + 5;
        }
        else{
            score = score + 0;
        }
        cout << endl;
        
        /* 
         * The user's quiz outcome is determined by the "score" variable.
         * If their score is less than or equal to 0, the first message will
         * cout to the terminal. 
         * If their score is greater than 0 but less than 30, the second 
         * message will cout to the terminal.
         * If their score is equal to 30 (maximum score), the third 
         * message will cout to the terminal.
         */ 
        if(score < 0 || score == 0){
            cout << "You are a traitor and spy, begone!" << endl;
        }
        else if(score > 0 && score < 30){
            cout << "Congratulations. You are in this council, but we do not grant "
                    "you the rank of Master." << endl;
        }
        else{
            cout << "Oni Chan? You are hereby granted Club President!" << endl;
        }
    }
    
    /*
     * If during initial program selection the user inputs anything other than 
     * "A" for calculator and "Q" for quiz, the following message will cout to 
     * the terminal.
     */ 
    else{
        cout << "Invalid Entry, Goodbye!" << endl;
    }
    
    return 0;
}