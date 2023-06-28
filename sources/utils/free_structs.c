/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:54:38 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/28 15:20:15 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	free_planes(t_plane **alst)
{
	t_plane	*temp;
	t_plane	*current;

	current = *alst;

	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
}

static void	free_spheres(t_sphere **alst)
{
	t_sphere	*temp;
	t_sphere	*current;

	current = *alst;

	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
}

static void	free_cylinders(t_cylinder **alst)
{
	t_cylinder	*temp;
	t_cylinder	*current;

	current = *alst;

	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
}

void	free_structs(t_data *data)
{
	if (data->camera)
		free(data->camera);
	if (data->light)
		free(data->light);
	if (data->ambient)
		free(data->ambient);
	if (data->planes)
		free_planes(&data->planes);
	if (data->spheres)
		free_spheres(&data->spheres);
	if (data->cylinders)
		free_cylinders(&data->cylinders);
}