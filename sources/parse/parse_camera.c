/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:30:49 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/28 12:53:07 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	parse_fov(char *str)
{
	int	nb;

	nb = ft_atoi(str);
	if (nb < 0 || nb > 180)
		return (-1);
	else if (!nb && !ft_is_zero(str))
		return (-1);
	else
		return (nb);
}

bool	parse_camera(t_data *data, char **tab)
{
	t_camera	*temp;

	if (ft_arrlen(tab) != 4)
		return (err_msg("Invalid camera arguments number", NULL, NULL), false);
	temp = malloc(sizeof(t_camera));
	if (!temp)
		return (false);
	data->camera = temp;
	if (!parse_vector(tab[1], false, &(temp->pos)) 
		|| !parse_vector(tab[2], true, &(temp->norm_vect)))
		return (err_msg("Invalid camera vector", NULL, NULL), false);
	temp->fov = parse_fov(tab[3]);
	if (temp->fov == -1)
		return (err_msg("Invalid camera FOV", NULL, NULL), false);
	return (true);
}
