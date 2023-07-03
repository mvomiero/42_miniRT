/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:16:02 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 12:52:14 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
		else if (is_scale_key(keycode))
			scale_element(keycode, &(selected_sphere->diameter));
	}
}