// { Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution
{
public:
    int minThrow(int N, int arr[])
    {
        int moves[35];
        bool vis[35];
        memset(moves, -1, sizeof(moves));
        memset(vis, false, sizeof(vis));

        // set snakes and laders
        for (int i = 0; i < 2 * N; i += 2)
            moves[arr[i]] = arr[i + 1];

        queue<pair<int, int>> q; // pair of <cell, num of moves to get here>
        pair<int, int> p;
        q.push({1, 0}); // first cell is 1 with 0 moves
        vis[1] = true;

        while (!q.empty())
        {
            p = q.front();
            int current_cell = p.first;
            int num_of_moves = p.second;

            if (current_cell == 30)
                break;
            q.pop();

            // every move possible with next throw of cube
            for (int next_cell = current_cell + 1; next_cell <= current_cell + 6 && current_cell <= 30; next_cell++)
            {
                pair<int, int> pp;
                if (!vis[next_cell])
                {
                    vis[next_cell] = true; // mark i have visited here
                    pp.second = num_of_moves + 1;

                    // if this a snake or ladder add special move
                    if (moves[next_cell] != -1)
                        pp.first = moves[next_cell];
                    else
                        pp.first = next_cell; // cube move
                    q.push(pp);
                }
            }
        }
        return p.second;
    }
};

// { Driver Code Starts.

// int main()
// {
//     int t;
//     cin >> t;
//     while (t--)
//     {
//         int N;
//         cin >> N;
//         int arr[2 * N];
//         for (int i = 0; i < 2 * N; i++)
//             cin >> arr[i];

//         Solution ob;
//         cout << ob.minThrow(N, arr) << "\n";
//     }
//     return 0;
//} // } Driver Code Ends