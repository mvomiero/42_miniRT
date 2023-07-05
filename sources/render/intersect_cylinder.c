/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:15:06 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/05 18:39:01 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int check_cy(t_cylinder *cy, t_vect hpnt)
{
	t_vect pmax;
	t_vect pmin;
	double capmin;
	double capmax;

	pmin = vector_add(cy->pos, vector_scale(cy->norm_vect, -0.5 * cy->height));
	pmax = vector_add(cy->pos, vector_scale(cy->norm_vect, 0.5 * cy->height));

	t_vect hpnt_pmin = vector_sub(hpnt, pmin);
	t_vect hpnt_pmax = vector_sub(hpnt, pmax);

	capmin = vector_dot_product(hpnt_pmin, hpnt_pmin);
	capmax = vector_dot_product(hpnt_pmax, hpnt_pmax);

	if (vector_dot_product(cy->norm_vect, hpnt_pmin) > 0 && vector_dot_product(cy->norm_vect, hpnt_pmax) < 0)
		return 1;

	if (capmin < pow(cy->diameter / 2, 2) || capmax < pow(cy->diameter / 2, 2))
		return 1;

	return 0;
}

bool is_cylinder_hit(t_cylinder *cylinder, t_vect ray_origin, t_vect ray_direction, double *t, t_data *data)
{
	// Calculate the direction vector of the cylinder's axis
	t_vect axisDirection = cylinder->norm_vect;

	// Calculate the vector from the ray origin to the cylinder's position
	t_vect oc = vector_sub(ray_origin, cylinder->pos);

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
		if (t1 > 0 && t1 < t2)
		{
			// Calculate the y-coordinate of the intersection point
			t_vect hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t1));

			// Check if the intersection point is within the height of the cylinder
			if (check_cy(cylinder, hitpoint))
			{
				*t = t1;
				if (data)
				{
					if (t1 < data->pix.t)
						data->pix.normal = vector_normalize(vector_sub(hitpoint, vector_add(cylinder->pos, vector_scale(axisDirection, vector_dot_product(vector_sub(hitpoint, cylinder->pos), axisDirection)))));
				}

				return true;
			}
		}
		if (t2 > 0 && t2 < t1)
		{
			// Calculate the y-coordinate of the intersection point
			t_vect hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t1));

			// Check if the intersection point is within the height of the cylinder
			if (check_cy(cylinder, hitpoint))
			{
				*t = t2;
				if (data)
				{
					if (t2 < data->pix.t)
						data->pix.normal = vector_normalize(vector_sub(hitpoint, vector_add(cylinder->pos, vector_scale(axisDirection, t2))));
				}
				return true;
			}
		}
		//(void)t2;
	}
	return false;
}

void hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect ray_origin, t_vect ray_direction)
{
	double t;

	while (cylinders)
	{
		if (is_cylinder_hit(cylinders, ray_origin, ray_direction, &t, data) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = cylinders->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			// data->pix.normal = vector_normalize(vector_sub(data->pix.hitpoint, vector_add(cylinders->pos, vector_scale(cylinders->norm_vect, vector_dot_product(vector_sub(data->pix.hitpoint, cylinders->pos), cylinders->norm_vect)))));
		}
		if (is_cylinder_disk_top_hit(cylinders, ray_origin, ray_direction, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = cylinders->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			data->pix.normal = cylinders->norm_vect;
		}
		if (is_cylinder_disk_bottom_hit(cylinders, ray_origin, ray_direction, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = cylinders->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			data->pix.normal = get_opposite_normal(cylinders->norm_vect);
		}
		cylinders = cylinders->next;
	}
}

/* OLDER VERSIONS --- TO DELETE */

/*void hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect rayOrigin, t_vect rayDirection)
{
	while (cylinders)
	{
		// Calculate the direction vector of the cylinder's axis
		t_vect axisDirection = cylinders->norm_vect;

		// Calculate the vector from the ray origin to the cylinder's position
		t_vect oc = {rayOrigin.x - cylinders->pos.x, rayOrigin.y - cylinders->pos.y, rayOrigin.z - cylinders->pos.z};

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
					data->pix.normal = vector_normalize(vector_sub(data->pix.hitpoint, vector_add(cylinders->pos, vector_scale(axisDirection, vector_dot_product(vector_sub(data->pix.hitpoint, cylinders->pos), axisDirection)))));
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
					data->pix.normal = vector_normalize(vector_sub(data->pix.hitpoint, vector_add(cylinders->pos, vector_scale(axisDirection, t2))));
					// Fill other values of pix
				}
			}
		}
		cylinders = cylinders->next;
	}
}*/
