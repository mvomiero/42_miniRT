/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:15:23 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 13:09:46 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#define EPSILON 1e-6
#define MAX_DISTANCE 200





// hit_sphere(data->spheres->pos, data->spheres->diameter / 2.0, data->camera->pos, rayDirection);


void hit_sphere(t_data *data, t_sphere *spheres, t_vect rayOrigin, t_vect rayDirection)
{
	while (spheres)
	{
		double radius = spheres->diameter/2;
		t_vect oc = {rayOrigin.x - spheres->pos.x, rayOrigin.y - spheres->pos.y, rayOrigin.z - spheres->pos.z};

		double a = vector_dot_product(rayDirection, rayDirection);
		double b = 2.0 * vector_dot_product(oc, rayDirection);
		double c = vector_dot_product(oc, oc) - radius * radius;
		double discriminant = b * b - 4 * a * c;

		if (discriminant >= 0)
		{
			// Calculate the solutions
			double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
			//double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

			// Check if the solutions are within the valid range and closer than the current closest hit
			if (t1 > 0 && t1 < data->pix.t )
			{
				data->pix.t = t1;
				data->pix.color = spheres->color;
				data->pix.hitpoint = vector_add(rayOrigin, vector_scale(rayDirection, t1));
				data->pix.normal = vector_normalize(vectorSubtraction(data->pix.hitpoint, spheres->pos));
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

/*bool hit_sphere(t_vect center, double radius, t_vect rayOrigin, t_vect rayDirection)
{
	t_vect oc = {rayOrigin.x - center.x, rayOrigin.y - center.y, rayOrigin.z - center.z};

	double a = dotProduct(rayDirection, rayDirection);
	double b = 2.0 * dotProduct(oc, rayDirection);
	double c = dotProduct(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;

	return (discriminant > 0);
}*/
