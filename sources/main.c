/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:27:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/27 16:35:16 by mvomiero         ###   ########.fr       */
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
	data.spheres = NULL;
	if (!parser(&data, argv[1]))
		err_msg("parsing error!", NULL, NULL);
	//printf("parser result is %d\n", parser(argv[1]));
	return 0;
}