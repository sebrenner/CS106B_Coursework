/*
 *  p1.h
 *  ProbSet01
 *
 *  Created by TV on 3/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef P1_H
#define P1_H

#include <fstream>
#include <iostream>
#include <string>
#include "filelib.h"
#include "error.h"
#include "simpio.h"
#include "vector.h"


/*
 Problem 1: Removing all occurrences of characters
 
 Write a function CensorString that takes two strings as input and returns the first string
 with all of the characters that are present in the second removed.
 "Stanford University" with “nt” removed becomes "Saford Uiversiy"
 "Llamas like to laugh" with “la” removed becomes "Lms ike to ugh"
 and so on . . .
 
 Note that the function is case sensitive. This function could be written two ways. One
 way is to return a completely new string, and the other is to modify the original string.
 For practice write both of these functions.  First write a function that returns a completely
 new string with the following prototype:
 
 string CensorString1(string text, string remove);
 
 and then write a function that modifies the original string with the following prototype:
 
 void CensorString2(string & text, string remove);
 */



//  Prototypes
int problem1();
string CensorString1( string text, string remove );
void CensorString2( string & text, string remove );

#endif
