/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:27:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/28 15:22:22 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	t_data data;

	if (argc != 2)
		return (err_msg("Wrong number of arguments!", NULL, NULL), 1);
	init_data(&data);
	if (!parser(&data, argv[1]))
		return (free_structs(&data), 1);
	init_mlx(&data);
	
	mlx_loop(data.mlx);
	return 0;
}