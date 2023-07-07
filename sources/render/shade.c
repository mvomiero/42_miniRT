/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:41:52 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/07 18:23:32 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vect	random_in_unit_disk()
{
	t_vect	point;
	double	r;

	r = 1.0;
	while (r >= 1.0)
	{
		double u1 = rand() / (RAND_MAX + 1.0);
		double u2 = rand() / (RAND_MAX + 1.0);
		point.x = 2.0 * u1 - 1.0;
		point.y = 2.0 * u2 - 1.0;
		point.z = 0.0;
		r = vector_length(point);
	}
	return (point);
}

static	t_vect get_light_direction(t_light *light, t_pixel *pix)
{
	t_vect	light_direction;
	double	light_distance;

	light_direction = vector_subtract(light->pos, pix->hitpoint);
	light_distance = vector_length(light_direction);
	light_direction = vector_divide(light_direction, light_distance);
	return (light_direction);
}

bool	is_in_shadow(t_data *data, t_vect ray_origin, t_vect ray_direction, double distance_to_light)
{
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_triangle	*triangles;
	double		t;

	if (data->scenes.render == R_SHADED)
		return (false);
	planes = data->planes;
	while (planes)
	{
		if (is_plane_hit(planes, ray_origin, ray_direction, &t) && t < distance_to_light)
		{
			t_vect offset_hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(planes->norm_vect, EPSILON));
			if (is_plane_hit(planes, offset_origin, ray_direction, &t) && t < distance_to_light)
				return true;
		}
		planes = planes->next;
	}
	triangles = data->triangles;
	while (triangles)
	{
		if (is_triangle_hit(triangles, ray_origin, ray_direction, &t) && t < distance_to_light)
		{
			t_vect offset_hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(triangles->norm_vect, EPSILON));
			if (is_triangle_hit(triangles, offset_origin, ray_direction, &t) && t < distance_to_light)
				return (true);
		}
		triangles = triangles->next;
	}
	spheres = data->spheres;
	while (spheres)
	{
		if (is_sphere_hit(spheres, ray_origin, ray_direction, &t) && t < distance_to_light)
			return (true);
		spheres = spheres->next;
	}
	cylinders = data->cylinders;
	while (cylinders)
	{
		if (is_cylinder_hit(cylinders, ray_origin, ray_direction, &t, NULL) && t < distance_to_light)
			return (true);
		if (is_cylinder_disk_bottom_hit(cylinders, ray_origin, ray_direction, &t) && t < distance_to_light)
		{
			t_vect offset_hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(cylinders->norm_vect, EPSILON));
			if (is_cylinder_disk_bottom_hit(cylinders, offset_origin, ray_direction, &t) && t < distance_to_light)
				return (true);
		}
		if (is_cylinder_disk_top_hit(cylinders, ray_origin, ray_direction, &t) && t < distance_to_light)
		{
			t_vect offset_hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(get_opposite_normal(cylinders->norm_vect), EPSILON));
			if (is_cylinder_disk_top_hit(cylinders, offset_origin, ray_direction, &t) && t < distance_to_light)
				return (true);
		}
		cylinders = cylinders->next;
	}
	return (false);
}

void	get_soft_shadow_color(t_data *data, t_light *light, t_pixel *pix, t_vect light_direction)
{
	// int num_shadow_rays = 20;  // Number of shadow rays to cast
	double	shadow_intensity;
	double	pixel_size; 
	int		i;
	double	offset_x;
	t_vect	shadow_target;
	t_vect	shadow_direction;
	double	distance_to_light;
	double	dot_product;
	double	ambient_dot_product;

	shadow_intensity = 0.0;
	pixel_size = 1.0 / data->scenes.n_rays; 
	i = 0;
	while (i < data->scenes.n_rays)
	{
		offset_x = (i % 10 - 5) * pixel_size;
		shadow_target = vector_add(light->pos, vector_scale(random_in_unit_disk(), 2));
		shadow_direction = vector_subtract(shadow_target, vector_add(pix->hitpoint, vector_scale(pix->normal, offset_x)));
		distance_to_light = vector_length(shadow_direction);
		shadow_direction = vector_divide(shadow_direction, distance_to_light);
		if (!is_in_shadow(data, pix->hitpoint, shadow_direction, distance_to_light))
			shadow_intensity += 1;
		i++;
	}
	shadow_intensity /= data->scenes.n_rays;
	dot_product = vector_dot_product(pix->normal, light_direction);
	ambient_dot_product = vector_dot_product(pix->normal, data->ambient->norm_vect);
	pix->color.r = clamp((pix->color.r * light->brightness * dot_product * shadow_intensity) + (ambient_dot_product * data->ambient->light_ratio * data->ambient->color.r), 0, 255);
	pix->color.g = clamp((pix->color.g * light->brightness * dot_product * shadow_intensity) + (ambient_dot_product * data->ambient->light_ratio * data->ambient->color.g), 0, 255);
	pix->color.b = clamp((pix->color.b * light->brightness * dot_product * shadow_intensity) + (ambient_dot_product * data->ambient->light_ratio * data->ambient->color.b), 0, 255);
}

void	get_diffuse_color(t_data *data, t_light *light, t_pixel *pix, t_vect light_direction)
{
	double	dot_product;
	double	ambient_dot_product;
	double	distance_to_light;

	dot_product = vector_dot_product(pix->normal, light_direction);
	ambient_dot_product = vector_dot_product(pix->normal, data->ambient->norm_vect);
	distance_to_light = vector_length(vector_subtract(light->pos, pix->hitpoint));
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

void	shade_diffuse(t_data *data, t_light *light, t_pixel *pix)
{
	t_vect	light_direction = get_light_direction(light, pix);

	if (data->scenes.render == R_SHADED || data->scenes.render == R_SOFT_SHADOWS)
		get_diffuse_color(data, light, pix, light_direction);
	if (data->scenes.render == R_SHADOWS)
		get_soft_shadow_color(data, light, pix, light_direction);
}

void	shade(t_data *data, t_coord pixel)
{
	if (data->pix.t != INFINITY)
		shade_diffuse(data, data->light, &(data->pix));
	else
		parse_color("0,0,0", &(data->pix.color));
	set_pixel_color(data, pixel.x, pixel.y, convert_rgb_to_hex(&(data->pix.color)));
}
