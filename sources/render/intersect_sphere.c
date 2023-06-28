/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:15:23 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/28 16:34:09 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
