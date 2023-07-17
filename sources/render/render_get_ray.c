/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_get_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 11:12:31 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/17 11:54:52 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
	aspect_ratio = (double)WIDTH / HEIGHT;
	p_x = (2 * (x + 0.5) / WIDTH - 1) * aspect_ratio * fov;
	p_y = (1 - 2 * (y + 0.5) / HEIGHT) * fov;
	return (new_vector(-p_x, p_y, 1));
}

t_ray	get_ray(t_data *data, int x, int y)
{
	t_vect	shooting_direction;
	t_ray	ray;

	if (data->camera->norm_vect.x == 0 && (data->camera->norm_vect.y == 1
			|| data->camera->norm_vect.y == -1))
		data->camera->norm_vect.x = EPSILON;
	shooting_direction = ray_pixel_to_world(data, x, y);
	shooting_direction = multiply_by_matrix(shooting_direction,
			data->camera->m);
	shooting_direction = vector_subtract(shooting_direction, data->camera->pos);
	shooting_direction = vector_normalize(shooting_direction);
	ray.origin = data->camera->pos;
	ray.direction = shooting_direction;
	return (ray);
}
