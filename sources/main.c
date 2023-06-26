/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:27:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/26 15:29:16 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	// t_data data;
	// data.objects (t_data *data) (&data)
	if (argc != 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Wrong number of arguments", 2);
		return (1);
	}
	printf("parser result is %d\n", parser(argv[1]));
	return 0;
}