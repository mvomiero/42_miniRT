/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:49:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/05 18:39:01 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_plane_hit(t_plane *plane, t_vect ray_org, t_vect ray_dir, double *t)
{
	double	dot_product_nd;
	t_vect	oc;

	dot_product_nd = vector_dot_product(plane->norm_vect, ray_dir);
	if (fabs(dot_product_nd) > EPSILON)
	{
		oc = vector_sub(plane->pos, ray_org);
		*t = vector_dot_product(oc, plane->norm_vect) / dot_product_nd;
		if (*t > 0)
			return (true);
	}
	return (false);
}

void	hit_plane(t_data *data, t_plane *planes, t_vect ray_org, t_vect ray_dir)
{
	double	t;

	while (planes)
	{
		if (is_plane_hit(planes, ray_org, ray_dir, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = planes->color;
			data->pix.hitpoint = vector_add(ray_org, vector_scale(ray_dir, t));
			data->pix.normal = planes->norm_vect;
		}
		planes = planes->next;
	}
}
