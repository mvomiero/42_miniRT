/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:37:24 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/17 10:53:38 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vect	new_vector(double x, double y, double z)
{
	t_vect	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vect	multiply_by_matrix(t_vect p, t_matrix m)
{
	t_vect	res;

	res.x = p.x * m.d[0][0] + p.y * m.d[1][0] + p.z * m.d[2][0] + m.d[3][0];
	res.y = p.x * m.d[0][1] + p.y * m.d[1][1] + p.z * m.d[2][1] + m.d[3][1];
	res.z = p.x * m.d[0][2] + p.y * m.d[1][2] + p.z * m.d[2][2] + m.d[3][2];
	return (res);
}

t_vect	ray_pixel_to_world(t_data *data, int x, int y)
{
	double	aspect_ratio;
	double	fov;
	double	p_x;
	double	p_y;

	fov = tanf((double)data->camera->fov / 2 * M_PI / 180);
	aspect_ratio = WIDTH / HEIGHT;
	p_x = (2 * (x + 0.5) / WIDTH - 1) * aspect_ratio * fov;
	p_y = (1 - 2 * (y + 0.5) / HEIGHT) * fov;
	
	return (new_vector(-p_x, p_y, 1));
}

t_ray	get_ray(t_data *data, int x, int y)
{
	t_vect	shooting_direction;
	t_ray	ray;

	if (data->camera->norm_vect.x == 0 && (data->camera->norm_vect.y == 1 || data->camera->norm_vect.y == -1))
		data->camera->norm_vect.x = EPSILON;
	shooting_direction = ray_pixel_to_world(data, x, y);
	shooting_direction = multiply_by_matrix(shooting_direction, data->camera->m);
	shooting_direction = vector_subtract(shooting_direction, data->camera->pos);
	shooting_direction = vector_normalize(shooting_direction);
	ray.origin = data->camera->pos;
	ray.direction = shooting_direction;
	return (ray);
}

void	matrix_look_at(t_data *s)
{
	t_vect		random;
	t_vect		right;
	t_vect		up;

	random = new_vector(0, 1, 0);
	right = vector_cross_product(random, s->camera->norm_vect);
	right = vector_normalize(right);
	up = vector_cross_product(s->camera->norm_vect, right);
	up = vector_normalize(up);

	if (vector_length(up) == 0) {
		random = new_vector(0, 0, 1);
		right = vector_cross_product(random, s->camera->norm_vect);
		right = vector_normalize(right);
		up = vector_cross_product(s->camera->norm_vect, right);
	}
	s->camera->m.d[0][0] = right.x;
	s->camera->m.d[0][1] = right.y;
	s->camera->m.d[0][2] = right.z;
	s->camera->m.d[0][3] = 0;
	s->camera->m.d[1][0] = up.x;
	s->camera->m.d[1][1] = up.y;
	s->camera->m.d[1][2] = up.z;
	s->camera->m.d[1][3] = 0;
	s->camera->m.d[2][0] = s->camera->norm_vect.x;
	s->camera->m.d[2][1] = s->camera->norm_vect.y;
	s->camera->m.d[2][2] = s->camera->norm_vect.z;
	s->camera->m.d[2][3] = 0;
	s->camera->m.d[3][0] = s->camera->pos.x;
	s->camera->m.d[3][1] = s->camera->pos.y;
	s->camera->m.d[3][2] = s->camera->pos.z;
	s->camera->m.d[3][3] = 1;
}

static void	render_pixel(t_data *data)
{
	int			x;
	int			y;
	t_coord		pixel;
	static int	i = 0;
	t_ray		ray;


	matrix_look_at(data);
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
