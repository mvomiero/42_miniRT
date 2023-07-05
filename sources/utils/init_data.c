/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:37:09 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/05 18:16:31 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init_data(t_data *data)
{
	data->ambient = NULL;
	data->camera = NULL;
	data->light = NULL;
	data->spheres = NULL;
	data->planes = NULL;
	data->cylinders = NULL;
	data->triangles = NULL;
	data->type = TYPE_UNDEFINED;
	data->scenes.render = R_SHADED;
	data->scenes.n_rays = 100;
	data->instructions = false;
}
