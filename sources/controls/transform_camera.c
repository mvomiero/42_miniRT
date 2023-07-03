/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:51:29 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 12:51:49 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void transform_camera(int keycode, t_data* data, t_type* selected_type)
{
	static t_camera* selected_camera = NULL;

	if (keycode == KEY_V)
	{
		if (*selected_type != TYPE_CAMERA && keycode == KEY_V)
		{
			*selected_type = TYPE_CAMERA;
			selected_camera = data->camera;
		}
	}
	if (selected_camera != NULL && *selected_type == TYPE_CAMERA)
	{
		if (is_movement_key(keycode))
			move_element(keycode, &(selected_camera->pos));
		else if (is_rotation_key(keycode))
			rotate_element(keycode, &(selected_camera->norm_vect));
		else if (is_scale_key(keycode))
		{
			double temp_fov = (double)(selected_camera->fov);
			scale_element(keycode, &temp_fov);
			selected_camera->fov = (int)temp_fov;
		}
	}
}