/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:37:09 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/28 15:20:15 by lde-ross         ###   ########.fr       */
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
	// data->spheres->next = NULL;
	// data->plane->next = NULL;
	// data->cylinders->next = NULL;
}