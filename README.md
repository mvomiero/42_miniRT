# miniRT

## Usage

Clone the repository with our [libft](https://github.com/mvomiero/42_libft) 
and the official 42 [minilibx](https://github.com/42Paris/minilibx-linux) submodules bu using the `--recurse-submodules` flag:

```
git clone --recurse-submodules https://github.com/mvomiero/42_miniRT.git
```

# Project description

## Conceptual diagram

The different phases of the project: parsing, intializing mlx, rendering and starting the mlx loop.
_(mlx is a windowing graphics library that provides a simple interface for creating graphical applications)_

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/diagram.jpg?raw=true)

## Ray tracing

After parsing and initializing the window and getting the image buffer thanks to the mlx library, the ray tracing process starts.

Ray tracing is a rendering technique used in computer graphics to generate realistic images by simulating the behavior of light. It works by tracing the path of light rays as they interact with objects in a virtual scene. Each ray is cast from a virtual camera through each pixel on the screen and traced as it bounces off objects, undergoes reflection or refraction (not implemented in our project), and eventually reaches a light source.



