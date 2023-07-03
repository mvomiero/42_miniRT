/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:15:23 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 15:11:18 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#define EPSILON 1e-6
#define MAX_DISTANCE 200

bool is_sphere_hit(t_sphere *sphere, t_vect ray_origin, t_vect ray_direction, double *t)
{
	double radius = sphere->diameter / 2;
	t_vect oc = vector_substract(ray_origin, sphere->pos);

	double a = vector_dot_product(ray_direction, ray_direction);
	double b = 2.0 * vector_dot_product(oc, ray_direction);
	double c = vector_dot_product(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;

	if (discriminant >= 0)
	{
		// Calculate the solutions
		double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		// double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

			// Check if the solutions are within the valid range and closer than the current closest hit
			if (t1 > 0 && t1 < data->pix.t )
			{
				data->pix.t = t1;
				data->pix.color = spheres->color;
				data->pix.hitpoint = vectorAdd(rayOrigin, vectorScale(rayDirection, t1));
				data->pix.normal = vectorNormalize(vectorSubtraction(data->pix.hitpoint, spheres->pos));
				// fill other values of pix
			}
			// if (t2 > 0 && t2 < data->pix.t)
			// {
			// 	data->pix.t = t2;
			// 	data->pix.color = spheres->color;
			// }
		}
		spheres = spheres->next;
	}
}
