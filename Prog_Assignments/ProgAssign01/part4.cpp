//
//  part4.cpp
//  narcissism
//
//  Created by Scott Brenner on 3/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "part4.h"

/*
 * Problem 4: Soundex Algorithm 
 * Write a program that allows the user to enter a name and prints its Soundex code as determined by the above algorithm. It should operate in a loop that allows the user to get codes for as many names as desired before exiting. 
 
 All Soundex codes have the same format (an uppercase letter followed by three digits e.g. Z452 or V200). The Soundex algorithm converts a surname to a code using these steps:
 1. Keep the first letter of the surname (convert to uppercase if necessary)
 2. Convert all other letters in the surname to a digit using the table below (discard any non- letter characters: dashes, spaces, and so on)
 ￼
 0  AEIOUHWY
 1  BFPV
 2  CGJKQSXZ
 3  DT
 4  MN
 5  L
 ￼       6  ￼R
 
 3. Remove any consecutive duplicate digits (e.g. A122235 becomes A1235) 
 4. Remove any zeros
 5. Make resulting code exactly length 4 by truncating or padding with zeros
 
 !!!!!!!!!!!!!!!!!
 THE ASSIGNEMENT SHEET INDICATES THAT THE SOUNDEXCODE FOR ZELENKSI IS Z452.  I THINK THIS IS AN ERORR.
 THE CORRECT SOUNDEXCODE FOR ZELENKSI IS Z542.  "L" IS THE FIRST CONSONANT FOLLOWING THE "Z" AND THE
 NUMBERICAL CODE FOR "L" IS 5.
 !!!!!!!!!!!!!!!!!
 */

int problem4(){
    std::cout << "Problem 4" << std::endl;
    while (true) {
        std::cout << "Enter surname: ";
        std::string surname = GetLine();
        if ( surname.length() == 0 ) return 0;
        std::string soundExCode = "";
        
        soundExCode = replaceLetters( surname );
        soundExCode = removeRepeats( soundExCode );
        soundExCode = removeZeros( soundExCode );
        
        //  Make resulting code exactly length 4 by truncating or padding with zeros
        soundExCode = soundExCode.substr(0, 4);
        while ( soundExCode.length() < 4 ) {
            soundExCode.insert( soundExCode.length() , "0");
        }
        std::cout << "Soundex code for " << surname << " is " << soundExCode << "." << std::endl;
    }
    return 0;
}

std::string removeZeros( std::string soundExCode ){
    for (int i = soundExCode.length() - 1; i >= 0; i--) {
        if (soundExCode.at(i) == '0') soundExCode.erase( i,1 );
    }
    return soundExCode;
}

std::string removeRepeats( std::string soundExCode ){
    //    std::cout << "Soundex code passed is " << soundExCode << "." << std::endl;
    //    std::cout << "Soundex code length is " << soundExCode.length() << "." << std::endl;
    for (int i = soundExCode.length() - 1; i >= 0; i--) {
        //        std::cout << "i is " << i << "." << std::endl;
        //        std::cout << "Soundex code passed is " << soundExCode << "." << std::endl;
        //        std::cout << "Soundex code length is " << soundExCode.length() << "." << std::endl;
        if ( i == 0) return soundExCode;
        if (soundExCode.at(i) == soundExCode.at(i-1)){
            soundExCode.erase( i, 1 );
        }
    }
    return soundExCode;
}

std::string replaceLetters( std::string surname ){
    std::string soundExCode ="";
    // Loop through surname building soundExCode
    for (int i = 0; i <= surname.length()-1; i++){
        if (i == 0) {
            soundExCode += toupper( surname.at(i) );    //  Keep first letter, capitalize.
            continue;
        }
        switch ( toupper( surname.at(i) ) ) {
            case 'A': case 'E': case 'I': case 'O': case 'U': case 'H': case 'W': case 'Y':
                soundExCode += "0";
                break;
            case 'B': case 'F': case 'P': case 'V':
                soundExCode += "1";
                break;
            case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z':
                soundExCode += "2";
                break;
            case 'D': case 'T':
                soundExCode += "3";
                break;
            case 'M': case 'N':
                soundExCode += "4";
                break;
            case 'L':
                soundExCode += "5";
                break;
            case 'R':
                soundExCode += "6";
                break;                    
            default:
                break;
        }
    }
    return soundExCode;
}
