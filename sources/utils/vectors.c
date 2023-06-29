/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:48:44 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/29 17:52:05 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vect vectorAdd(t_vect v1, t_vect v2)
{
	t_vect result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

t_vect vectorScale(t_vect v, double scalar)
{
	t_vect result;
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return result;
}

double vectorDotProduct(t_vect vector1, t_vect vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

t_vect vectorNormalize(t_vect v)
{
	double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	t_vect normalized = {v.x / magnitude, v.y / magnitude, v.z / magnitude};
	return normalized;
}

t_vect vectorSubtraction(t_vect v1, t_vect v2)
{
	t_vect result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}
