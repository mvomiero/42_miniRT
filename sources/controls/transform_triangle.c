/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:48:47 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/05 16:49:34 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void transform_triangle(int keycode, t_data* data, t_type* selected_type)
{
	static t_triangle* selected_triangle = NULL;

	if (keycode == KEY_G)
	{
		if (*selected_type != TYPE_TRIANGLE && keycode == KEY_G)
		{
			*selected_type = TYPE_TRIANGLE;
			selected_triangle = data->triangles;
		}
		else if (*selected_type == TYPE_TRIANGLE && keycode == KEY_G)
		{
			selected_triangle = selected_triangle->next;
			if (selected_triangle == NULL)
				selected_triangle = data->triangles;
		}
	}

	if (selected_triangle != NULL && *selected_type == TYPE_TRIANGLE)
	{
		if (is_movement_key(keycode))
		{
			move_element(keycode, &(selected_triangle->v1));
			move_element(keycode, &(selected_triangle->v2));
			move_element(keycode, &(selected_triangle->v3));
		}

		if (is_rotation_key(keycode))
		{
			rotate_element(keycode, &(selected_triangle->v1));
			rotate_element(keycode, &(selected_triangle->v2));
			rotate_element(keycode, &(selected_triangle->v3));
		}
	}
}
