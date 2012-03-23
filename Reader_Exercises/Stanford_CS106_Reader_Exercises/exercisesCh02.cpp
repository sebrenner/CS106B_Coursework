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
			cout << endl;
			createWindChillTable();
        }
			break;            
        case 5:{
			problem5();
			break;
		}
        case 6:
			problem6();
            break;
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
double windChill( double t, double v ){
    if (v == 0) {
        return t;
    }
    if (t > 40 ){
        //        error("Windchill is undefined for temperature above 40.")
        return t;
    }
	double v16 = pow( v, .16 );

	double windChillTemp = 35.74 + (.6215 * t) - (35.75 * v16) + (.4275 * t * v16);
	
    return windChillTemp;
}

void createWindChillTable(){
	//	Print table title
	std::cout <<	"\t\t\t\t\t\tWindchill Table\n\t\t\t\tTemperature in Farenheit\n\n";

	//	print table header
	std::cout << "Calm";
	for (int t = 40; t >= -45; t -= 5) {
		std::cout << "\t" << t;
	}
	std::cout << std::endl;
	
	//  Print each row of table starting with windspeed	
	for ( int v = 5; v <= 60; v+=5 ) {
		std::cout << v << "\t";
		for (int t = 40; t >= -45; t -= 5) {
			std::cout << "\t" << int( windChill( t, v ) );
		}
		std::cout << std::endl;
	}
}

/* Problem 5

 Greek mathematicians took a special interest in numbers that are equal to the sum of their proper divisors (a proper divisor of n is any divisor less than n itself). 
 They called such numbers perfect numbers. For example, 6 is a perfect number because it is the sum of 1, 2, and 3, which are the integers less than 6 that divide evenly into 6. Similarly, 28 is a perfect number because it is the sum of 1, 2, 4, 7, and 14.
 
 Write a predicate function isPerfect that takes an integer n and returns true if n is perfect, and false otherwise. Test your implementation by writing a main program that uses the isPerfect function to check for perfect numbers in the range 1 to 9999 by testing each number in turn. When a perfect number is found, your program should display it on the screen. The first two lines of output should be 6 and 28. Your program should find two other perfect numbers in the range as well.

 Note this problem is also in Programming Assignment 01.
 
*/

int problem5(){
    std::cout<< endl << "Problem 5:" << std::endl;
    for ( int i = 1; i <= 10000; i++){
        if ( IsPerfect(i) ) std::cout << i << " is perfect." << std::endl;
    }
    return 0;
}

bool IsPerfect( int n ){
    int sum = 0;
    //  Starting at 1 check each integer up to half the value of n to see if the integer is a divisor
    for ( int i = 1; i <= n / 2; i++){
        // If the integer is a divisor add it to the sum.
        if ( n % i == 0 ) sum += i;
    }
    //    cout << "n is " << n << ". The sum is " << sum << endl;
    if (sum == n) return true;
    return false;
}


/* Problem 6

An integer greater than 1 is said to be prime if it has no divisors other than itself and one. The number 17, for example, is prime, because there are no numbers other than 1 and 17 that divide evenly into it. The number 91, however, is not prime because it is divisible by 7 and 13. Write a predicate method isPrime(n) that returns true if the integer n is prime, and false otherwise. To test your algorithm, write a main program that lists the prime numbers between 1 and 100.
 
	An isPrime predicate function was created in the chaper 1 exercises. I created a second one. I think my second one is less efficient.
*/

int problem6(){
    cout<< endl << "Problem 6:" << endl;
    for ( int i = 1; i <= 100; i++){
		if ( isPrime2(i) ){
			cout << i << " is prime." << endl;
		}
    }
    return 0;
}

bool isPrime2( int n ){
	// Loop through each in between 2 and 1/2 n.
	// If n is not evenly divisible by any of the ints then n is prime.
	if ( n%2 == 0) return false;
	
	for (int i = 3; i <= n/2; i += 2) {
		if ( n % i == 0 ) return false;
	}
	return true;
}
