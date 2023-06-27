/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:30:49 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 16:10:06 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int parse_fov(char *str)
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
	t_vect		*pos;
	t_vect		*norm_vect;
	int			fov; // field of view

	if (ft_arrlen(tab) != 4)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	pos = parse_vector(tab[1], false);
	norm_vect = parse_vector(tab[2], true);
	if (!pos || !norm_vect)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	fov = parse_fov(tab[3]);
	if (fov == -1)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	temp = malloc(sizeof(temp));
	if (!temp)
		return (false);
	temp->pos = pos;
	temp->norm_vect = norm_vect;
	temp->fov = fov;
	data->camera = temp;
	return (true);
}
