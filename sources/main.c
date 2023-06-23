/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:27:58 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/23 16:51:48 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Wrong number of arguments", 2);
		return (1);
	}
	int *ptr = NULL;  // Initializing pointer to NULL

    *ptr = 10;  // Trying to dereference a NULL pointer

    printf("The value is: %d\n", *ptr);
	parser(argv[1]);
}