/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 19:16:21 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/27 19:34:52 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	close_rt(void *param)
{
	t_data	*app;

	app = (t_data *)param;
	free_structs(app);
	mlx_destroy_window(app->mlx, app->window.reference);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
	exit(0);
	return (0);
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->window.reference = mlx_new_window(data->mlx, 800, 600, "miniRT");
	mlx_hook(data->window.reference, 17, 0, close_rt, (void *)data);
	
}