/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:15:06 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 12:20:54 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#include <math.h>

bool intersectPlane(const t_vect *n, const t_vect *p0, const t_vect *l0, const t_vect *l, double *t)
{
    double denom = vectorDotProduct(*n, *l);

    if (fabs(denom) < EPSILON)
        return false;

    *t = vectorDotProduct(*n, vectorSubtraction(*p0, *l0)) / denom;

    if (*t >= 0)
        return true;

    return false;
}

bool intersectDisk(const t_vect *n, const t_vect *p0, const double *radius, const t_vect *l0, const t_vect *l)
{
    double t = 0;
    if (intersectPlane(n, p0, l0, l, &t)) {
        t_vect p = vectorAdd(*l0, vectorScale(*l, t));
        t_vect v = vectorSubtraction(p, *p0);
        double d2 = vectorDotProduct(v, v);
        return (sqrt(d2) <= *radius);
    }

    return false;
}



int check_cy(t_cylinder *cy, t_vect hpnt)
{
    t_vect pmin = vectorAdd(cy->pos, vectorScale(cy->norm_vect, -0.5 * cy->height));
    t_vect pmax = vectorAdd(cy->pos, vectorScale(cy->norm_vect, 0.5 * cy->height));

    if (vectorDotProduct(cy->norm_vect, vectorSubtraction(hpnt, pmin)) > 0 && vectorDotProduct(cy->norm_vect, vectorSubtraction(hpnt, pmax)) < 0)
        return 1;

    double radius2 = cy->diameter / 2 * cy->diameter / 2;

    t_vect disk_center = vectorAdd(cy->pos, vectorScale(cy->norm_vect, -0.5 * cy->height));
    t_vect scaled_norm_vect = vectorScale(cy->norm_vect, -1.0);
    if (intersectDisk(&cy->norm_vect, &disk_center, &radius2, &hpnt, &scaled_norm_vect))
        return 1;

    disk_center = vectorAdd(cy->pos, vectorScale(cy->norm_vect, 0.5 * cy->height));
    if (intersectDisk(&cy->norm_vect, &disk_center, &radius2, &hpnt, &cy->norm_vect))
        return 1;

    return 0;
}








/*int check_cy(t_cylinder *cy, t_vect hpnt)
{
	t_vect pmax;
	t_vect pmin;
	double capmin;
	double capmax;

	pmin = vectorAdd(cy->pos, vectorScale(cy->norm_vect, -0.5 * cy->height));
	pmax = vectorAdd(cy->pos, vectorScale(cy->norm_vect, 0.5 * cy->height));

	t_vect hpnt_pmin = vectorSubtraction(hpnt, pmin);
	t_vect hpnt_pmax = vectorSubtraction(hpnt, pmax);

	capmin = vectorDotProduct(hpnt_pmin, hpnt_pmin);
	capmax = vectorDotProduct(hpnt_pmax, hpnt_pmax);

	if (vectorDotProduct(cy->norm_vect, hpnt_pmin) > 0 && vectorDotProduct(cy->norm_vect, hpnt_pmax) < 0)
		return 1;

	if (capmin < pow(cy->diameter / 2, 2) || capmax < pow(cy->diameter / 2, 2))
		return 1;

	return 0;
}*/

void hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect rayOrigin, t_vect rayDirection)
{
	while (cylinders)
	{
		// Calculate the direction vector of the cylinder's axis
		t_vect axisDirection = cylinders->norm_vect;

		// Calculate the vector from the ray origin to the cylinder's position
		t_vect oc = {rayOrigin.x - cylinders->pos.x, rayOrigin.y - cylinders->pos.y, rayOrigin.z - cylinders->pos.z};

		// Calculate the dot products needed for the quadratic equation
		double a = vectorDotProduct(rayDirection, rayDirection) - pow(vectorDotProduct(rayDirection, axisDirection), 2);
		double b = 2 * (vectorDotProduct(rayDirection, oc) - vectorDotProduct(rayDirection, axisDirection) * vectorDotProduct(oc, axisDirection));
		double c = vectorDotProduct(oc, oc) - pow(vectorDotProduct(oc, axisDirection), 2) - pow(cylinders->diameter / 2, 2);

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
				t_vect hitpoint = vectorAdd(rayOrigin, vectorScale(rayDirection, t1));

				// Check if the intersection point is within the height of the cylinder
				if (check_cy(cylinders, hitpoint))
				{
					data->pix.t = t1;
					data->pix.color = cylinders->color;
					data->pix.hitpoint = hitpoint;
					data->pix.normal = vectorNormalize(vectorSubtraction(data->pix.hitpoint, vectorAdd(cylinders->pos, vectorScale(axisDirection, vectorDotProduct(vectorSubtraction(data->pix.hitpoint, cylinders->pos), axisDirection)))));
					// Fill other values of pix
				}
			}

			if (t2 > 0 && t2 < data->pix.t)
			{
				// Calculate the intersection point
				t_vect hitpoint = vectorAdd(rayOrigin, vectorScale(rayDirection, t2));

				// Check if the intersection point is within the height of the cylinder
				if (check_cy(cylinders, hitpoint))
				{
					data->pix.t = t2;
					data->pix.color = cylinders->color;
					data->pix.hitpoint = hitpoint;
					data->pix.normal = vectorNormalize(vectorSubtraction(data->pix.hitpoint, vectorAdd(cylinders->pos, vectorScale(axisDirection, t2))));
					// Fill other values of pix
				}
			}
		}

		cylinders = cylinders->next;
	}
}


/*void hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect rayOrigin, t_vect rayDirection)
{
	while (cylinders)
	{
		// Calculate the direction vector of the cylinder's axis
		t_vect axisDirection = cylinders->norm_vect;

		// Calculate the vector from the ray origin to the cylinder's position
		t_vect oc = {rayOrigin.x - cylinders->pos.x, rayOrigin.y - cylinders->pos.y, rayOrigin.z - cylinders->pos.z};

		// Calculate the dot products needed for the quadratic equation
		double a = vectorDotProduct(rayDirection, rayDirection) - pow(vectorDotProduct(rayDirection, axisDirection), 2);
		double b = 2 * (vectorDotProduct(rayDirection, oc) - vectorDotProduct(rayDirection, axisDirection) * vectorDotProduct(oc, axisDirection));
		double c = vectorDotProduct(oc, oc) - pow(vectorDotProduct(oc, axisDirection), 2) - pow(cylinders->diameter / 2, 2);

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
				// Calculate the y-coordinate of the intersection point
				//double y = rayOrigin.y + t1 * rayDirection.y;
				
				// Calculate the intersection point
				t_vect hitpoint = vectorAdd(rayOrigin, vectorScale(rayDirection, t1));

				// Calculate the y-coordinate of the intersection point
				double y = hitpoint.y;

				// Check if the intersection point is within the height of the cylinder
				if (y >= cylinders->pos.y && y <= cylinders->pos.y + cylinders->height)
				{
					data->pix.t = t1;
					data->pix.color = cylinders->color;
					data->pix.hitpoint = vectorAdd(rayOrigin, vectorScale(rayDirection, t1));
					data->pix.normal = vectorNormalize(vectorSubtraction(data->pix.hitpoint, vectorAdd(cylinders->pos, vectorScale(axisDirection, vectorDotProduct(vectorSubtraction(data->pix.hitpoint, cylinders->pos), axisDirection)))));
				}
					// Fill other values of pix
			}

			if (t2 > 0 && t2 < data->pix.t)
			{
				// Calculate the intersection point
				t_vect hitpoint = vectorAdd(rayOrigin, vectorScale(rayDirection, t2));

				// Calculate the y-coordinate of the intersection point
				double y = hitpoint.y;

				// Check if the intersection point is within the height of the cylinder
				if (y >= cylinders->pos.y && y <= cylinders->pos.y + cylinders->height)
				{
					data->pix.t = t2;
					data->pix.color = cylinders->color;
					data->pix.hitpoint = vectorAdd(rayOrigin, vectorScale(rayDirection, t2));
					data->pix.normal = (vectorSubtraction(data->pix.hitpoint, vectorAdd(cylinders->pos, vectorScale(axisDirection, t2))));
					// Fill other values of pix
				}
			}
		}

		cylinders = cylinders->next;
	}
}*/
