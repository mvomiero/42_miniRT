#include "../../includes/minirt.h"

bool parser(char *arg)
{
	if (ft_strncmp(ft_strrchr(arg, '.'), ".rt", 3) != 0)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Wrong file extension", 2);
		return (false);
	}
	return (true);
}