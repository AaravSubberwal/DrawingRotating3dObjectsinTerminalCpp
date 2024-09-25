
/*************************************************************************************************
Author: Aarav Subberwal
Date: 22/09/2024


**************************************************************************************************/
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "Parameters.cpp"

void wait(double wait_time_seconds)
{ // Wait(this many seconds) function
    auto wait_duration = std::chrono::duration<double>(wait_time_seconds);
    std::this_thread::sleep_for(wait_duration);
}

class Point3d
{ // point3d class to define the points
public:
    double x, y, z;
    void setPos(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }
    int prox()
    {
        return (static_cast<int>(std::round(D * x / (D + z)))) + (Pixwidth / 2);
    }
    int proy()
    {
        return -(static_cast<int>(std::round(D * y / (D + z)))) + (Pixheight / 2);
    }
};

// Stuff for rotations
double getXAfterRot(double i, double j, double k)
{
    return j * sin_l * sin_m * cos_n - k * cos_l * sin_m * cos_n + j * cos_l * sin_n + k * sin_l * sin_n + i * cos_m * cos_n;
}

double getYAfterRot(double i, double j, double k)
{
    return j * cos_l * cos_n + k * sin_l * cos_n - j * sin_l * sin_m * sin_n + k * cos_l * sin_m * sin_n - i * cos_m * sin_n;
}

double getZAfterRot(double i, double j, double k)
{
    return k * cos_l * cos_m - j * sin_l * cos_m + i * sin_m;
}

void rotatePoint(Point3d &coordinate)
{
    flagx = coordinate.x;
    flagy = coordinate.y;
    flagz = coordinate.z;
    coordinate.x = getXAfterRot(flagx, flagy, flagz);
    coordinate.y = getYAfterRot(flagx, flagy, flagz);
    coordinate.z = getZAfterRot(flagx, flagy, flagz); // stuff to rotate the pts
}

// This sexy function gets all the coordinates from the file supplied and returns a vector array
// of all the points
std::vector<Point3d> getCoordinatesfromFile(std::string fileName)
{
    std::vector<Point3d> coord_list;
    std::ifstream file(fileName);

    Point3d New_Point;
    std::string line;
    int b = 0;
    int pos[2];
    while (std::getline(file, line))
    {
        if (line[0] == '/')
        {
            continue; // so that i can comment in the txts if i want to
        }
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',') // each line has coordinates which are entered in
            {
                pos[b] = i;
                b++; // SMASH
            }
        }

        New_Point.x = SCALE * std::stod(line.substr(0, pos[0]));
        New_Point.y = SCALE * std::stod(line.substr(pos[0] + 1, pos[1] - pos[0] - 1));
        New_Point.z = SCALE * std::stod(line.substr(pos[1] + 1));

        coord_list.push_back(New_Point);
        b = 0;
    }
    file.close();
    return coord_list;
}

// Prints shit up
void PrintEverything(bool *screen)
{
    std::cout << "\033[H"; // clears out the terminal

    for (int i = 0; i < Pixheight; i++)
    {
        for (int j = 0; j < Pixwidth; j++)
        {
            if (*(screen + i * Pixwidth + j))
            {
                line += " # "; // the projected values of the coordinates are put
            } // in suitable places line by line
            else
            {
                line += "   ";
            }
        }
        std::cout << line << "\n"; // Prints the entire line at once
        line.clear();              // clears out the string to be reused by the next line
        std::fill(screen + i * Pixwidth, screen + (i + 1) * Pixwidth, false);;
    }
}