/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_utils_t.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:32:18 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/13 13:58:02 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	fill_normal_t1(double t1, t_data *data, t_cylinder *cyl, t_vect hp)
{
	if (data)
	{
		if (t1 < data->pix.t)
			data->pix.normal = vector_normalize(
					vector_subtract(hp,
						vector_add(cyl->pos,
							vector_scale(cyl->norm_vect,
								vector_dot_product(
									vector_subtract(hp, cyl->pos),
									cyl->norm_vect)))));
	}
}

void	fill_normal_t2(double t2, t_data *data, t_cylinder *cyl, t_vect hp)
{
	if (data)
	{
		if (t2 < data->pix.t)
			data->pix.normal = vector_normalize(
					vector_subtract(hp,
						vector_add(cyl->pos,
							vector_scale(cyl->norm_vect, t2))));
	}
}

bool	t1_routine(t_vect ray_o, t_vect ray_d, t_cylinder *cyl, t_data *data)
{
	t_vect	hitpoint;

	hitpoint = vector_add(ray_o, vector_scale(ray_d, cyl->inter.t1));
	if (check_cy(cyl, hitpoint))
	{
		if (data->no_shadows)
			fill_normal_t1(cyl->inter.t1, data, cyl, hitpoint);
		return (true);
	}
	return (false);
}

bool	t2_routine(t_vect ray_o, t_vect ray_d, t_cylinder *cyl, t_data *data)
{
	t_vect	hitpoint;

	hitpoint = vector_add(ray_o, vector_scale(ray_d, cyl->inter.t1));
	if (check_cy(cyl, hitpoint))
	{
		if (data->no_shadows)
			fill_normal_t2(cyl->inter.t2, data, cyl, hitpoint);
		return (true);
	}
	return (false);
}
