/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_disks.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:43:08 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/07 17:57:26 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_cylinder_disk_top_hit(t_cylinder *cyl, t_vect ray_o,
	t_vect ray_d, double *t)
{
	double	dot_product_nd;
	t_vect	pos_top;
	t_vect	oc;
	t_vect	hit_point;
	double	distance;

	dot_product_nd = vector_dot_product(cyl->norm_vect, ray_d);
	pos_top = move_point_along_normal(cyl->pos,
			cyl->norm_vect, cyl->height / 2);
	if (fabs(dot_product_nd) > EPSILON)
	{
		oc = vector_subtract(pos_top, ray_o);
		*t = vector_dot_product(oc, cyl->norm_vect) / dot_product_nd;
		if (*t > 0)
		{
			hit_point = vector_add(ray_o, vector_scale(ray_d, *t));
			distance = vector_length(vector_subtract(hit_point, pos_top));
			if (distance <= cyl->diameter / 2)
				return (true);
		}
	}
	return (false);
}

bool	is_cylinder_disk_bottom_hit(t_cylinder *cyl, t_vect ray_o,
	t_vect ray_d, double *t)
{
	double	dot_product_nd;
	t_vect	pos_bottom;
	t_vect	oc;
	t_vect	hit_point;
	double	distance;

	dot_product_nd = vector_dot_product(cyl->norm_vect, ray_d);
	pos_bottom = move_point_along_normal(
			cyl->pos, cyl->norm_vect, -cyl->height / 2);
	dot_product_nd = vector_dot_product(cyl->norm_vect, ray_d);
	if (fabs(dot_product_nd) > EPSILON)
	{
		oc = vector_subtract(pos_bottom, ray_o);
		*t = vector_dot_product(oc, cyl->norm_vect) / dot_product_nd;
		if (*t > 0)
		{
			hit_point = vector_add(ray_o, vector_scale(ray_d, *t));
			distance = vector_length(vector_subtract(hit_point, pos_bottom));
			if (distance <= cyl->diameter / 2)
				return (true);
		}
	}
	return (false);
}
