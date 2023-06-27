/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:14:27 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 18:22:32 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	parse_ambient(t_data *data, char **tab)
{
	t_ambient	*temp;

	if (ft_arrlen(tab) != 3)
		return (err_msg("Invalid ambient settings", "Wrong number of arguments", NULL), false);
	temp = malloc(sizeof(t_ambient));
	if (!temp)
		return (false);
	data->ambient = temp;
	temp->light_ratio = ft_atof(tab[1]);
	if ((!temp->light_ratio && !ft_is_zero(tab[1])) ||
			temp->light_ratio < 0 || temp->light_ratio > 1)
		return (err_msg("Invalid ambient settings", "Invalid light ratio", NULL), false);
	if (!parse_color(tab[2],&(temp->color)))
		return (err_msg("Invalid ambient settings", "Invalid color", NULL), false);
	return (true);
}
