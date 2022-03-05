/*--------------------------------------------------------------------
  Class and function to preform vector (phisycal) actions.
--------------------------------------------------------------------*/
#include <iostream>
#include <String>
#include <cmath>
using namespace std;

class Vector3D
{
private:
    double x = 0, y = 0, z = 0, length = 0;

    void operation_debug(string msg, Vector3D vec)
    {
        cout << "Doing " << msg << " of myself: (" + to_str() + "), and second: (" + vec.to_str() + ")" << endl;
    }

public:
    // parameters constructor
    Vector3D(double x, double y, double z) : x(x), y(y), z(z)
    {
        length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }

    string to_str()
    {
        return "x: " + to_string(x) + " y: " + to_string(y) + " z: " + to_string(z);
    }

    // calculate addition of self and antoher vector and return result as new Vector3D
    Vector3D add(Vector3D vec)
    {
        operation_debug("Addition", vec);
        Vector3D result = Vector3D(x + vec.x, y + vec.y, z + vec.z);
        cout << "Addition result: " << result.to_str() << endl;
        return result;
    }

    // calculate substucrtion of self and antoher vector, return result as new Vector3D
    Vector3D sub(Vector3D vec)
    {
        operation_debug("Substucrtion", vec);
        Vector3D result = Vector3D(x - vec.x, y - vec.y, z - vec.z);
        cout << "Substucrtion result: " << result.to_str() << endl;
        return result;
    }

    // dot_product (scalar multiplication) of self and another vector
    double dot_product(Vector3D vec)
    {
        operation_debug("Dot Product", vec);
        double result = x * vec.x + y * vec.y + z * vec.z;
        cout << "Dot Product result: " << result << endl;
        return result;
    }

    // cross_product (vector multiplication) of self and another vector, return result as new Vector3D
    double cross_product(Vector3D vec)
    {
        operation_debug("Cross Product", vec);
        double result = x * vec.x + y * vec.y + z * vec.z;
        cout << "Cross Product result: " << result << endl;
        return result;
    }

    // scalar multiplication of self and scalar, return result as new Vector3D
    Vector3D mul(double scalar)
    {
        Vector3D result = Vector3D(x * scalar, y * scalar, z * scalar);
        cout << "Scalar Mul of " << scalar << " result: " << result.to_str() << endl;
        return result;
    }
};

int main()
{
    // Q1 given vectors
    Vector3D u(2, -3, 1);
    Vector3D v(1, -2, -1);
    Vector3D w(2, 3, 0);

    // section a
    // s = 2u - v + 3w
    Vector3D s = u.mul(2).sub(v).add(w.mul(3));
    cout << "\n$> s: " << s.to_str() << endl
         << endl;

    // r = u + v + w
    Vector3D r = u.add(v).add(w);
    cout << "\n$> r: " << r.to_str() << endl
         << endl;
}