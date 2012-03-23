/*
 *  main.h
 *  ProbSet01
 *
 *  Created by TV on 3/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include <fstream>
#include <iostream>
#include <string>
//#include "filelib.h"
#include "error.h"
#include "simpio.h"
#include "strutils.h"
#include "vector.h"


//  Stuct definitions
struct EXAMSUMMARY {
    // where 0 <= score <= 100
    double min;
    double max;
    double avg;
};

//  Prototypes

// Problem1
int problem1();
string CensorString1( string text, string remove );
void CensorString2( string & text, string remove );

// Problem2
int problem2();
EXAMSUMMARY summarizeScores ( string fileName );


// Problem3
void CountLetters(string fileName);
int problem3();
