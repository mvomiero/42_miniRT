/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:16:21 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/28 15:49:15 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	close_rt(void *param)
{
	t_data	*app;

	app = (t_data *)param;
	free_structs(app);
	mlx_destroy_window(app->mlx, app->win);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
	exit(0);
	return (0);
}

static int	keys(int key, void *param)
{
	if (key == 65307)
		close_rt(param);
	return (0);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	mlx_hook(data->win, 17, 0, close_rt, (void *)data);
	mlx_key_hook(data->win, *keys, (void *)data);
}