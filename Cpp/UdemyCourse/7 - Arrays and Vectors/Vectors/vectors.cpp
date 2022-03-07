/*--------------------------------------------------------------------
  Challange solution of chapter 7 (Arrays and Vectors) from Udemy.
--------------------------------------------------------------------*/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<int> vector1;
    vector<int> vector2;

    vector1.push_back(10);
    vector1.push_back(20);

    vector2.push_back(100);
    vector2.push_back(200);

    // 2D vector
    vector<vector<int>> vector_2d;
    vector_2d.push_back(vector1);
    vector_2d.push_back(vector2);

    cout << "Vector 2d values:" << endl;
    for (const vector<int> &vec : vector_2d)
    {
        for (const int &data : vec)
        {
            cout << data << " ";
        }
    }
    cout << endl;

    vector1.at(0) = 1000;
    cout << "Vector 2d values:" << endl;
    for (const vector<int> &vec : vector_2d)
    {
        for (const int &data : vec)
        {
            cout << data << " ";
        }
    }
    cout << endl;

    cout << "Vector1 values:" << endl;
    for (const int &data : vector1)
    {
        cout << data << " ";
    }
    cout << endl;
}