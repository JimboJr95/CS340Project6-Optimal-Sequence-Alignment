//
//  Author:     James Callahan
//  Class:      CS 340
//  Assignment: Project 6
//  Date:       28 November 2017
//  File:       SequenceAlignment.cpp
//

#include<stdlib.h>
#include<iostream>
#include "SequenceAlignment.h"

using namespace std;

// Default (and only) constructor
SequenceAlignment::SequenceAlignment(){
    opt1 = "";
    opt2 = "";
    middle = "";
    
    // Initialize array of similar letters
    similarPairs[0].a = "b";
    similarPairs[0].b = "p";
    
    similarPairs[1].a = "c";
    similarPairs[1].b = "k";
    
    similarPairs[2].a = "c";
    similarPairs[2].b = "s";
    
    similarPairs[3].a = "d";
    similarPairs[3].b = "t";
    
    similarPairs[4].a = "e";
    similarPairs[4].b = "y";
    
    similarPairs[5].a = "g";
    similarPairs[5].b = "j";
    
    similarPairs[6].a = "g";
    similarPairs[6].b = "k";
    
    similarPairs[7].a = "i";
    similarPairs[7].b = "y";
    
    similarPairs[8].a = "k";
    similarPairs[8].b = "q";
    
    similarPairs[9].a = "m";
    similarPairs[9].b = "n";
    
    similarPairs[10].a = "s";
    similarPairs[10].b = "z";
    
    similarPairs[11].a = "v";
    similarPairs[11].b = "w";
    
}



// Custom destructor
SequenceAlignment::~SequenceAlignment(){
    
    // Got some help deleting the 2d array using the following source
    // source: https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
    for (int i = 0; i < word1Length; i++) {
        delete [] word[i];
    }
    
    delete []word;
    delete []similarPairs;
}



// Essentially runs the whole sequence alignment
void SequenceAlignment::run(){
    
    inputs(); // Gets all inputs needed from user
    
    // Get the length of the two words
    word1Length = (int)word1.length();
    word2Length = (int)word2.length();
    
    // Got some help initializing the 2d array using the following source
    // source: https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new
    word = new node *[word1Length + 1];
    for (int i = 0; i < word1Length + 1; i++) {
        word[i] = new node[word2Length + 1];
    }
    
    // Populate the 2D array with the sequence alignment data
    initializeArray();
    
    // Prints our the sequence alignment array
    printArray();
    
    // Output string data
    createOptOutput();
    
}



// Gets input values from user such as what type of sequence alignment to use and the words to compare
void SequenceAlignment::inputs(){
    bool valid, validSeqAli;
    
    // Find which type of sequence alignment the user wants to use
    do{
        // Get sequence alignment selection
        cout << "Which type of sequence alignment would you like to use?\n1:Longest Common Subsequence\t2:Optimal Sequence Alignment\n";
        cout << "Selection (1 or 2): ";
        cin >> seqSel;
        
        // Get whether the selected sequence alignment is a valid one
        validSeqAli = validSequenceSelection(seqSel);
        
        // Output if an incorrect number was entered
        if (!validSeqAli) {
            cout << "Enter 1 or 2.\n";
        }
        
    }while(!validSeqAli);
    
    // Get the input words
    cout << "Please input the first word to use in the sequence alignment: ";
    cin >> word1;
    validateWord(word1);
    
    cout << "Please input the second word to use in the sequence alignment: ";
    cin >> word2;
    validateWord(word2);

    // If they want to use Optimal Sequence Alignment, additional setup required
    if (seqSel == 2) {
        // Get values for match, gap, similar sub and dissimilar sub scores
        do{
            cout << "Match score: ";
            cin >> match;
            cout << "\n";
        
            validateNumeric(match);
        
            cout << "Gap score: ";
            cin >> gap;
            cout << "\n";
        
            validateNumeric(gap);
        
            cout << "Substitution score for similar letters: ";
            cin >> mismatchSimilar;
            cout << "\n";
        
            validateNumeric(mismatchSimilar);
        
            cout << "Substitution score for dissimilar letters: ";
            cin >> mismatchDissimilar;
            cout << "\n";
        
            validateNumeric(mismatchDissimilar);
            
            // Validate that the inputs folow the given requirements
            valid = validateComparisonValues();
            
            if (!valid) {
                cout << "Invalid parameters. The value must adhere to the following specifications\n";
                cout << "match score > similar letters score > 0\tdissimilar letters score < 0\tgap score < 0\n";
            }
            
        }while(!valid); // While the inputs are invalid
    }
    // If LCS, use set pre-set values
    else{
        match = 1;
        gap = 0;
        mismatchDissimilar = INFINITY;
        mismatchSimilar = INFINITY;
    }

}



// Validates that the selected sequence alignment is a valid one
bool SequenceAlignment::validSequenceSelection(int num){
    bool val;
    
    if ( (num <= 0) || (num >= 3) ) {
        val = false;
    }
    else{
        val = true;
    }
    
    return val;
}



// Validates if all the values in the string are alpha values
void SequenceAlignment::validateWord(string &word){
    bool wordNotAlpha = false;
    
    // Trap word
    do{
        wordNotAlpha = false;
        
        // For each letter in the word
        for (int i = 0; i < word.length(); i++) {
            // If the word entered contains non-alpha characters, set bool
            if (!isalpha(word[i])) {
                wordNotAlpha = true;
                break;
            }
        }
        
        // If the word is invalid, ask the user for a new word
        if (wordNotAlpha) {
            cout << "Please enter a word with only apha characters: ";
            cin >> word;
            cout <<"\n";
        }
        
    }while(wordNotAlpha); // While the word contains non-alpha elements
}



// not working right now
// Validates that the value passed in is a number
void SequenceAlignment::validateNumeric(int &num){
    //
//    while (num) {
//        cin.clear();
//        cin.ignore(10000, '\n');
//        cout << "Please enter a number: ";
//        cin >> num;
//        cout << endl;
//    }
}



// For validating that the entered scores for the Optimal Sequence Alignment follow the specification given
bool SequenceAlignment::validateComparisonValues(){
    // Check that
    if ( (match <= mismatchSimilar) || (match <= 0) || (mismatchSimilar <= 0) || (mismatchDissimilar >= 0) || (gap >= 0) ) {
        return false;
    }
    else{
        return true;
    }
}



// Sets up the values of the 2D array
void SequenceAlignment::initializeArray(){
    // Variables used for calculating the largest values of the diagonal (mostly Optimal Sequence Alignment)
    int largest, exactMatch, vowelMatch, simMatch, disMatch, similar, disimilar;
    bool w1Vowel, w2Vowel; // holds values if both letters are vowels
    string compareA, compareB, compareC, compareD; // for vowel comparison, wouldn't compare correctly otherwise
    
    // Goes through each row
    for (int row = word1Length; row >= 0; row--) {
        // Goes through each column for each row
        for (int col = 0; col <= word2Length; col++) {
            node tmp;
            
            // bottom left corner
            if( (row == (word1Length)) && (col == 0) ){
                tmp.deletion = 0;
                tmp.insertion = 0;
                tmp.diag = INFINITY;
                tmp.substitution = INFINITY;
                tmp.best = 0;
                tmp.value = 0;
                tmp.diagIn = true;
                tmp.subIn = false;
                word[row][col] = tmp;
            }
            
            // Bottom row
            else if(row == (word1Length) ){
                tmp.deletion = INFINITY;
                tmp.diag = INFINITY;
                tmp.insertion = word[row][col-1].value + gap; // previous column value
                tmp.substitution = INFINITY;
                largest = tmp.insertion;
                tmp.best = 1; // insertion is the best
                tmp.value = largest;
                tmp.diagIn = false;
                tmp.subIn = false;
                word[row][col] = tmp;
            }
            
            // First column
            else if(col == 0){
                tmp.deletion = word[row + 1][col].value + gap;
                tmp.diag = INFINITY;
                tmp.insertion = INFINITY; // previous column value
                tmp.substitution = INFINITY;
                largest = tmp.deletion;
                tmp.best = 2; // insertion is the best
                tmp.value = largest;
                tmp.diagIn = false;
                tmp.subIn = false;
                word[row][col] = tmp;
            }
            
            // Everything in between
            else{
                // Could have if, else for whether it is a LCS or not
                if(seqSel == 1){
                    tmp.subIn = false; // There won't be substitution in LCS
                    
                    // Set deletion first and give it the largest value
                    tmp.deletion = word[row + 1][col].value + gap; // get deletion value
                    largest = tmp.deletion;
                    tmp.best = 2;
                    
                    // Letters match
                    if(word1[word1Length - row - 1] == word2[col - 1]){
                        tmp.diag = word[row + 1][col - 1].value + match;
                    }
                    else{
                        tmp.diag = 0;
                    }
                    
                    // If diagonal is the new largest
                    if (largest < tmp.diag) {
                        largest = tmp.diag;
                        tmp.best = 0;
                    }
                    
                    // Set insertion value
                    tmp.insertion = word[row][col-1].value + gap; // get insertion value
                    
                    // If insertion is the largest
                    if (largest < tmp.insertion) {
                        largest = tmp.insertion;
                        tmp.best = 1;
                    }
                    
                    // unused, will likely remove
                    tmp.substitution = INFINITY;
                    
                    // Set the largest value
                    tmp.value = largest;
                    
                    // If the best option is the diagonal in, set bool to true
                    if (tmp.best == 0) {
                        tmp.diagIn = true;
                    }
                    // Otherwise set bool to false
                    else{
                        tmp.diagIn = false;
                    }
                    
                    // Set calculated values to the corresponding element in the 2D array
                    word[row][col] = tmp;
                    
                }
                // Other seq alignment
                else{
                    // Initialize the variables to false or infinity
                    // These are all used to find the greatest diagonal value
                    w1Vowel = false;
                    w2Vowel = false;
                    vowelMatch = INFINITY;
                    simMatch = INFINITY;
                    disMatch = INFINITY;
                    exactMatch = INFINITY;
                    similar = INFINITY;
                    disimilar = INFINITY;
                    
                    // Initially set the diagonal in bools to false
                    tmp.subIn = false;
                    tmp.diagIn = false;
                    
                    // Set deletion first, I will make comparisons as we go and change value in array as needed
                    tmp.deletion = word[row + 1][col].value + gap; // get deletion value
                    largest = tmp.deletion;
                    tmp.best = 2;
                    
                    
                    // set diag to infinity
                    tmp.diag = INFINITY;
                    
                    // check perfect match, set it
                    if (word1[word1Length - row - 1] == word2[col - 1]) {
                        exactMatch = word[row + 1][col - 1].value + match;
                    }
                    
                    // check similar mismatch, if greater than largest, set it
                    // Is letter from word1 a vowel
                    for (int i = 0; i < VOWEL_COUNT; i++) {
                        compareA = vowels[i];
                        compareB = word1[word1Length - row - 1];
                        
                        // Exact match is the greatest diagonal value
                        if( compareA.compare(compareB) == 0 ){
                            w1Vowel = true;
                            break;
                        }
                    }
                    
                    // Is the letter from word2 a vowel
                    for (int i = 0; i < VOWEL_COUNT; i++) {
                        compareA = vowels[i];
                        compareB = word2[col - 1];
                        
                        // Exact match is the greatest diagonal value
                        if ( compareA.compare(compareB) == 0 ) {
                            w2Vowel = true;
                            break;
                        }
                    }
                    
                    // If both letters are vowels, change from infinity
                    if (w1Vowel && w2Vowel) {
                        vowelMatch = word[row + 1][col - 1].value + mismatchSimilar;
                    }
                    
                    // check similar mismatch (non-vowel pairs), if greater than largest, set it
                    for (int i = 0; i < SIMILAR_LETTERS_COUNT; i++) {
                        compareA = similarPairs[i].a; // similar letter a
                        compareB = similarPairs[i].b; // similar letter b
                        compareC = word1[word1Length - row - 1]; // the letter from word 1
                        compareD = word2[col - 1]; // the letter from word 2
                        
                        // Checks if similar letter a matches letter from word 1 and if similar letter b matches word 2
                        if ( (compareA.compare(compareC) == 0)
                                && (compareB.compare(compareD) == 0) ) {
                            simMatch = word[row + 1][col - 1].value + mismatchSimilar;
                            break;
                        }
                        // Vice versa of previous if statement
                        if((compareB.compare(compareC) == 0)
                                && (compareA.compare(compareD) == 0) ){
                            simMatch = word[row + 1][col - 1].value + mismatchSimilar;
                            break;
                        }
                    }
                    
                    // dissimilar mismatch value
                    disMatch = word[row + 1][col - 1].value + mismatchDissimilar;
                    
                    // Get greatest value for the diagonal
                    // Exact match is the greatest diagonal value
                    if ( (exactMatch >= vowelMatch) && (exactMatch >= simMatch) && (exactMatch >= disMatch) ) {
                        tmp.diag = exactMatch;
                        tmp.diagIn = true;
                    }
                    // Vowel match is the greatest diagonal value
                    else if( (vowelMatch >= exactMatch) && (vowelMatch >= simMatch) && (vowelMatch >= disMatch) ){
                        tmp.diag = vowelMatch;
                        tmp.subIn = true;
                    }
                    // Similar match is the greatest diagonal value
                    else if( (simMatch >= exactMatch) && (simMatch >= vowelMatch) && (simMatch >= disMatch) ){
                        tmp.diag = simMatch;
                        tmp.subIn = true;
                    }
                    // Dissimilar match is the greatest diagonal value
                    else if( (disMatch >= exactMatch) && (disMatch >= vowelMatch) && (disMatch >= simMatch) ){
                        tmp.diag = disMatch;
                        tmp.subIn = true;
                    }
                    
                    // If diag value is greatest, set tmp.best = 0 and set largest
                    if (largest < tmp.diag) {
                        largest = tmp.diag;
                        tmp.best = 0;
                    }
                    // If the diagonal in (or substitution) isn't the greatest value, set bools to false
                    else{
                        tmp.diagIn = false;
                        tmp.subIn = false;
                    }
                    
                    // Get insertion value
                    tmp.insertion = word[row][col-1].value + gap; // get insertion value
                    
                    // If insertion is the largest
                    if (largest < tmp.insertion) {
                        largest = tmp.insertion;
                        tmp.best = 1;
                    }

                    // Sets the value of the item in the 2D array to the largest possible value
                    tmp.value = largest;
                    
                    // Set final values to the current index of the 2D array
                    word[row][col] = tmp;
                }
            
            }

            
        }
    }
}



// This outputs the sequence alignment selected from the 2D array
void SequenceAlignment::createOptOutput(){
    int largest = 0, row = 0, col = word2Length; // largest value to pick next, current row and column
    string temp; // used for construction sequence alignment strings
    
    largest = word[row][col].value; // grabs the top right corner first for largest
    
    // Key for the sequence alignment output
    cout << "Key: |->match\td->deletion\ti->insertion\ts->substitution\n";
    
    // This is the construction of the output that gives a visualization of the options selected
    //  for the sequence alignment.
        while( (row != word1Length) && (col != 0) ){
            
            // diagonal best (for match in or substitution)
            if ( (word[row + 1][col - 1].value >= word[row][col-1].value) && (word[row + 1][col - 1].value >= word[row + 1][col].value)
                    && ( (word[row][col].diagIn == true) || (word[row][col].subIn == true) ) ) {
                // If it was a match
                if(word[row][col].diagIn == true){
                    middle.insert(0, "| ");
                }
                // If it was a substitution
                else{
                    middle.insert(0, "s ");
                }
                // Happens regardless of match or substitution
                temp = word1[word1Length - row - 1];
                opt1.insert(0, temp);
                opt1.insert(1, " ");
                temp = word2[col - 1];
                opt2.insert(0, temp);
                opt2.insert(1, " ");
                row++;
                col--;
            }
            
            // deletion best, decrement row
            else if( (word[row + 1][col].value >= word[row + 1][col - 1].value) && (word[row + 1][col].value >= word[row][col - 1].value) ){
                temp = word1[word1Length - row - 1];
                opt1.insert(0, temp);
                opt1.insert(1, " ");
                opt2.insert(0, "_ ");
                middle.insert(0, "d ");
                row++;
            }
            
            // insertion best, decrement col
            else if( (word[row][col - 1].value >= word[row + 1][col - 1].value) && (word[row][col - 1].value >= word[row + 1][col].value) ){
                opt1.insert(0, "_ ");
                temp = word2[col - 1];
                opt2.insert(0, temp);
                opt2.insert(1, " ");
                middle.insert(0, "i ");
                col--;
            }
        }
    
    // Outputs the selected items from above
    cout << endl << "opt1: "<< opt1 << endl << "mid:  " << middle << endl << "opt2: " << opt2;
    cout << endl << endl;
    cout << "Optimum value: " << word[0][word2Length].value << endl;
    
}



// Prints out the 2D array of nodes using whatever value I set it to
void SequenceAlignment::printArray(){
    cout << endl;
    
    // For each row
    for (int i = 0; i < word1Length + 1; i++) {
        
        // If not the last row (output letter)
        if(i != word1Length){
            cout << word1[word1Length - i - 1] << "\t";
        }
        else{
            cout << "-\t";
        }
        
        // For each item in the row (goes through column items) output value
        for (int j = 0; j < word2Length + 1; j++) {
            cout << word[i][j].value << "\t";
        }
        cout << endl;
    }
    
    // For each letter in the bottom row
    for (int i = 0; i < word2Length + 1; i++) {
        if(i == 0){
            cout << " \t-\t";
        }
        else{
            cout << word2[i - 1] << "\t";
        }
    }
    
    cout << endl;
}


