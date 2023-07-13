/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:16:03 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/13 16:29:55 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	parse_elements(t_data *data, char **tab)
{
	if (ft_strncmp("A", tab[0], 2) == 0)
		return (parse_ambient(data, tab));
	else if (ft_strncmp("C", tab[0], 2) == 0)
		return (parse_camera(data, tab));
	else if (ft_strncmp("L", tab[0], 2) == 0)
		return (parse_light(data, tab));
	else if (ft_strncmp("sp", tab[0], 3) == 0)
		return (parse_sphere(data, tab));
	else if (ft_strncmp("pl", tab[0], 3) == 0)
		return (parse_plane(data, tab));
	else if (ft_strncmp("cy", tab[0], 3) == 0)
		return (parse_cylinder(data, tab));
	else if (ft_strncmp("tr", tab[0], 3) == 0)
		return (parse_triangle(data, tab));
	return (false);
}

static bool	parse_lines(t_data *data, int fd)
{
	char	*line;
	char	**tab;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] != '\n' && line[0] != '#')
		{
			tab = ft_split(line, ' ');
			if (!tab || !parse_elements(data, tab))
			{
				free(line);
				free_tab(tab);
				return (false);
			}
			free_tab(tab);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!data->ambient || !data->camera || !data->light)
		return (err_msg("Missing elements", NULL, NULL), false);
	return (true);
}

bool	parser(t_data *data, char *arg)
{
	int	fd;

	if (!ft_strrchr(arg, '.'))
		return (err_msg("Wrong file path or extension", NULL, NULL), false);
	if (ft_strncmp(ft_strrchr(arg, '.'), ".rt", 4) != 0)
		return (err_msg("Wrong file extension", NULL, NULL), false);
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (err_msg("Promblem opening file", NULL, NULL), false);
	return (parse_lines(data, fd));
}
