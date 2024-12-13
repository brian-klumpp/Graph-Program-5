//
//  WeightedGraph.cpp
//  Graphing Program 5
//
//  Created by Brian Klumpp on 12/12/24.
//

#include "WeightedGraph.h"
#include <iostream>
#include <queue>
#include <climits>

using namespace std;

WeightedGraph::WeightedGraph(int size)
{
    m_numVertices = 0;
    m_maxVertices = size;
    m_vertices.resize(size, nullptr);
    m_marks.resize(size, false);
    m_edges.resize(size, vector<int>(size, NULL_EDGE));
}

    void WeightedGraph::addVertex(Vertex* aVertex)
{
    m_vertices[m_numVertices] = aVertex;

    // Initialize all edges of the new vertex to NULL EDGE
        for (int i = 0; i < m_maxVertices; i++) {
            m_edges[m_numVertices][i] = NULL_EDGE;
            m_edges[i][m_numVertices] = NULL_EDGE;
    }

    m_numVertices++;
}

    void WeightedGraph::addEdge(int fromVertex, int toVertex, int weight)
{
        int row = indexIs(m_vertices[fromVertex]);
        int column = indexIs(m_vertices[toVertex]);

    m_edges[row][column] = weight;
}

    int WeightedGraph::indexIs(Vertex* aVertex)
{
    for (int i = 0; i < m_numVertices; i++) {
        if (m_vertices[i] == aVertex) {
            return i;
        }
    }
    return -1;
}

    void WeightedGraph::clearMarks()
{
    fill(m_marks.begin(), m_marks.end(), false);
}

    void WeightedGraph::doDFS(Vertex* aVertex)
{
        if (aVertex == nullptr) return;

        int ix = indexIs(aVertex);
            if (ix == -1) return;

    cout << aVertex->getTitle() << " ";
    m_marks[ix] = true;

    // Traverse to adjacent vertices
    for (int i = 0; i < m_numVertices; i++) {
        if (m_edges[ix][i] != NULL_EDGE && !m_marks[i]) {
            doDFS(m_vertices[i]);
        }
    }
}

    void WeightedGraph::DFS(Vertex* aVertex)
{
    clearMarks();
    doDFS(aVertex);
    cout << endl;
}

    void WeightedGraph::doBFS(Vertex* aVertex)
{
    if (aVertex == nullptr) return;

    queue<Vertex*> q;
    int ix = indexIs(aVertex);
    m_marks[ix] = true;

    q.push(aVertex);

    while (!q.empty()) {
        Vertex* node = q.front();
        q.pop();
        cout << node->getTitle() << " ";

        ix = indexIs(node);
        for (int i = 0; i < m_numVertices; i++) {
            if (m_edges[ix][i] != NULL_EDGE && !m_marks[i]) {
                m_marks[i] = true;
                q.push(m_vertices[i]);
            }
        }
    }
}

    bool WeightedGraph::isEmpty() {
        return m_numVertices == 0;
}

    bool WeightedGraph::isFull() {
        return m_numVertices >= m_maxVertices;
}

    void WeightedGraph::BFS(Vertex* aVertex)
{
    clearMarks();
    doBFS(aVertex);
    cout << endl;
}

    void WeightedGraph::findPath(Vertex* src, Vertex* dest)
{
    int start = indexIs(src);
    int end = indexIs(dest);
    
    if (start == -1 || end == -1) {
        cout << "Invalid source or destination node." << endl;
        return;
    }
    
    // Arrays to store the shortest path and its cost
    vector<int> dist(m_numVertices, INT_MAX);
    vector<int> prev(m_numVertices, -1);
    dist[start] = 0;
    
    auto compare = [&](int lhs, int rhs) { return dist[lhs] > dist[rhs]; };
    priority_queue<int, vector<int>, decltype(compare)> pq(compare);
    pq.push(start);
    
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        
        if (u == end) break;
        
        for (int v = 0; v < m_numVertices; v++) {
            if (m_edges[u][v] != NULL_EDGE) {
                int alt = dist[u] + m_edges[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                    pq.push(v);
                }
            }
        }
    }
    
   
    vector<string> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.insert(path.begin(), m_vertices[at]->getTitle());
    }
    
    // If the destination cant be reached print no path
    if (path.size() == 1) {
        cout << "No path found from " << src->getTitle() << " to " << dest->getTitle() << "." << endl;
    } else {
        int cost = dist[end];
        cout << "Path from " << src->getTitle() << " to " << dest->getTitle() << ": ";
        for (const auto& node : path) {
            cout << node << " ";
        }
        cout << "\nCost: " << cost << endl;
    }
}
