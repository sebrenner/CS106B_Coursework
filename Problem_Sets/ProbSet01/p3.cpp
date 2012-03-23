/*
 *  p3.cpp
 *  ProbSet01
 *
 *  Created by TV on 3/13/12.
 *  Copyright 2012 Scott Brenner. All rights reserved.
 *
 */

#include "p3.h"

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

int problem3(){
    std::cout << "Enter file name: ";
    string fileName = GetLine();
	std::cout << "file name: " << fileName << std::endl;
    // try to summarize the letters
    CountLetters( fileName );
//	std::cout << "Returning from CountLetters." << std::endl;
    return 0;
}

/*
 Function: void CountLetters(string filename);
 Takes a filename as a string.
 Prints a tally of the number of occurence of each letter in the file.
 Returns void.
 */

void CountLetters(string fileName){
    int numLetters = 26;
    
	// Open file and read lines into a vector
	ifstream fileStream;
    fileStream.open( fileName.c_str() );
	if ( fileStream.fail() ) {
        Error("File could not be opened.");
    }	
//	std::cout << "Here we opened the file named: " << fileName.c_str() << std::endl;
	
		
	// readEntireFile( fileStream, lines);
	
    //  Create 26 items in vector; initialize them to 0
    Vector<int> letterTable;
    for ( int i = 0; i < numLetters; i++ ){
        letterTable.add(0);
    }

	string tempString = "";
	while (true) {
		getline( fileStream, tempString );
		if (fileStream.fail()) break;
		
		tempString = ConvertToLowerCase( tempString );
		
		for (int j = 0; j < tempString.size(); j++){
			//  find the differnce between 'a' and the current letter
			int index = tempString.at( j ) - 'a';

			//  confirm current letter is 'a' or within 25 letters of 'a.'
			if ( index >= 0 && index < numLetters ){
				// increment value at index
				letterTable.setAt( index, letterTable.getAt( index ) + 1 );
			}
		}
	}
	
	// Print the vector
	for (int i = 0; i < numLetters; i++){
		char currLetter = 'a' + i;
		std::cout << currLetter << ": " << letterTable.getAt( i ) << std::endl;
	}
}