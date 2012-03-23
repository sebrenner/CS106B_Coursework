//
//  part2.h
//  narcissism
//
//  Created by Scott Brenner on 3/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef narcissism_part2_h
#define narcissism_part2_h

#include <iostream>
#include <string>
#include "random.h"
#include "simpio.h"

int miscountedVotes( int votesCast, double errorRate );
int runSimulations();
bool electionSimulation( int voters, double spread, double errorRate );

#endif
