//
//  exercisesCh02.h
//  CS106B_Reader_Excercises
//
//  This file implements the interfaces go the exercises in chpater 2.
//
//  Created by Scott Brenner on 2/13/12.
//  Copyright (c) 2012 Scott Brenner.
//

#ifndef CS106B_Reader_Excercises_exerciseCh02_h
#define CS106B_Reader_Excercises_exerciseCh02_h

// Exercise selector
void chapter02();

// Exercise 1
double celciusToFarenheit( double celcius );
// Exercise 2
void metersToFeet(double meters, int &feet, double &inches);
// Exercise 3
int roundToNearestInt(double x);
// Exercise 4
double windChill(double t, double v );
void createWindChillTable();
// Exercise 5
int problem5();
bool IsPerfect( int n );
// Exercise 6
int problem6();
//bool isPrime( int n );	// This is weird: this function is declared here, but it is defined in exercisesCh01.cpp.  But I can call it in exercisesCh02.cpp
bool isPrime2( int n );

#endif
