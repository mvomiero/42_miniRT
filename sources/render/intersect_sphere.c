/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:15:23 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 15:12:58 by mvomiero         ###   ########.fr       */
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

		// Check if the solutions are within the valid range
		if (t1 > 0)
		{
			*t = t1;
			return true;
		}

		// if (t2 > 0)
		// {
		//     *t = t2;
		//     return true;
		// }
	}

	return false;
}

void hit_sphere(t_data *data, t_sphere *spheres, t_vect ray_origin, t_vect ray_direction)
{
	double t;

	while (spheres)
	{
		if (is_sphere_hit(spheres, ray_origin, ray_direction, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = spheres->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			data->pix.normal = vector_normalize(vector_substract(data->pix.hitpoint, spheres->pos));
		}

		spheres = spheres->next;
	}
}

