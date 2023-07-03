/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:46:34 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 13:01:15 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void rotate_element(int keycode, t_vect* norm_vect)
{
	double angle = ROTATION_ANGLE * M_PI / 180.0; // Convert degrees to radians

	if (keycode == KEY_H)
		rotate_vector_y(angle, norm_vect); // Rotate counterclockwise along the y-axis
	else if (keycode == KEY_J)
		rotate_vector_y(-angle, norm_vect); // Rotate clockwise along the y-axis
	else if (keycode == KEY_U)
		rotate_vector_x(angle, norm_vect); // Rotate counterclockwise along the x-axis
	else if (keycode == KEY_N)
		rotate_vector_x(-angle, norm_vect); // Rotate clockwise along the x-axis
	else if (keycode == KEY_Y)
		rotate_vector_z(angle, norm_vect); // Rotate counterclockwise along the z-axis
	else if (keycode == KEY_M)
		rotate_vector_z(-angle, norm_vect); // Rotate clockwise along the z-axis
}




void move_element(int keycode, t_vect *pos)
{
	if (keycode == KEY_PAGE_DOWN)
		pos->y -= STEP;
	else if (keycode == KEY_PAGE_UP)
		pos->y += STEP;
	else if (keycode == KEY_LEFT)
		pos->x -= STEP;
	else if (keycode == KEY_RIGHT)
		pos->x += STEP;
	else if (keycode == KEY_DOWN)
		pos->z -= STEP;
	else if (keycode == KEY_UP)
		pos->z += STEP;
}

void scale_element(int keycode, double *parameter)
{
	if (keycode == KEY_PLUS)
		*parameter *= SCALE_FACTOR;
	else if (keycode == KEY_MINUS)
		*parameter /= SCALE_FACTOR;
}