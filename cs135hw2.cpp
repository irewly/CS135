/*
 * Name: Irene Wang, 5005298618, Assignment 2
 * Description: This program will calculate the radius of a sandworm based
 * on the slant distance and angle measurements taken by the drone.
 * Input: Slant distance and slant angle measurements.
 * Output: Radius of the sandworm.
 */

#include<iostream>
#include<string>
//This grants access to the cmath library and allows use of mathematical
//operations sin(), sqrt(), and pow().
#include<cmath>

using namespace std;

int main(){

    //Variable declarations and initilizations:

    //This initializes the variables beta (slant angle) and
    //sd (slant distance) as doubles with a value of 0.
    double beta = 0;
    double sd = 0;
    //This identifies PI as a double constant with a value of 3.14159.
    const double PI = 3.14159;
    //Double x and double y are given code fragments.
    double x = 0.0;
    //Double y is the value of 90 degrees in radians.
    double y = 1.570795;
    //Double radian is the value of beta in radians.
    double radian;
    //Double alpha is the value of alpha in radians.
    double alpha;
    //Double cL is the value of chordLength in feet.
    double cL;
    //Double radius is the value of sandworm radius in feet.
    double radius;

    //This formula is a given code fragment used to calculate the sin.
    x = sin (y);

    /*
     * This is the program prompt that asks the user to input the
     * values of beta in degrees and slant distance (sd) in feet.
     * into the program through "cin".
     * The values for the variables are then saved and used to
     * perform the later calculations for the radius of the
     * sandworm.
     */
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "Program to calculate a sandworm radius" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
    cout << "Enter beta in degrees: ";
    cin >> beta;
    cout << "Enter the slant distance (feet): ";
    cin >> sd;

    /*
     * The following formulas are adapted from the given formulas
     * with new variables defined above to calculate sandworm radius.
     */

    //Since the user initially inputs the value of beta in degreees,
    //this equation converts the value of beta into radians in order to perform the
    //sin functions later on.
    radian = beta * PI / 180;
    alpha = y - radian / 2;
    cL = sd * sin(radian) / sin (alpha);
    radius = cL * sin (y - alpha) / sin (alpha * 2);

    /*
     * The following is the formatted cout statements that will be displayed
     * after the beta and slant distance have been inputed by the user.
     * It will echo print the values of beta and slant distance for the user
     * to double check, along with the calculated value of the sandworm radius.
     */
    cout << ">>>>>>>>>>>>>>>>>>>>>" << endl;
    cout << "Sandworm calculations" << endl;
    cout << "Beta: " << beta << " degrees" << endl;
    cout << "Slant distance: " << sd << " feet" << endl;
    cout << "Radius: " << radius << " feet" << endl;

    return 0;
}
