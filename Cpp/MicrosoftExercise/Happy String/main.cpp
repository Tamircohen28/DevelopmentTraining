#include <string>
#include <iostream>
#include <queue>
using namespace std;

// Idea is simple:
// Aside from a max heap, also keep track of an item that was previously used.pred
// Each time after append, update the pred.

string longestDiverseString(int a, int b, int c)
{
    priority_queue<pair<int, char>> pq; // assumption: stores items that can be appended if frequency > 0
    pq.push({a, 'a'});
    pq.push({b, 'b'});
    pq.push({c, 'c'});

    string result;
    pair<int, char> pred{-1, 0}; // predecessor
    while (!pq.empty())
    {
        pair<int, char> item = pq.top();
        pq.pop();

        if (item.first-- > 0) // if i can append this char
        {
            result += item.second;
            if (pred.first > 0) // if my predecessor can be appended again (and i didn't already pushed him)
            {
                pq.push(pred);
                pred.first = -1;
            }
        }

        // if have already put 2 in a row
        if (result.size() >= 2 && result.substr(result.size() - 2) == string(2, (char)item.second))
        {
            pred = item;
        }
        else if (item.first > 0)
        {
            pq.push(item); // put back if not exceeding
        }
    }
    return result;
}

int main()
{
    cout << longestDiverseString(10, 2, 2) << endl;
}

string longestDiverseString(int a, int b, int c)
{
    priority_queue<pair<int, char>> p;
    if (a != 0)
    {
        p.push({a, 'a'});
    }
    if (b != 0)
    {
        p.push({b, 'b'});
    }
    if (c != 0)
    {
        p.push({c, 'c'});
    }
    string ans = "";
    int i = 0;
    while (!p.empty())
    {
        pair<int, char> val = p.top();
        if (ans.length() >= 2 && ans[i - 1] == val.second && ans[i - 2] == val.second)
        { // if length is greater than 1 we put one
            p.pop();
            if (p.empty())
            {
                return ans;
            }
            ans += p.top().second;
            pair<int, char> var = p.top();
            i++;
            if (p.top().first == 1)
            {
                p.pop();
            }
            else
            {
                p.pop();
                p.push({var.first - 1, var.second});
            }
            p.push(val);
        }
        if (val.first >= 2)
        { // if top frequency is greater than 2 we push two at atime
            ans += val.second;
            ans += val.second;
            if (val.first > 2)
            {
                p.pop();
                p.push({val.first - 2, val.second});
            }
            else
            {
                p.pop();
            }
            i += 2;
        }
        else
        { // else we push only one
            ans += val.second;
            i++;
            p.pop();
        }
    }
    return ans;
}