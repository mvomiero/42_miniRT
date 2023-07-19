# miniRT

## Usage

Clone the repository with our [libft](https://github.com/mvomiero/42_libft) 
and the official 42 [minilibx](https://github.com/42Paris/minilibx-linux) submodules bu using the `--recurse-submodules` flag:

```
git clone --recurse-submodules https://github.com/mvomiero/42_miniRT.git
```
to run the python script to test some scenes, error handling and features of the project:
```
make test
```

# Project description

## Conceptual diagram

The different phases of the project: parsing, intializing mlx, rendering and starting the mlx loop.
_(mlx is a windowing graphics library that provides a simple interface for creating graphical applications)_

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/diagram.jpg?raw=true)

## Ray tracing

After parsing and initializing the window and getting the image buffer thanks to the mlx library, the ray tracing process starts.

Ray tracing is a rendering technique used in computer graphics to generate realistic images by simulating the behavior of light. It works by tracing the path of light rays as they interact with objects in a virtual scene. Each ray is cast from a virtual camera through each pixel on the screen and traced as it bounces off objects, undergoes reflection or refraction (not implemented in our project), and eventually reaches a light source.

#### Tracing the camera-pixel ray
#### Findind the conversion matrix to translate the ray from the world to the camera coordinate system

1. the camera is defined by a coordinate position and a normal
2. normal is translated to the origin to perform operations
3. up random vector (normal 0,1,0) is set
4. with the cross product (perpendicular vector to the plane defined by two other vectors) the right vector is found
5. the cross product of the camera direction and the right vector is the up vector
6. the camera coordinate system is defined, with a matrix is possible to perform the operations to translate a vector from a system to another


![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/minirt_camera_matrix.gif?raw=true)

#### Rendering the pixel color

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/minirt_intersections.gif?raw=true)

