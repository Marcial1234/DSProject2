//
//  main.cpp
//  Project2
//
//  Created by Nicholas Miller on 4/19/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>
#include <sstream>

using std::cin;
using std::cout;
using std::string;
using std::min;
using std::endl;
using std::stringstream;

// This is a basic node class
class Node {
    string charm;
    Node * next;
    
public:
    Node(string x) {
        charm = x;
        next = NULL;
    }
    Node(string x, Node *y) {
        charm = x;
        next = y;
    }
};

// This is a basic edge class that connects two nodes
class Edge {
    Node *origin;
    Node *destination;
    int weight;
    
public:
    Edge(Node *beginNode, Node *endNode, int w) {
        origin = beginNode;
        destination = endNode;
        weight = w;
    }
    
    Node* getOrigin() {
        return origin;
    }
    
    Node* getDestination() {
        return destination;
    }
    
    int getWeight() {
        return weight;
    }
};

// Get the min of three numbers
int getMin(int a, int b, int c) {
    
    return min(min(a, b), c);
}

// Binary search for index no recursion
int ceilIndex(int array[], int left, int right, int key) {
    
    while (right - left > 1) {
        // Get middle index, same as saying (right + left)/2 but safer
        int mid = left + (right - left)/2;
        
        if (array[mid] >= key) {
            right = mid;
        }
        else {
            left = mid;
        }
    }
    
    return right;
}

// This gets the ideal squence of magi powers dynamically O(n * log(n))
int getMagiSequence(int array[], int arraySize) {
    
    int *tailArray = new int[arraySize];
    int length = 0;
    
    string outSequence = "";
    
    for (int i = 0; i < arraySize; i++) {
        tailArray[i] = 0;
    }
    
    tailArray[0] = array[0];
    length = 1;
    for (int i = 1; i < arraySize; i++) {
        if (array[i] < tailArray[0]) {
            // new smallest value could start new sequence that is better
            tailArray[0] = array[i];
        }
        
        else if (array[i] > tailArray[length-1]) {
            // array[i] wants to extend largest subsequence
            tailArray[length++] = array[i];
        }
        
        else {
            // array[i] wants to be current end candidate of an existing subsequence
            tailArray[ceilIndex(tailArray, -1, length-1, array[i])] = array[i];
        }
    }
    
    stringstream ss;
    for (int i = 0; i < length; i++) {
        ss << tailArray[i] << " ";
    }
    
    // Was not sure if we should return the length or the sequence itself
    outSequence = ss.str();
    
    delete[] tailArray;
    
    return length;
}

//// This gets the ideal squence of magi powers dynamically O(n^2)
//int getMagiSequence(int array[], int arraySize) {
//    
//    int *temp = new int[arraySize];
//    int i = 0;
//    int j = 0;
//    int max = 0;
//    
//    string sequence = "";
//    
//    // Give all indices values
//    for (i = 0; i < arraySize; i++) {
//        temp[i] = 1;
//    }
//    
//    // Optimized temp values by bottom up
//    for (i = 1; i < arraySize; i++) {
//        for (j = 0; j < i; j++ ) {
//            if ( array[i] > array[j] && temp[i] < temp[j] + 1) {
//                temp[i] = temp[j] + 1;
//            }
//        }
//    }
//    
//    // Pick max of temp values
//    for (i = 0; i < arraySize; i++) {
//        if (max < temp[i]) {
//            max = temp[i];
//        }
//    }
//    
//    // Remove temp from memory
//    delete[] temp;
//    
//    return max;
//    
//}

// This is the edit distance dynamically O(l1 x l2)
int getEditDistance(string word1, int l1, string word2, int l2) {
    
    // Table to store all the results
    int resultsArray[l1 + 1][l2 + 1];
    
    // Fill resultsArray[][] bottom up
    for (int i = 0; i <= l1; i++) {
        for (int j = 0; j <= l2; j++) {
            
            // word1 = "" we have to add all characters from word2 to word1
            if (i == 0) {
                // j = number of operations
                resultsArray[i][j] = j;
            }
            
            // word2 = "" we have to remove all characters from word1
            else if (j == 0) {
                // i = number of operations
                resultsArray[i][j] = i;
            }
            
            // If the last character of each word is the same then move down the words until different
            else if (word1[i-1] == word2[j-1]) {
                resultsArray[i][j] = resultsArray[i-1][j-1];
            }
            
            // If the last character of each word is not the same compute the min frome each operation below
            else {
                // Insert, Remove, Replace
                resultsArray[i][j] = 1 + getMin(resultsArray[i][j-1], resultsArray[i-1][j], resultsArray[i-1][j-1]);
            }
        }
    }
    
    return resultsArray[l1][l2];
}

int main() {

    int numOfRealms = 0;
//    cin >> numOfRealms;
    
    string charmOfRealm = "";
    int numOfMagi = 0;
    int powerOfMagi = 0;
    
    string kaelCharm = "";
    string destCharm = "";
    
    int numOfIncantsTo = 0;
    int numOfGemsTo = 0;
    
    int numOfIncantsFrom = 0;
    int numOfGemsFrom = 0;
    
    int array[] = { 2, 5, 3, 1, 7, 11, 8, 10, 13, 6 };
    int length = getMagiSequence(array, 10);
    cout << "\n" << length << "\n";
    
    cout << "\n";
    return 0;
}





