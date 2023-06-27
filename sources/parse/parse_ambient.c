/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:14:27 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 15:14:42 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	parse_ambient(t_data *data, char **tab)
{
	t_ambient	*temp;
	double		light_ratio;
	t_color		*color;

	if (ft_arrlen(tab) != 3)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	
	light_ratio = ft_atof(tab[1]);
	if ((!light_ratio && !ft_is_zero(tab[1])) ||
			light_ratio < 0 || light_ratio > 1)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	color = parse_color(tab[2]);
	if (!color)
		return (err_msg("invalid .rt file color", NULL, NULL), false);
	temp = malloc(sizeof(temp));
	if (!temp)
		return (false);
	temp->light_ratio = light_ratio;
	temp->color = color;
	// add to back list for other elements
	data->ambient = temp;
	return (true);
}
