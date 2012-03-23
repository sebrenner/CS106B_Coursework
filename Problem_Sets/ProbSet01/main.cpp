/*
 *  main.cpp
 *  ProbSet01
 *
 *  Created by Scott Brenner on 3/13/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "main.h"

int main(){

	problem1();
	problem2();
	problem3();
	return 0;
}




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
	std::cout << "Problem 1: Removing all occurrences of characters" << std::endl;
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





/*
 Problem 2: Files and Structs
 When we grade your exams, weâ€™re going to keep track of some statistics like 
 the min, max and average scores.  
 
 Define a struct containing these statistics. 
 
 Then, write afunction that takes a filename, reads the scores from it (one
 per line where 0 <= score <= 100), and returns the struct you defined.  
 
 For efficiencyâ€™s sake, your function should make only a single pass over 
 the file.
 */

int problem2(){
	std::cout << std::endl << "Problem 2: Files and Structs ( Exam Scores )" << std::endl;

    //  Get file name
	EXAMSUMMARY mySummary;
	
    while (true){
		std::cout << "Enter file name (try scores.txt): ";
        string fileName = GetLine( );
		std::cout << "File name: " << fileName << std::endl;
        // try to summarize the scores
        mySummary = summarizeScores ( fileName );
        if ( mySummary.max > -1) break;  // if max is not -1 then scores were summarized.
    }
	
    std::cout << "Score Summary:" << endl;
    std::cout << "Max score: " << mySummary.max << endl;
    std::cout << "Min score: " << mySummary.min << endl;
    std::cout << "Avg score: " << mySummary.avg << endl;
    
    return 0;
}

EXAMSUMMARY summarizeScores ( string fileName ){
	EXAMSUMMARY theSummary;
	// Create exam summary struct and initialize variables
	theSummary.min = 100;
    theSummary.max = 0;
    theSummary.avg = 0;
	
	// Open file
	ifstream fileStream;
    fileStream.open( fileName.c_str() );
	if ( fileStream.fail() ) {
        Error("File could not be opened.");
    }	
	
	// Read in lines//scores
	string tempScoreS = "";
	int tempScoreI = 0;
	int total = 0;
	int scoreCounter = 0;
	while (true) {
		getline( fileStream, tempScoreS );
//		std::cout << tempScoreS << std::endl;
		
		tempScoreI = StringToInteger( tempScoreS );
//		std::cout << tempScoreI << std::endl;

		if ( fileStream.fail() ) break;
		if ( tempScoreI > theSummary.max ) theSummary.max = tempScoreI;
		if ( tempScoreI < theSummary.min ){
			std::cout << "The min score is " << tempScoreI << std::endl;
			theSummary.min = tempScoreI;
		}

		scoreCounter++;
		total += tempScoreI;
	}
	theSummary.avg = total / scoreCounter;
	return theSummary;
}


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
	std::cout << std::endl << "Problem 3: Vectors ( Counting Letters )" << std::endl;
    std::cout << "Enter file name (try text.txt): ";
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
    
	// Open file
	ifstream fileStream;
    fileStream.open( fileName.c_str() );
	if ( fileStream.fail() ) {
        Error("File could not be opened.");
    }	
	
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