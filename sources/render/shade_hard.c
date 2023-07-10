/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 17:15:55 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/10 17:16:39 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	get_diff_shadow_rgb(int color, t_data *data, t_shadow shadow)
{
	int	new_color;

	new_color = clamp((shadow.ambient_dot_product * data->ambient->light_ratio
				* color), 0, 255);
	return (new_color);
}

static int	get_diff_rgb(int color, t_data *data,
	t_light *light, t_shadow shadow)
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
		pix->color.r = get_diff_shadow_rgb(data->ambient->color.r,
				data, shadow);
		pix->color.g = get_diff_shadow_rgb(data->ambient->color.g,
				data, shadow);
		pix->color.b = get_diff_shadow_rgb(data->ambient->color.b,
				data, shadow);
	}
	else
	{
		pix->color.r = get_diff_rgb(pix->color.r, data, light, shadow);
		pix->color.g = get_diff_rgb(pix->color.g, data, light, shadow);
		pix->color.b = get_diff_rgb(pix->color.b, data, light, shadow);
	}
}
