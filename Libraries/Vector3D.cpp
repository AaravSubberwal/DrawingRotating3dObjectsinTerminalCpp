#include <cmath>
/**************************************************************************************************
Author: Aarav Subberwal
Date: 22/09/2024

Project needs some work atm

A library to implement 3d vectors data type which can be used to perform all vector related
operations using member functions. This is intended to be used for all 3d related projects I might 
work on in the future!

"I’m Vector! I commit crimes with both direction and magnitude! Oh yeah!"
***************************************************************************************************/

class Vector3D {
public:
    double i, j, k;

    // Constructor
    Vector3D(double i = 0, double j = 0, double k = 0) : i(i), j(j), k(k) {}

    // Addition------------------------------------------------------------------------------------------
    Vector3D add(const Vector3D& other) const {
        return Vector3D(i + other.i, j + other.j, k + other.k);
    }
    Vector3D operator+(const Vector3D& other)const{
        return Vector3D(i + other.i, j + other.j, k + other.k);
    }

    // Subtraction------------------------------------------------------------------------------------------
    Vector3D subtract(const Vector3D& other) const {
        return Vector3D(i - other.i, j - other.j, k - other.k);
    }
    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(i - other.i, j - other.j, k - other.k);
    }

    // Dot product--------------------------------------------------------------------------------------------
    double dotProduct(const Vector3D& other) const {
        return i * other.i + j * other.j + k * other.k;
    }
    double operator,(const Vector3D& other) const {
        return i * other.i + j * other.j + k * other.k;
    }

    // Cross product--------------------------------------------------------------------------------------------
    Vector3D crossProduct(const Vector3D& other) const {
        return Vector3D(j * other.k - k * other.j,
                       k * other.i - i * other.k,
                       i * other.j - j * other.i);
    }
    Vector3D operator*(const Vector3D& other) const {
        return Vector3D(j * other.k - k * other.j,
                       k * other.i - i * other.k,
                       i * other.j - j * other.i);
    }

    // Multiply by a scalar-------------------------------------------------------------------------------------
    Vector3D scalarMultiply(double scalar) const {
        return Vector3D(i * scalar, j * scalar, k * scalar);
    }

    Vector3D operator*(double scalar) const {
        return Vector3D(i * scalar, j * scalar, k * scalar);    //SMASH
    }

    // Taking modulas--------------------------------------------------------------------------------------------
    double mod()const{
        return sqrt(i*i+j*j+k*k);
    }

    //Duhhhh
    void set(double a, double b, double c){
        i=a;
        j=b;
        k=c;
    }
    //Finds angle between 2 vectors, v1.Angle_between(v2)-------------------------------------------
    double Angle_Between(const Vector3D& other) const {
        double dotProduct = this->dotProduct(other);
        double magnitude1 = this->mod();
        double magnitude2 = other.mod();

        double cosTheta = dotProduct / (magnitude1 * magnitude2);
        return acos(cosTheta);;
    }

};
