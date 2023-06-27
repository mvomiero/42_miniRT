/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:24:23 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 17:46:42 by lde-ross         ###   ########.fr       */
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

bool	parse_color(char *str, t_color *color)
{
	char	**tab;

	tab = ft_split(str, ',');
	if (!tab)
		return (false);
	if (ft_arrlen(tab) != 3 || !color_check(tab))
		return (free_tab(tab), false);
	color->r = ft_atoi(tab[0]);
	color->g = ft_atoi(tab[1]);
	color->b = ft_atoi(tab[2]);
	free_tab(tab);
	return (true);
}
