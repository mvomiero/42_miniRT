/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:48:47 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/10 16:28:01 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	select_next_triangle(t_data *data, t_type *selected_type,
		t_triangle **selected_triangle)
{
	if (*selected_type == TYPE_TRIANGLE)
	{
		*selected_triangle = (*selected_triangle)->next;
		if (*selected_triangle == NULL)
			*selected_triangle = data->triangles;
	}
}

void	move_selected_triangle(int keycode, t_triangle *selected_triangle)
{
	if (is_movement_key(keycode))
	{
		move_element(keycode, &(selected_triangle->v1));
		move_element(keycode, &(selected_triangle->v2));
		move_element(keycode, &(selected_triangle->v3));
	}
}

void	rotate_selected_triangle(int keycode, t_triangle *selected_triangle)
{
	if (is_rotation_key(keycode))
	{
		rotate_element(keycode, &(selected_triangle->v1));
		rotate_element(keycode, &(selected_triangle->v2));
		rotate_element(keycode, &(selected_triangle->v3));
	}
}

void	transform_triangle(int keycode, t_data *data, t_type *selected_type)
{
	static t_triangle	*selected_triangle = NULL;

	if (keycode == KEY_G)
	{
		if (*selected_type != TYPE_TRIANGLE)
		{
			*selected_type = TYPE_TRIANGLE;
			selected_triangle = data->triangles;
		}
		else
			select_next_triangle(data, selected_type, &selected_triangle);
	}
	if (selected_triangle != NULL && *selected_type == TYPE_TRIANGLE)
	{
		move_selected_triangle(keycode, selected_triangle);
		rotate_selected_triangle(keycode, selected_triangle);
	}
}
