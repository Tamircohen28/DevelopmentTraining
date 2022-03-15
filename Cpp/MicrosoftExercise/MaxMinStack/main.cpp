// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class SpecialStack
{
    deque<int> stack;
    int maxEle = 0;
    int minEle = 0;

public:
    SpecialStack()
    {
    }

    void push(int x)
    {
        if (stack.empty())
        {
            stack.push_back(x);
            maxEle = minEle = x;
            return;
        }

        if (x > maxEle)
        {
            stack.push_back(2 * x - maxEle);
            maxEle = x;
        }
        else if (x < minEle)
        {
            stack.push_back(2 * x - minEle);
            minEle = x;
        }
        else
        {
            stack.push_back(x);
        }
    }

    void pop()
    {
        if (!stack.empty())
        {
            int val = stack.back();

            if (val > maxEle)
            {
                maxEle = 2 * maxEle - val;
            }
            else if (val < minEle)
            {
                minEle = 2 * minEle - val;
            }

            stack.pop_back();
        }
    }

    int getMax()
    {
        return stack.empty() ? -1 : maxEle;
    }

    int getMin()
    {
        return stack.empty() ? -1 : minEle;
    }
};

// { Driver Code Starts.

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int q;
        SpecialStack obj;
        cin >> q;
        while (q--)
        {
            string s;
            cin >> s;
            if (s == "push")
            {
                int x;
                cin >> x;
                obj.push(x);
            }
            else if (s == "pop")
            {
                obj.pop();
            }
            else if (s == "getMax")
            {
                cout << obj.getMax() << " ";
            }
            else
            {
                cout << obj.getMin() << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
// } Driver Code Ends