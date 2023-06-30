/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:47:14 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/30 15:50:14 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

#define STEP 2
#define SCALE_FACTOR 1.2

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
	if (keycode == KEY_PLUS || keycode == KEY_W)
		return true;
	return false;
}

void	transform_sphere(int keycode, t_data *data, t_type *selected_type)
{
	static t_sphere *selected_sphere = NULL;

	if (keycode == KEY_S || is_movement_key(keycode) || is_scale_key(keycode))
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
		if (selected_sphere != NULL)
		{
			if (is_movement_key(keycode))
				move_element(keycode, &(selected_sphere->pos));
			if (is_scale_key(keycode))
				scale_element(keycode, &(selected_sphere->diameter));
		}
	}
}

int	key_event(int keycode, t_data *data)
{
	static t_type selected_type = TYPE_UNDEFINED;

	printf("\n keycode: %d\n", keycode);

	if (keycode == KEY_ESC)
		close_rt(data);

	transform_sphere(keycode, data, &selected_type);

	render(data); // Render the scene using the modified data

	return (0);
}
