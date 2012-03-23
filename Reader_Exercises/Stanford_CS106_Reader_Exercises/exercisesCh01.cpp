//
//  exercisesCh01.cpp
//  Learning Cplusplus
//
//  Created by Scott Brenner on 2/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

using namespace std;
#include <math.h>   // for the squart root function
#include <iostream>


// prototypes
void chapter01();
double convertCelciusToFarenheit( double celciusTemp );
int exerciseOne();
double convertMetersToFeet();
int computeSums ( int target );
int sumOdds ( int last );
int pickLargest();
int pickLargestAndSecond();
int AverageList();
int reverseTheDigits();
bool isPrime( int x );
void primeFactors();
int hailstone();
double liebnizPi();
double quarterCirclePi();

// Exercise selector
void chapter01(){
    short exerciseSelection;
    cout << "Chapter 01: Enter the exercise number to execute: ";
    cin >> exerciseSelection;
    switch (exerciseSelection) {
        case 1:
            exerciseOne();
            break;
        case 2:
            convertMetersToFeet();
            break;
        case 3:
            cout << "The sum of the number between 1 and 100 is " << computeSums( 100 );
            break;
        case 4:
            int nInput;
            cout << "This calculates and displays the sum of the first N odd integers.  Enter N: ";
            cin >> nInput;
            cout << "The sums is " << sumOdds ( nInput );
            break;            
        case 5:
            cout << "This program returns the largest integer in the list." << endl << "Enter 0 to signal the end of the list." << endl;
            int results;
            results = pickLargest();
            cout << "The largest integer is " << results;
            break;
        case 6:
            cout << "This program returns the two largest integers in the list." << endl << "Enter 0 to signal the end of the list." << endl;
            pickLargestAndSecond();
            break;
        case 7:
            AverageList();
            break;
        case 8:
            reverseTheDigits();
            break;
        case 9:
            primeFactors();
            break;
        case 10:
            hailstone();
            break;
        case 11:
            liebnizPi();
            break;
        case 12:
            quarterCirclePi();
            break;
            
        default:
            break;
    }
    return;
}

/*
 * Exercise 1
 * -------------------------
 *
 * Write a program that reads in a temperature in degrees Celsius
 * and displays the corresponding temperature in degrees Fahrenheit.
*/
double convertCelciusToFarenheit( double celciusTemp ){
    return ( 9.0 / 5.0 * celciusTemp ) + 32;
}

int exerciseOne(){
    double celciusTemp;
    cout << "Enter temp in celcius: ";
    cin >> celciusTemp;
    cout << celciusTemp << " celcius is " << convertCelciusToFarenheit( celciusTemp ) << " farenheit." << endl;
    return 0;
}

//  Excercise two
double convertMetersToFeet(){
    double totalInches;
    int totalFeet;
    short remainderInches;
    int meters;
    
    cout << "Enter a distance in meters and I will convert it to feet and inches: ";
    cin >> meters;
    
    // convert meters to inches
    totalInches =  meters / .0254;
    
    // convert inches to feet and inches
    totalFeet = totalInches / 12;
    remainderInches = int( totalInches )  % 12;
    
    cout << meters << " meters is " << totalFeet << " feet and " << remainderInches << " inches." << endl;
    
    return 0;
}


//  Exercise 03  Compute the sum of the numbers between 1 and 100.
/*
    As mathematical historians have told the story, the German mathematician
    Karl Friedrich Gauss (1777-1855) began to show his mathematical talent 
    at a very early age. When he was in elementary school, Gauss was asked by
    his teacher to compute the sum of the numbers between 1 and 100. Gauss is
    said to have given the answer instantly: 5050. Write a program that computes
    the answer to the question Gauss’s teacher posed.
*/

int computeSums ( int target ){
    int result = 0;
    for (int i = 1; i <= target; i++) {
        result += i;
    }
    return result;
}


//  Exercise 4: calculates and displays the sum of the first N odd integers
/*
    Write a program that reads in a positive integer N and then calculates and
    displays the sum of the first N odd integers. For example, if N is 4, your
    program should display the value 16, which is 1 + 3 + 5 + 7.
*/

int sumOdds ( int last ){
    int result = 0;
    int odd = 1;
    for ( int i = 0; i < last; i++ ) {
        result += odd;
        odd += 2;
    }
    return result ;
}


//  Exercise 5: Takes list of numbers, return largest.
/*
    Write a program that reads in a list of integers from the user
    until the user enters the value 0 as a sentinel. When the sentinel
    appears, your program should display the largest value in the list,
    as illustrated in the following sample run:
 */

int pickLargest(){
    int result = 0;
    int input;
    while ( true ) {
        cout << " ? ";
        cin >> input;
        if (input == 0) {
            return result;
        }
        if (input > result) {
            result = input;
        }
    }
}

//  Exercise 6: Takes list of numbers, return largest and second largest
/*
    For a slightly more interesting challenge, write a program that finds 
    both the largest and the second-largest number in a list, prior to the 
    entry of a sentinel. Once again using 0 as the sentinel
    
*/

int pickLargestAndSecond(){
    int largest  = 0;
    int second  = 0;
    int input;
    while ( true ) {
        cout << " ? ";
        cin >> input;
        if (input == 0) {
            cout << "The largest integer is " << largest;
            cout << ". The second largest integer is " << second << ".";
        }
        if (input > largest) {
            second = largest;
            largest = input;
        }
    }
}

//  Exercise 7: Average a list of integers
/*
 Using the AddIntegerList program from Figure 1-5 as a model, 
 write a program AverageList that reads in a list of integers 
 representing exam scores and then prints out the average. 
 Because some unprepared student might actually get a score of 0,
 your program should use −1 as the sentinel to mark the end of the input. 
 */

int AverageList() {
    int SENTINEL = -1;
    cout << "This program averages a list of numbers." << endl;
    cout << "Use " << SENTINEL << " to signal the end of the list." <<  endl;
    int total = 0;
    double numScores = 0;
    while (true) {
        int value;
        cout << " ? ";
        cin >> value;
        if (value == SENTINEL) {
            double average = double(total) / numScores;
            cout << "The average is " << average << endl;
            return 0;
        }
        total += value;
        numScores ++;
    }
    return 0;
}

//  Exercise 8: Average a list of integers
/*
 Using the digitSum function from the section entitled 
 “The while statement” as a model, write a program that
 reads in an integer and then displays the  number that 
 has the same digits in the reverse order, as illustrated
 by this sample run:  123456789 -> 987654321
 */
int reverseTheDigits(){
    int theInteger = 0;
    cout << "This program reverses the digits of a postivie integer" << endl;
    cout << "Enter a positive integer: " << endl;
    cin >> theInteger;
    while ( theInteger > 0) {
        cout << theInteger % 10;
        theInteger /= 10;
    }
    cout << endl;
    return 0;
}

//  Exercise 9: Prime Factorization
/*
 Every positive integer greater than 1 can be expressed as a product
 of prime numbers. This factorization is unique and is called the prime
 factorization. For example, the number 60 can be decomposed into the 
 factors 2 x 2 x 3 x 5, each of which is prime. Note that the same prime
 can appear more than once in the factorization.
 Write a program to display the prime factorization of a number n,  
 */

bool isPrime( int x ){
    if ( x%2 == 0) return false;  // Return false if x is even
    int cnt = 3;
    while ( cnt * cnt <=  x ){
        if ((x % cnt) == 0) return false;
        cnt += 2;
    }
    return true;
}

void primeFactors(){
    int target = 0;
    cout << "This program displays the prime factorization of a postivie integer" << endl;
    cout << "Enter a positive integer: " << endl;
    cin >> target;
    int candidate = 2;
    while (target > 0) {
        if ( isPrime(candidate) && (target % candidate) == 0 ) {
            cout << candidate << " x ";
            target /= candidate;
        }
        else{
        candidate ++;
        }
    }
}

//  Exercise 10: Generate the hailstone sequence
/*
 Write a program that reads in a number from the user and then 
 generates the hailstone sequence from that point.
 
 • If n is equal to 1, you’ve reached the end of the sequence and can stop.
 • If n is even, divide it by two.
 • If n is odd, multiply it by three and add one.
 
 */

int hailstone(){
    int n = 0;
    cout << "This function generates the hailstone sequence from an integer." << endl;
    cout << "Enter an integer:";
    cin >> n;
    int result = 0;
    while (n != 1){
        if (n%2 == 0){
            result = n/2;
            cout << n << " is even, so I divide by 2 to get " << result << "." << endl;
        }
        else{
            result = (3 * n) +1;
            cout << n << " is odd, so I multiply by 3 and add 1 to get " << result << "." << endl;
        }
        n = result;
    }
    return 0;
}

//  Exercise 11: Calculate Leibniz pi
/*
 The German mathematician Leibniz (1646–1716) discovered the rather 
 remarkable fact that the mathematical constant π can be computed using
 the following mathematical relationship:
 
    π ≅ 1–1/3 + 1/5 – 1/7 + 1/9 – 1/11...
 
 The formula to the right of the equal sign represents an infinite series;
 each fraction represents a term in that series. If you start with 1, subtract
 one-third, add one-fifth, and so on, for each of the odd integers, you get
 a number that gets closer and closer to the value of π/4 as you go along.
 
 Write a program that calculates an approximation of π consisting of the 
 first 10,000 terms in Leibniz’s series. 
 */

double liebnizPi(){
    double total = 0;
    cout << "This function calcuatle pi using Liebniz's series." << endl;
    bool subtract = true;
    int counter = 0;
    for (int i = 3; i <= 20001; i+=2) {
        if (subtract) {
            total -= 1.0/i;            
        }
        else{
            total += 1.0/i;
        }
        subtract = !subtract;
        counter ++;
    }
//    cout << "Counter: " << counter << endl;
//    cout << "total: " << total << endl;
    double pi = 4 * ( 1 + total );
    cout << "Pi: " << pi << endl;
    return 4 * (1 - total);
}

//  Exercise 12: Calculate pi by estimating area of 1/4 circle
/*
 You can also compute π by approximating the area bounded by a 
 circular arc. Consider the following quarter circle ￼￼￼￼￼￼￼￼which has a
 radius r equal to two inches. From the formula for the area of
 a circle, you can easily determine that the area of the quarter
 circle should be π square inches. You can also approximate the 
 area computationally by adding up the areas of a series of rectangles,
 where each rectangle has a fixed width and the height is chosen
 so that the circle passes through the midpoint of the top of the
 rectangle. For example, if you divide the area into 10 rectangles
 from left to right, you get the following diagram:
 
 The sum of the areas of the rectangles approximates the area of the
 quarter circle. The more rectangles there are, the closer the
 approximation.
 
 For each rectangle, the width w is a constant derived by dividing
 the radius by the number of rectangles. The height h, on the other
 hand, varies depending on the position of the rectangle. If the
 midpoint of the rectangle in the horizontal direction is given by x,
 the height of the rectangle can be computed using the sqrt function
 to express the distance formula
    h = sqrt(r2 – x2)
 The area of each rectangle is then simply h × w.
 
 Write a program to compute the area of the quarter circle by dividing
 it into 10,000 rectangles.
 
 */

double quarterCirclePi(){
    double radiusOfCircle = 2.0;
    double pi = 0;
    int numRects = 10000;
    double rectWidth = radiusOfCircle / numRects;
//    cout << "rectWidth: " << rectWidth << endl;
    for (int i = 0; i < numRects; i++) {
        double rectMidpoint = (i * rectWidth) + ( rectWidth / 2 );
//        cout << "rectMidpoint: " << rectMidpoint << endl;
        double rectHeight = sqrt ( (radiusOfCircle * radiusOfCircle) - (rectMidpoint * rectMidpoint)); 
//        cout << "rectHeight: " << rectHeight << endl;
        double rectArea = rectHeight * rectWidth;
//        cout << "rectArea: " << rectArea << endl;
        pi += rectArea;
    }
    cout << "pi: " << pi << endl;
    return pi;
}
