//
//  hash.cpp
//  Programming Assignment 01
//
//  Created by Scott Brenner on 3/8/12.
//  Copyright (c) 2012 Scott Brenner.
//

#include "hash.h"

/*
 * Function: Hash
 * Usage: hash_number = Hash(key, max_hash);
 * -----------------------------------------
 * This function takes the key and uses it to derive a hash code,
 * which is an integer in the range [0, maxCode - 1].  The hash
 * code is computed using a method called linear congruence.
 */

int Hash(std::string s, int maxCode)
{
    unsigned long hashcode = 0;
    for (int i = 0; i < s.length(); i++) 
        hashcode = hashcode * Multiplier + s[i];
    return (hashcode % maxCode);
}

int createHash (){
    std::cout<< endl << "Hash function:" << endl;
    std::cout << "Please enter your name: ";
	std::string name = GetLine();
	
	int hashcode = Hash(name, MAX_HASH_CODE);
	std::cout << "The hash code for your name is " << hashcode << "." <<std::endl;
    return 0;
}