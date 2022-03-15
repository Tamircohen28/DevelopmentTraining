// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution
{
public:
    void print_tail(vector<int> &tail)
    {
        cout << "Tail: " << endl;
        for (int i = 0; i < tail.size(); i++)
        {
            cout << "[" << i << "]: " << tail[i] << endl;
        }
    }
    // Helper function to find LIS
    int LongestIncreasingSubsequenceLength(vector<int> &v)
    {
        if (v.size() == 0)
            return 0;

        vector<int> tail(v.size(), 0);
        int length = 1; // always points empty slot in tail

        tail[0] = v[0];

        for (int i = 1; i < v.size(); i++)
        {
            cout << "\n----- ITER: " << i << endl;
            // Do binary search for the element in
            // the range from begin to begin + length
            auto b = tail.begin(), e = tail.begin() + length;
            cout << "Looking for lower bound than: " << v[i] << " in tail from start to " << length << endl;
            auto it = lower_bound(b, e, v[i]);

            // If not present change the tail element to v[i]
            if (it == tail.begin() + length)
            {
                cout << "All lower then me so tail[" << length + 1 << "] = v[" << i << "] = " << v[i] << endl;
                tail[length++] = v[i];
                cout << "New length is " << length << endl;
                print_tail(tail);
            }
            else
            {
                cout << "Found someone bigger/equal than me, put me for him. so tail[" << it - tail.begin() << "] = v[" << i << "] = " << v[i] << endl;
                // *it = v[i];
                print_tail(tail);
            }
        }

        return length;
    }

    int removeStudents(int H[], int N)
    {
        vector<int> arr;
        for (int i = 0; i < N; i++)
            arr.push_back(H[i]);

        int ans = N - LongestIncreasingSubsequenceLength(arr);

        return ans;
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

        int H[N];
        for (int i = 0; i < N; i++)
            cin >> H[i];

        Solution ob;
        cout << ob.removeStudents(H, N) << endl;
    }
    return 0;
} // } Driver Code Ends