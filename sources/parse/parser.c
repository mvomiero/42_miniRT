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



bool	parse_ambient(t_data *data, char **tab)
{
	t_ambient	*temp;
	double		light_ratio;
	t_color		*color;

	if (ft_arrlen(tab) != 3)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	
	light_ratio = ft_atof(tab[1]);
	if ((!light_ratio && !ft_is_zero(tab[1])) ||
			light_ratio < 0 || light_ratio > 1)
		return (err_msg("invalid .rt file", NULL, NULL), false);
	color = parse_color(tab[2]);
	if (!color)
		return (err_msg("invalid .rt file color", NULL, NULL), false);
	temp = malloc(sizeof(temp));
	if (!temp)
		return (false);
	temp->light_ratio = light_ratio;
	temp->color = color;
	// add to back list for other elements
	data->ambient = temp;
	return (true);
}

static bool	parse_elements(t_data *data, char **tab)
{
	if (ft_strncmp("A", tab[0], 2) == 0)
		return (parse_ambient(data, tab));
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