/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:40:21 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/05 18:16:07 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	convert_rgb_to_hex(t_color *color)
{
	int	hex;

	hex = (color->r << 16) | (color->g << 8) | color->b;
	return (hex);
}

void	set_pixel_color(t_data *data, int x, int y, int color)
{
	data->buf[x * 4 + y * WIDTH * 4] = color;
	data->buf[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
	data->buf[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
	data->buf[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
}
