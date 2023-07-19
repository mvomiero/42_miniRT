# miniRT

## Usage

* Clone the repository with our [libft](https://github.com/mvomiero/42_libft) 
and the official 42 [minilibx](https://github.com/42Paris/minilibx-linux) submodules bu using the `--recurse-submodules` flag:

```
git clone --recurse-submodules https://github.com/mvomiero/42_miniRT.git
```
* to run the python script to test some scenes, error handling and features of the project:
```
make test
```
* When the rendered window shows, press `I` to have for the list of keys

# Project description

## Conceptual diagram

The different phases of the project: parsing, intializing mlx, rendering and starting the mlx loop.
_(mlx is a windowing graphics library that provides a simple interface for creating graphical applications)_

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/diagram.jpg?raw=true)

## Ray tracing

_click on the gifs to see the process_

After parsing and initializing the window and getting the image buffer thanks to the mlx library, the ray tracing process starts.

Ray tracing is a rendering technique used in computer graphics to generate realistic images by simulating the behavior of light. It works by tracing the path of light rays as they interact with objects in a virtual scene. Each ray is cast from a virtual camera through each pixel on the screen and traced as it bounces off objects, undergoes reflection or refraction (not implemented in our project), and eventually reaches a light source.

#### Findind the conversion matrix to translate the ray from the world to the camera coordinate system

1. the camera is defined by a coordinate position and a normal
2. normal is translated to the origin to perform operations
3. up random vector (normal 0,1,0) is set
4. with the cross product (perpendicular vector to the plane defined by two other vectors) the right vector is found
5. the cross product of the camera direction and the right vector is the up vector
6. the camera coordinate system is defined, with a matrix is possible to perform the operations to translate a vector from a system to another

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/minirt_camera_matrix.gif?raw=true)

#### Tracing the camera-pixel ray in the world coordinate system and translate it to the camer coordinate system

1. Define the viewport knowing the field of view and the image ratio
2. find the point world coordinates knowing x and y
3. having two points, the ray is traced
4. the ray is found for the world coordinate system, it has to be translated to the camera's one, by applying the conversion matrix
5. the ray in the camera system is found

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/minirt_camera_ray.gif?raw=true)


#### Rendering the pixel color

1. camera-pixel iterates through the objects and finds intersection points (if an object is hit in two points, the closesest one is choose)
2. pixel color is updated with the object color
3. the iteration continues, a closer hitted object is found. The picel color is changed accordingly.
4. the inluence of ambient light. A vector is traced from the hit point to the light source, a dot product operation is then performed with this ray and the normal to the surface of the hitten object at the hit point. This way the contribution of the ambient light for the shading of the object is calculated.
5. spotlight, in the case of an object drawing projected shadow on the object.

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/minirt_intersections.gif?raw=true)

# Output




