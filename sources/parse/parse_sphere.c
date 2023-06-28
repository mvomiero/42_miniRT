/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:41:33 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/27 19:09:01 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	lstadd_sphere(t_sphere **alst, t_sphere *new)
{
	t_sphere	*node;

	node = *alst;
	if (alst && *alst)
	{
		while (node -> next)
			node = node -> next;
		node -> next = new;
	}
	else
		*alst = new;
}

bool	parse_sphere(t_data *data, char **tab)
{
	t_sphere	*temp;

	if (ft_arrlen(tab) != 4)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	temp = malloc(sizeof(t_sphere));
	if (!temp)
		return (false);
	lstadd_sphere(&data->spheres, temp);
	temp->diameter = ft_atof(tab[2]);
	if (!temp->diameter && !ft_is_zero(tab[2]))
		return (err_msg("invalid .rt file", NULL, NULL), false);
	if (!parse_vector(tab[1], false, &(temp->pos)) || 
						!parse_color(tab[3], &temp->color))
		return (err_msg("invalid .rt file color", NULL, NULL), false);
	temp->next = NULL;
	return (true);
}
