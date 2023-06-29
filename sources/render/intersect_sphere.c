/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:15:23 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/29 14:53:02 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#define EPSILON 1e-6
#define MAX_DISTANCE 200

double dotProduct(t_vect vector1, t_vect vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

t_vect normalize(t_vect v)
{
    double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    t_vect normalized = {v.x / magnitude, v.y / magnitude, v.z / magnitude};
    return normalized;
}


bool hit_plane(t_plane *plane, t_vect rayOrigin, t_vect rayDirection)
{
    t_vect oc = {rayOrigin.x - plane->pos.x, rayOrigin.y - plane->pos.y, rayOrigin.z - plane->pos.z };
    t_vect normRayDir = normalize(rayDirection);
    t_vect normPlaneNorm = normalize(plane->norm_vect);

    double denominator = dotProduct(normPlaneNorm, normRayDir);

    // Check if the ray is parallel or almost parallel to the plane
    if (denominator < EPSILON)
        return true;

    // Calculate the parameter t at which the ray intersects the plane
    double t = dotProduct(oc, normPlaneNorm) / denominator;
    if (t < 0)
        printf("plane\n");
    return !(t >= 0);
}


// hit_sphere(data->spheres->pos, data->spheres->diameter / 2.0, data->camera->pos, rayDirection);


void hit_sphere(t_data *data, t_sphere *spheres, t_vect rayOrigin, t_vect rayDirection)
{
	while (spheres)
	{
		double radius = spheres->diameter/2;
		t_vect oc = {rayOrigin.x - spheres->pos.x, rayOrigin.y - spheres->pos.y, rayOrigin.z - spheres->pos.z};

		double a = dotProduct(rayDirection, rayDirection);
		double b = 2.0 * dotProduct(oc, rayDirection);
		double c = dotProduct(oc, oc) - radius * radius;
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
