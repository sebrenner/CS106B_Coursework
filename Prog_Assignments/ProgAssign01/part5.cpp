//
//  part5.cpp
//  narcissism
//
//  Created by Scott Brenner on 3/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "part5.h"

/**
 * Problem 5: histogram
 * I think my while loop for tallying the scores is pretty elegant.
 * The code for creating the labels is pretty lame.
 * I am unsure if it would have been worthwile to decompose the code further.
 * Further decomposition would have involved passign a lot of variables around.
 * 
 */

int problem5() {
    std::cout<< endl << "Problem 5: (try entering scores.txt)" << endl;
    //  Create vector with ten buckets
    Vector<int> histoVector;
    for (int i = 0; i < 10; i++){
        histoVector.add(0);
    }
    Vector<std::string> labels;
    labels.add( "0-9" );
    labels.add( "10-19" );
    labels.add( "20-29" );
    labels.add( "30-39" );
    labels.add( "40-49" );
    labels.add( "50-59" );
    labels.add( "60-69" );
    labels.add( "70-79" );
    labels.add( "80-89" );
    labels.add( "90-99" );
    
    //  Get filename
    ifstream infile;
    while (true){
        std::cout << "Please enter file name: ";
        std::string fileName = GetLine();
        infile.open( fileName.c_str() );
        if (infile.fail()) {
            std::cout << "Could not open file." << std::endl;
        }
        else{
            break;
        }
    }
    
    //  Fill the histogram buckets
    while (true) {
        int tempInt = 0;
        infile >> tempInt;
        if ( tempInt == 0 ) break;
        //        std::cout << "tempInt: " << tempInt << std::endl;
        int bucket = tempInt / 10;
        //        std::cout << "bucket #: " << bucket << std::endl;
        histoVector.setAt( bucket, histoVector.getAt( bucket ) + 1);
        //        std::cout << "new bucket value: " << histoVector.getAt( bucket ) << std::endl;
    }
    
    // Print the histogram
    for (int i = 0; i < 10; i++){
        std::cout << labels.getAt(i) << ": ";
        for (int j = 0; j < histoVector.getAt(i); j++){
            std::cout << "X";
        }
        std::cout << endl;
    }
    
	return 0;
}
