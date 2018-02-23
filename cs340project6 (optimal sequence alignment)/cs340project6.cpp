//
//  Author:     James Callahan
//  Class:      CS 340
//  Assignment: Project 6
//  Date:       28 November 2017
//  File:       cs340project6.cpp
//

#include <iostream>
#include "SequenceAlignment.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // Make an object for sequence alignment
    SequenceAlignment *s = new SequenceAlignment();
    
    // Run the sequence alignment
    s->run();
    
    return 0;
}
