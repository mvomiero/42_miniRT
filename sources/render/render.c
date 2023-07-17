/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:37:24 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/17 18:15:13 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	render_pixel_loop(t_data *data)
{
	int			x;
	int			y;
	t_coord		pixel;
	static int	i = 0;
	t_ray		ray;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pixel.x = x;
			pixel.y = y;
			ray = get_ray(data, x, y);
			data->pix.dir = ray.direction;
			ray_tracer(data, pixel);
			shade(data, pixel);
		}
		if (i++ == 10)
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
	matrix_look_at(data);
	render_pixel_loop(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
