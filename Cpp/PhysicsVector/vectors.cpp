/*--------------------------------------------------------------------
  Class and function to preform vector (phisycal) actions.
--------------------------------------------------------------------*/
#include <iostream>
#include <String>
using namespace std;

class Vector3D
{
public:
    double x = 0, y = 0, z = 0;

    // parameters constructor
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    string to_str()
    {
        return "x: " + to_string(x) + " y: " + to_string(y) + " z: " + to_string(z);
    }

    // calculate addition of second vector and return result as new Vector3D
    Vector3D add(Vector3D second)
    {
        cout << "Doing Addition of myself: (" + to_str() + "), and second: (" + second.to_str() + ")" << endl;
        return Vector3D(x + second.x, y + second.y, z + second.z);
    }
};

int main()
{
    Vector3D a(1, 2, 3);
    Vector3D b(1, 2, 3);
    Vector3D result = a.add(b);
    cout << "Result: " << result.to_str() << endl;
}