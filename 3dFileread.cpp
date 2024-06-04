/********************************************************************************************
Program to make a 3d spinning circle using the fucking terminal by reading a file which has 
all coordinates inside

Author: Aarav Subberwal
Date: 13/05/24

"Go! My Minions"

For the output to make even remote sense some terminal settings are required
--> Open the setting in terminal File>Preferences>settings>terminal
--> Font size = 6 scroll to find them
--> Line spacing = 0
--> Line height = 1.2

The project has a few files to read and choose from. Just type the name into the main
function of 3dFileread.cpp to run them. Also feel free to mess around with l,m,n which are
the rotation angles to mess with the rotations.
*********************************************************************************************/
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#define D 25   // Distance to user
#define t 0.01 // time
#define SCALE 1
#define l 0.02 // x axis         rotational angles
#define m 0.02 // y axis
#define n 0.02 // z axis

const unsigned short int Pixheight = 70, Pixwidth = 100;
const double sin_l = sin(l);
const double sin_m = sin(m); // calculating sin, cos beforehand to reduce calculations
const double sin_n = sin(n);
const double cos_l = cos(l);
const double cos_m = cos(m);
const double cos_n = cos(n);

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

int main()
{
    // Open whichever files you want, by timing the name here
    std::ifstream file("3d-data-DwarvenHammer.txt");
    
    std::vector <Point3d> coord;
    Point3d New_Point;    
    std::string line;
    int b = 0;
    int pos[2];
    while (std::getline(file, line))
    {
        if (line[0]=='/'){
            continue;
        }
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')         //each line has coordinates which are entered in
            {
                pos[b] = i;
                b++;
            }
        }
        
        New_Point.x = SCALE*std::stod(line.substr(0, pos[0]));
        New_Point.y = SCALE*std::stod(line.substr(pos[0] + 1, pos[1] - pos[0] - 1));
        New_Point.z = SCALE*std::stod(line.substr(pos[1] + 1));

        coord.push_back(New_Point);
        b = 0;
    }

    // Setting the screen
    bool screen[Pixheight][Pixwidth];
    for (int i = 0; i < Pixheight; ++i)
    { 
        std::fill(screen[i], screen[i] + Pixwidth, false);
    }
    line = "";
    double flagx, flagy, flagz;

    // loop to iterate every frame
    while (1)
    {
        auto start = std::chrono::steady_clock::now();  //start the timer

        for (auto &coordinate: coord)
        {
            flagx = coordinate.x; 
            flagy = coordinate.y;
            flagz = coordinate.z;
            coordinate.x = getXAfterRot(flagx, flagy, flagz);
            coordinate.y = getYAfterRot(flagx, flagy, flagz);
            coordinate.z = getZAfterRot(flagx, flagy, flagz);     //stuff to rotate the pts
            int prox = coordinate.prox(), proy = coordinate.proy();
            //check if the projected values are within the domain of the screen
            if (proy > 0 && proy < Pixheight && prox > 0 && prox < Pixwidth) 
            { // puts them in the screen at suitable place
                screen[proy][prox] = true;
            }
        }

        // printing shit up
        std::cout << "\033[H"; // clears out the terminal

        for (int i = 0; i < Pixheight; i++)
        {
            for (int j = 0; j < Pixwidth; j++)
            {
                if (screen[i][j])
                {
                    line += " # ";      //the projected values of the coordinates are put
                }                       //in suitable places line by line
                else
                {
                    line += "   ";
                }
            }
            std::cout << line << "\n"; // Prints the entire line at once
            line.clear();              // clears out the string to be reused by the next line
            std::fill(screen[i], screen[i] + Pixwidth, false);
        }
        auto end = std::chrono::steady_clock::now();    //stop timer
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        wait(t);
        std::cout << 1000.0 / (duration.count()) << "\n";  //print out the fps counter
    }

    return 0;
}
