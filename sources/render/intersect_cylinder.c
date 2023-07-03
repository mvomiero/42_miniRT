/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:15:06 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 15:09:26 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect rayOrigin, t_vect rayDirection)
{
	while (cylinders)
	{
		// Calculate the direction vector of the cylinder's axis
		t_vect axisDirection = cylinders->norm_vect;

	// Calculate the vector from the ray origin to the cylinder's position
	t_vect oc = vector_substract(ray_origin, cylinder->pos);

		// Calculate the dot products needed for the quadratic equation
		double a = vector_dot_product(rayDirection, rayDirection) - pow(vector_dot_product(rayDirection, axisDirection), 2);
		double b = 2 * (vector_dot_product(rayDirection, oc) - vector_dot_product(rayDirection, axisDirection) * vector_dot_product(oc, axisDirection));
		double c = vector_dot_product(oc, oc) - pow(vector_dot_product(oc, axisDirection), 2) - pow(cylinders->diameter / 2, 2);

	// Solve the quadratic equation to find the intersection points
	double discriminant = b * b - 4 * a * c;

	if (discriminant >= 0)
	{
		// Calculate the solutions
		// Quadratic equations always have two solutions, one with -sqrt and the other with +sqrt
		double t1 = (-b - sqrt(discriminant)) / (2 * a);
		double t2 = (-b + sqrt(discriminant)) / (2 * a);

			// Check if the solutions are within the valid range and closer than the current closest hit
			// > 0 means that they are not in the ray but behind the origin
			if (t1 > 0 && t1 < data->pix.t)
			{
				// Calculate the intersection point
				t_vect hitpoint = vector_add(rayOrigin, vector_scale(rayDirection, t1));

				// Check if the intersection point is within the height of the cylinder
				if (check_cy(cylinders, hitpoint))
				{
					data->pix.t = t1;
					data->pix.color = cylinders->color;
					data->pix.hitpoint = hitpoint;
					data->pix.normal = vector_normalize(vector_subtraction(data->pix.hitpoint, vector_add(cylinders->pos, vector_scale(axisDirection, vector_dot_product(vector_subtraction(data->pix.hitpoint, cylinders->pos), axisDirection)))));
					// Fill other values of pix
				}
			}

			if (t2 > 0 && t2 < data->pix.t)
			{
				// Calculate the intersection point
				t_vect hitpoint = vector_add(rayOrigin, vector_scale(rayDirection, t2));

				// Check if the intersection point is within the height of the cylinder
				if (check_cy(cylinders, hitpoint))
				{
					data->pix.t = t2;
					data->pix.color = cylinders->color;
					data->pix.hitpoint = hitpoint;
					data->pix.normal = vector_normalize(vector_subtraction(data->pix.hitpoint, vector_add(cylinders->pos, vector_scale(axisDirection, t2))));
					// Fill other values of pix
				}
			}
		}
		cylinders = cylinders->next;
	}
}

