#define D 25   // Distance to user
#define t 0.01 // time

#define SCALE 1 //if u wanna resize the sprite

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

std::string line = "";
double flagx, flagy, flagz;
