# 3d-engine

So I was looking for some fancy programs to write and then I decided to make a circle generator in a terminal. When I finally made it I was inspired and wanted to build something even better. So I though Why not just make a 3d rotating cube in a terminal using the same sort of screen in the terminal I did for the circle generator earlier. After a few days of work I did pull it off.

The resources I used was mostly this book my dad bought in 1994 called cutting edge 3d game programming with c++ by John De Goes. 

Basically what the program does is it can take input points and it'll put them up on a screen
everywhere there's supposed to be a point a "#" is printed and where there is none it's just "   ". after making a desired image it clears out the terminal and prints it again. In every frame all points are rotatated and then printed.

For the output to make even remote sense some specific terminal settings are required. So far I've only tested the project in vscode.
--> Open the setting in terminal File>Preferences>settings>terminal
--> Font size = 6 scroll to find them
--> Line spacing = 0
--> Line height = 1.2

The project has a few files to read and choose from. Just type the name into the main function of 3dFileread.cpp to run them. Also feel free to mess around with l,m,n which are the rotation angles to mess with the rotations.

# Project Roadmap

> *The next step is physics.*
- render a sphere in 3d
- I want to add some sort of lightsource which reflects light on a sphere and this light source is oscilating and it looks amazing
- *A 3d game in which you can walk around using wasd keys*