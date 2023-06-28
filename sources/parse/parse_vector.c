/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:50:40 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/28 12:48:45 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	vector_check(char **str, bool normalized)
{
	double	nb;
	int		i;

	i = 0;
	while (i < 3)
	{
		nb = ft_atof(str[i]);
		if (!nb && !ft_is_zero(str[i]))
			return (false);
		if (normalized && (nb < -1 || nb > 1))
			return (false);
		i++;
	}
	return (true);
}

bool	parse_vector(char *str, bool normalized, t_vect *vect)
{
	char	**tab;

	tab = ft_split(str, ',');
	if (!tab)
		return (false);
	if (ft_arrlen(tab) != 3 || !vector_check(tab, normalized))
		return (free_tab(tab), false);
	vect->x = ft_atof(tab[0]);
	vect->y = ft_atof(tab[1]);
	vect->z = ft_atof(tab[2]);
	free_tab(tab);
	return (true);
}
