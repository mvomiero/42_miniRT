/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:30:44 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/06 11:25:29 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool is_triangle_hit(t_triangle *triangle, t_vect ray_origin, t_vect ray_direction, double *t)
{
	t_vect edge1, edge2, h, s, q;
	double a, f, u, v;

	edge1 = vector_subtract(triangle->v2, triangle->v1);
	edge2 = vector_subtract(triangle->v3, triangle->v1);

	h = vector_cross_product(ray_direction, edge2);
	a = vector_dot_product(edge1, h);

	if (fabs(a) < EPSILON)
		return false;

	f = 1.0 / a;
	s = vector_subtract(ray_origin, triangle->v1);
	u = f * vector_dot_product(s, h);

	if (u < 0.0 || u > 1.0)
		return false;

	q = vector_cross_product(s, edge1);
	v = f * vector_dot_product(ray_direction, q);

	if (v < 0.0 || u + v > 1.0)
		return false;

	*t = f * vector_dot_product(edge2, q);

	if (*t > 0.0)
		return true;

	return false;
}

void hit_triangle(t_data *data, t_triangle *triangles, t_vect ray_origin, t_vect ray_direction)
{
	double t;
	while (triangles)
	{
		if (is_triangle_hit(triangles, ray_origin, ray_direction, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = triangles->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			//data->pix.normal = vector_cross_product(vector_subtract(triangles->v2, triangles->v1), vector_subtract(triangles->v3, triangles->v1));
			/*t_vect edge1 = vector_subtract(triangles->v2, triangles->v1);
			t_vect edge2 = vector_subtract(triangles->v3, triangles->v1);
			data->pix.normal = vector_normalize(vector_cross_product(edge1, edge2));*/
			data->pix.normal = triangles->norm_vect;

		}
		triangles = triangles->next;
	}
}
