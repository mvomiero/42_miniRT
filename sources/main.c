/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:27:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/27 17:08:01 by lde-ross         ###   ########.fr       */
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
	init(&data);
	if (!parser(&data, argv[1]))
	{
		free_structs(&data);
		return (1);
	}
	//printf("parser result is %d\n", parser(argv[1]));
	
	return 0;
}