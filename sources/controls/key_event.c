/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:47:14 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 13:01:52 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"


int	key_event(int keycode, t_data *data)
{
	static t_type selected_type = TYPE_UNDEFINED;

	printf("\n keycode: %d\n", keycode);

	if (keycode == KEY_ESC)
		close_rt(data);

	transform_sphere(keycode, data, &selected_type);
	transform_cylinder(keycode, data, &selected_type);
	transform_camera(keycode, data, &selected_type);
	transform_plane(keycode, data, &selected_type);

	render(data); // Render the scene using the modified data

	return (0);
}