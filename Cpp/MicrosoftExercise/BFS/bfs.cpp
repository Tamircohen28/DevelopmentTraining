// { Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

#include <algorithm>

/**
    utility function to form edge between two vertices source and dest.
    @param adj edges vector list
    @param src start of new edge
    @param dest end of new edge
*/
void add_edge(vector<int> adj[], int src, int dest)
{
    // in our case we could only use src->dst
    adj[src].push_back(dest);

    // This is for generic BFS where edge is two-ways
    // adj[dest].push_back(src);
}

/**
    a modified version of BFS that stores predecessor
    of each vertex in array p and its distance from source in array d.
    @param adj edges vector list
    @param src source node to start from
    @param dest node to find path to
    @param vertices number of total nodes
    @param pred predecessor array (filled by funtion)
    @param dist distance array (filled by funtion)
*/
bool BFS(vector<int> adj[], int src, int dest, int vertices,
         int pred[], int dist[])
{
    // a queue to maintain queue of vertices whose
    // adjacency list is to be scanned as per normal
    // DFS algorithm
    list<int> queue;

    // boolean array visited[] which stores the
    // information whether ith vertex is reached
    // at least once in the Breadth first search
    bool visited[vertices];

    // initially all vertices are unvisited
    // so v[i] for all i is false
    // and as no path is yet constructed
    // dist[i] for all i set to infinity
    for (int i = 0; i < vertices; i++)
    {
        visited[i] = false;
        dist[i] = INT_MAX;
        pred[i] = -1;
    }

    // now source is first to be visited and
    // distance from source to itself should be 0
    visited[src] = true;
    dist[src] = 0;
    queue.push_back(src);

    // standard BFS algorithm
    while (!queue.empty())
    {
        int u = queue.front();
        queue.pop_front();

        // visiting all edges
        for (int i = 0; i < adj[u].size(); i++)
        {

            if (visited[adj[u][i]] == false)
            { // if not visited
                visited[adj[u][i]] = true;
                dist[adj[u][i]] = dist[u] + 1; // edge dist is vertex + 1
                pred[adj[u][i]] = u;           // im the edge pred
                queue.push_back(adj[u][i]);    // need to visit edge as well

                // We stop BFS when we find destination.
                if (adj[u][i] == dest)
                    return true;
            }
        }
    }

    // visited all nodes but didn't found path
    return false;
}

/**
    utility function to print the shortest distance
    between source vertex and destination vertex
    @param adj edges vector list
    @param src source node to start from
    @param dest node to find path to
    @param vertices number of total nodes
    @param arr snakes and ladders array
    @param N snakes and ladders count
    @return shortest path length from src to dst
*/

int BFSShortestDistance(vector<int> adj[], int src, int dest, int vertices, int arr[], int N)
{
    // predecessor[i] array stores predecessor of
    // i and distance array stores distance of i
    // from s
    int pred[vertices], dist[vertices];

    if (BFS(adj, src, dest, vertices, pred, dist) == false)
    {
        cout << "Given source and destination"
             << " are not connected" << endl;
        return -1;
    }

    // vector path stores the shortest path
    vector<int> path;
    int crawl = dest;

    // revers path from dest to source
    path.push_back(crawl);
    while (pred[crawl] != -1)
    {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }

    // distance from source is in distance array
    // cout << "Shortest path length is : " << dist[dest] << endl;

    // printing path from source to destination
    cout << "\nBFS Path is::\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";

    // Only for snake and ladders case, remove all of them that occure after ladder
    for (int i = 0; i < N; i++)
    {
        // edge case, no reason for us to use snakes
        if (arr[i * 2 + 1] > arr[i * 2])
        {
            path.erase(std::remove(path.begin(), path.end(), arr[i * 2 + 1]), path.end());
        }
    }

    cout << "\nAFTER REMOVE: path length is : " << path.size() << endl;

    // printing path from source to destination
    cout << "\nSNAKE Path is::\n";
    for (int i = path.size() - 1; i >= 0; i--)
        cout << path[i] << " ";
    cout << endl;

    return path.size() - 1;
}

class Solution
{
public:
    int minThrow(int N, int arr[])
    {
        int last_cell = 30;
        int vertices = last_cell + 1; // we don't use 0

        // array of vectors is used to store the graph
        // in the form of an adjacency list
        vector<int> adj[vertices];

        // connect ladders and snake
        for (int i = 0; i < N; i++)
        {
            add_edge(adj, arr[i * 2], arr[i * 2 + 1]);
        }

        for (int cell = 1; cell <= 30; cell++)
        {
            for (int cube = 4; cube <= 6; cube++)
            {
                if (cell + cube <= last_cell)
                {
                    add_edge(adj, cell, cell + cube);
                }
            }
        }

        // BFS path, substuct all moves done with ladder or snake
        return BFSShortestDistance(adj, 1, 30, vertices, arr, N);
    }
};

// { Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int N;
        cin >> N;
        int arr[2 * N];
        for (int i = 0; i < 2 * N; i++)
            cin >> arr[i];

        Solution ob;
        cout << ob.minThrow(N, arr) << "\n";
    }
    return 0;
} // } Driver Code Ends