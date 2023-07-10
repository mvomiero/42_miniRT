/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:41:52 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/10 16:47:18 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vect	random_in_unit_disk(void)
{
	t_vect	point;
	double	r;
	double	u1;
	double	u2;

	r = 1.0;
	while (r >= 1.0)
	{
		u1 = rand() / (RAND_MAX + 1.0);
		u2 = rand() / (RAND_MAX + 1.0);
		point.x = 2.0 * u1 - 1.0;
		point.y = 2.0 * u2 - 1.0;
		point.z = 0.0;
		r = vector_length(point);
	}
	return (point);
}

static t_vect	get_light_direction(t_light *light, t_pixel *pix)
{
	t_vect	light_direction;
	double	light_distance;

	light_direction = vector_subtract(light->pos, pix->hitpoint);
	light_distance = vector_length(light_direction);
	light_direction = vector_divide(light_direction, light_distance);
	return (light_direction);
}

void	calculate_soft_shadow(t_shadow *shadow, t_light *light,
	t_pixel *pix, int i)
{
	shadow->offset_x = (i % 10 - 5) * shadow->pixel_size;
	shadow->target = vector_add(light->pos,
			vector_scale(random_in_unit_disk(), 2));
	shadow->direction = vector_subtract(shadow->target,
			vector_add(pix->hitpoint,
				vector_scale(pix->normal, shadow->offset_x)));
	shadow->distance_to_light = vector_length(shadow->direction);
	shadow->direction = vector_divide(shadow->direction,
			shadow->distance_to_light);
}


void	get_soft_shadow_color(t_data *data, t_light *light,
	t_pixel *pix, t_vect light_direction)
{
	int			i;
	t_shadow	shadow;

	shadow.intensity = 0.0;
	shadow.pixel_size = 1.0 / data->scenes.n_rays; 
	i = 0;
	while (i < data->scenes.n_rays)
	{
		calculate_soft_shadow(&shadow, light, pix, i);
		if (!is_in_shadow(data, pix->hitpoint,
				shadow.direction, shadow.distance_to_light))
			shadow.intensity += 1;
		i++;
	}
	shadow.intensity /= data->scenes.n_rays;
	shadow.light_dot_product = vector_dot_product(pix->normal, light_direction);
	shadow.ambient_dot_product = vector_dot_product(pix->normal,
			data->ambient->norm_vect);
	pix->color.r = clamp((pix->color.r * light->brightness
				* shadow.light_dot_product * shadow.intensity)
			+ (shadow.ambient_dot_product * data->ambient->light_ratio
				* data->ambient->color.r), 0, 255);
	pix->color.g = clamp((pix->color.g * light->brightness
				* shadow.light_dot_product * shadow.intensity)
			+ (shadow.ambient_dot_product * data->ambient->light_ratio
				* data->ambient->color.g), 0, 255);
	pix->color.b = clamp((pix->color.b * light->brightness
				* shadow.light_dot_product * shadow.intensity)
			+ (shadow.ambient_dot_product * data->ambient->light_ratio
				* data->ambient->color.b), 0, 255);
}

static int	get_diffuse_shadow_rgb(int color, t_data *data, t_shadow shadow)
{
	int	new_color;

	new_color = clamp((shadow.ambient_dot_product * data->ambient->light_ratio
					* color), 0, 255);
	return (new_color);
}

static int	get_diffuse_rgb(int color, t_data *data, t_light *light, t_shadow shadow)
{
	int	new_color;

	new_color = clamp((color * light->brightness * shadow.light_dot_product)
				+ (shadow.ambient_dot_product * data->ambient->light_ratio
					* color), 0, 255);
	return (new_color);
}

void	get_diffuse_color(t_data *data, t_light *light,
	t_pixel *pix, t_vect light_direction)
{
	t_shadow	shadow;

	shadow.light_dot_product = vector_dot_product(pix->normal, light_direction);
	shadow.ambient_dot_product = vector_dot_product(pix->normal,
			data->ambient->norm_vect);
	shadow.distance_to_light = vector_length(
			vector_subtract(light->pos, pix->hitpoint));
	if (shadow.light_dot_product <= 0
		|| is_in_shadow(data, pix->hitpoint,
			light_direction, shadow.distance_to_light))
	{
		pix->color.r = get_diffuse_shadow_rgb(data->ambient->color.r,data, shadow);
		pix->color.g = get_diffuse_shadow_rgb(data->ambient->color.g,data, shadow);
		pix->color.b = get_diffuse_shadow_rgb(data->ambient->color.b,data, shadow);
	}
	else
	{
		pix->color.r = get_diffuse_rgb(pix->color.r, data, light, shadow);
		pix->color.g = get_diffuse_rgb(pix->color.g, data, light, shadow);
		pix->color.b = get_diffuse_rgb(pix->color.b, data, light, shadow);
	}
}

void	shade_diffuse(t_data *data, t_light *light, t_pixel *pix)
{
	t_vect	light_direction;

	light_direction = get_light_direction(light, pix);
	if (data->scenes.render == R_SHADED
		|| data->scenes.render == R_SOFT_SHADOWS)
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
	set_pixel_color(data, pixel.x, pixel.y,
		convert_rgb_to_hex(&(data->pix.color)));
}
