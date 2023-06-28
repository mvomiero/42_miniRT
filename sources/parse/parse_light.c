/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 16:17:55 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/28 12:47:08 by mvomiero         ###   ########.fr       */
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

	if (ft_arrlen(tab) != 4)
		return (err_msg("Invalid light arguments number", NULL, NULL), false);
	temp = malloc(sizeof(t_light));
	data->light = temp;
	if (!temp)
		return (false);
	if (!parse_vector(tab[1], false, &(temp->pos)))
		return (err_msg("Invalid light position", NULL, NULL), false);
	temp->brightness = parse_brightness(tab[2]);
	if (temp->brightness == -1)
		return (err_msg("Invalid light brightness", NULL, NULL), false);
	if (!parse_color(tab[3], &(temp->color)))
		return (err_msg("Invalid light color", NULL, NULL), false);
	return (true);
}
