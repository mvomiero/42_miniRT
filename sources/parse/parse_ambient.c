/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:14:27 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/28 12:44:28 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	parse_ambient(t_data *data, char **tab)
{
	t_ambient	*temp;

	if (ft_arrlen(tab) != 3)
		return (err_msg("Invalid ambient arguments number", NULL, NULL), false);
	temp = malloc(sizeof(t_ambient));
	if (!temp)
		return (false);
	data->ambient = temp;
	temp->light_ratio = ft_atof(tab[1]);
	if ((!temp->light_ratio && !ft_is_zero(tab[1])) ||
			temp->light_ratio < 0 || temp->light_ratio > 1)
		return (err_msg("Invalid ambient light ratio", NULL, NULL), false);
	if (!parse_color(tab[2],&(temp->color)))
		return (err_msg("Invalid ambient color", NULL, NULL), false);
	return (true);
}
