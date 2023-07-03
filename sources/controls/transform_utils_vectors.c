/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils_vectors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:58:22 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 12:58:33 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void rotate_vector_y(double angle, t_vect* vect)
{
	double newX = vect->x * cos(angle) + vect->z * sin(angle);
	double newZ = -vect->x * sin(angle) + vect->z * cos(angle);
	vect->x = newX;
	vect->z = newZ;
}

void rotate_vector_x(double angle, t_vect* vect)
{
	double newY = vect->y * cos(angle) - vect->z * sin(angle);
	double newZ = vect->y * sin(angle) + vect->z * cos(angle);
	vect->y = newY;
	vect->z = newZ;
}

void rotate_vector_z(double angle, t_vect* vect)
{
	double newX = vect->x * cos(angle) - vect->y * sin(angle);
	double newY = vect->x * sin(angle) + vect->y * cos(angle);
	vect->x = newX;
	vect->y = newY;
}