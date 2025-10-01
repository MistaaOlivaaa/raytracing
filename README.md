# SimpleRaytracer

A basic raytracing implementation in C++ that demonstrates fundamental concepts of ray tracing, including sphere intersection, basic lighting, and camera positioning.

## Features

- Ray-sphere intersection
- Diffuse lighting
- Configurable camera with field of view and aspect ratio
- Multiple object support
- PPM image output (convertible to PNG)

## Prerequisites

- C++ compiler with C++17 support
- CMake (version 3.10 or higher)
- ImageMagick (optional, for PNG conversion)

## Project Structure

```
raytracing/
├── src/
│   ├── main.cpp         # Main raytracer implementation
│   ├── vector3.hpp      # 3D vector operations
│   ├── ray.hpp          # Ray class definition
│   └── sphere.hpp       # Sphere object implementation
├── build/              # Build directory
├── CMakeLists.txt     # CMake configuration
└── README.md          # This file
```

## Building the Project

1. Create and enter the build directory:
   ```bash
   mkdir build
   cd build
   ```

2. Generate the build files:
   ```bash
   cmake ..
   ```

3. Build the project:
   ```bash
   make
   ```

## Running the Raytracer

After building, run the raytracer from the build directory:
```bash
./raytracer
```

This will generate an `output.ppm` file containing the rendered image.

### Converting PPM to PNG

To convert the output to PNG format using ImageMagick:
```bash
convert output.ppm output.png
```

## Customizing the Scene

You can modify the scene by editing `src/main.cpp`:

- Add or modify spheres in the scene
- Change the camera position and direction
- Adjust the light direction
- Modify the image resolution

Example of adding a sphere:
```cpp
spheres.push_back(Sphere(Vector3(x, y, z), radius, Vector3(r, g, b)));
```

## Technical Details

- The raytracer uses a simple diffuse lighting model
- Vectors are implemented with double precision
- Camera implements a perspective projection model
- Image output is in PPM (P3) format

## Future Improvements

Potential enhancements that could be added:

- Reflections and shadows
- Multiple light sources
- Different materials
- Anti-aliasing
- Other geometric primitives (planes, triangles)
- Texture support
- Parallel processing for faster rendering
