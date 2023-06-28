/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:15:23 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/28 17:15:58 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/* 	double dot_product(t_vect a, t_vect b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
} */

bool rayIntersectsSphere(t_vect rayOrigin, t_vect rayDirection, t_sphere sphere) 
{
	t_vect oc = { rayOrigin.x - sphere.pos.x, rayOrigin.y - sphere.pos.y, rayOrigin.z - sphere.pos.z };
	double a = pow(rayDirection.x, 2) + pow(rayDirection.y, 2) + pow(rayDirection.z, 2);
	double b = 2 * (rayDirection.x * oc.x + rayDirection.y * oc.y + rayDirection.z * oc.z);
	double c = pow(oc.x, 2) + pow(oc.y, 2) + pow(oc.z, 2) - pow(sphere.diameter/2, 2);
	double discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0) {
		// No intersection
		return (false);
	} else if (discriminant == 0) {
		// Ray intersects the sphere at one point (tangent)
		return true;
	} else {
		// Ray intersects the sphere at two points
		return true;
	}

}

// Helper function to calculate the dot product of two vectors
double dot_product(t_vect a, t_vect b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

bool rayIntersectsSphere2(t_camera camera, t_sphere sphere) {
    // Calculate the direction vector of the ray based on the camera's position and normalized vector
    t_vect rayDirection;
    rayDirection.x = camera.norm_vect.x;
    rayDirection.y = camera.norm_vect.y;
    rayDirection.z = camera.norm_vect.z;

    // Calculate the vector from the camera's position to the sphere's position
    t_vect oc;
    oc.x = sphere.pos.x - camera.pos.x;
    oc.y = sphere.pos.y - camera.pos.y;
    oc.z = sphere.pos.z - camera.pos.z;

    // Calculate the coefficients for the quadratic equation
    double a = dot_product(rayDirection, rayDirection);
    double b = 2 * dot_product(rayDirection, oc);
    double c = dot_product(oc, oc) - pow(sphere.diameter / 2, 2);

    // Calculate the discriminant
    double discriminant = pow(b, 2) - 4 * a * c;

    // Check if the ray intersects the sphere
    if (discriminant >= 0) {
        return true;
    } else {
        return false;
    }
}


