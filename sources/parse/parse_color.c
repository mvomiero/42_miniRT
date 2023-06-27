/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:24:23 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 15:24:38 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	color_check(char **str)
{
	int	nb;
	int	i;

	i = 0;
	while (i < 3)
	{
		nb = ft_atoi(str[i]);
		if (!nb && !ft_is_zero(str[i]))
			return (false);
		if (nb < 0 || nb > 255)
			return (false);
		i++;
	}
	return (true);
}

t_color	*parse_color(char *str)
{
	char	**tab;
	t_color	*temp;

	tab = ft_split(str, ',');
	if (!tab)
		return (NULL);
	if (ft_arrlen(tab) != 3 || !color_check(tab))
		return (free_tab(tab), NULL);
	temp = malloc(sizeof(temp));
	temp->r = ft_atoi(tab[0]);
	temp->g = ft_atoi(tab[1]);
	temp->b = ft_atoi(tab[2]);
	free_tab(tab);
	return (temp);
}
