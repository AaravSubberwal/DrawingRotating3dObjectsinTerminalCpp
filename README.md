A program that reads vertices of arbitrary shapes from a file and visually displays their rotation in the terminal

# To run
clone the repo and run 3dfileread.cpp.
For the output to make even remote sense some specific terminal settings are required. So far I've only tested the project in vscode. I already added these to the setting.json file but here they are just in case
--> Open the setting in terminal File>Preferences>settings>terminal
--> Font size = 6 scroll to find them
--> Line spacing = 0
--> Line height = 1.2

The project has a few files to read and choose from. Just type the name into the main function of 3dFileread.cpp to run them. Also feel free to mess around with l,m,n which are the rotation angles to mess with the rotations.

# background
The resources I used was mostly this book my dad bought in 1994 called cutting edge 3d game programming with c++ by John De Goes. 

Basically the program takes 3D coordinates as input, and projects it on a 2D screen. In the space, a point is denoted by "#" and nothing as whitespace. After making the desired image, the program clears out the terminal and prints it again. In every frame all points are rotated and then printed.

# Project Roadmap

## Ideas
- [x] Render a sphere in 3D
- [ ] Adding light sources which reflect light on a sphere. Allow the light source to oscillate and look amazing.
- [ ] Show multiple objects on the screen at once that rotate and translate individually.
- [ ] Render objects as opaque, not displaying points which are behind others.
- [ ] Use Unicode and color to make point size uniform, improving aesthetics, and add depth.
- [ ] Explain the math behind the functions (rotational matrix, vector addition, 2D projection mapping)
- [ ] Adding gravity, oscillations.
- [ ] Building a primitive 3D game in which you can walk around on a floor with objects.

