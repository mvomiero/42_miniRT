/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 18:24:03 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/05 18:31:19 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	vector_dot_product(t_vect vector1, t_vect vector2)
{
	return (vector1.x * vector2.x
		+ vector1.y * vector2.y
		+ vector1.z * vector2.z);
}

t_vect	vector_normalize(t_vect v)
{
	double	magnitude;
	t_vect	normalized;

	magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	normalized.x = v.x / magnitude;
	normalized.y = v.y / magnitude;
	normalized.z = v.z / magnitude;
	return (normalized);
}

double	vector_length(t_vect direction)
{
	return (sqrt(direction.x * direction.x
			+ direction.y * direction.y
			+ direction.z * direction.z));
}

t_vect	get_opposite_normal(t_vect normal)
{
	double	magnitude;
	t_vect	opposite_normal;

	magnitude = vector_length(normal);
	opposite_normal = vector_scale(normal, -magnitude);
	return (opposite_normal);
}

t_vect	move_point_along_normal(t_vect point, t_vect normal, double distance)
{
	t_vect	normalized_normal;
	t_vect	displacement;
	t_vect	moved_point;

	normalized_normal = vector_normalize(normal);
	displacement = vector_scale(normalized_normal, -distance);
	moved_point = vector_add(point, displacement);
	return (moved_point);
}
