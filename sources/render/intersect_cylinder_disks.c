/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_disks.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:43:08 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/05 17:05:18 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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


/* OLDER VERSIONS --- TO BE DELETED */


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



/*int is_cylinder_disk_hit(t_data *data, t_cylinder* cylinder, t_vect ray_origin, t_vect ray_direction, double* t)
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
}*/