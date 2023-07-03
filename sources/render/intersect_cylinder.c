/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:15:06 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 19:18:32 by lde-ross         ###   ########.fr       */
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

	t_vect hpnt_pmin = vector_substract(hpnt, pmin);
	t_vect hpnt_pmax = vector_substract(hpnt, pmax);

	capmin = vector_dot_product(hpnt_pmin, hpnt_pmin);
	capmax = vector_dot_product(hpnt_pmax, hpnt_pmax);

	if (vector_dot_product(cy->norm_vect, hpnt_pmin) > 0 && vector_dot_product(cy->norm_vect, hpnt_pmax) < 0)
		return 1;

	if (capmin < pow(cy->diameter / 2, 2) || capmax < pow(cy->diameter / 2, 2))
		return 1;

	return 0;
}

double vector_distance(t_vect v1, t_vect v2)
{
    double dx = v2.x - v1.x;
    double dy = v2.y - v1.y;
    double dz = v2.z - v1.z;
    
    return sqrt(dx * dx + dy * dy + dz * dz);
}


void hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect rayOrigin, t_vect rayDirection)
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
					data->pix.normal = vector_normalize(vector_substract(data->pix.hitpoint, vector_add(cylinders->pos, vector_scale(axisDirection, vector_dot_product(vector_substract(data->pix.hitpoint, cylinders->pos), axisDirection)))));
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
					data->pix.normal = vector_normalize(vector_substract(data->pix.hitpoint, vector_add(cylinders->pos, vector_scale(axisDirection, t2))));
					// Fill other values of pix
				}
			}
		}

		 t_vect center_bottom_disk = {
            cylinders->pos.x + (cylinders->norm_vect.x * (-cylinders->height / 2.0)),
            cylinders->pos.y + (cylinders->norm_vect.y * (-cylinders->height / 2.0)),
            cylinders->pos.z + (cylinders->norm_vect.z * (-cylinders->height / 2.0))
        };

        // Calculate the normal of the bottom disk
        t_vect normal_bottom_disk = cylinders->norm_vect;

        // Calculate the distance between the ray origin and the center of the bottom disk
        t_vect ray_to_center = {center_bottom_disk.x - rayOrigin.x, center_bottom_disk.y - rayOrigin.y, center_bottom_disk.z - rayOrigin.z};
        double t_bottom = (ray_to_center.x * rayDirection.x + ray_to_center.y * rayDirection.y + ray_to_center.z * rayDirection.z) / (rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z);
        t_vect intersection_point_bottom = {rayOrigin.x + t_bottom * rayDirection.x, rayOrigin.y + t_bottom * rayDirection.y, rayOrigin.z + t_bottom * rayDirection.z};
        double distance_bottom = vector_distance(intersection_point_bottom, center_bottom_disk);

        if (distance_bottom <= cylinders->diameter / 2.0 && t_bottom < data->pix.t) 
        {
            // The ray intersects the bottom disk
            data->pix.t = distance_bottom;
            data->pix.color = cylinders->color;
            data->pix.hitpoint = intersection_point_bottom;
            data->pix.normal = vector_normalize(normal_bottom_disk);
            // Fill other values of pix
        }

		// Calculate the center of the top disk
        t_vect center_top_disk = {
            cylinders->pos.x + (cylinders->norm_vect.x * (cylinders->height / 2.0)),
            cylinders->pos.y + (cylinders->norm_vect.y * (cylinders->height / 2.0)),
            cylinders->pos.z + (cylinders->norm_vect.z * (cylinders->height / 2.0))
        };

		// Calculate the normal of the top disk
        t_vect normal_top_disk = {
            cylinders->norm_vect.x * -1,
            cylinders->norm_vect.y * -1,
            cylinders->norm_vect.z * -1
        };

        // Calculate the distance between the ray origin and the center of the top disk
        t_vect ray_to_center_top = {center_top_disk.x - rayOrigin.x, center_top_disk.y - rayOrigin.y, center_top_disk.z - rayOrigin.z};
        double t_top = (ray_to_center_top.x * rayDirection.x + ray_to_center_top.y * rayDirection.y + ray_to_center_top.z * rayDirection.z) / (rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y + rayDirection.z * rayDirection.z);
        t_vect intersection_point_top = {rayOrigin.x + t_top * rayDirection.x, rayOrigin.y + t_top * rayDirection.y, rayOrigin.z + t_top * rayDirection.z};
        double distance_top = vector_distance(intersection_point_top, center_top_disk);

        if (distance_top <= cylinders->diameter / 2.0 && t_top < data->pix.t) 
        {
            // The ray intersects the top disk
            data->pix.t = distance_top;
            data->pix.color = cylinders->color;
            data->pix.hitpoint = intersection_point_top;
            data->pix.normal = vector_normalize(normal_top_disk);
            // Fill other values of pix
        }

		cylinders = cylinders->next;
	}
}





bool is_cylinder_hit(t_cylinder *cylinder, t_vect ray_origin, t_vect ray_direction, double *t, t_vect *normal)
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
		if (t1 > 0 && t1 < t2)
		{
			// Calculate the y-coordinate of the intersection point
			t_vect hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t1));

				// Check if the intersection point is within the height of the cylinder
			if (check_cy(cylinder, hitpoint))
			{
				*t = t1;
				if (normal)
					*normal = vector_normalize(vector_substract(hitpoint, vector_add(cylinder->pos, vector_scale(axisDirection, vector_dot_product(vector_substract(hitpoint, cylinder->pos), axisDirection)))));

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
				if (normal)
					*normal = vector_normalize(vector_substract(hitpoint, vector_add(cylinder->pos, vector_scale(axisDirection, t2))));
				return true;
			}
		}
		//(void)t2;
	}
	return false;
}
