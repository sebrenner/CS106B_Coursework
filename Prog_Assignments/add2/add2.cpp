/*
* File: add2.cpp
* --------------
* This program reads in two numbers, adds them together,
* and prints their sum.
*/

#include <iostream>
#include "genlib.h"
#include "simpio.h"

int main() 
{
	int n1, n2, total;

	cout << "This program adds two numbers." << endl;
	cout << "1st number? ";
	n1 = GetInteger();
	cout << "2nd number? ";
	n2 = GetInteger();
	total = n1 + n2;
	cout << "The total is " << total << "." << endl;
	return 0;
}
