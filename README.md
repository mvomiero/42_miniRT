# miniRT

## About

This is a ray tracing project that is part of the core curriculum at 42 school. It was developed by myself and [Luca](https://github.com/lucafisc). The subject can be found [here](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/en.subject.pdf).

## Usage

* Clone the repository along with our [libft](https://github.com/mvomiero/42_libft) and the official 42 [minilibx](https://github.com/42Paris/minilibx-linux) submodule by using the `--recurse-submodules` flag:

```bash
git clone --recurse-submodules https://github.com/mvomiero/42_miniRT.git
```

* To run the python script and test some scenes, error handling, and features of the project, use the following command:

```bash
make test
```

* When the rendered window appears, press `I` to view the list of keys.

## Project Description

### Conceptual Diagram

The different phases of the project include parsing, initializing mlx, rendering, and starting the mlx loop. _(mlx is a windowing graphics library that provides a simple interface for creating graphical applications)_

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/diagram.jpg?raw=true)

### Ray Tracing

_(click on the gifs to see the process)_

After parsing and initializing the window and obtaining the image buffer thanks to the mlx library, the ray tracing process starts.

Ray tracing is a rendering technique used in computer graphics to generate realistic images by simulating the behavior of light. It works by tracing the path of light rays as they interact with objects in a virtual scene. Each ray is cast from a virtual camera through each pixel on the screen and traced as it bounces off objects, undergoes reflection or refraction (not implemented in our project), and eventually reaches a light source.

#### Finding the Conversion Matrix to Translate the Ray from the World to the Camera Coordinate System

1. The camera is defined by a coordinate position and a normal.
2. The normal is translated to the origin to perform operations.
3. An up random vector (normal 0, 1, 0) is set.
4. The cross product (perpendicular vector to the plane defined by two other vectors) finds the right vector.
5. The cross product of the camera direction and the right vector yields the up vector.
6. The camera coordinate system is defined, and with a matrix, it is possible to perform the operations to translate a vector from one system to another.

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/minirt_camera_matrix.gif?raw=true)

#### Tracing the Camera-Pixel Ray in the World Coordinate System and Translating it to the Camera Coordinate System

1. Define the viewport by knowing the field of view and the image ratio.
2. Find the point in world coordinates knowing x and y.
3. Trace the ray by having two points.
4. The ray is initially in the world coordinate system; it needs to be translated to the camera's one by applying the conversion matrix.
5. The ray in the camera system is then found.

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/minirt_camera_ray.gif?raw=true)

#### Rendering the Pixel Color

1. The camera-pixel iterates through the objects and finds intersection points (if an object is hit in two points, the closest one is chosen).
2. The pixel color is updated with the object color.
3. The iteration continues, and a closer hit object is found. The pixel color is changed accordingly.
4. The influence of ambient light is calculated. A vector is traced from the hit point to the light source, and a dot product operation is performed with this ray and the normal to the surface of the hit object at the hit point. This way, the contribution of the ambient light for the shading of the object is calculated.
5. Spotlight, in the case of an object casting a projected shadow on another object.

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/minirt_intersections.gif?raw=true)

## Output

![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/spheres.png?raw=true)
![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/cylinders.png?raw=true)
![Alt Text](https://github.com/mvomiero/42_miniRT/blob/publishing/assets/cat.png?raw=true)
