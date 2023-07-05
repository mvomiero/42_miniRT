/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:49:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/05 16:20:17 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool is_plane_hit(t_plane *plane, t_vect ray_origin, t_vect ray_direction, double *t)
{
	double dot_product_nd;

	dot_product_nd = vector_dot_product(plane->norm_vect, ray_direction);
	// Check if the ray is not parallel to the plane (dot_product_nd is close to zero)
	if (fabs(dot_product_nd) > EPSILON)
	{
		t_vect oc = vector_substract(plane->pos, ray_origin);
		*t = vector_dot_product(oc, plane->norm_vect) / dot_product_nd;
		if (*t > 0)
			return true;
	}
	return false;
}

void hit_plane(t_data *data, t_plane *planes, t_vect ray_origin, t_vect ray_direction)
{
	double t;
	while (planes)
	{
		if (is_plane_hit(planes, ray_origin, ray_direction, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = planes->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			data->pix.normal = planes->norm_vect;
		}
		planes = planes->next;
	}
}

// void hit_plane(t_data *data, t_plane *planes, t_vect ray_origin, t_vect ray_direction)
// {
//     double t;
//     while (planes)
//     {
//         if (is_plane_hit(planes, ray_origin, ray_direction, &t))
//         {
//             // Apply offset to avoid self-intersection
//             t_vect offset_hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
//             t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(planes->norm_vect, EPSILON));

//             // Check if the offset ray still intersects with the plane
//             if (is_plane_hit(planes, offset_origin, ray_direction, &t) && t < data->pix.t)
//             {
//                 data->pix.t = t;
//                 data->pix.color = planes->color;
//                 data->pix.hitpoint = vector_add(offset_origin, vector_scale(ray_direction, t));
//                 data->pix.normal = planes->norm_vect;
//             }
//         }
//         planes = planes->next;
//     }
// }
