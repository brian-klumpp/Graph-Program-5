//
//  main.cpp
//  Graphing Program 5
//
//  Created by Brian Klumpp on 12/12/24.
//
// This program will do a BFS and DFS from the given Graphic and start from
// Node E and print out the path and cost of each traversal


#include "WeightedGraph.h"
#include "Vertex.h"
#include <iostream>

using namespace std;

int main() {
    WeightedGraph myGraph(5);

    Vertex* A = new Vertex("A");
    Vertex* B = new Vertex("B");
    Vertex* C = new Vertex("C");
    Vertex* D = new Vertex("D");
    Vertex* E = new Vertex("E");

    
    myGraph.addVertex(E);
    myGraph.addVertex(A);
    myGraph.addVertex(C);
    myGraph.addVertex(D);
    myGraph.addVertex(B);

    
    myGraph.addEdge(4, 0, 7);
    myGraph.addEdge(0, 2, 12);
    myGraph.addEdge(0, 3, 60);
    myGraph.addEdge(2, 1, 20);
    myGraph.addEdge(2, 3, 32);
    myGraph.addEdge(1, 0, 10);

    cout << "DFS from E: ";
    myGraph.DFS(E);

    cout << "BFS from E: ";
    myGraph.BFS(E);

    cout << "\nFinding path from E to A:" << endl;
    myGraph.findPath(E, A);

    cout << "\nFinding path from A to B:" << endl;
    myGraph.findPath(A, B);

    cout << "\nFinding path from B to D:" << endl;
    myGraph.findPath(B, D);

    cout << "\nFinding path from D to C:" << endl;
    myGraph.findPath(D, C);

    return 0;
}
