/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:49:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/29 17:10:54 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define EPSILON 1e-6


t_vect vectorSubtraction(t_vect v1, t_vect v2)
{
    t_vect result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}


void hit_plane(t_data *data, t_plane *planes, t_vect rayOrigin, t_vect rayDirection)
{
    while (planes)
    {
        double dotProductND = dotProduct(planes->norm_vect, rayDirection);
        
        // Check if the ray is not parallel to the plane (dotProductND is close to zero)
        if (fabs(dotProductND) > EPSILON)
        {
            t_vect oc = vectorSubtraction(planes->pos, rayOrigin);
            double t = dotProduct(oc, planes->norm_vect) / dotProductND;
            
            if (t > 0 && t < data->pix.t)
            {
                data->pix.t = t;
                data->pix.color = planes->color;
                // Fill other values of pix
            }
        }
        
        planes = planes->next;
    }
}


