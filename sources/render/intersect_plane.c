/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:49:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/30 16:35:04 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"





void hit_plane(t_data *data, t_plane *planes, t_vect rayOrigin, t_vect rayDirection)
{
    while (planes)
    {
        double dotProductND = vector_dot_product(planes->norm_vect, rayDirection);
        
        // Check if the ray is not parallel to the plane (dotProductND is close to zero)
        if (fabs(dotProductND) > EPSILON)
        {
            t_vect oc = vector_substract(planes->pos, rayOrigin);
            double t = vector_dot_product(oc, planes->norm_vect) / dotProductND;
            
            if (t > 0 && t < data->pix.t)
            {
                data->pix.t = t;
                data->pix.color = planes->color;
				data->pix.hitpoint = vector_add(rayOrigin, vector_scale(rayDirection, t));
				data->pix.normal = planes->norm_vect;

                // Fill other values of pix
            }
        }
        
        planes = planes->next;
    }
}


