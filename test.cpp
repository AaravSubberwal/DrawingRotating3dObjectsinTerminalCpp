#include <iostream>
#include <cmath>

using namespace std;
class Vector3D
{
public:
    double i, j, k;

    // Constructor
    Vector3D(double i = 0, double j = 0, double k = 0) : i(i), j(j), k(k) {}

    // Addition
    Vector3D add(const Vector3D &other) const
    {
        return Vector3D(i + other.i, j + other.j, k + other.k);
    }

    // Subtraction
    Vector3D subtract(const Vector3D &other) const
    {
        return Vector3D(i - other.i, j - other.j, k - other.k);
    }

    // Dot product
    double dotProduct(const Vector3D &other) const
    {
        return i * other.i + j * other.j + k * other.k;
    }

    // Cross product
    Vector3D crossProduct(const Vector3D &other) const
    {
        return Vector3D(j * other.k - k * other.j,
                        k * other.i - i * other.k,
                        i * other.j - j * other.i);
    }
    // Multiply by a scalar
    Vector3D scalarMultiply(double scalar) const
    {
        return Vector3D(i * scalar, j * scalar, k * scalar);
    }
    // Taking modulas
    double mod()const 
    {
        return sqrt(i * i + j * j + k * k);
    }
    void set(double a, double b, double c)
    {
        i = a;
        j = b;
        k = c;
    }
    double Angle_Between(const Vector3D &other) const{
        double dotProduct = this->dotProduct(other);
        double magnitude1 = this->mod();
        double magnitude2 = other.mod();

        double cosTheta = dotProduct / (magnitude1 * magnitude2);
        return acos(cosTheta);
    }
};
int main()
{
    Vector3D point;
    Vector3D light(-30, 0, 30);
    double theta = 0;
    Vector3D eye(0, 0, 0);
    Vector3D reflected_ray(0, 0, 0);
    Vector3D normal(0, 0,-1);
    point.set(10, 10, 10);
    reflected_ray = ((point.subtract(light)).subtract(normal.scalarMultiply(2 * (point.subtract(light)).dotProduct(normal))));
    //theta = (((eye.dotProduct(reflected_ray)) - point.dotProduct(reflected_ray)) / reflected_ray.mod() * (eye.subtract(reflected_ray)).mod());
    theta=reflected_ray.Angle_Between(eye.subtract(point));
    //cout << (reflected_ray).i << "\n";
    //cout << (reflected_ray).j << "\n";
    //cout << (reflected_ray).k;
    cout<<eye.Angle_Between(normal);
    return 0;
}