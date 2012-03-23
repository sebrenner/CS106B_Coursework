/*
 *  p1.cpp
 *  ProbSet01
 *
 *  Created by TV on 3/13/12.
 *  Copyright 2012 Scott Brenner. All rights reserved.
 *
 */

#include "p1.h"

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

int problem1(){
    std::cout << "CensortString1 (pass by value):" << std::endl;
	std::cout << " Result of removing nt from Stanford University: " << CensorString1( "Stanford University", "nt" ) << "." << std::endl;

    std::cout << "CensortString2 (pass by reference):" << std::endl;
    string myText = "Stanford University";
    CensorString2( myText, "nt" );
    std::cout << " Result of removing nt from Stanford University: " << myText << std::endl << std::endl;
	
	
    std::cout << "CensortString1 (pass by value):" << std::endl;
	std::cout << " Result of removing la from Llamas like to laugh: " << CensorString1( "Llamas like to laugh", "la" ) << std::endl;

	std::cout <<  "CensortString2 (pass by reference):" << std::endl;
	myText = "Llamas like to laugh";
    CensorString2( myText, "la" );
    std::cout << " Result of removing la from Llamas like to laugh: " << myText << std::endl;
    
    return 0;}

/*  
 Function: CensorString1
 Takes two strings: text and remove.
 Returns a string whill all the individual characters of remove removed from text.
 */

string CensorString1( string text, string remove ){
    //  Loop through each character in remove.  While each character continues
    //  to be found in text, keep erasing that character.
    for (int i = 0;  i < remove.length(); i++){
        while ( text.find( remove.at(i) ) != string::npos ){
            // Erase the i character found at the index returnd by find.
			text.erase( text.find( remove.at(i) ), 1);
        }
	}
    return text;
}

/*  
 Function: CensorString2
 Takes two arguments: a reference to a string (& text) and a string (remove).
 Returns a string whill all the individual characters of remove removed from text.
 */
void CensorString2(string & text, string remove){
    //  Loop through each character in remove.  While each character continues
    //  to be found in text, keep erasing that character.
    for (int i = 0; i < remove.length(); i++){
//		std::cout << "Removing " << remove.at(i) << " from " << text << std::endl;
        while ( text.find( remove.at(i)) != string::npos){
            // Erase the i character found at the index returnd by find.
			//std::cout<<"Text is " << text << ". Removing " << remove.at(i) << "..." << std::endl;
            text.erase( text.find( remove.at( i ) ),1);
			//std::cout<<"Now text is " << text <<  std::endl;
        }
	}
}