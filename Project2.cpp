//
//  main.cpp
//  Project2
//
//  Created by Nikhil Thota on 4/19/16.
//  Copyright © 2016 NikhilThota. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::string;
using std::min;
using std::endl;
using std::stringstream;
using std::vector;
using std::priority_queue;
using std::queue;

// Initialize Classes
class Node;
class Edge;
class LinkedList;
class Graph;
class Dijkstra;

// Initialize Methods
int getMagiSequenceInt(int array[], int arraySize);
vector<int> getMagiSequenceVector(int array[], int arraySize);
int getEditDistance(string word1, int l1, string word2, int l2);

// Global queue for keepin track of the important edges
//queue<int> globalEdgeQueue;

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
    vector<int> lis;
    double minDistance = std::numeric_limits<double>::infinity();
    vector<Edge*> pubEdges;
    Node *previous = NULL;
    
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
        pubEdges = edges;
    }
    
    void printEdges() {
        cout << charm << ":" << endl;
        for (int i = 0; i < edges.size(); i++)
        {
            Edge *edge = edges[i];
            cout << "Dest: " << edge->getDestination()->charm << " with weight: " << edge->getWeight() << endl;
        }
        cout << endl;
    }
};

// This is a basic linked list class
class LinkedList {
    Node *head;
    Node *tail;
public:
    
    Node *publicHead;
    
    LinkedList() {
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
    
    // Looks weird but is a dynamic array of node pointers
    Node* *nodes;
    int pubNumOfVertices;
    
    Graph(int numOfVertices) {
        this->numOfVertices = numOfVertices;
        pubNumOfVertices = numOfVertices;
        adjNodeList = new LinkedList[numOfVertices];
        nodes = new Node*[numOfVertices];
    }
    
    void addNodeToArray(string charm, int id, vector<int> lis) {
        Node *node = new Node(charm, id);
        node->lis = lis;
        nodes[id] = node;
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
    
    void setupGraph() {
        for(int i = 0; i < numOfVertices; i++) {
            for(int j = i + 1; j < numOfVertices; j++) {
                addEdgeBidirectional(nodes[i], nodes[j], getEditDistance(nodes[i]->charm, (int)nodes[i]->charm.length(), nodes[j]->charm, (int)nodes[j]->charm.length()));
            }
        }
    }
    
    int findIDWithCharm(string charm) {
        Node *p = nodes[0];
        
        while (p != NULL && p->charm != charm) {
            p = p->next;
        }
        
        if (p != NULL) {
            return p->id;
        }
        else {
            return -1;
        }
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
    
    void printEdges() {
        for (int i = 0; i < numOfVertices; i++) {
            cout << "From vertex " << i << ":\n";
            nodes[i]->printEdges();
            cout << "\n";
        }
    }
    
    void printNodeLis(int id) {
        vector<int> lis = nodes[id]->lis;
        
        for (int i = 0; i < lis.size(); i++) {
            cout << lis[i] << " ";
        }
        cout << "\n";
    }
};

// A class for holding Dijkstra's algorithm
class Dijkstra {
    
public:
    
    Graph graph = NULL;
    
    Dijkstra(Graph g) {
        graph = g;
    }
    
    void computePaths(Node *source) {
        source->minDistance = 0;
        priority_queue<Node*> vertexQueue;
        vertexQueue.push(source);
        
        while (!vertexQueue.empty()) {
            Node *u = vertexQueue.top();
            vertexQueue.pop();
            
            // Visit each edge exiting u
            for (Edge *e : u->pubEdges) {
                Node *v = e->getDestination();
                double weight = e->getWeight();
                double distanceThroughU = u->minDistance + weight;
                if (distanceThroughU < v->minDistance && u->lis.size() >= e->getWeight()) {
                    
                    priority_queue<Node*> tempQueue;
                    bool done = false;
                    while (!vertexQueue.empty()) {
                        if (vertexQueue.top() == v && !done) {
                            vertexQueue.pop();
                            done = true;
                        }
                        else {
                            Node *p = vertexQueue.top();
                            tempQueue.push(p);
                            vertexQueue.pop();
                        }
                    }
                    
                    vertexQueue = tempQueue;
                    
                    v->minDistance = distanceThroughU ;
                    v->previous = u;
                    vertexQueue.push(v);
                    
                }
            }
        }
    }
    
    vector<Node*> getShortestPathTo(Node *target) {
        vector<Node*> path;
        for (Node *vertex = target; vertex != NULL; vertex = vertex->previous) {
            path.push_back(vertex);
        }
        
        std::reverse(path.begin(), path.end());
        
        return path;
    }
    
    void printPath(vector<Node*> vec, int start, int end) {
        
        if (graph.nodes[start] != graph.nodes[end] && vec.size() == 1 && vec[vec.size()-1] == graph.nodes[end]) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            int edgeSum = 0;
            int gemSum = 0;
            
            for (int i = 0; i < vec.size() - 1; i++) {
                
                int editD = getEditDistance(vec[i]->charm, (int)vec[i]->charm.size(), vec[i + 1]->charm, (int)vec[i + 1]->charm.size());
                edgeSum = edgeSum + editD;
                
                for (int j = 0; j < editD; j++) {
                    gemSum = gemSum + vec[i]->lis[j];
                }
            }
            
            cout << edgeSum << " " << gemSum << endl;
        }
    }
    
    void resetNodes() {
        for (int i = 0; i < graph.pubNumOfVertices; i++) {
            graph.nodes[i]->previous = NULL;
            graph.nodes[i]->minDistance = std::numeric_limits<double>::infinity();
        }
    }
    
    void doDijkstra(int start, int end) {
        if (start == -1 || end == -1) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            resetNodes();
            computePaths(graph.nodes[start]);
            vector<Node*> result = getShortestPathTo(graph.nodes[end]);
            
            printPath(result, start, end);
        }
    }
};

// Get the min of three numbers
int getMin(int a, int b, int c) {
    return min(min(a, b), c);
}

// Binary search for index no recursion
int getCeilingIndex(int array[], int tail[], int left, int right, int key) {
    int mid = 0;
    
    while(right - left > 1) {
        
        // Get middle index, same as saying (right + left)/2 but safer
        mid = left + (right - left)/2;
        if( array[tail[mid]] >= key ) {
            right = mid;
        }
        else {
            left = mid;
        }
    }
    
    return right;
}

vector<int> getMagiSequenceVector(int array[], int arraySize) {
    
    vector<int> outSequence;
    
    int *tailIndices = new int[arraySize];
    int *prevIndices = new int[arraySize];
    int length;
    
    for (int i = 0; i < arraySize; i++) {
        tailIndices[i] = 0;
        prevIndices[i] = 0;
    }
    
    tailIndices[0] = 0;
    prevIndices[0] = -1;
    
    length = 1;
    
    for(int i = 1; i < arraySize; i++) {
        if(array[i] < array[tailIndices[0]]) {
            // We have encountered a new smallest value
            tailIndices[0] = i;
        }
        else if(array[i] > array[tailIndices[length-1]]) {
            // array[i] wants to increase our longest sequence
            prevIndices[i] = tailIndices[length-1];
            tailIndices[length++] = i;
        }
        else {
            // array[i] wants to be a potential for a future subsequence
            int position = getCeilingIndex(array, tailIndices, -1, length-1, array[i]);
            
            prevIndices[i] = tailIndices[position-1];
            tailIndices[position] = i;
        }
    }
    
    for(int i = tailIndices[length-1]; i >= 0; i = prevIndices[i]) {
        outSequence.push_back(array[i]);
    }
    
    delete[] tailIndices;
    delete[] prevIndices;
    
    std::reverse(outSequence.begin(), outSequence.end());
    
    return outSequence;
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
    int numOfRealms = 0;
    cin >> numOfRealms;
    
    Graph graph(numOfRealms);
    
    for (int i = 0; i < numOfRealms; i++) {
        string charmOfRealm = "";
        cin >> charmOfRealm;
        int numOfMagi = 0;
        cin >> numOfMagi;
        int magiArray[numOfMagi];
        
        for (int j = 0; j < numOfMagi; j++) {
            int powerOfMagi = 0;
            cin >> powerOfMagi;
            magiArray[j] = powerOfMagi;
        }
        
        vector<int> lis = getMagiSequenceVector(magiArray, numOfMagi);
        graph.addNodeToArray(charmOfRealm, i, lis);
        
    }
    
    // call method inside graph class to connect all nodes and set edges
    graph.setupGraph();
    
    string kaelCharm = "";
    cin >> kaelCharm;
    string destCharm = "";
    cin >> destCharm;
    
    int startIndex = graph.findIDWithCharm(kaelCharm);
    int endIndex = graph.findIDWithCharm(destCharm);
    
    Dijkstra dj(graph);
    dj.doDijkstra(startIndex, endIndex);
    dj.doDijkstra(endIndex, startIndex);
    
    cout << "\n";
    return 0;
}