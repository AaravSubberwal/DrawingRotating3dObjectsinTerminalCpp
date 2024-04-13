# 3d-engine

> a terminal-based 3D engine that can render 3D objects, apply transformations like rotation and translation, and project them onto a 2D screen using ASCII characters

## The Backstory

I was looking for fancy programs to write and then I decided to make a circle generator in a terminal. When I finally made it, I was inspired and wanted to build something extraordinary. So I thought to make a 3D rotating cube in a terminal just like I did with the circle generator earlier. After a few days of work I did pull it off.

The resources I used was mostly this book my dad bought in 1994 called Cutting Edge 3D Game Programming with C++ by John De Goes.

Basically the program takes 3D coordinates as input, and projects it on a 2D screen. In the space, a point is denoted by "#" and nothing as whitespace. After making the desired image, the program clears out the terminal and prints it again. In every frame all points are rotated and then printed.

# Project Roadmap

## Short Term Ideas
- Render a sphere in 3D
- Adding light sources which reflect light on a sphere. Allow the light source to oscillate and look amazing.
- Show multiple objects on the screen at once that rotate and translate individually.
- Render objects as opaque, not displaying points which are behind others.
- Use Unicode and color to make point size uniform, improving aesthetics, and add depth.
- Explain the math behind the functions (rotational matrix, vector addition, 2D projection mapping)

## Long Term
> *"The future is in physics."*
- Adding gravity, oscillations.
- Building a primitive 3D game in which you can walk around on a floor with objects.
- Building a database of the 2D projections of 3D shapes, from a finite set of viewing angles based on human visual acuity, from different humanly-discerible viewpoints for efficient rendering, and stopping rotation at points.
- Building a 3D engine for virtual reality headsets, where 4D objects project to 3D and appear in 3D virtual space.
