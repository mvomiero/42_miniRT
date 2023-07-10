/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:51:04 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/10 18:32:52 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	lstadd_cylinder(t_cylinder **alst, t_cylinder *new)
{
	t_cylinder	*node;

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

bool	parse_cylinder(t_data *data, char **tab)
{
	t_cylinder	*temp;

	if (ft_arrlen(tab) != 6)
		return (err_msg("invalid cylinder arguments", NULL, NULL), false);
	temp = malloc(sizeof(t_cylinder));
	if (!temp)
		return (false);
	lstadd_cylinder(&data->cylinders, temp);
	if (!parse_vector(tab[1], false, &(temp->pos)) || 
		!parse_vector(tab[2], true, &(temp->norm_vect)) || 
		!parse_color(tab[5], &temp->color))
		return (err_msg("invalid cylinder configuration", NULL, NULL), false);
	temp->diameter = ft_atof(tab[3]);
	temp->height = ft_atof(tab[4]);
	if ((!temp->diameter && !ft_is_zero(tab[3])) 
		|| (!temp->height && !ft_is_zero(tab[4])))
		return (err_msg("invalid cylinder configuration", NULL, NULL), false);
	if (temp->diameter <= 0 || temp->height <= 0)
		return (err_msg("invalid cylinder configuration", NULL, NULL), false);
	temp->next = NULL;
	return (true);
}
