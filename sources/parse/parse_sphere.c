/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:41:33 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/27 18:34:07 by mvomiero         ###   ########.fr       */
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
	t_vect		*center;
	double		diameter;
	t_color		*color;

	if (ft_arrlen(tab) != 4)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	center = parse_vector(tab[1], false);
	diameter = ft_atof(tab[2]);
	if (!diameter && !ft_is_zero(tab[2]))
		return (err_msg("invalid .rt file", NULL, NULL), false);
	color = parse_color(tab[3]);
	if (!color)
		return (err_msg("invalid .rt file color", NULL, NULL), false);
	temp = malloc(sizeof(t_sphere));
	if (!temp)
		return (false);
	temp->pos = center;
	temp->diameter = diameter;
	temp->color = color;
	temp->next = NULL;
	lstadd_sphere(&data->spheres, temp);
	return (true);
}

/* bool	parse_sphere(t_data *data, char **tab)
{
	t_sphere	temp;
	t_vect		*center;
	double		diameter;
	t_color		*color;

	if (ft_arrlen(tab) != 4)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	center = parse_vector(tab[1], false);
	diameter = ft_atof(tab[2]);
	if (!diameter && !ft_is_zero(tab[2]))
		return (err_msg("invalid .rt file", NULL, NULL), false);
	color = parse_color(tab[3]);
	if (!color)
		return (err_msg("invalid .rt file color", NULL, NULL), false);
	temp.pos = center;
	temp.diameter = diameter;
	temp.color = color;
	temp.next = NULL;
	lstadd_sphere(&data->spheres, &temp);
	return (true);
} */

/* bool parse_sphere(t_data *data, char **tab)
{
    t_sphere temp;
    t_vect *center;
    double diameter;
    t_color *color;

    if (ft_arrlen(tab) != 4)
        return (err_msg("invalid .rt file", NULL, NULL), false);

    center = parse_vector(tab[1], false);
    diameter = ft_atof(tab[2]);
    if (!diameter && !ft_is_zero(tab[2]))
        return (err_msg("invalid .rt file", NULL, NULL), false);

    color = parse_color(tab[3]);
    if (!color)
        return (err_msg("invalid .rt file color", NULL, NULL), false);

    temp.pos = center;
    temp.diameter = diameter;
    temp.color = color;
    temp.next = NULL;

    lstadd_sphere(&data->spheres, &temp);

    return true;
} */


