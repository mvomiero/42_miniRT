/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:15:06 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/30 18:02:13 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool is_cylinder_hit(t_cylinder *cylinder, t_vect ray_origin, t_vect ray_direction, double *t)
{
	// Calculate the direction vector of the cylinder's axis
	t_vect axisDirection = cylinder->norm_vect;

	// Calculate the vector from the ray origin to the cylinder's position
	t_vect oc = vector_substract(ray_origin, cylinder->pos);

	// Calculate the dot products needed for the quadratic equation
	double a = vector_dot_product(ray_direction, ray_direction) - pow(vector_dot_product(ray_direction, axisDirection), 2);
	double b = 2 * (vector_dot_product(ray_direction, oc) - vector_dot_product(ray_direction, axisDirection) * vector_dot_product(oc, axisDirection));
	double c = vector_dot_product(oc, oc) - pow(vector_dot_product(oc, axisDirection), 2) - pow(cylinder->diameter / 2, 2);

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
		if (t1 > 0)
		{
			// Calculate the y-coordinate of the intersection point
			double y = ray_origin.y + t1 * ray_direction.y;

			// Check if the intersection point is within the height of the cylinder
			if (y >= cylinder->pos.y && y <= cylinder->pos.y + cylinder->height)
			{
				*t = t1;
				return true;
			}
		}
		(void)t2;
		// if (t2 > 0)
		// {
		// 	// Calculate the y-coordinate of the intersection point
		// 	double y = ray_origin.y + t2 * ray_direction.y;

		// 	// Check if the intersection point is within the height of the cylinder
		// 	if (y >= cylinder->pos.y && y <= cylinder->pos.y + cylinder->height)
		// 	{
		// 		*t = t2;
		// 		return true;
		// 	}
		// }
	}
	return false;
}

void hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect ray_origin, t_vect ray_direction)
{
	double t;

	while (cylinders)
	{
		if (is_cylinder_hit(cylinders, ray_origin, ray_direction, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = cylinders->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			data->pix.normal = vector_normalize(vector_substract(data->pix.hitpoint, vector_add(cylinders->pos, vector_scale(cylinders->norm_vect, vector_dot_product(vector_substract(data->pix.hitpoint, cylinders->pos), cylinders->norm_vect)))));
		}
		cylinders = cylinders->next;
	}
}
