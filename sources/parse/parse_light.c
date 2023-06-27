/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:17:55 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 16:26:07 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static double parse_brightness(char *str)
{
	double	nb;

	nb = ft_atof(str);
	if (nb < 0 || nb > 1)
		return (-1);
	else if (!nb && !ft_is_zero(str))
		return (-1);
	else
		return nb;
}

bool	parse_light(t_data *data, char **tab)
{
	t_light	*temp;
	t_vect	*pos;
	double	brightness;
	t_color	*color;

	if (ft_arrlen(tab) != 4)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	pos = parse_vector(tab[1], false);
	if (!pos)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	brightness = parse_brightness(tab[2]);
	if (brightness == -1)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	color = parse_color(tab[3]);
	if (!color)
		return (err_msg("invalid .rt file color", NULL, NULL), false);
	temp = malloc(sizeof(temp));
	if (!temp)
		return (false);
	temp->pos = pos;
	temp->brightness = brightness;
	temp->color = color;
	data->light = temp;
	return (true);
}
