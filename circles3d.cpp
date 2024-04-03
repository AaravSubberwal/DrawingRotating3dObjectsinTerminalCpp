// program to simulate molecules of gas
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <string>
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

class point3d
{ // point3d class to define the points
public:
    double x, y, z;
    void setpos(double a, double b, double c)
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
int u = 8;
class circle3d
{
public:
    point3d center;
    point3d coord[500];
    circle3d(int r, double a, double b, double c, bool choice)
    {
        center.x = a;
        center.y = b;
        center.z = c;
        int x = r;
        int y = 0;
        int decision_parameter = 1 - x;
        int yes[500][2] = {};

        // Draw the initial points
        yes[0][0] = x;
        yes[0][1] = y;

        yes[1][0] = -x;
        yes[1][1] = y;

        yes[2][0] = x;
        yes[2][1] = -y;

        yes[3][0] = -x;
        yes[3][1] = -y;

        yes[4][0] = y;
        yes[4][1] = x;

        yes[5][0] = -y;
        yes[5][1] = x;

        yes[6][0] = y;
        yes[6][1] = -x;

        yes[7][0] = -y;
        yes[7][1] = -x;

        while (y <= x)
        {
            y += 1;
            if (decision_parameter <= 0)
            {
                decision_parameter += 2 * y + 1;
            }
            else
            {
                x -= 1;
                decision_parameter += 2 * (y - x) + 1;
            }

            // Draw the next set of points
            yes[u][0] = x;
            yes[u][1] = y;
            u++; // 9 17
            yes[u][0] = -x;
            yes[u][1] = y;
            u++;
            yes[u][0] = x;
            yes[u][1] = -y;
            u++;
            yes[u][0] = -x;
            yes[u][1] = -y;
            u++;
            yes[u][0] = y;
            yes[u][1] = x;
            u++;
            yes[u][0] = -y;
            yes[u][1] = x;
            u++;
            yes[u][0] = y;
            yes[u][1] = -x;
            u++;
            yes[u][0] = -y;
            yes[u][1] = -x;
            u++; // 16 24
        }
        if (choice)
        {
            for (int i = 0; i < u; i++)
            {
                coord[i].x = center.x + yes[i][0];
                coord[i].y = center.y + yes[i][1];
                coord[i].z = center.z;
            }
        }
        else
        {
            for (int i = 0; i < u; i++)
            {
                coord[i].x = center.x + yes[i][0];
                coord[i].y = center.y;
                coord[i].z = center.z + yes[i][1];
            }
        }
    }
};

int main()
{
    circle3d circle1(15, 0, 0, 0, true);
    circle3d circle2(15, 0, 0, 0, false);

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
        for (int i = 0; i < u; i++)
        {                                                  // loop iterates through each coordinate
            flagx = circle1.coord[i].x - circle1.center.x; // get all coord wrt to the origin
            flagy = circle1.coord[i].y - circle1.center.y;
            flagz = circle1.coord[i].z - circle1.center.z; // for rotation
            circle1.coord[i].x = getXAfterRot(flagx, flagy, flagz);
            circle1.coord[i].y = getYAfterRot(flagx, flagy, flagz);
            circle1.coord[i].z = getZAfterRot(flagx, flagy, flagz);
            circle1.coord[i].x += circle1.center.x;
            circle1.coord[i].y += circle1.center.y;
            circle1.coord[i].z += circle1.center.z;

            int prox = circle1.coord[i].prox(), proy = circle1.coord[i].proy(); // gives the coordinates
            if (proy > 0 && proy < Pixheight && prox > 0 && prox < Pixwidth)
            { // puts them in the grid at suitable place
                grid[proy][prox] = true;
            }
        }
        for (int i = 0; i < u; i++)
        {                                                  // loop iterates through each coordinate
            flagx = circle2.coord[i].x - circle2.center.x; // get all coord wrt to the origin
            flagy = circle2.coord[i].y - circle2.center.y;
            flagz = circle2.coord[i].z - circle2.center.z; // for rotation
            circle2.coord[i].x = getXAfterRot(flagx, flagy, flagz);
            circle2.coord[i].y = getYAfterRot(flagx, flagy, flagz);
            circle2.coord[i].z = getZAfterRot(flagx, flagy, flagz);
            circle2.coord[i].x += circle2.center.x;
            circle2.coord[i].y += circle2.center.y;
            circle2.coord[i].z += circle2.center.z;

            int prox = circle2.coord[i].prox(), proy = circle2.coord[i].proy(); // gives the coordinates
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
        std::cout << 1000.0/(duration.count())<<"\n";
    }

    return 0;
}