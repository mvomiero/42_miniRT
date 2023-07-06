/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 17:48:44 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/06 19:31:18 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_vect	vector_add(t_vect v1, t_vect v2)
{
	t_vect	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vect	vector_subtract(t_vect v1, t_vect v2)
{
	t_vect	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vect	vector_divide(t_vect v, double scalar)
{
	t_vect	result;

	result.x = v.x / scalar;
	result.y = v.y / scalar;
	result.z = v.z / scalar;
	return (result);
}

t_vect	vector_multiply(t_vect v1, t_vect v2)
{
	t_vect	result;

	result.x = v1.x * v2.x;
	result.y = v1.y * v2.y;
	result.z = v1.z * v2.z;
	return (result);
}

t_vect	vector_scale(t_vect v, double scalar)
{
	t_vect	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}
