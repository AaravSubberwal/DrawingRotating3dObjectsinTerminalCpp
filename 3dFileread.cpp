// Program to make a 3d spinning circle using the fucking terminal by reading a
// file which has all coordinates inside
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>
#include <fstream>
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

int main()
{
    std::string filename = "3d-data-cube.txt";

    // Open the file in read mode
    std::ifstream file(filename);
    int lineCount = 0;
    std::string li;
    while (std::getline(file, li))
    {
        // Increment line count for each line read
        lineCount++;
    }
    file.clear();                 // Clear any errors.
    file.seekg(0, std::ios::beg); // Move the file pointer to the beginning.

    Point3d coord[lineCount];
    std::string line;
    int a = 0, b = 0;
    int pos[2];
    while (std::getline(file, line))
    {
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == ',')
            {
                pos[b] = i;
                b++;
            }
        }
        coord[a].x = std::stod(line.substr(0, pos[0]));
        coord[a].y = std::stod(line.substr(pos[0] + 1, pos[1] - pos[0] - 1));
        coord[a].z = std::stod(line.substr(pos[1] + 1));
        b = 0;
        a++;
    }

    // Setting the screen
    bool grid[Pixheight][Pixwidth];
    for (int i = 0; i < Pixheight; ++i)
    { // set the entire grid to false
        std::fill(grid[i], grid[i] + Pixwidth, false);
    }
    line = "";
    double flagx, flagy, flagz;
    double time = 0;

    // loop to iterate every frame
    while (1)
    {
        auto start = std::chrono::steady_clock::now();

        for (int i = 0; i < lineCount; i++)
        {
            flagx = coord[i].x; // get all coord wrt to the origin
            flagy = coord[i].y;
            flagz = coord[i].z;
            coord[i].x = getXAfterRot(flagx, flagy, flagz);
            coord[i].y = getYAfterRot(flagx, flagy, flagz);
            coord[i].z = getZAfterRot(flagx, flagy, flagz);
            int prox = coord[i].prox(), proy = coord[i].proy();
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
