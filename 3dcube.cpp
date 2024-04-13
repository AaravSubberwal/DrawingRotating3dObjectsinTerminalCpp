// Program to make a 3d spinning cube using the fucking terminal
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#include <vector>
#define D 25   // Distance to user
#define t 0.01 // time

#define l 0.02 // x axis         rotational angles
#define m 0.02 // y axis
#define n 0.02 // z axis
const unsigned int Pixheight = 70, Pixwidth = 100;
double sin_l = sin(l);
double sin_m = sin(m); // calculating sin, cos beforehand to reduce calculations
double sin_n = sin(n);
double cos_l = cos(l);
double cos_m = cos(m);
double cos_n = cos(n);

void wait(double wait_time_seconds)
{ // Wait(this many seconds) function
    auto wait_duration = std::chrono::duration<double>(wait_time_seconds);
    std::this_thread::sleep_for(wait_duration);
}

// functions for rotation

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

class Box3d
{ // class to make a box in 3d
public:
    Point3d vertice[8];
    Point3d center;
    double size;
    
    Box3d(double x_Center, double y_Center, double z_Center, double Size_cube)
    {
        center.x = x_Center;
        center.y = y_Center;
        center.z = z_Center;
        size = Size_cube;
        vertice[0].setPos(center.x + size / 2, center.y + size / 2, center.z + size / 2);
        vertice[1].setPos(center.x + size / 2, center.y - size / 2, center.z + size / 2);
        vertice[2].setPos(center.x - size / 2, center.y + size / 2, center.z + size / 2);
        vertice[3].setPos(center.x - size / 2, center.y - size / 2, center.z + size / 2);
        vertice[4].setPos(center.x + size / 2, center.y + size / 2, center.z - size / 2);
        vertice[5].setPos(center.x + size / 2, center.y - size / 2, center.z - size / 2);
        vertice[6].setPos(center.x - size / 2, center.y + size / 2, center.z - size / 2);
        vertice[7].setPos(center.x - size / 2, center.y - size / 2, center.z - size / 2);

        
    }

    void setboxPos(double targeted_x, double targeted_y, double targeted_z)
    {
        for (int i = 0; i < 8; i++)
        {
            vertice[i].x += (targeted_x - center.x);
            vertice[i].y += (targeted_y - center.y); // adds a vector to all the points
            vertice[i].z += (targeted_z - center.z);
        }
        center.x = targeted_x;
        center.y = targeted_y;
        center.z = targeted_z;
    }
};

int main()
{
    Box3d cube(0, 0, 0,20); // Defining the cube

    // Setting the screen
    bool grid[Pixheight][Pixwidth];
    for (int i = 0; i < Pixheight; ++i)
    { // set the entire grid to false
        std::fill(grid[i], grid[i] + Pixwidth, false);
    }
    std::string line = "";
    double flagx, flagy, flagz;
    double time = 0;

    // loop to iterate every frame
    while (1)
    {
        auto start = std::chrono::steady_clock::now();
        // cube.setboxPos(-20 * cos(time), -10 * sin(time), 0); // makes the cube oscilates
        for (int i = 0; i < 8; i++)
        {                                              // loop iterates through each coordinate
            flagx = cube.vertice[i].x - cube.center.x; // get all coord wrt to the origin
            flagy = cube.vertice[i].y - cube.center.y;
            flagz = cube.vertice[i].z - cube.center.z; // for rotation
            cube.vertice[i].x = getXAfterRot(flagx, flagy, flagz);
            cube.vertice[i].y = getYAfterRot(flagx, flagy, flagz);
            cube.vertice[i].z = getZAfterRot(flagx, flagy, flagz);
            cube.vertice[i].x += cube.center.x;
            cube.vertice[i].y += cube.center.y; // revert all the points wrt cube centre
            cube.vertice[i].z += cube.center.z;

            int prox = cube.vertice[i].prox(), proy = cube.vertice[i].proy(); // gives the coordinates
            if (proy > 0 && proy < Pixheight && prox > 0 && prox < Pixwidth)
            { // puts them in the grid at suitable place
                grid[proy][prox] = true;
            }
        }

        // printing shit up
        std::cout << "\033[H"; // clears out the terminal

        for (int i = 0; i < Pixheight; i++)
        {
            for (int j = 0; j < Pixwidth; j++)
            {
                if (grid[i][j])
                {
                    line += " # ";
                }
                else
                {
                    line += "   ";
                }
            }
            std::cout << line << "\n"; // Prints the entire line at once
            line.clear();              // clears out the string to be reused by the next line
            std::fill(grid[i], grid[i] + Pixwidth, false);
        }
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        wait(t);
        std::cout << 1000.0 / (duration.count()) << "\n";
        time += 0.03;
    }

    return 0;
}
