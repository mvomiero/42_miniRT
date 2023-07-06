/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:41:52 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/06 11:00:10 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vect random_in_unit_disk()
{
	t_vect point;
	double r;

	do
	{
		double u1 = rand() / (RAND_MAX + 1.0); // Generate a random value between 0 and 1
		double u2 = rand() / (RAND_MAX + 1.0); // Generate another random value between 0 and 1

		point.x = 2.0 * u1 - 1.0; // Map u1 to the range -1 to 1
		point.y = 2.0 * u2 - 1.0; // Map u2 to the range -1 to 1
		point.z = 0.0;			  // Set the z-coordinate to 0 since we're working in a 2D disk

		r = vector_length(point); // Calculate the length of the vector from the origin to the point
	} while (r >= 1.0);			  // Repeat if the point is outside the unit disk

	return point; // Return the randomly generated point within the unit disk
}

static t_vect get_light_direction(t_light *light, t_pixel *pix)
{
	t_vect light_direction;
	double light_distance;

	light_direction = vector_sub(light->pos, pix->hitpoint);	  // Calculate the vector from the pixel's hitpoint to the light source
	light_distance = vector_length(light_direction);				  // Calculate the distance between the pixel's hitpoint and the light source
	light_direction = vector_divide(light_direction, light_distance); // Normalize the light direction vector

	return light_direction; // Return the normalized light direction vector
}

bool is_in_shadow(t_data *data, t_vect ray_origin, t_vect ray_direction, double distance_to_light)
{
	t_sphere *spheres;
	t_cylinder *cylinders;
	t_plane *planes;
	t_triangle *triangles;
	double t;

	if (data->scenes.render == R_SHADED)
		return (false);
	planes = data->planes;
	while (planes)
	{
		if (is_plane_hit(planes, ray_origin, ray_direction, &t) && t < distance_to_light)
		{
			// Apply offset to avoid self-intersection
			t_vect offset_hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(planes->norm_vect, EPSILON));

			// Check if the offset ray intersects the plane before the light
			if (is_plane_hit(planes, offset_origin, ray_direction, &t) && t < distance_to_light)
				return true;
		}
		planes = planes->next;
	}
	triangles = data->triangles;
	while (triangles)
	{
		if (is_triangle_hit(triangles, ray_origin, ray_direction, &t) && t < distance_to_light)
			return true; // If a plane is hit and the hit distance is smaller than the distance to the light, return true
		triangles = triangles->next;
	}

	spheres = data->spheres;
	while (spheres)
	{
		if (is_sphere_hit(spheres, ray_origin, ray_direction, &t) && t < distance_to_light)
			return true; // If a sphere is hit and the hit distance is smaller than the distance to the light, return true
		spheres = spheres->next;
	}
	cylinders = data->cylinders;
	while (cylinders)
	{
		if (is_cylinder_hit(cylinders, ray_origin, ray_direction, &t, NULL) && t < distance_to_light)
			return true;
		else if (is_cylinder_disk_bottom_hit(cylinders, ray_origin, ray_direction, &t) && t < distance_to_light)
		{
			// Apply offset to avoid self-intersection
			t_vect offset_hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(cylinders->norm_vect, EPSILON));
			
			// Check if the offset ray intersects the plane before the light
			if (is_cylinder_disk_bottom_hit(cylinders, offset_origin, ray_direction, &t) && t < distance_to_light)
				return true;
		}
		else if (is_cylinder_disk_top_hit(cylinders, ray_origin, ray_direction, &t) && t < distance_to_light)
		{
			// Apply offset to avoid self-intersection
			t_vect offset_hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(get_opposite_normal(cylinders->norm_vect), EPSILON));
			
			// Check if the offset ray intersects the plane before the light
			if (is_cylinder_disk_top_hit(cylinders, offset_origin, ray_direction, &t) && t < distance_to_light)
				return true;
		}
		cylinders = cylinders->next;
	}

	return false;
}

void get_soft_shadow_color(t_data *data, t_light *light, t_pixel *pix, t_vect light_direction)
{
	// int num_shadow_rays = 20;  // Number of shadow rays to cast
	double shadow_intensity = 0.0;				   // Accumulator for shadow intensity
	double pixel_size = 1.0 / data->scenes.n_rays; // Size of each pixel for sampling

	for (int i = 0; i < data->scenes.n_rays; i++)
	{
		double offset_x = (i % 10 - 5) * pixel_size; // Calculate a random offset within the pixel

		t_vect shadow_target = vector_add(light->pos, vector_scale(random_in_unit_disk(), 2)); // Calculate the position of the shadow ray's target on the light source

		t_vect shadow_direction = vector_sub(shadow_target, vector_add(pix->hitpoint, vector_scale(pix->normal, offset_x))); // Calculate the direction of the shadow ray
		double distance_to_light = vector_length(shadow_direction);																   // Calculate the distance between the pixel's hitpoint and the shadow target
		shadow_direction = vector_divide(shadow_direction, distance_to_light);													   // Normalize the shadow direction vector

		if (!is_in_shadow(data, pix->hitpoint, shadow_direction, distance_to_light))
		{
			shadow_intensity += 1; // If the shadow ray is not obstructed, increment the shadow intensity
		}
	}

	shadow_intensity /= data->scenes.n_rays; // Calculate the average shadow intensity

	double dot_product = vector_dot_product(pix->normal, light_direction);					// Calculate the dot product between the pixel's normal and the light direction
	double ambient_dot_product = vector_dot_product(pix->normal, data->ambient->norm_vect); // Calculate the dot product between the pixel's normal and the ambient light direction
	// Apply the shadow intensity to the diffuse color calculation
	pix->color.r = clamp((pix->color.r * light->brightness * dot_product * shadow_intensity) + (ambient_dot_product * data->ambient->light_ratio * data->ambient->color.r), 0, 255);
	pix->color.g = clamp((pix->color.g * light->brightness * dot_product * shadow_intensity) + (ambient_dot_product * data->ambient->light_ratio * data->ambient->color.g), 0, 255);
	pix->color.b = clamp((pix->color.b * light->brightness * dot_product * shadow_intensity) + (ambient_dot_product * data->ambient->light_ratio * data->ambient->color.b), 0, 255);
}

void get_diffuse_color(t_data *data, t_light *light, t_pixel *pix, t_vect light_direction)
{
	double dot_product;
	double ambient_dot_product;

	dot_product = vector_dot_product(pix->normal, light_direction);
	ambient_dot_product = vector_dot_product(pix->normal, data->ambient->norm_vect);
	double distance_to_light = vector_length(vector_sub(light->pos, pix->hitpoint));
	if (dot_product <= 0 || is_in_shadow(data, pix->hitpoint, light_direction, distance_to_light))
	{
		pix->color.r = clamp((ambient_dot_product * data->ambient->light_ratio * data->ambient->color.r), 0, 255);
		pix->color.g = clamp((ambient_dot_product * data->ambient->light_ratio * data->ambient->color.g), 0, 255);
		pix->color.b = clamp((ambient_dot_product * data->ambient->light_ratio * data->ambient->color.b), 0, 255);
	}
	else
	{
		pix->color.r = clamp((pix->color.r * light->brightness * dot_product) + (ambient_dot_product * data->ambient->light_ratio * data->ambient->color.r), 0, 255);
		pix->color.g = clamp((pix->color.g * light->brightness * dot_product) + (ambient_dot_product * data->ambient->light_ratio * data->ambient->color.g), 0, 255);
		pix->color.b = clamp((pix->color.b * light->brightness * dot_product) + (ambient_dot_product * data->ambient->light_ratio * data->ambient->color.b), 0, 255);
	}
}

void shade_diffuse(t_data *data, t_light *light, t_pixel *pix)
{
	t_vect light_direction = get_light_direction(light, pix); // Get the normalized light direction

	// Calculate soft shadow color
	if (data->scenes.render == R_SHADED || data->scenes.render == R_SOFT_SHADOWS)
		get_diffuse_color(data, light, pix, light_direction);
	if (data->scenes.render == R_SHADOWS)
		get_soft_shadow_color(data, light, pix, light_direction);
}

void shade(t_data *data, t_coord pixel)
{
	if (data->pix.t != INFINITY)
		shade_diffuse(data, data->light, &(data->pix)); // If the pixel has been hit by a ray, calculate the diffuse shading
	else
		parse_color("0,0,0", &(data->pix.color));									 // If the pixel has not been hit, set the color to black
	set_pixel_color(data, pixel.x, pixel.y, convert_rgb_to_hex(&(data->pix.color))); // Set the color of the pixel in the image buffer
}
