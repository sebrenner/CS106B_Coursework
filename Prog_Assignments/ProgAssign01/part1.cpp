//
//  part1.cpp
//  narcissism
//
//  Created by Scott Brenner on 3/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "part1.h"

/*
 * Problem 1
 * Function: IsPerfect
 * Usage: isPerfect = IsPerfect( integer );
 * -----------------------------------------
 * This function takes an integer n and returns true if n is perfect, and false otherwise.
*/

int problem1(){
    std::cout<< endl << "Problem 1:" << std::endl;
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
