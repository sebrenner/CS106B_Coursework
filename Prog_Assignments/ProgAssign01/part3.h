//
//  part3.h
//  narcissism
//
//  Created by Scott Brenner on 3/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef narcissism_part3_h
#define narcissism_part3_h

#include <iostream>
#include <string>
#include "simpio.h"
#include "graphics.h"
#include "extgraph.h"
#include "vector.h"
#include "random.h"

// define the structures
struct point
{
    double x;
    double y;
    std::string label;
};

//  Function Prototypes
int connectPoints( point a, point b);
int createTriangle( Vector<point> & points );
point getPoint( string label );
int problem3();
point findMidPoint( point & A, point B);

#endif
