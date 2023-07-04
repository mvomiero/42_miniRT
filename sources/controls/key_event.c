/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:47:14 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/04 17:40:49 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	print_instructions(t_data* data)
{
	if (data->instructions == false)
	{
		data->instructions = true;
		mlx_string_put(data->mlx, data->win, 5, 15, 0xffffff, "ciao");
	}
	else if (data->instructions == true)
	{
		data->instructions = false;
		render(data);
	}
}

int	key_event(int keycode, t_data *data)
{
	static t_type selected_type = TYPE_UNDEFINED;

	printf("\n keycode: %d\n", keycode);

	if (keycode == KEY_ESC)
		close_rt(data);
	if (keycode == KEY_R)
		data->render = R_SHADED;
	if (keycode == KEY_T)
		data->render = R_SHADOWS;

	
	transform_sphere(keycode, data, &selected_type);
	transform_cylinder(keycode, data, &selected_type);
	transform_camera(keycode, data, &selected_type);
	transform_plane(keycode, data, &selected_type);

	if (keycode == KEY_I)
		return(print_instructions(data), 0);

	render(data); // Render the scene using the modified data

	return (0);
}
