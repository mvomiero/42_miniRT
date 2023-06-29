/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 16:49:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/29 17:56:28 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define EPSILON 1e-6




void hit_plane(t_data *data, t_plane *planes, t_vect rayOrigin, t_vect rayDirection)
{
    while (planes)
    {
        double dotProductND = vectorDotProduct(planes->norm_vect, rayDirection);
        
        // Check if the ray is not parallel to the plane (dotProductND is close to zero)
        if (fabs(dotProductND) > EPSILON)
        {
            t_vect oc = vectorSubtraction(planes->pos, rayOrigin);
            double t = vectorDotProduct(oc, planes->norm_vect) / dotProductND;
            
            if (t > 0 && t < data->pix.t)
            {
                data->pix.t = t;
                data->pix.color = planes->color;
				data->pix.hitpoint = vectorAdd(rayOrigin, vectorScale(rayDirection, t));
				data->pix.normal = planes->norm_vect;

                // Fill other values of pix
            }
        }
        
        planes = planes->next;
    }
}


