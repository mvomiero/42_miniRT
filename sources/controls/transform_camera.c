/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:51:29 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/14 16:34:27 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	transform_camera(int keycode, t_data *data, t_type *selected_type)
{
	static t_camera	*selected_camera = NULL;
	double			temp_fov;

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
		{
			rotate_element(keycode, &(selected_camera->norm_vect));
			selected_camera->norm_vect = vector_normalize(selected_camera->norm_vect);
			printf("Camera norm: x %f, y %f, z %f\n\n", selected_camera->norm_vect.x, selected_camera->norm_vect.y, selected_camera->norm_vect.z);
		}
		else if (is_scale_key(keycode))
		{
			temp_fov = (double)(selected_camera->fov);
			scale_element(keycode, &temp_fov);
			selected_camera->fov = (int)temp_fov;
		}
	}

}
