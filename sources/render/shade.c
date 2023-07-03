/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:41:52 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/30 18:25:53 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_vect get_light_direction(t_light *light, t_pixel *pix)
{
	t_vect light_direction;
	double light_distance;

	light_direction = vector_substract(light->pos, pix->hitpoint);
	light_distance = vector_length(light_direction);
	light_direction = vector_divide(light_direction, light_distance);

	return (light_direction);
}

bool is_in_shadow(t_data *data, t_vect ray_origin, t_vect ray_direction)
{
	t_sphere *spheres;
	t_cylinder *cylinders;
	t_plane *planes;
	double t;

	planes = data->planes;
	while (planes)
	{
		if (is_plane_hit(planes, ray_origin, ray_direction, &t))
			return true;
		planes = planes->next;
	}
	spheres = data->spheres;
	while (spheres)
	{
		if (is_sphere_hit(spheres, ray_origin, ray_direction, &t))
			return true;
		spheres = spheres->next;
	}
	cylinders = data->cylinders;
	while (cylinders)
	{
		if (is_cylinder_hit(cylinders, ray_origin, ray_direction, &t))
			return true;
		cylinders = cylinders->next;
	}

	return false;
}

void shade_diffuse(t_data *data,t_light *light, t_pixel *pix)
{
	t_vect light_direction;
	double dot_product;

	light_direction = get_light_direction(light, pix);
	dot_product = vector_dot_product(pix->normal, light_direction);
	if (dot_product <= 0 || is_in_shadow(data, pix->hitpoint, light_direction))
		parse_color("0,0,0", &(pix->color));
	else
	{
		pix->color.r = (unsigned char)(pix->color.r * light->brightness * dot_product);
		pix->color.g = (unsigned char)(pix->color.g * light->brightness * dot_product);
		pix->color.b = (unsigned char)(pix->color.b * light->brightness * dot_product);
	}
}

void shade(t_data *data, t_coord pixel)
{
	if (data->pix.t != INFINITY)
		shade_diffuse(data, data->light, &(data->pix));
	else
		parse_color("0,0,0", &(data->pix.color));
	set_pixel_color(data, pixel.x, pixel.y, convert_rgb_to_hex(&(data->pix.color)));
}