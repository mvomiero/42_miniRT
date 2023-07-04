/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:37:09 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/04 16:50:11 by mvomiero         ###   ########.fr       */
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
	data->type = TYPE_UNDEFINED;
	data->render = R_SHADED;
}