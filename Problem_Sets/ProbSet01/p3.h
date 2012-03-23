/*
 *  p3.h
 *  ProbSet01
 *
 *  Created by TV on 3/13/12.
 *  Copyright 2012 Scott Brenner. All rights reserved.
 *
 */

#ifndef P3_H
#define P3_H

#include <fstream>
#include <iostream>
#include <string>
#include "error.h"
#include "simpio.h"
#include "vector.h"
#include "filelib.h"


/*
 Problem 3: Vectors
 
 Write a function CountLetters that takes a filename and prints the number 
 of times each letter of the alphabet appears in that file. Because there are 
 26 numbers to be printed, CountLetters needs to create a Vector. For 
 example, if the file is:
 Abcd K..
 ijk;;
 cab-Bage
 fad
 
 CountLetters should print the following:
 a: 4
 b: 3
 c: 2
 d: 2
 ...
 z: 0
 
 When you really print this out, it should be 26 elements long, but we 
 couldn't easily display that on the page. Note that there may be upper case 
 letters, lower case letters, and non-letter characters in the file. All 
 letters should be counted regardless of case (so “Aa” is two a’s), and 
 non-alphabetic characters should be ignored. You should use the following 
 prototype.
 
 void CountLetters(string filename);
 */


//  Function prototypes
void CountLetters(string fileName);
int problem3();

#endif