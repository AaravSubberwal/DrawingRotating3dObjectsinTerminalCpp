/********************************************************************************************
Program to read most Obj files downloaded from the internet from whatever platform and
converted into a format to be readable by 3dFileread.cpp.

Author: Aarav Subberwal
Date: 13/05/24

Copy and paste the output into a 
*********************************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

int main() {
    std::string filename = "DwarfHammerBrown.txt";  // Replace with your OBJ file name
    std::ifstream objFile(filename);

    if (!objFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(objFile, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        // Process only lines that start with "v " and not "vn", "vt", etc.
        if (prefix == "v") {
            float x, y, z;
            if (iss >> x >> y >> z) {
                std::cout << 7*x << "," << 7*y << "," << 7*z << std::endl;
            }
        }
    }

    objFile.close();
    return 0;
}

