/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:50:11 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/30 16:16:11 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static t_coord normalize_pixel(t_coord pixel)
{
	pixel.x = (pixel.x + 0.5) / WIDTH;
	pixel.y = (pixel.y + 0.5) / HEIGHT;
	return (pixel);
}

static t_coord get_viewport(t_camera *camera, t_coord pixel)
{
	double fovRadians;
	double aspectRatio;
	t_coord viewport;

	fovRadians = camera->fov * M_PI / 180.0; // Convert FOV to radians
	aspectRatio = (double)WIDTH / (double)HEIGHT;
	viewport.y = 2.0 * tan(fovRadians / 2.0);
	viewport.x = aspectRatio * viewport.y;
	viewport.x = (2 * pixel.x - 1) * viewport.x / 2.0;
	viewport.y = (1 - 2 * pixel.y) * viewport.y / 2.0;
	return (viewport);
}

static t_vect get_ray_direction(t_camera *camera, t_coord pixel)
{
	t_coord viewport;
	t_vect rayDirection;

	pixel = normalize_pixel(pixel);
	viewport = get_viewport(camera, pixel);
	rayDirection.x = camera->norm_vect.x + viewport.x;
	rayDirection.y = camera->norm_vect.y + viewport.y;
	rayDirection.z = camera->norm_vect.z;
	return (rayDirection);
}

void ray_tracer(t_data *data, t_coord pixel)
{
	data->pix.t = INFINITY;
	data->pix.dir = get_ray_direction(data->camera, pixel);
	hit_sphere(data, data->spheres, data->camera->pos, data->pix.dir);
	hit_cylinder(data, data->cylinders, data->camera->pos, data->pix.dir);
	hit_plane(data, data->planes, data->camera->pos, data->pix.dir);
}