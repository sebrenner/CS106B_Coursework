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

// Exercsie 1
double celciusToFarenheit( double celcius );
// Exercsie 2
void metersToFeet(double meters, int &feet, double &inches);
// Exercsie 3
int roundToNearestInt(double x);
// Exercsie 4
double windChill(double t, double v );
void createWindChillTable();

#endif
