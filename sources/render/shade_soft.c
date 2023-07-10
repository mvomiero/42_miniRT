/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_soft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:11:06 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/10 17:15:22 by lde-ross         ###   ########.fr       */
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

static void	get_soft_rgb(t_data *data, t_light *light, t_shadow shadow)
{
	data->pix.color.r = clamp((data->pix.color.r * light->brightness
				* shadow.light_dot_product * shadow.intensity)
			+ (shadow.ambient_dot_product * data->ambient->light_ratio
				* data->ambient->color.r), 0, 255);
	data->pix.color.g = clamp((data->pix.color.g * light->brightness
				* shadow.light_dot_product * shadow.intensity)
			+ (shadow.ambient_dot_product * data->ambient->light_ratio
				* data->ambient->color.g), 0, 255);
	data->pix.color.b = clamp((data->pix.color.b * light->brightness
				* shadow.light_dot_product * shadow.intensity)
			+ (shadow.ambient_dot_product * data->ambient->light_ratio
				* data->ambient->color.b), 0, 255);
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
	get_soft_rgb(data, light, shadow);
}
