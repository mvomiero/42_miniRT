/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:49:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/04 13:27:00 by mvomiero         ###   ########.fr       */
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

/*t_vect move_point_along_normal(t_vect point, t_vect normal, double distance)
{
    // Normalize the normal vector (if it's not already normalized)
    double magnitude = vector_magnitude(normal);
    t_vect normalized_normal = {
        .x = normal.x / magnitude,
        .y = normal.y / magnitude,
        .z = normal.z / magnitude
    };
    
    // Calculate the displacement vector
    t_vect displacement = {
        .x = normalized_normal.x * distance,
        .y = normalized_normal.y * distance,
        .z = normalized_normal.z * distance
    };
    
    // Move the point along the normal direction
    t_vect moved_point = {
        .x = point.x + displacement.x,
        .y = point.y + displacement.y,
        .z = point.z + displacement.z
    };
    
    return moved_point;
}*/

t_vect move_point_along_normal(t_vect point, t_vect normal, double distance)
{
    // Normalize the normal vector (if it's not already normalized)
    t_vect normalized_normal = vector_normalize(normal);

    // Calculate the displacement vector in the opposite direction
    t_vect displacement = vector_scale(normalized_normal, -distance);

    // Move the point along the normal direction
    t_vect moved_point = vector_add(point, displacement);

    return moved_point;
}


/*t_vect get_opposite_normal(t_vect normal)
{
    t_vect opposite_normal = {
        .x = -normal.x,
        .y = -normal.y,
        .z = -normal.z
    };
    
    return opposite_normal;
}*/

t_vect get_opposite_normal(t_vect normal)
{
    double magnitude = vector_length(normal);
    t_vect opposite_normal = vector_scale(normal, -magnitude);

    return opposite_normal;
}



/*int is_cylinder_disk_hit(t_data *data, t_cylinder* cylinder, t_vect ray_origin, t_vect ray_direction, double* t)
{
    double dot_product_nd = vector_dot_product(cylinder->norm_vect, ray_direction);
    
	(void)data;

	t_vect pos_top = move_point_along_normal(cylinder->pos, cylinder->norm_vect, cylinder->height/2);
    // Check if the ray is not parallel to the cylinder (dot_product_nd is close to zero)
    if (fabs(dot_product_nd) > EPSILON)
    {
        t_vect oc = vector_substract(pos_top, ray_origin);
        *t = vector_dot_product(oc, cylinder->norm_vect) / dot_product_nd;
        
        if (*t > 0)
        {
            t_vect hit_point = vector_add(ray_origin, vector_scale(ray_direction, *t));
            double distance = vector_magnitude(vector_substract(hit_point, pos_top));
            
            if (distance <= cylinder->diameter / 2)
			{
				//data->pix.normal = data->cylinders->norm_vect;
                return 1;
			}
        }
    }

	
	t_vect	normal_bottom = get_opposite_normal(cylinder->norm_vect);
	t_vect pos_bottom = move_point_along_normal(cylinder->pos, normal_bottom, cylinder->height/2);
	dot_product_nd = vector_dot_product(normal_bottom, ray_direction);
    if (fabs(dot_product_nd) > EPSILON)
    {
        t_vect oc = vector_substract(pos_bottom, ray_origin);
        *t = vector_dot_product(oc, normal_bottom) / dot_product_nd;
        
        if (*t > 0)
        {
            t_vect hit_point = vector_add(ray_origin, vector_scale(ray_direction, *t));
            double distance = vector_magnitude(vector_substract(hit_point, pos_bottom));
            
            if (distance <= cylinder->diameter / 2)
			{
				//data->pix.normal = normal_bottom;
                return 2;
			}
        }
    }

	
	
    return false;
}*/

bool is_cylinder_disk_top_hit(t_cylinder* cylinder, t_vect ray_origin, t_vect ray_direction, double* t)
{
	double dot_product_nd = vector_dot_product(cylinder->norm_vect, ray_direction);

    t_vect pos_top = move_point_along_normal(cylinder->pos, cylinder->norm_vect, cylinder->height / 2);
    // Check if the ray is not parallel to the top disk (dot_product_nd is close to zero)
    if (fabs(dot_product_nd) > EPSILON)
    {
        t_vect oc = vector_substract(pos_top, ray_origin);
        *t = vector_dot_product(oc, cylinder->norm_vect) / dot_product_nd;

        if (*t > 0)
        {
            t_vect hit_point = vector_add(ray_origin, vector_scale(ray_direction, *t));
            double distance = vector_magnitude(vector_substract(hit_point, pos_top));

            if (distance <= cylinder->diameter / 2)
				return (true);
        }
    }
	return (false);
}

bool is_cylinder_disk_bottom_hit(t_cylinder* cylinder, t_vect ray_origin, t_vect ray_direction, double* t)
{
	double dot_product_nd = vector_dot_product(cylinder->norm_vect, ray_direction);

    // Calculate the position of the bottom disk
    t_vect pos_bottom = move_point_along_normal(cylinder->pos, cylinder->norm_vect, -cylinder->height / 2);
    dot_product_nd = vector_dot_product(cylinder->norm_vect, ray_direction);
    if (fabs(dot_product_nd) > EPSILON)
    {
        t_vect oc = vector_substract(pos_bottom, ray_origin);
        *t = vector_dot_product(oc, cylinder->norm_vect) / dot_product_nd;

        if (*t > 0)
        {
            t_vect hit_point = vector_add(ray_origin, vector_scale(ray_direction, *t));
            double distance = vector_magnitude(vector_substract(hit_point, pos_bottom));

            if (distance <= cylinder->diameter / 2)
				return (true);
        }
    }

    // No intersection with either disk
    return false;
}

int is_cylinder_disk_hit(t_data *data, t_cylinder* cylinder, t_vect ray_origin, t_vect ray_direction, double* t)
{
    double dot_product_nd = vector_dot_product(cylinder->norm_vect, ray_direction);

    (void)data;

    t_vect pos_top = move_point_along_normal(cylinder->pos, cylinder->norm_vect, cylinder->height / 2);
    // Check if the ray is not parallel to the top disk (dot_product_nd is close to zero)
    if (fabs(dot_product_nd) > EPSILON)
    {
        t_vect oc = vector_substract(pos_top, ray_origin);
        *t = vector_dot_product(oc, cylinder->norm_vect) / dot_product_nd;

        if (*t > 0)
        {
            t_vect hit_point = vector_add(ray_origin, vector_scale(ray_direction, *t));
            double distance = vector_magnitude(vector_substract(hit_point, pos_top));

            if (distance <= cylinder->diameter / 2)
            {
                // Top disk is hit, return immediately
                return 1;
            }
        }
    }

    // Calculate the position of the bottom disk
    t_vect pos_bottom = move_point_along_normal(cylinder->pos, cylinder->norm_vect, -cylinder->height / 2);
    dot_product_nd = vector_dot_product(cylinder->norm_vect, ray_direction);
    if (fabs(dot_product_nd) > EPSILON)
    {
        t_vect oc = vector_substract(pos_bottom, ray_origin);
        *t = vector_dot_product(oc, cylinder->norm_vect) / dot_product_nd;

        if (*t > 0)
        {
            t_vect hit_point = vector_add(ray_origin, vector_scale(ray_direction, *t));
            double distance = vector_magnitude(vector_substract(hit_point, pos_bottom));

            if (distance <= cylinder->diameter / 2)
            {
                // Bottom disk is hit, return immediately
                return 2;
            }
        }
    }

    // No intersection with either disk
    return false;
}



void hit_disk_cylinder(t_data* data, t_cylinder* cylinders, t_vect ray_origin, t_vect ray_direction)
{
    double t;
    
    while (cylinders)
    {
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



