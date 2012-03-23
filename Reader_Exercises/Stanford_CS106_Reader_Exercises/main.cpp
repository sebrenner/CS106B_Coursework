//
//  main.cpp
//  Created by Scott Brenner on 2/11/12.
//  Copyright (c) 2012 Scott Brenner.
//
//  Stanford CS106B: Programming Abstractions
//  <http://see.stanford.edu/see/courseInfo.aspx?coll=11f4f422-5670-4b4c-889c-008262e09e4e>
//
//  The xcode project will include my code solutions to all the exercises included in the 
//  the course reader--Programming Abstractions in C++ (Chapters 1–13) by Eric S. Roberts.
//  I am working from a draft edition downloaded from 
//  <http://www.stanford.edu/class/cs106b/materials/CS106B-Reader-Draft.pdf>
//  
//  Each chapter's excersices are coded in their own file(s), e.g., exercisesCh01.cpp.
//  main.cpp will be updated to provide an interface to accessing the exercises in each
//  chapter.
//
//  I have chosen this somewhat unusual and perhaps inconvenient scheme in order to help me
//  learn how to manage a complex code base.
//
/*
 This code is license under The MIT License (MIT) <http://www.opensource.org/licenses/mit-license.php>:
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

using namespace std;
#include <iostream>
#include "exercisesCh01.h"
#include "exercisesCh02.h"

int main(){
    while ( true ) {
        short chapterSelection;
        cout << endl << "Enter the chapter number (-1 to exit): ";
        cin >> chapterSelection;
        switch ( chapterSelection ) {
            case -1:
                return 0;
                break;
            case 1:
                chapter01();
                break;
            case 2:
                chapter02();
                break;
            case 3:
                break;
            case 4:
                break;            
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            default:
                break;
        }
    }
    return 0;
}
