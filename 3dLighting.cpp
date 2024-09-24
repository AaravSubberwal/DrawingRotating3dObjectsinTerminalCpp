/********************************************************************************************
Work in Progress atm
*********************************************************************************************/
#include "libraries/3dstuffLib.cpp"
#include "libraries/Vector3D.cpp"

class lightsource{
    public:
    double x,y,z;
    void setPos(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }
};

int main()
{
    // Open whichever files you want, by timing the name here
    std::string file_you_want = "flatplane.txt";
    std::vector<Point3d> coord_list = getCoordinatesfromFile("txtFiles/" + file_you_want);
   

    Vector3D light(-30,0,30);
    double theta=0;
    Vector3D eye(0,0,-D);
    Vector3D reflected_ray(0,0,0);
    Vector3D normal(0,0,-1);
    Vector3D point;

    // Setting the screen
    double screen[Pixheight][Pixwidth];
    for (int i = 0; i < Pixheight; ++i)
    { 
        std::fill(screen[i], screen[i] + Pixwidth, 0);
    }
   
    // loop to iterate every frame
    while (1)
    {
        for (auto &coordinate: coord_list)
        {   
            point.set(coordinate.x,coordinate.y,coordinate.z);
            reflected_ray=((point.subtract(light)).subtract(normal.scalarMultiply(2*(point.subtract(light)).dotProduct(normal)))).scalarMultiply(1/(point.subtract(light)).mod());
            theta=acos(((eye.dotProduct(reflected_ray))-point.dotProduct(reflected_ray))/reflected_ray.mod()*(eye.subtract(reflected_ray)).mod());


            int prox = coordinate.prox(), proy = coordinate.proy();
            //check if the projected values are within the domain of the screen
            if (proy > 0 && proy < Pixheight && prox > 0 && prox < Pixwidth) 
            { // puts them in the screen at suitable place
                screen[proy][prox] = (static_cast<int>(std::round(theta)))%18;
            }
        }

        // printing shit up
        std::cout << "\033[H"; // clears out the terminal

        for (int i = 0; i < Pixheight; i++)
        {
            for (int j = 0; j < Pixwidth; j++)
            {
                if (screen[i][j]==0)
                {
                    line += "   ";      //the projected values of the coordinates are put
                }                       //in suitable places line by line
                else
                {
                    line = line+ " "+std::to_string(static_cast<int>(screen[i][j]))+" ";
                }
            }
            std::cout << line << "\n"; // Prints the entire line at once
            line.clear();              // clears out the string to be reused by the next line
            std::fill(screen[i], screen[i] + Pixwidth, false);
        }
        wait(t);
    }

    return 0;
}
