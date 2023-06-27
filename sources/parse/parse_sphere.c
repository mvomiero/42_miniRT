/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:41:33 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/27 15:51:59 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	parse_sphere(t_data *data, char **tab)
{
	t_sphere	*temp;
	t_vect		*center;
	double		diameter;
	t_color		*color;

	if (ft_arrlen(tab) != 4)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	center = parse_vector(center);
	diameter = ft_atof(tab[1]);
	if ((!diameter && !ft_is_zero(tab[1])) ||
			diameter < 0 || diameter > 1)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	color = parse_color(tab[2]);
	if (!color)
		return (err_msg("invalid .rt file color", NULL, NULL), false);
	temp = malloc(sizeof(temp));
	if (!temp)
		return (false);
	temp->pos = center;
	temp->diameter = diameter;
	temp->color = color;
	// add to back list for other elements
	//data->sphere = temp;
	return (true);
}
