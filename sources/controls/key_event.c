/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:47:14 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/30 16:41:03 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define STEP 2
#define SCALE_FACTOR 1.2
#define ROTATION_ANGLE 20

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

bool is_movement_key(int keycode)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT ||
		keycode == KEY_RIGHT || keycode == KEY_PAGE_UP || keycode == KEY_PAGE_DOWN)
		return true;
	return false;
}

bool is_scale_key(int keycode)
{
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		return true;
	return false;
}

bool is_rotation_key(int keycode)
{
	if (keycode == KEY_H || keycode == KEY_J || keycode == KEY_U ||
		keycode == KEY_N || keycode == KEY_Y || keycode == KEY_M)
		return true;
	return false;
}


void	transform_sphere(int keycode, t_data *data, t_type *selected_type)
{
	static t_sphere *selected_sphere = NULL;

	if (keycode == KEY_S)
	{
		if (*selected_type != TYPE_SPHERE && keycode == KEY_S)
		{
			*selected_type = TYPE_SPHERE;
			selected_sphere = data->spheres;
		}
		else if (*selected_type == TYPE_SPHERE && keycode == KEY_S)
		{
			selected_sphere = selected_sphere->next;
			if (selected_sphere == NULL)
				selected_sphere = data->spheres;
		}
	}
	if (selected_sphere != NULL && *selected_type == TYPE_SPHERE)
	{
		if (is_movement_key(keycode))
			move_element(keycode, &(selected_sphere->pos));
		if (is_scale_key(keycode))
			scale_element(keycode, &(selected_sphere->diameter));
	}
}

void transform_cylinder(int keycode, t_data* data, t_type* selected_type)
{
	static t_cylinder* selected_cylinder = NULL;

	if (keycode == KEY_C)
	{
		if (*selected_type != TYPE_CYLINDER && keycode == KEY_C)
		{
			*selected_type = TYPE_CYLINDER;
			selected_cylinder = data->cylinders;
		}
		else if (*selected_type == TYPE_CYLINDER && keycode == KEY_C)
		{
			selected_cylinder = selected_cylinder->next;
			if (selected_cylinder == NULL)
				selected_cylinder = data->cylinders;
		}
	}
	if (selected_cylinder != NULL && *selected_type == TYPE_CYLINDER)
	{
		if (is_movement_key(keycode))
			move_element(keycode, &(selected_cylinder->pos));
		if (is_scale_key(keycode))
		{
			scale_element(keycode, &(selected_cylinder->diameter));
			scale_element(keycode, &(selected_cylinder->height));
		}
		if (is_rotation_key(keycode))
			rotate_element(keycode, &(selected_cylinder->norm_vect));
	}
}


int	key_event(int keycode, t_data *data)
{
	static t_type selected_type = TYPE_UNDEFINED;

	printf("\n keycode: %d\n", keycode);

	if (keycode == KEY_ESC)
		close_rt(data);

	transform_sphere(keycode, data, &selected_type);
	transform_cylinder(keycode, data, &selected_type);

	render(data); // Render the scene using the modified data

	return (0);
}
