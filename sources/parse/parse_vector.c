/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:50:40 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 16:10:58 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	vector_check(char **str, bool normalized)
{
	double	nb;
	int	i;

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

t_vect	*parse_vector(char *str, bool normalized)
{
	char	**tab;
	t_vect	*temp;

	tab = ft_split(str, ',');
	if (!tab)
		return (NULL);
	if (ft_arrlen(tab) != 3 || !vector_check(tab, normalized))
		return (free_tab(tab), NULL);
	temp = malloc(sizeof(temp));
	temp->x = ft_atof(tab[0]);
	temp->y = ft_atof(tab[1]);
	temp->z = ft_atof(tab[2]);
	free_tab(tab);
	return (temp);
}
