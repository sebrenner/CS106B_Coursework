/* 
 * File: console.h
 * Last modified on Fri Jan  4 13:46:57 PST 2008 by jzelenski
 * ----------------------------------------------------------
 * This header exposes control over the size of the CS106
 * text console.
 */
#ifndef _console106_h
#define _console106_h


/*
 * Function: SetConsoleSize
 * Usage: SetConsoleSize(18);
 * --------------------------
 * This function changes the size of the CS106 text console. The user's fixed
 * pitch font family and point size is used by default. (default is NSFixedPitchFontSize)
 * and the console is sized for 20 rows by 80 columns of text.  If desired, this function
 * can be called to change the point size and optionally change number of rows/columns
 * as well. The resized window is horizontally centered on screen if last argument is true,
 * otherwise leaves upper left of window unchanged. Typically this function is called as the
 * first line of main.
 */

void SetConsoleSize(int pointSize, int numRows = 20, int numCols = 80, bool centered = true);



#endif 