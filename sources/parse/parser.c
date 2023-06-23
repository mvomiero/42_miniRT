#include "../../includes/minirt.h"

int	ft_is_space(char x)
{
	if (!x)
		return (0);
	if (x == '\t' || x == '\v'
		|| x == '\f' || x == '\r' || x == ' ')
		return (1);
	else
		return (0);
}

bool direct_parser(char *line)
{
	int i;

	i = 0;
	while (ft_is_space(line[i]))
		i++;
	if (ft_strncmp(line + i, "A", 1) == 0 && ft_is_space(line[i + 1]))
	{
		printf("found A!\n");
		// if (!parse_ambience(line))
		// 	return (false);
	}
	// else
	// {
	// 	ft_putendl_fd("Error", 2);
	// 	ft_putendl_fd("Identifier not supported", 2);
	// 	return (false);
	// }
	return (true);
}

bool parse_lines(int fd)
{
	char *line;

	line = get_next_line(fd);
	while (line)
	{
		if (!direct_parser(line))
			return (false);
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}

bool parser(char *arg)
{
	int fd;
	if (ft_strncmp(ft_strrchr(arg, '.'), ".rt", 4) != 0)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Wrong file extension", 2);
		return (false);
	}
	fd = open(arg, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("File not found", 2);
		return (false);
	}
	return (parse_lines(fd));
}