/********************************************************************************************
Program to make a 3d spinning circle using the fucking terminal by reading a file which has
all coordinates inside

Author: Aarav Subberwal
Date: 13/05/24

For the output to make even remote sense some terminal settings are required
--> Open the setting in terminal File>Preferences>settings>terminal
--> Font size = 6 scroll to find them
--> Line spacing = 0
--> Line height = 1.2

The project has a few files to read and choose from. Just type the name into the main
function of 3dFileread.cpp to run them. Also feel free to mess around with l,m,n which are
the rotation angles to mess with the rotations.

"Go! My Minions"
*********************************************************************************************/

#include "libraries/3dstuffLib.cpp"

int main()
{
    // Open whichever files you want, by timing the name here.
    // They're in the txtFiles folder.
    std::string file_you_want = "cube.txt";

    std::vector<Point3d> coord_list = getCoordinatesfromFile("txtFiles/" + file_you_want);

    // Setting the screen
    bool screen[Pixheight][Pixwidth];
    for (int i = 0; i < Pixheight; ++i)
    {
        std::fill(screen[i], screen[i] + Pixwidth, false);
    }

    // loop to iterate every frame
    while (1)
    {
        auto start = std::chrono::steady_clock::now(); // start the timer

        for (auto &coordinate : coord_list)
        {
            rotatePoint(coordinate); // function to rotate the pts

            int prox = coordinate.prox(), proy = coordinate.proy();
            // check if the projected values are within the domain of the screen
            if (proy > 0 && proy < Pixheight && prox > 0 && prox < Pixwidth)
            { // puts them in the screen at suitable place
                screen[proy][prox] = true;
            }
        }

        // printing shit up
        PrintEverything(&screen[0][0]);

        auto end = std::chrono::steady_clock::now(); // stop timer
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        wait(t);
        std::cout << 1000.0 / (duration.count()) << "\n"; // print out the fps counter
    }
    return 0;
}
