/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:17:25 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/06 11:25:21 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	lstadd_triangle(t_triangle **alst, t_triangle *new)
{
	t_triangle	*node;

	node = *alst;
	if (alst && *alst)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*alst = new;
}

bool	parse_triangle(t_data *data, char **tab)
{
	t_triangle	*temp;

	if (ft_arrlen(tab) != 5)
		return (err_msg("invalid triangle arguments", NULL, NULL), false);
	temp = malloc(sizeof(t_triangle));
	if (!temp)
		return (false);
	lstadd_triangle(&data->triangles, temp);
	if (!parse_vector(tab[1], false, &(temp->v1))
		|| !parse_vector(tab[2], false, &(temp->v2))
		|| !parse_vector(tab[3], false, &(temp->v3))
		|| !parse_color(tab[4], &(temp->color)))
		return (err_msg("invalid triangle configuration", NULL, NULL), false);
	t_vect edge1 = vector_subtract(temp->v2, temp->v1);
	t_vect edge2 = vector_subtract(temp->v3, temp->v1);
	temp->norm_vect = vector_normalize(vector_cross_product(edge1, edge2));
	temp->next = NULL;
	return (true);
}
