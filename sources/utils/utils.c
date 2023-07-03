/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:36:39 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 16:30:55 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);

	return (value);
}

void	free_tab(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			if (array[i])
			{
				free(array[i]);
				array[i] = NULL;
			}
			i++;
		}
		free(array);
		array = NULL;
	}
}