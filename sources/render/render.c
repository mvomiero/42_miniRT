/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:37:24 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/28 17:18:15 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


static void	set_pixel_color(t_data *data, int x, int y, int color)
{
	data->buf[x * 4 + y * WIDTH * 4] = (char)color; // B
	data->buf[x * 4 + y * WIDTH * 4 + 1] = (char)0; // G
	data->buf[x * 4 + y * WIDTH * 4 + 2] = (char)0; // R
	data->buf[x * 4 + y * WIDTH * 4 + 3] = (char)0; // Trans
}

void	render_2(t_data *data)
{
	// int		x;
	// int		y;
	// t_vect ray;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			// ray.x = data->camera->norm_vect.x + x;
			// ray.y = data->camera->norm_vect.y + y;
			// ray.z = data->camera->norm_vect.z;
			//if (rayIntersectsSphere(data->camera->pos, ray, *(data->spheres)))
			if (rayIntersectsSphere2(*(data->camera), *(data->spheres)))
				set_pixel_color(data, x, y, 12);
			else
				set_pixel_color(data, x, y, 255);
		}
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	render(t_data *data)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);

	data->buf = mlx_get_data_addr(data->img, &pixel_bits, &line_bytes, &endian);
	
	render_2(data);

	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

	//mlx_destroy_image(f->mlx, f->img);

}