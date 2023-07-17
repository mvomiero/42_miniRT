/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils_vectors.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:58:22 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/17 10:45:58 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	rotate_vector_y(double angle, t_vect *vect)
{
	double	new_x;
	double	new_z;

	new_x = vect->x * cos(angle) + vect->z * sin(angle);
	new_z = -vect->x * sin(angle) + vect->z * cos(angle);
	vect->x = new_x;
	vect->z = new_z;
}

void	rotate_vector_x(double angle, t_vect *vect)
{
	double	new_y;
	double	new_z;

	new_y = vect->y * cos(angle) - vect->z * sin(angle);
	new_z = vect->y * sin(angle) + vect->z * cos(angle);
	vect->y = new_y;
	vect->z = new_z;
}

void	rotate_vector_z(double angle, t_vect *vect)
{
	double	new_x;
	double	new_y;

	new_x = vect->x * cos(angle) - vect->y * sin(angle);
	new_y = vect->x * sin(angle) + vect->y * cos(angle);
	vect->x = new_x;
	vect->y = new_y;
}
