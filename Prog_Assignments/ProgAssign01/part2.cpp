//
//  part2.cpp
//  narcissism
//
//  Created by Scott Brenner on 3/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "part2.h"

/*
 * Problem 2:  Voter Simulation
 * Assignemnt: Write a program that prompts the user to enter the voting simulation parameters, then performs 500 simulation trials and reports the ratio calculated above. A sample run of the program is shown below:
 
 Results of one simuluation:
 Enter number of voters: 10000
 Enter percentage spread between candidates: .005
 Enter voting error percentage: .15
 Enter number of simulations: 500
 Chance of an invalid election result after 500 trials = 16.8%
 */

int runSimulations(){
    std::cout<< endl << "Problem 2:" << endl;
    // This simulation assumes A is always the true winner (or a tie if the spread is 0).
    // When the resulst indiate B won we know the election results are unreliable.
    std::cout << "Enter number of voters: " ;
    int voters = GetInteger( );
    std::cout << "Enter percentage spread between candidates: " ;
    double spread = GetReal( );
    std::cout << "Enter voting error percentage: " ;
    double errorRate = GetReal( );
    std::cout << "Enter number of simulations: " ;
    int simulations = GetInteger(  );
    
    int reliableElections = 0;
    for (int i = 1; i <= simulations; i++) {
        if ( electionSimulation( voters, spread, errorRate ) ) {
            // if the election result is reliable count it.
            reliableElections++; 
        }
    }
    
    double result = (simulations - reliableElections ) / double (simulations);
    //    std::cout << "reliableElections " <<  reliableElections << std::endl;
    std::cout << "Chance of an invalid election result after " <<  simulations << " trials = " << result * 100 << "%" << std::endl;
    return result;
    
}

bool electionSimulation( int voters, double spread, double errorRate ){
    // This simulates a sinlge election.
    
    int votesCastForA = (.5 * voters) + (spread * voters);
    int votesCastForB = (.5 * voters) - (spread * voters);
    //    std::cout << "Votes Cast For A: " << votesCastForA << std::endl;
    //    std::cout << "Votes Cast For B: " << votesCastForB << std::endl;
    //    std::cout << "Total Votes Cast: " << votesCastForA + votesCastForB << std::endl << std::endl;
    
    int falseBVotes = miscountedVotes(votesCastForA, errorRate);
    int falseAVotes = miscountedVotes(votesCastForB, errorRate);
    
    //    std::cout << "False Votes Recorded For B: " << falseBVotes << std::endl;
    //    std::cout << "False Votes Recorded For A: " << falseAVotes << std::endl;
    
    
    int votesRecordedForA = votesCastForA - falseBVotes + falseAVotes;
    int votesRecordedForB = votesCastForB - falseAVotes + falseBVotes;
    
    //    std::cout << "Votes Recorded For A: " << votesRecordedForA << std::endl;
    //    std::cout << "Votes Recorded For B: " << votesRecordedForB << std::endl;
    //    std::cout << "Total Votes Recorded: " << votesRecordedForA + votesRecordedForB << std::endl << std::endl;
    
    if( votesRecordedForA > votesRecordedForB ){
        // Valid election results
        //        std::cout << "This election was valid." << std::endl;
        return true;
    }
    else {
        // Invalid elections 
        //        std::cout << "This election was not valid." << std::endl;
        return false;
    }
}

/*
 * Function: int miscountedVotes( int votesCast, double errorRate )
 * Usage: isPerfect = miscountedVotes( integer );
 * -----------------------------------------
 * This function takes an integer n and returns true if n is perfect, and false otherwise.
 */

int miscountedVotes( int votesCast, double errorRate ){
    int votesMiscounted = 0;
    for (int i =0; i <= votesCast; i++){
        if ( RandomChance( errorRate ) ){
            votesMiscounted ++;
        }
    }
    return votesMiscounted;
}
