/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:41:33 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/27 19:09:01 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	lstadd_plane(t_plane **alst, t_plane *new)
{
	t_plane	*node;

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

bool	parse_plane(t_data *data, char **tab)
{
	t_plane	*temp;

	if (ft_arrlen(tab) != 4)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	temp = malloc(sizeof(t_plane));
	if (!temp)
		return (false);
	lstadd_plane(&data->plane, temp);
	if (!parse_vector(tab[1], false, &(temp->pos)) || 
				!parse_vector(tab[2], true, &(temp->norm_vect)) || 
						!parse_color(tab[3], &temp->color))
		return (err_msg("invalid plane configuration", NULL, NULL), false);
	temp->next = NULL;
	return (true);
}
