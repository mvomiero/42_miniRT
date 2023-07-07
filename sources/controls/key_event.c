/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:47:14 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/07 17:01:43 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	put_instructions(t_data *data)
{
	mlx_string_put(data->mlx, data->win, 5, 15, W_INST, "miniRT");
	mlx_string_put(data->mlx, data->win, 5, 25, W_INST, "Instructions: (I)");
	mlx_string_put(data->mlx, data->win, 5, 50, W_INST,
		"Objects: (S) sphere, (P) plane, (C) cylinder, \
(G) triangle, (L) light, (V) view");
	mlx_string_put(data->mlx, data->win, 5, 70, W_INST,
		"Move: arrows to move in the xz plane, Pg to move in z axis ");
	mlx_string_put(data->mlx, data->win, 5, 90, W_INST, "Rotate:");
	mlx_string_put(data->mlx, data->win, 5, 90, W_INST, "(H)-(J) -> y axis");
	mlx_string_put(data->mlx, data->win, 5, 110, W_INST, "(U)-(N) -> x axis");
	mlx_string_put(data->mlx, data->win, 5, 130, W_INST, "(Y)-(M) -> z axis");
	mlx_string_put(data->mlx, data->win, 5, 170, W_INST, "Scale: + -");
	mlx_string_put(data->mlx, data->win, 5, 190, W_INST,
		"Render: (R) shaded, (E) hard shadows, (T) soft shadows");
	mlx_string_put(data->mlx, data->win, 5, 210, W_INST, "Exit: Esc");
}

void	print_instructions(int keycode, t_data *data)
{
	if (keycode == KEY_I && data->instructions == false)
		data->instructions = true;
	else if (keycode == KEY_I && data->instructions == true)
		data->instructions = false;
	if (data->instructions == true)
	{
		data->instructions = true;
		put_instructions(data);
	}
}

int	key_event(int keycode, t_data *data)
{
	static t_type	selected_type;

	selected_type = TYPE_UNDEFINED;
	if (keycode == KEY_ESC)
		close_rt(data);
	if (keycode == KEY_R)
		data->scenes.render = R_SHADED;
	if (keycode == KEY_T)
		data->scenes.render = R_SHADOWS;
	if (keycode == KEY_E)
		data->scenes.render = R_SOFT_SHADOWS;
	transform_sphere(keycode, data, &selected_type);
	transform_cylinder(keycode, data, &selected_type);
	transform_camera(keycode, data, &selected_type);
	transform_plane(keycode, data, &selected_type);
	transform_triangle(keycode, data, &selected_type);
	render(data);
	print_instructions(keycode, data);
	return (0);
}
