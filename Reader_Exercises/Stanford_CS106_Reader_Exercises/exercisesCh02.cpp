//
//  exercisesCh02.cpp
//  CS106B_Reader_Excercises
//
//  Created by Scott Brenner on 2/13/12.
//  Copyright (c) 2012 Scott Brenner.
//

#include "exercisesCh02.h"
// using namespace std;

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
        case 7:
			problem7();
            break;
        case 8:
			problem8();
            break;
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


/* Problem 7

Even though clients of the <cmath> library typically don’t need to understand how functions like sqrt work internally, the implementers of that library have to be able to design an effective algorithm and write the necessary to code. If you were asked to implement the sqrt function without using the library version, there are many strategies you could adopt. One of the easiest strategies to understand is successive approximation in which you make a guess at the solution and then refine that guess by choosing new values that move closer to the solution.
 
 You can use successive approximation to determine the square root of x by adopting the following strategy:
 
	 1. Begin by guessing that the square root is x / 2. Call that guess g.
	 2. The actual square root must lie between g and x / g. At each step in the
	 successive approximation, generate a new guess by averaging g and x / g.
	 3. Repeat step 2 until the values g and x / g are as close together as the machine precision allows. In C++, the best way to check for this condition is to test whether the average is equal to either of the values used to generate it.

 Use this strategy to write your own implementation of the sqrt function.
*/

int problem7(){
	int n;
	cout << "This function approximates the square root of a number.\nEnter a numer: ";
	cin >> n;
	cout << "The square root of " << n << " is " << mySqRt( n );
	return 0;
}

double mySqRt ( double x ){
	double g = x / 2;
	while ( g != x/g ) {
		g = ( g + x/g )/2;
	}
	return g;
}


/* Problem 8
 
 Although Euclid’s algorithm for calculating the greatest common divisor is one of the oldest to be dignified with that term, there are other algorithms that date back many centuries. In the Middle Ages, one of the problems that required sophisticated algorithmic thinking was determining the date of Easter, which falls on the first Sunday after the first full moon following the vernal equinox. Given this definition, the calculation involves interacting cycles of the day of the week, the orbit of the moon, and the passage of the sun through the zodiac. Early algorithms for solving this problem date back to the third century and are fully described in the writings of the eighth-century scholar now known as the Venerable Bede.
 
 In 1800, the German mathematician Carl Friedrich Gauss published an algorithm for determining the date of Easter that was purely computational in the sense that it relied on arithmetic rather than looking up values in tables. His algorithm—translated directly from the German—appears in Figure 2-15.
 
 Gauss’s algorithm for computing the date of Easter
	 ￼￼I. Divide the number of the year for which one wishes to calculate Easter by 19, by 4, and by 7, and call the remainders of these divisions a, b, and c, respectively. If the division is even, set the remainder to 0; the quotients are not taken into account. Precisely the same is true of the following divisions.
	 II. Divide the value 19a + 23 by 30 and call the remainder d.
	 III. Finally, divide 2b + 4c + 6d + 3, or 2b + 4c + 6d + 4, choosing the former for years between 1700 and 1799 and the latter for years between 1800 and 1899, by 7 and call the remainder e.

 Then Easter falls on March 22 + d + e, or when d + e is greater than 9, on April d + e – 9.
 
 
 Write a procedure
 
	 void findEaster(int year, string & month, int & day); that takes a year and returns the Easter date in the reference parameters month and day.
 
 Unfortunately, the simple algorithm in Figure 2-15 only works for years in the 18th and 19th centuries. It is easy, however, to search the web for extensions that work for all years
 Once you have coded and tested your implementation of Gauss’s original algorithm, undertake the necessary research to find a more general approach.
 
 */

int problem8(){
	int year;
	string month = "";
	int day = 0;
	
	// Print a list of all easter date from 1700 through 1899.
	// Both functions produce the same results.  And there results match these:
	// http://www.assa.org.au/edm.html#List17
	
	cout << "\n\nHere is list of Easter dates for 1700 through 1899.\nThe first column of dates is calculated by Gauss' algorithmn. \nThe second column is from Meeus/Jones/Butcher Gregorian algorithm\n\n";
	
	for ( int i = 1700; i <= 1899; i++) {

		findEaster( i, month, day );
		cout << "Easter will be on " << month << " " << day << ", " << i << ".\t";

		findEaster2( i, month, day );
		cout << "\tEaster will be on " << month << " " << day << ", " << i << ".\n";
	}
	
	while (true) {
		cout << "\n\nThis function calculates the month and day of easter for the given year.\nIt only works for the years 1700-1899.\nEnter a year: ";
		cin >> year;
		if ( year >= 1700 && year <= 1899 ){
			findEaster( year, month, day );
			cout << "Easter will be on " << month << " " << day << ", " << year << ".";
			break;
		}
	}
	return 0;
}

int findEaster(int year, string & month, int & day){
	//	￼￼I. Divide the number of the year for which one wishes to calculate Easter by 19, by 4, and by 7, and call the remainders of these divisions a, b, and c, respectively. If the division is even, set the remainder to 0; the quotients are not taken into account. Precisely the same is true of the following divisions.
	int a = year % 19;
	int b = year % 4;
	int c = year % 7;
	
	//	II. Divide the value 19a + 23 by 30 and call the remainder d.
	int d = (19 * a + 23) % 30;
	int e = 0;
	
	//	III. Finally, divide 2b + 4c + 6d + 3, or 2b + 4c + 6d + 4, choosing the former for years between 1700 and 1799 and the latter for years between 1800 and 1899, by 7 and call the remainder e.
	if ( year >= 1700 && year <= 1799) {
		e = ( 2 * b + 4 * c + 6 * d + 3 ) % 7;
	} else if (year >= 1800 && year <= 1899 ) {
		e = ( 2 * b + 4 * c + 6 * d + 4 ) % 7;
	}
	
	//	Then Easter falls on March 22 + d + e, or when d + e is greater than 9, on April d + e – 9.
	day = 22 + d + e;
	month = "March";
	if ( d + e > 9 ){
		day = d + e - 9;
		month = "April";
	}
	return 0;	
}

/* 
 Alternative algorithmn for calculating easter.
 It was found at http://calendars.wikia.com/wiki/Computus.
	Meeus/Jones/Butcher Gregorian algorithmEdit

	a = year%19
	b = year / 100	
	c = year%100	
	d = b / 4		
	e = b%4	
	f = (b + 8) / 25		
	g = (b - f + 1) / 3	
	h = (19 × a + b - d - g + 15)%30	
	i = c / 4	
	k = c%4		
	L = (32 + 2 × e + 2 × i - h - k)%7	
	m = (a + 11 × h + 22 × L) / 451	
	month = (h + L - 7 × m + 114) / 31	
	day = ((h + L - 7 × m + 114)%31) + 1
 */
 
int findEaster2(int year, string & month, int & day){
	int a = year%19;
	int b = year / 100;
	int c = year%100;
	int d = b / 4;
	int e = b%4;
	int f = (b + 8) / 25;
	int g = (b - f + 1) / 3;
	int h = (19 * a + b - d - g + 15)%30;
	int i = c / 4;
	int k = c%4;
	int L = (32 + 2 * e + 2 * i - h - k)%7;
	int m = (a + 11 * h + 22 * L) / 451;
	int monthI = (h + L - 7 * m + 114) / 31;
	day = ((h + L - 7 * m + 114) % 31) + 1;
	month = "March";
	if ( monthI == 4) month = "April";
	return 0;
} 
