//
//  part3.cpp
//  narcissism
//
//  Created by Scott Brenner on 3/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "part3.h"

int problem3(){
    std::cout<< endl << "Problem 3:" << endl;
    InitGraphics();
    double radius = .01;
    Vector<point> points;
    
    createTriangle( points );
    
    // 1.  Randomly choose one vertex--A, B, or C.  Draw a small circle around the point.
    int vertexIndex = RandomInteger(0, 2);
    SetPenColor	( "Red" );
    MovePen( points.getAt( vertexIndex ).x + radius, points.getAt( vertexIndex ).y );
    DrawArc( radius, 0, 360 );

    // 2 . Randomly choose a different vertex.  Move the point halfway towards the vertex.  
    // Draw a small circle around the point.
    for (int i =0; i < 1000000; i++) {
        point currentPoint;
        currentPoint.x = GetCurrentX();
        currentPoint.y = GetCurrentY();

        point nextPoint = points.getAt( RandomInteger(0, 2) );
        point midPoint = findMidPoint( currentPoint, points.getAt(RandomInteger(0, 2)) );

        MovePen( midPoint.x + radius , midPoint.y );
        DrawArc( radius, 0, 360 );
        //Pause( .051 );
    }
    return 0;
}

/*
 *  Draws a line from point x1, y1 to x2, y2.
 */
int connectPoints( point start, point end){
    double xDist = end.x - start.x;
    double yDist = end.y - start.y;
    MovePen( start.x, start.y );
    SetPenColor("Blue");
    DrawLine( xDist, yDist );
    return 1;
}

point getPoint( string label ) {
    std::cout << "Click in window to select a point:" << std::endl;
    UpdateDisplay();
    point myPoint;
    myPoint.label = label;
    WaitForMouseDown();
    myPoint.x = GetMouseX();
    myPoint.y = GetMouseY();
    MovePen( myPoint.x, myPoint.y );    
    DrawArc(.01, 0, 360);
    SetFont("SansSerif-Bold-48");
    DrawTextString( myPoint.label.c_str() );
    return myPoint;
}

int createTriangle( Vector<point> & points ){
    //  Ask user for points and store them in a vector
    points.add( getPoint( "A" ) );
    points.add( getPoint( "B" ) );
    points.add( getPoint( "C" ) );
    
    // Draw Triagle
    connectPoints( points.getAt(0), points.getAt(1) );
    connectPoints( points.getAt(1), points.getAt(2) );
    connectPoints( points.getAt(2), points.getAt(0) );
    return 0;
}

point findMidPoint( point & A, point B){
    point midPoint;
    midPoint.label = "midpoint";
    midPoint.x = (( B.x - A.x) / 2) + A.x;
    midPoint.y = (( B.y - A.y) / 2) + A.y;
    
    return midPoint;
}








