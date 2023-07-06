/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:50:07 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/06 19:41:05 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	transform_plane(int keycode, t_data *data, t_type *selected_type)
{
	static t_plane	*selected_plane = NULL;

	if (keycode == KEY_P)
	{
		if (*selected_type != TYPE_PLANE && keycode == KEY_P)
		{
			*selected_type = TYPE_PLANE;
			selected_plane = data->planes;
		}
		else if (*selected_type == TYPE_PLANE && keycode == KEY_P)
		{
			selected_plane = selected_plane->next;
			if (selected_plane == NULL)
				selected_plane = data->planes;
		}
	}
	if (selected_plane != NULL && *selected_type == TYPE_PLANE)
	{
		if (is_movement_key(keycode))
			move_element(keycode, &(selected_plane->pos));
		if (is_rotation_key(keycode))
			rotate_element(keycode, &(selected_plane->norm_vect));
	}
}
