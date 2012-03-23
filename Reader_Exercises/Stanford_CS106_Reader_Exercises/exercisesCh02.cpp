//
//  exercisesCh02.cpp
//  CS106B_Reader_Excercises
//
//  Created by Scott Brenner on 2/13/12.
//  Copyright (c) 2012 __MyCompanyName__.
//

#include <iostream>
#include "exercisesCh02.h"
#include <math.h>
using namespace std;

void chapter02(){
    short exerciseSelection;
    cout << "Chapter 02: Enter the exercise number to execute: ";
    cin >> exerciseSelection;
    switch (exerciseSelection) {
        case 1:{
            double celcius = 0.0;
            cout << "Enter a temperature in Celcius: ";
            cin >> celcius;
            cout << celcius << " Celcius is " << celciusToFarenheit( celcius ) << " Farenheit." << endl;
        }
        break;

        case 2:{
            double meters;
            int feet;
            double inches;
            cout << "Enter a distance in meters and I will convert it to feet and inches: ";
            cin >> meters;
            metersToFeet( meters, feet, inches );
            cout << meters << " meters is " << feet << " feet and " << inches << " inches." << endl;
        }
        break;
        case 3:{
            cout << "This exercise will repeat four times." << endl;
            for (int i=0; i < 4 ; i++) {
                double realNum;
                cout << "Enter a real number and it will be rounded to the nearest integer: ";
                cin >> realNum;
                cout << realNum << " rounded to the neares integer is " << roundToNearestInt(realNum) << "." << endl;
            }
        }
        break;
        case 4:{
            double temperatureF;
            double windSpeed;
            cout << "Enter the temperature in Farenheit: ";
            cin >> temperatureF;
            cout << "Enter the windspeed in mph: ";
            cin >> windSpeed;
            cout << "The wind chill is " << windChill( temperatureF, windSpeed ) << "." << endl;
        }
        break;            
//        case 5:
//            break;
//        case 6:
//            break;
//        case 7:
//            break;
//        case 8:
//            break;
//        case 9:
//            break;
//        case 10:
//            break;
//        case 11:
//            break;
//        case 12:
//            break;
        default:
            break;
    }
    return;
}

/*  Exercise 1
 *
 *  If you did not do so the first time around, rewrite the 
 *  Celsius-to-Fahrenheit program from exercise 1 in Chapter 1
 *  so that it uses a function to perform the conversion.
 */
double celciusToFarenheit( double celcius ){
    return ( 9.0 / 5.0 * celcius ) + 32;
}


/*  Exercise 2
 *
 *  Reimplement the distance-conversion program from exercise 2 in Chapter 1
 *  so that it uses a function. In this case, the function must produce both
 *  the number of feet and the number of inches, which means that you need to
 *  use call by reference to return these values.  
 */
void metersToFeet(double meters, int &feet, double &inches){
    // convert meters to inches
    double totalInches =  meters / .0254;
    
    // convert inches to feet and inches
    feet = totalInches / 12;
    inches = int(totalInches) % 12;    
    return;
}


/*  Exercise 3
 When a floating-point number is converted to an integer in C++, the value is 
 truncated by throwing away any fraction. Thus, when 4.99999 is converted to an
 integer, the result is 4. In many cases, it would be useful to have the option
 of rounding a floating-point value to the nearest integer. Given a positive
 floating-point number x, you can round it to the closest integer by adding 0.5
 and then truncating the result to an integer. Because truncation always moves
 toward zero, rounding negative numbers requires you to subtract 0.5, rather than
 adding it.
 
 Write a function roundToNearestInt(x) that rounds the floating-point number x to
 the nearest integer. Show that your function works by writing a suitable main
 program to test it.
 
 */
int roundToNearestInt(double x){
    if (x >= 0) {
        x += .5;
        return int(x);
    }
    else{
        x -= .5;
        return int(x);
    }
}

/* Exercise 4

 If you are unfortunate enough to be outside in winter weather, you know that your perception of the cold is dependent on the wind speed as well as the temperature. The faster the wind blows, the colder you feel. To quantify the how wind affects temperature perception, the National Weather Service reports the wind chill, which is illustrated on their website as shown in Figure 2-15. At the bottom of the figure, you can see that the formula for wind chill is
 35.74 + 0.6215 t – 35.75 v 0.16 + 0.4275 t v 0.16
 where t is the Fahrenheit temperature and v is the wind speed in miles per hour.
 ￼￼￼
 118 Functions and Libraries
 Write a function windChill that takes the values of t and v and returns the wind chill. In doing so, your function should take account of two special cases:
 • If there is no wind, windChill should return the original temperature t.
 • If the temperature is greater than 40° F, the wind chill is undefined, and
 your function should call error with an appropriate message.
 Although it will be easier to do so once you learn how to format numeric data in Chapter 4, you already know enough to generate a table that presents the wind-chill data in columns as shown in Figure 2-15. If you’re up for more of a challenge, write a main program that uses windChill to produce that table.
*/
double windChill(double t, double v ){
    if (v == 0) {
        return t;
    }
    if (t > 40 ){
        //        error("Windchill is undefined for temperature above 40.")
        return t;
    }
    return 35.74 + .06215 * t - 35.75 * pow(v, .16) + .4275 * t * pow(v,.16);
//    return 35.74 + 0.6215 * t - 35.75 pow(v, 0.16) + 0.4275 * t * pow(v, 0.16);
    
}