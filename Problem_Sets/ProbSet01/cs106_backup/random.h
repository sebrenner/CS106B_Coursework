#ifndef RANDOM_H_
#define RANDOM_H_
/*
 * File: random.h
 * Version: 1.0CPP
 * Last modified on Wed Sep 18 13:32:23 PDT 2002 by jzelenski
 * ----------------------------------------------------------
 * This interface provides several functions for generating
 * pseudo-random numbers.
 */

/*
 * Function: Randomize
 * Usage: Randomize();
 * -------------------
 * This function sets the random seed so that the random sequence
 * is unpredictable.   If this function is not called, the other 
 * functions will return the same values on each run. During the
 * debugging phase, it is best not to call this function, so that 
 * program behavior is repeatable.
 */
void Randomize();

/*
 * Function: RandomInteger
 * Usage: n = RandomInteger(low, high);
 * ------------------------------------
 * This function returns a random integer in the range low to high,
 * inclusive.
 */
int RandomInteger(int low, int high);

/*
 * Function: RandomReal
 * Usage: d = RandomReal(low, high);
 * ---------------------------------
 * This function returns a random real number in the half-open
 * interval [low .. high), meaning that the result is always
 * greater than or equal to low but strictly less than high.
 */
double RandomReal(double low, double high);

/*
 * Function: RandomChance
 * Usage: if (RandomChance(p)) . . .
 * ---------------------------------
 * The RandomChance function returns true with the probability
 * indicated by p, which should be a floating-point number between
 * 0 (meaning never) and 1 (meaning always).  For example, calling
 * RandomChance(.30) returns true 30 percent of the time.
 */
bool RandomChance(double p);

#endif /*RANDOM_H_*/
