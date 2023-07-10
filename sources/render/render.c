/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:37:24 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/10 16:42:33 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	render_pixel(t_data *data)
{
	int			x;
	int			y;
	t_coord		pixel;
	static int	i = 0;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pixel.x = x;
			pixel.y = y;
			ray_tracer(data, pixel);
			shade(data, pixel);
		}
		i++;
		if (i == 10)
		{
			i = 0;
			mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
		}
	}
}

void	render(t_data *data)
{
	int	pixel_bits;
	int	line_bytes;
	int	endian;

	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->buf = mlx_get_data_addr(data->img, &pixel_bits, &line_bytes, &endian);
	render_pixel(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
