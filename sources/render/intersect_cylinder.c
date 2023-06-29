/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:15:06 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/29 16:02:24 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect rayOrigin, t_vect rayDirection)
{
    while (cylinders)
    {
        // Calculate the direction vector of the cylinder's axis
        t_vect axisDirection = cylinders->norm_vect;

        // Calculate the vector from the ray origin to the cylinder's position
        t_vect oc = {rayOrigin.x - cylinders->pos.x, rayOrigin.y - cylinders->pos.y, rayOrigin.z - cylinders->pos.z};

        // Calculate the dot products needed for the quadratic equation
        double a = dotProduct(rayDirection, rayDirection) - pow(dotProduct(rayDirection, axisDirection), 2);
        double b = 2 * (dotProduct(rayDirection, oc) - dotProduct(rayDirection, axisDirection) * dotProduct(oc, axisDirection));
        double c = dotProduct(oc, oc) - pow(dotProduct(oc, axisDirection), 2) - pow(cylinders->diameter / 2, 2);

        // Solve the quadratic equation to find the intersection points
        double discriminant = b * b - 4 * a * c;

        if (discriminant >= 0)
        {
            // Calculate the solutions
            double t1 = (-b - sqrt(discriminant)) / (2 * a);
            double t2 = (-b + sqrt(discriminant)) / (2 * a);

            // Check if the solutions are within the valid range and closer than the current closest hit
            if (t1 > 0 && t1 < data->pix.t)
            {
                // Calculate the y-coordinate of the intersection point
                double y = rayOrigin.y + t1 * rayDirection.y;

                // Check if the intersection point is within the height of the cylinder
                if (y >= cylinders->pos.y && y <= cylinders->pos.y + cylinders->height)
                {
                    data->pix.t = t1;
                    data->pix.color = cylinders->color;
                    // Fill other values of pix
                }
            }

            if (t2 > 0 && t2 < data->pix.t)
            {
                // Calculate the y-coordinate of the intersection point
                double y = rayOrigin.y + t2 * rayDirection.y;

                // Check if the intersection point is within the height of the cylinder
                if (y >= cylinders->pos.y && y <= cylinders->pos.y + cylinders->height)
                {
                    data->pix.t = t2;
                    data->pix.color = cylinders->color;
                    // Fill other values of pix
                }
            }
        }

        cylinders = cylinders->next;
    }
}






