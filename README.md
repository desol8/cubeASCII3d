ASCII 3D Cube Renderer

A lightweight C++ console application that renders a rotating 3D wireframe cube using ASCII characters.
Features

    Real-time 3D Rotation: Mathematical rotation around X and Y axes.

    Perspective Projection: Simulates depth by scaling coordinates based on distance.

    Bresenham's Line Algorithm: Efficiently draws edges between vertices in the console.

    Zero Dependencies: Uses only standard C++ libraries (iostream, cmath, vector, thread).

How It Works

    Vertices & Edges: Defines a cube as a set of 3D points and connections.

    Rotation: Applies trigonometric rotation matrices to each vertex.

    Projection: Maps 3D coordinates (x,y,z) to 2D screen space (xp​,yp​) using:
    xp=2width​+x⋅viewer_distance+zfov​

    Rasterization: Draws the resulting lines onto a 2D character buffer and prints it to the terminal.

Requirements

    C++11 compatible compiler (GCC, Clang, or MSVC).

    Terminal supporting ANSI escape codes (for screen clearing).
Start
    g++ -o cube main.cpp
    ./cube
