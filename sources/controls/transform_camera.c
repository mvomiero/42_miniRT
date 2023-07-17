/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:51:29 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/17 10:47:15 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	transform_camera(int keycode, t_data *data, t_type *selected_type)
{
	static t_camera	*sel_camera = NULL;
	double			temp_fov;

	if (keycode == KEY_V)
	{
		if (*selected_type != TYPE_CAMERA && keycode == KEY_V)
		{
			*selected_type = TYPE_CAMERA;
			sel_camera = data->camera;
		}
	}
	if (sel_camera != NULL && *selected_type == TYPE_CAMERA)
	{
		if (is_movement_key(keycode))
			move_element(keycode, &(sel_camera->pos));
		else if (is_rotation_key(keycode))
			rotate_element(keycode, &(sel_camera->norm_vect));
		else if (is_scale_key(keycode))
		{
			temp_fov = (double)(sel_camera->fov);
			scale_element(keycode, &temp_fov);
			sel_camera->fov = (int)temp_fov;
		}
	}
}
