/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:37:09 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 16:42:07 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init(t_data *data)
{
	data->ambient = NULL;
	data->camera = NULL;
	data->light = NULL;
	data->spheres = NULL;
	data->plane = NULL;
	data->cylinders = NULL;
	// data->spheres->next = NULL;
	// data->plane->next = NULL;
	// data->cylinders->next = NULL;
}