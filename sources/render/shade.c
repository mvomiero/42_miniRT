/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:41:52 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/10 17:16:46 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_vect	get_light_direction(t_light *light, t_pixel *pix)
{
	t_vect	light_direction;
	double	light_distance;

	light_direction = vector_subtract(light->pos, pix->hitpoint);
	light_distance = vector_length(light_direction);
	light_direction = vector_divide(light_direction, light_distance);
	return (light_direction);
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
