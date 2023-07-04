/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:49:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/04 10:59:04 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool is_plane_hit(t_plane *plane, t_vect ray_origin, t_vect ray_direction, double *t)
{
	double dot_product_nd;

	dot_product_nd = vector_dot_product(plane->norm_vect, ray_direction);
	// Check if the ray is not parallel to the plane (dot_product_nd is close to zero)
	if (fabs(dot_product_nd) > EPSILON)
	{
		t_vect oc = vector_substract(plane->pos, ray_origin);
		*t = vector_dot_product(oc, plane->norm_vect) / dot_product_nd;
		if (*t > 0)
			return true;
	}
	return false;
}

void hit_plane(t_data *data, t_plane *planes, t_vect ray_origin, t_vect ray_direction)
{
	double t;
	while (planes)
	{
		if (is_plane_hit(planes, ray_origin, ray_direction, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = planes->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			data->pix.normal = planes->norm_vect;
		}
		planes = planes->next;
	}
}


double vector_magnitude(t_vect vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}


bool is_cylinder_disk_hit(t_cylinder* cylinder, t_vect ray_origin, t_vect ray_direction, double* t)
{
    double dot_product_nd = vector_dot_product(cylinder->norm_vect, ray_direction);
    
    // Check if the ray is not parallel to the cylinder (dot_product_nd is close to zero)
    if (fabs(dot_product_nd) > EPSILON)
    {
        t_vect oc = vector_substract(cylinder->pos, ray_origin);
        *t = vector_dot_product(oc, cylinder->norm_vect) / dot_product_nd;
        
        if (*t > 0)
        {
            t_vect hit_point = vector_add(ray_origin, vector_scale(ray_direction, *t));
            double distance = vector_magnitude(vector_substract(hit_point, cylinder->pos));
            
            if (distance <= cylinder->diameter / 2)
                return true;
        }
    }
    
    return false;
}

void hit_disk_cylinder(t_data* data, t_cylinder* cylinders, t_vect ray_origin, t_vect ray_direction)
{
    double t;
    
    while (cylinders)
    {
        if (is_cylinder_disk_hit(cylinders, ray_origin, ray_direction, &t) && t < data->pix.t)
        {
            data->pix.t = t;
            data->pix.color = cylinders->color;
            data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
            data->pix.normal = cylinders->norm_vect;
        }
        
        cylinders = cylinders->next;
    }
}

