/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:41:52 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/30 16:54:51 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_vect get_light_direction(t_light *light, t_pixel *pix)
{
	t_vect lightDirection;
	double lightDistance;

	lightDirection = vector_substract(light->pos, pix->hitpoint);
	lightDistance = vector_length(lightDirection);
	lightDirection = vector_divide(lightDirection, lightDistance);

	return (lightDirection);
}

void shade_diffuse(t_light *light, t_pixel *pix)
{
	t_vect lightDirection;
	double dotProduct;

	lightDirection = get_light_direction(light, pix);
	dotProduct = vector_dot_product(pix->normal, lightDirection);
	if (dotProduct <= 0)
		parse_color("0,0,0", &(pix->color));
	else
	{
		pix->color.r = (unsigned char)(pix->color.r * light->brightness * dotProduct);
		pix->color.g = (unsigned char)(pix->color.g * light->brightness * dotProduct);
		pix->color.b = (unsigned char)(pix->color.b * light->brightness * dotProduct);
	}
}

void shade(t_data *data, t_coord pixel)
{
	if (data->pix.t != INFINITY)
		shade_diffuse(data->light, &(data->pix));
	else
		parse_color("0,0,0", &(data->pix.color));
	set_pixel_color(data, pixel.x, pixel.y, convert_rgb_to_hex(&(data->pix.color)));
}