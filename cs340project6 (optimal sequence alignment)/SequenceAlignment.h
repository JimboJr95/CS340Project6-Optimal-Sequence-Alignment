//
//  Author:     James Callahan
//  Class:      CS 340
//  Assignment: Project 6
//  Date:       28 November 2017
//  File:       SequenceAlignment.h
//

#pragma once
#include<stdlib.h>
#include<string.h>

using namespace std;

static int INFINITY = -999; // to disallow using certain scoring
static int SIMILAR_LETTERS_COUNT = 12; // pairs of similar letters
static int VOWEL_COUNT = 5;

struct node{
    // Each value corresponds to its given name for sequence alignment
    int diag, // best = 0
        insertion, // best = 1
        deletion, // best = 2
        substitution, // best = 4 (unused, used bool instead)
        best,
        value; // Holds the value of the best option
    bool diagIn;
    bool subIn;
};

struct similar{
    string a;
    string b;
};

class SequenceAlignment{
public:
    // Constructor
    SequenceAlignment(); // Default constructor
    ~SequenceAlignment(); // Destructor
    
    // Functions
    void run();
    
private:
    // Variables
    string word1, word2; // Two words we are comparing
    int word1Length, word2Length;
    int seqSel; // 1-> Longest Common Subsequence, 2->Optimal Sequence Alignment
    
    // Scoring variables
    int match,
        gap,
        mismatchSimilar,
        mismatchDissimilar;
    
    
    node **word; // Got some help creating the 2d array using the following source
                 // source: https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
    
    string opt1, middle, opt2; // will hold the optimum solution
    
    similar *similarPairs = new similar[SIMILAR_LETTERS_COUNT]; // will hold all similar letters
    
    string vowels[5] = {"a", "e", "i", "o", "u"}; // holds all the vowels
    
    // Functions
    void inputs();
    bool validSequenceSelection(int num);
    void validateWord(string &word);
    void validateNumeric(int &num);
    bool validateComparisonValues();
    void initializeArray();
    void createOptOutput();
    void printArray();
};
