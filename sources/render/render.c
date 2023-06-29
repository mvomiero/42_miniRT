/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 15:37:24 by lde-ross          #+#    #+#             */
/*   Updated: 2023/06/29 14:53:13 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*static void set_pixel_color(t_data *data, int x, int y, int color)
{
	data->buf[x * 4 + y * WIDTH * 4] = (char)color; // B
	data->buf[x * 4 + y * WIDTH * 4 + 1] = (char)0; // G
	data->buf[x * 4 + y * WIDTH * 4 + 2] = (char)0; // R
	data->buf[x * 4 + y * WIDTH * 4 + 3] = (char)0; // Trans
}*/

static void	set_pixel_color(t_data *data, int x, int y, int color)
{
	data->buf[x * 4 + y * WIDTH * 4] = color;
	data->buf[x * 4 + y * WIDTH * 4 + 1] = color >> 8;
	data->buf[x * 4 + y * WIDTH * 4 + 2] = color >> 16;
	data->buf[x * 4 + y * WIDTH * 4 + 3] = color >> 24;
}

int convert_rgb_to_hex(t_color *color)
{
    int hex = (color->r << 16) | (color->g << 8) | color->b;
    return hex;
}

void calculateRayDirection(t_data *data, t_camera *camera, int pixelX, int pixelY)
{
	double fovRadians = camera->fov * M_PI / 180.0; // Convert FOV to radians
	double aspectRatio = (double)WIDTH / (double)HEIGHT;
	double viewportHeight = 2.0 * tan(fovRadians / 2.0);
	double viewportWidth = aspectRatio * viewportHeight;

	double pixelNormalizedX = (pixelX + 0.5) / WIDTH; // Normalize pixel coordinates
	double pixelNormalizedY = (pixelY + 0.5) / HEIGHT;

	double viewportX = (2 * pixelNormalizedX - 1) * viewportWidth / 2.0;
	double viewportY = (1 - 2 * pixelNormalizedY) * viewportHeight / 2.0;

	t_vect rayDirection = {
		camera->norm_vect.x + viewportX,
		camera->norm_vect.y + viewportY,
		camera->norm_vect.z};

	data->pix.dir = rayDirection;
}

static void ray_tracer(t_data *data, int x, int y)
{
	parse_color("0,0,255",&(data->pix.color));
	data->pix.t = INFINITY;
	calculateRayDirection(data, data->camera, x, y);
	//t_vect rayDirection = calculateRayDirection(data->camera, x, y);

	
	//bool isHit = hit_sphere(data->spheres->pos, data->spheres->diameter / 2.0, data->camera->pos, rayDirection);
	// bool hit_sphere(t_data *data, t_sphere *spheres, t_vect rayOrigin, t_vect rayDirection)

	hit_sphere(data, data->spheres, data->camera->pos, data->pix.dir);
	//bool isPlaneHit = hit_plane(data->planes, data->camera->pos, rayDirection);
	// shade with pix
		set_pixel_color(data, x, y, convert_rgb_to_hex(&(data->pix.color)));
}

static void render_pixel(t_data *data)
{
	int x;
	int y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			ray_tracer(data, x, y);
	}
}

void render(t_data *data)
{
	int pixel_bits;
	int line_bytes;
	int endian;
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);

	data->buf = mlx_get_data_addr(data->img, &pixel_bits, &line_bytes, &endian);
	render_pixel(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	// mlx_destroy_image(f->mlx, f->img);
}