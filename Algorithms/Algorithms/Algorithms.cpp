// Algorithms.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Created bubble sort algorithm, BFS/DFS, and A* algorithm
// A* algorithm was pulled and modified from https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
//

#include <iostream>
#include <vector>
#include <chrono>
#include <tuple>
#include <stack>
#include <string>
using namespace std;
using namespace std::chrono;

// Number of vertices in graph
const int V = 9;

// Simple bubble sort algorithm for a vector of ints (returns sorted vector in ascending order)
std::chrono::nanoseconds bubbleSort(std::vector<int>& arrayInput)
{
    auto start = high_resolution_clock::now();

    bool sorted = false;

    while (!sorted) {
        sorted = true;
        for (int i = 0; i < (int) arrayInput.size() - 1; i++) {
            if (arrayInput[i] > arrayInput[i + 1]) {
                int temp = arrayInput[i];
                arrayInput[i] = arrayInput[i + 1];
                arrayInput[i + 1] = temp;
                sorted = false;
            }
        }
    }

    auto stop = high_resolution_clock::now();
    std::chrono::nanoseconds duration = duration_cast<nanoseconds>(stop - start);

    return duration;
}

// Node struct for trees
struct Node 
{
    char letter;
    int data;
    Node* left;
    Node* right;

    Node(char letter, int data, Node* left, Node* right) 
    {
        this->letter = letter;
        this->data = data;
        this->left = left;
        this->right = right;
    }
};

static bool found = false;

// Check if node was found or not in DFS
void foundCheck() {
    if (!found) {
        cout << "Node not found\n";
        found = false;
    }

    else 
    {
        found = false;
    }
}

// BFS algorithm
void breadthFirstSearch(Node* tree, int data) 
{
    stack<Node*> queue;
    queue.push(tree);

    int children = 0;

    while (!queue.empty()) 
    {
        Node* curr = queue.top();
        queue.pop();

        if (data == curr->data) 
        {
            cout << "Node with data " << to_string(data) << " is " << curr->letter << '\n';
            return;
        }

        if (curr->left != NULL) 
        {
            queue.push(curr->left);
        }

        if (curr->right != NULL) 
        {
            queue.push(curr->right);
        }
    }

    cout << "Node not found\n";
}

// DFS algorithm
void depthFirstSearch(Node* tree, int data) 
{
    if (tree != NULL)
    {
        if (tree->data == data)
        {
            cout << "Node with data " << to_string(data) << " is " << tree->letter << '\n';
            found = true;
            return;
        }

        depthFirstSearch(tree->left, data);

        depthFirstSearch(tree->right, data);
    }
}

// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// A utility function to print the constructed distance array
void printSolution(int dist[], int src)
{
    std::cout << "Vertex \t Distance from Source " << src << '\n';
    for (int i = 0; i < V; i++)
        std::cout << i << " \t\t" << dist[i] << '\n';
    std::cout << "\n";
}

// Function that implements A* algorithms's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
// NOTE: This uses a heuristic of 0 (no heuristic)
void astar(int graph[V][V], int src)
{
    int dist[V]; // The output array.  dist[i] will hold the shortest
    // distance from src to i

    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
    // path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not
        // yet processed. u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)

            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist, src);
}

int main()
{
    cout << "BUBBLE SORTING ARRAYS:\n";
    // Bubble sort arrays
    std::vector<int> array1 = { 3, 2, 1 };
    std::vector<int> array2 = { 1, 2 };
    std::vector<int> array3 = { 10, 45, 5, 24, 26, 72, 0, -1, 2 };
    std::vector<int> array4 = { 10, 9, 8, 7, 6, 4, 1, 5, 3, 2 };
    std::vector<int> array5 = { 0 };

    std::vector<std::vector<int>> arrays = { array1, array2, array3, array4, array5 };

    cout << "Arrays before sorting:\n";

    for (int i = 0; i < (int)arrays.size(); i++) {
        std::cout << "Array " << i + 1 << ": ";
        for (int j = 0; j < (int)arrays[i].size(); j++) {
            std::cout << arrays[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";

    for (int i = 0; i < (int) arrays.size(); i++) {
        std::chrono::nanoseconds seconds = bubbleSort(arrays[i]);
        std::cout << "Array " << i + 1 << " was sorted in " << seconds.count() << " nanoseconds.\n";
    }

    std::cout << "\nArrays after sorting:\n";

    for (int i = 0; i < (int) arrays.size(); i++) {
        std::cout << "Array " << i+1 << ": ";
        for (int j = 0; j < (int) arrays[i].size(); j++) {
            std::cout << arrays[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << '\n';

    cout << "PERFORM BFS AND DFS ON A TREE:\n";

    // Perform BFS and DFS on a tree
    Node* a = new Node('a', 1, NULL, NULL);
    Node* b = new Node('b', 6, NULL, NULL);
    Node* c = new Node('c', 2, NULL, NULL);
    Node* d = new Node('d', 3, NULL, NULL);
    Node* e = new Node('e', 9, NULL, NULL);
    Node* f = new Node('f', 4, NULL, NULL);
    Node* g = new Node('g', 5, NULL, NULL);

    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->left = f;
    c->right = g;

    cout << "Breadth first search:\n";
    breadthFirstSearch(a, 5);
    breadthFirstSearch(a, 9);
    breadthFirstSearch(a, 1);
    breadthFirstSearch(a, 11);

    cout << '\n';

    cout << "Depth first search:\n";
    depthFirstSearch(a, 5);
    foundCheck();
    depthFirstSearch(a, 9);
    foundCheck();
    depthFirstSearch(a, 1);
    foundCheck();
    depthFirstSearch(a, 11);
    foundCheck();

    cout << '\n';

    cout << "USE A* ALGORITHM ON A GRAPH:\n";

    // Use A* algorithm on an adjacency matrix
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    astar(graph, 0);
    astar(graph, 6);
    astar(graph, 8);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
