/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:37:24 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/29 18:51:22 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*static void set_pixel_color(t_data *data, int x, int y, int color)
{
	data->buf[x * 4 + y * WIDTH * 4] = (char)color; // B
	data->buf[x * 4 + y * WIDTH * 4 + 1] = (char)0; // G
	data->buf[x * 4 + y * WIDTH * 4 + 2] = (char)0; // R
	data->buf[x * 4 + y * WIDTH * 4 + 3] = (char)0; // Trans
}*/

// Function to negate a vector
t_vect vectorNegation(t_vect vector)
{
    t_vect result;
    result.x = -vector.x;
    result.y = -vector.y;
    result.z = -vector.z;
    return result;
}

// Function to calculate the reflection direction of a vector
t_vect vectorReflect(t_vect incident, t_vect normal)
{
    double dotProduct = vectorDotProduct(incident, normal);
    t_vect reflection;
    reflection.x = incident.x - 2 * dotProduct * normal.x;
    reflection.y = incident.y - 2 * dotProduct * normal.y;
    reflection.z = incident.z - 2 * dotProduct * normal.z;
    return reflection;
}

// Function to scale a color by a factor
t_color colorScale(t_color color, double factor)
{
    t_color scaledColor;
    scaledColor.r = color.r * factor;
    scaledColor.g = color.g * factor;
    scaledColor.b = color.b * factor;
    return scaledColor;
}

// Macro to clamp a value within a specified range
#define clamp(value, min, max) ((value) < (min) ? (min) : ((value) > (max) ? (max) : (value)))

// Specular exponent value
#define SPECULAR_EXPONENT 32

// Function to add two colors
t_color colorAdd(t_color color1, t_color color2)
{
    t_color result;
    result.r = color1.r + color2.r;
    result.g = color1.g + color2.g;
    result.b = color1.b + color2.b;
    return result;
}

void shade_pixel(t_pixel *pixel, t_light *light)
{
    // Calculate the light direction
    t_vect light_direction = vectorSubtraction(light->pos, pixel->hitpoint);
    light_direction = vectorNormalize(light_direction);

    // Calculate the diffuse factor based on the light direction and the surface normal
    double diffuse_factor = vectorDotProduct(pixel->normal, light_direction);
    diffuse_factor = clamp(diffuse_factor, 0.0, 1.0);

    // Calculate the specular factor based on the view direction and the reflected light direction
    t_vect view_direction = vectorNegation(pixel->dir);
    t_vect reflect_direction = vectorReflect(light_direction, pixel->normal);
    double specular_factor = pow(vectorDotProduct(view_direction, reflect_direction), SPECULAR_EXPONENT);
    specular_factor = clamp(specular_factor, 0.0, 1.0);

    // Calculate the total brightness based on the diffuse and specular factors and the light's brightness
    double total_brightness = light->brightness * (diffuse_factor + specular_factor);

    // Calculate the diffuse and specular color contributions
    t_color diffuse_color = colorScale(light->color, total_brightness);
    t_color specular_color = colorScale(light->color, total_brightness);

    // Add the diffuse and specular colors to obtain the shaded color
    t_color shaded_color = colorAdd(diffuse_color, specular_color);

    // Clamp the color values to the range of 0-255
    shaded_color.r = clamp(shaded_color.r * 255, 0, 255);
    shaded_color.g = clamp(shaded_color.g * 255, 0, 255);
    shaded_color.b = clamp(shaded_color.b * 255, 0, 255);

    // Assign the shaded color to the pixel
    pixel->color = shaded_color;
}


/*void calculateShadedColor(t_data *data, t_pixel *pix, t_ambient *ambient, t_light *lights, int numLights)
{
	(void)data;
    // Initialize the shaded color with the ambient color
    t_color shadedColor = ambient->color;

    // Calculate the ambient component of the shaded color
    shadedColor.r *= ambient->light_ratio;
    shadedColor.g *= ambient->light_ratio;
    shadedColor.b *= ambient->light_ratio;

	(void)lights;
	(void)numLights;

    // Iterate over each light source
    for (int i = 0; i < numLights; i++)
    {
        t_light *light = &lights[i];

        // Calculate the direction from the intersection point to the light source
        t_vect lightDirection = vectorNormalize(vectorSubtraction(light->pos, pix->hitpoint));

        // Calculate the dot product between the light direction and the surface normal
        double cosTheta = vectorDotProduct(pix->normal, lightDirection);

        // Check if the light source is illuminating the surface (cosTheta > 0)
        if (cosTheta > 0)
        {
            // Calculate the diffuse component of the shaded color
            shadedColor.r += pix->color.r * light->color.r * light->brightness * cosTheta;
            shadedColor.g += pix->color.g * light->color.g * light->brightness * cosTheta;
            shadedColor.b += pix->color.b * light->color.b * light->brightness * cosTheta;
        }
    }

    // Update the shaded color in the pixel structure
    pix->color = shadedColor;
}*/




static void	set_pixel_color(t_data *data, int x, int y, int color)
{
	data->buf[x * 4 + y * WIDTH * 4] = color;
	data->buf[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
	data->buf[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
	data->buf[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
}

int convert_rgb_to_hex(t_color *color)
{
    int hex = (color->r << 16) | (color->g << 8) | color->b;
    return hex;
}

void calculateRayDirection(t_data *data, t_camera *camera, int pixelX, int pixelY)
{
	double fovRadians = camera->fov * M_PI / 180.0; // Convert FOV to radians
	double aspectRatio = (double)WIDTH / (double)HEIGHT;
	double viewportHeight = 2.0 * tan(fovRadians / 2.0);
	double viewportWidth = aspectRatio * viewportHeight;

	double pixelNormalizedX = (pixelX + 0.5) / WIDTH; // Normalize pixel coordinates
	double pixelNormalizedY = (pixelY + 0.5) / HEIGHT;

	double viewportX = (2 * pixelNormalizedX - 1) * viewportWidth / 2.0;
	double viewportY = (1 - 2 * pixelNormalizedY) * viewportHeight / 2.0;

	t_vect rayDirection = {
		camera->norm_vect.x + viewportX,
		camera->norm_vect.y + viewportY,
		camera->norm_vect.z};

	data->pix.dir = rayDirection;
}

static void ray_tracer(t_data *data, int x, int y)
{
	parse_color("0,0,120",&(data->pix.color));
	data->pix.t = INFINITY;
	calculateRayDirection(data, data->camera, x, y);

	hit_sphere(data, data->spheres, data->camera->pos, data->pix.dir);
	hit_cylinder(data, data->cylinders, data->camera->pos, data->pix.dir);
	hit_plane(data, data->planes, data->camera->pos, data->pix.dir);

	//calculateShadedColor(data, &(data->pix), data->ambient, data->light, 1);
	shade_pixel(&(data->pix), data->light);

	// shade with pix function
		set_pixel_color(data, x, y, convert_rgb_to_hex(&(data->pix.color)));
}

static void render_pixel(t_data *data)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ray_tracer(data, x, y);
	}
}

void render(t_data *data)
{
	int pixel_bits;
	int line_bytes;
	int endian;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);

	data->buf = mlx_get_data_addr(data->img, &pixel_bits, &line_bytes, &endian);
	render_pixel(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	// mlx_destroy_image(f->mlx, f->img);
}