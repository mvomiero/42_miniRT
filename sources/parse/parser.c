/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:16:03 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 17:18:52 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	parse_elements(t_data *data, char **tab)
{
	if (ft_strncmp("A", tab[0], 2) == 0)
		return (parse_ambient(data, tab));
	else if (ft_strncmp("sp", tab[0], 2) == 0)
		return (parse_sphere(data, tab));
/* 	else if (ft_strncmp("C", tab[0], 2) == 0)
		return (parse_camera(data, tab)); */
	return (false);
}

static bool	parse_lines(t_data *data, int fd)
{
	char *line;
	char **tab;

	line = get_next_line(fd);
	while (line)
	{
		tab = ft_split(line, ' ');
		// protect split output
		free(line);


		// split
		// parseing 
		if (!tab || !parse_elements(data, tab))
		{
			free_tab(tab);
			//err_msg("parsing error!");
			return (false);


		}
		ft_print_strarr(tab);
		free_tab(tab);

		//printf("%s\n", line);
		line = get_next_line(fd);
	}
	return (true);
}

bool parser(t_data *data, char *arg) // add the struct t_data *data
{
	int fd;
	if (ft_strncmp(ft_strrchr(arg, '.'), ".rt", 4) != 0)
		return(err_msg("Wrong file extension", NULL, NULL), false);
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return(err_msg("Promblem opening file", NULL, NULL), false);
	// creation of the 2D array
	// parse it in our struct
	// free the array

	return (parse_lines(data, fd));
}