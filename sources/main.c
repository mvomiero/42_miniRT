/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:27:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/28 12:13:27 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_data data;
	// data.objects (t_data *data) (&data)
	if (argc != 2)
	{
		err_msg("Wrong number of arguments!", NULL, NULL);
		return (1);
	}
	init_data(&data);
	// if (!parser(&data, argv[1]))
	// {
	// 	free_structs(&data);
	// 	return (1);
	// }
	parser(&data, argv[1]);
	init_mlx(&data);
	mlx_loop(data.mlx);

	return 0;
}