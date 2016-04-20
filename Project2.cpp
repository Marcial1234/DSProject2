//
//  main.cpp
//  Project2
//
//  Created by Nicholas Miller on 4/19/16.
//  Copyright © 2016 nickbryanmiller. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::min;
using std::endl;
using std::stringstream;
using std::vector;

// Initialize classes
class Node;
class Edge;
class LinkedList;
class Graph;

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

// This is a basic node class
class Node {
    // list of every edge from this node
    vector<Edge*> edges;
    
public:
    string charm;
    int id;
    Node *next;
    
    Node(string x, int identity) {
        charm = x;
        id = identity;
        next = NULL;
    }
    Node(string x, int identity, Node *n) {
        charm = x;
        id = identity;
        next = n;
    }
    
    void addEdge(Node *node, int weight) {
        Edge *myEdge = new Edge(this, node, weight);
        edges.push_back(myEdge);
    }
    
    void printEdges() {
        cout << charm << ":" << endl;
        for (int i = 0; i < edges.size(); i++) {
            Edge *edge = edges[i];
            cout << "Dest: " << edge->getDestination()->charm << " with weight: " << edge->getWeight() << endl;
        }
        cout << endl;
    }
};

// This is a basic linked list class
class LinkedList{
    Node *head;
    Node *tail;
public:
    
    Node *publicHead;
    
    LinkedList(){
        head = NULL;
        publicHead = NULL;
        tail = NULL;
    }
    
    int getAbs(int num) {
        
        int ans = 0;
        
        if (num < 0) {
            ans = 0 - num;
        }
        else if (num > 0) {
            ans = num;
        }
        
        return ans;
    }
    
    void addNodeToTail(string value, int id) {
        Node *p;
        
        if(head == NULL) {
            head = new Node(value, id, NULL);
            publicHead = head;
            tail = head;
        }
        else {
            p = tail;
            p->next = new Node(value, id, NULL);
            tail = p->next;
        }
    }
    
    void appendNodeToTail(Node *node) {
        Node *p;
        
        if(head == NULL) {
            head = node;
            publicHead = head;
            tail = head;
        }
        else {
            p = tail;
            p->next = node;
            tail = p->next;
        }
    }
    
    void printListOfValues() {
        Node *p = head;
        while(p != NULL) {
            cout << p->charm << " ";
            p = p->next;
        }
    }
    
};

// This is a basic graph class
class Graph {
    
    int numOfVertices;
    LinkedList *adjNodeList;
    
public:
    
    Graph(int numOfVertices) {
        this->numOfVertices = numOfVertices;
        adjNodeList = new LinkedList[numOfVertices];
    }
    
    void addEdgeUnidirectional(Node *v1, Node *v2, int weight) {
        v1->addEdge(v2, weight);
        adjNodeList[v1->id].appendNodeToTail(v2);
    }
    
    void addEdgeBidirectional(Node *v1, Node *v2, int weight) {
        v1->addEdge(v2, weight);
        adjNodeList[v1->id].appendNodeToTail(v2);
        
        v2->addEdge(v1, weight);
        adjNodeList[v2->id].appendNodeToTail(v1);
    }
    
    void createV1NodeAndEdge(string charm, int id, Node *v2, int weight) {
        Node *v1 = new Node(charm, id);
        
        v1->addEdge(v2, weight);
        adjNodeList[v1->id].appendNodeToTail(v2);
        
        v2->addEdge(v1, weight);
        adjNodeList[v2->id].appendNodeToTail(v1);
    }
    
    void createV2NodeAndEdge(Node *v1, string charm, int id, int weight) {
        Node *v2 = new Node(charm, id);
        
        v1->addEdge(v2, weight);
        adjNodeList[v1->id].appendNodeToTail(v2);
        
        v2->addEdge(v1, weight);
        adjNodeList[v2->id].appendNodeToTail(v1);
    }
    
    void createBothNodesAndEdge(string charm1, int id1, string charm2, int id2, int weight) {
        Node *v1 = new Node(charm1, id1);
        Node *v2 = new Node(charm2, id2);
        
        v1->addEdge(v2, weight);
        adjNodeList[v1->id].appendNodeToTail(v2);
        
        v2->addEdge(v1, weight);
        adjNodeList[v2->id].appendNodeToTail(v1);
    }

    void printAllVertices() {
        for (int i = 0; i < numOfVertices; i++) {
            cout << "From vertex " << i << ":\n";
            adjNodeList[i].printListOfValues();
            cout << "\n";
        }
    }
    
    void printVerticesFrom(int id) {
        cout << "From vertex " << id << ":\n";
        adjNodeList[id].printListOfValues();
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

//    int numOfRealms = 0;
////    cin >> numOfRealms;
//    
//    string charmOfRealm = "";
//    int numOfMagi = 0;
//    int powerOfMagi = 0;
//    
//    string kaelCharm = "";
//    string destCharm = "";
//    
//    int numOfIncantsTo = 0;
//    int numOfGemsTo = 0;
//    
//    int numOfIncantsFrom = 0;
//    int numOfGemsFrom = 0;
    
//    int array[] = { 2, 5, 3, 1, 7, 11, 8, 10, 13, 6 };
//    int length = getMagiSequence(array, 10);
//    cout << "\n" << length << "\n";
    
//    Graph graph(4);
//    Node *n0 = new Node("sitting", 0);
//    Node *n1 = new Node("knitting", 1);
//    Node *n2 = new Node("knowing", 2);
//    Node *n3 = new Node("kneeding", 3);
//    
//    graph.addEdgeUnidirectional(n0, n1, 10);
//    graph.addEdgeUnidirectional(n0, n2, 12);
//    graph.addEdgeUnidirectional(n0, n3, 14);
//    
//    graph.addEdgeUnidirectional(n1, n2, 20);
//    graph.addEdgeUnidirectional(n1, n3, 22);
//    
//    graph.addEdgeUnidirectional(n2, n3, 30);
//    graph.addEdgeUnidirectional(n3, n1, 40);
//    
//    graph.printVerticesFrom(3);
    
    cout << "\n";
    return 0;
}





