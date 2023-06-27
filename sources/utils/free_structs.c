/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:54:38 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 18:23:06 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	free_structs(t_data *data)
{
	if (data->camera)
		free(data->camera);
	if (data->light)
		free(data->light);
	if (data->ambient)
		free(data->ambient);
}