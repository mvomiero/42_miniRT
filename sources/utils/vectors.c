/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:48:44 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/04 13:45:39 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vect vector_add(t_vect v1, t_vect v2)
{
	t_vect result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

t_vect vector_scale(t_vect v, double scalar)
{
	t_vect result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

double vector_dot_product(t_vect vector1, t_vect vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

t_vect vector_normalize(t_vect v)
{
	double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	t_vect normalized = {v.x / magnitude, v.y / magnitude, v.z / magnitude};
	return normalized;
}

t_vect vector_substract(t_vect v1, t_vect v2)
{
	t_vect result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

t_vect vector_divide(t_vect v, double scalar)
{
	t_vect result;
	result.x = v.x / scalar;
	result.y = v.y / scalar;
	result.z = v.z / scalar;
	return result;
}

double vector_length(t_vect direction)
{
	return sqrt(direction.x * direction.x +
				direction.y * direction.y +
				direction.z * direction.z);
}

t_vect get_opposite_normal(t_vect normal)
{
	double magnitude = vector_length(normal);
	t_vect opposite_normal = vector_scale(normal, -magnitude);

	return opposite_normal;
}

double vector_magnitude(t_vect vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}

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
