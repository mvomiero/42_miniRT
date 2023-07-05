/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:47:14 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/05 16:55:31 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

# define COL_COMMANDS 0xffffff

void	print_instructions(int keycode, t_data* data)
{
	if (keycode == KEY_I && data->instructions == false)
		data->instructions = true;
	else if (keycode == KEY_I && data->instructions == true)
		data->instructions = false;
	if (data->instructions == true)
	{
		data->instructions = true;
		mlx_string_put(data->mlx, data->win, 5, 15, COL_COMMANDS, "miniRT");
		mlx_string_put(data->mlx, data->win, 5, 25, COL_COMMANDS, "Instructions: (I)");
		mlx_string_put(data->mlx, data->win, 5, 50, COL_COMMANDS, "Objects: (S) sphere, (P) plane, (C) camera, (G) triangle, (L) light, (V) view");
		mlx_string_put(data->mlx, data->win, 5, 70, COL_COMMANDS, "Move: arrows to move in the xz plane, Pg to move in z axis ");
		mlx_string_put(data->mlx, data->win, 5, 90, COL_COMMANDS, "Rotate: (H)-(J) -> y axis");
		mlx_string_put(data->mlx, data->win, 5, 110, COL_COMMANDS, "        (U)-(N) -> x axis");
		mlx_string_put(data->mlx, data->win, 5, 130, COL_COMMANDS, "        (Y)-(M) -> z axis");
		mlx_string_put(data->mlx, data->win, 5, 150, COL_COMMANDS, "        (Y)-(M) -> z axis");
		mlx_string_put(data->mlx, data->win, 5, 170, COL_COMMANDS, "Scale: + -");
		mlx_string_put(data->mlx, data->win, 5, 190, COL_COMMANDS, "Render: (R) shaded, (E) hard shadows, (T) soft shadows");
		mlx_string_put(data->mlx, data->win, 5, 210, COL_COMMANDS, "Exit: Esc");
	}
}

int	key_event(int keycode, t_data *data)
{
	static t_type selected_type = TYPE_UNDEFINED;

	printf("\n keycode: %d\n", keycode);

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

	//if (keycode == KEY_I)
	//	return(print_instructions(keycode, data), 0);

	render(data); // Render the scene using the modified data
	print_instructions(keycode, data);

	return (0);
}
