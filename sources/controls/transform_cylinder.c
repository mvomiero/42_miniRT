/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:50:26 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 12:52:04 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
		else if (is_scale_key(keycode))
		{
			scale_element(keycode, &(selected_cylinder->diameter));
			scale_element(keycode, &(selected_cylinder->height));
		}
		else if (is_rotation_key(keycode))
			rotate_element(keycode, &(selected_cylinder->norm_vect));
	}
}