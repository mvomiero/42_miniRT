/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:50:11 by lde-ross          #+#    #+#             */
/*   Updated: 2023/07/13 18:35:22 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
typedef double t_mat3x3[3][3];


static t_coord	normalize_pixel(t_coord pixel)
{
	pixel.x = (pixel.x + 0.5) / WIDTH;
	pixel.y = (pixel.y + 0.5) / HEIGHT;
	return (pixel);
}

static t_vect get_viewport(t_camera *camera, t_coord pixel)
{
    double fov_radians;
    double aspect_ratio;
    t_vect viewport;
    
    fov_radians = camera->fov * M_PI / 180.0;
    aspect_ratio = (double)WIDTH / (double)HEIGHT;
    viewport.y = 2.0 * tan(fov_radians / 2.0);
    viewport.x = aspect_ratio * viewport.y;
    viewport.x = (2 * pixel.x - 1) * viewport.x / 2.0;
    viewport.y = (1 - 2 * pixel.y) * viewport.y / 2.0;
    
    // Set the z-coordinate of the viewport to 1
    viewport.z = 1.0;
    
    return viewport;
}

static void get_rotation_matrix(t_vect normal, t_mat3x3 rotation_matrix)
{
    // Compute the rotation angles based on the camera's normal vector
    double theta = atan2(normal.y, normal.x);
    double phi = acos(normal.z);
    
    // Compute the rotation matrix
    rotation_matrix[0][0] = cos(theta);
    rotation_matrix[0][1] = -sin(theta);
    rotation_matrix[0][2] = 0;
    rotation_matrix[1][0] = sin(theta) * cos(phi);
    rotation_matrix[1][1] = cos(theta) * cos(phi);
    rotation_matrix[1][2] = -sin(phi);
    rotation_matrix[2][0] = sin(theta) * sin(phi);
    rotation_matrix[2][1] = cos(theta) * sin(phi);
    rotation_matrix[2][2] = cos(phi);
}

static t_vect get_ray_direction(t_camera *camera, t_coord pixel)
{
    t_vect viewport;
    t_vect ray_direction;
    t_mat3x3 rotation_matrix;
    
    pixel = normalize_pixel(pixel);
    viewport = get_viewport(camera, pixel);
    
    // Compute the rotation matrix based on the camera's orientation
    get_rotation_matrix(camera->norm_vect, rotation_matrix);
    
    // Apply the rotation matrix to the viewport coordinates
    t_vect transformed_viewport;
    transformed_viewport.x = rotation_matrix[0][0] * viewport.x + rotation_matrix[0][1] * viewport.y + rotation_matrix[0][2] * viewport.z;
    transformed_viewport.y = rotation_matrix[1][0] * viewport.x + rotation_matrix[1][1] * viewport.y + rotation_matrix[1][2] * viewport.z;
    transformed_viewport.z = rotation_matrix[2][0] * viewport.x + rotation_matrix[2][1] * viewport.y + rotation_matrix[2][2] * viewport.z;
    
    // Compute the ray direction by combining the transformed viewport coordinates and camera orientation
    ray_direction.x = camera->norm_vect.x + transformed_viewport.x;
    ray_direction.y = camera->norm_vect.y + transformed_viewport.y;
    ray_direction.z = camera->norm_vect.z + transformed_viewport.z;
    
    // Normalize the ray direction vector
    ray_direction = vector_normalize(ray_direction);
    
    return ray_direction;
}

void	ray_tracer(t_data *data, t_coord pixel)
{
	data->pix.t = INFINITY;
	data->pix.dir = get_ray_direction(data->camera, pixel);
	hit_sphere(data, data->spheres, data->camera->pos, data->pix.dir);
	hit_cylinder(data, data->cylinders, data->camera->pos, data->pix.dir);
	hit_plane(data, data->planes, data->camera->pos, data->pix.dir);
	hit_triangle(data, data->triangles, data->camera->pos, data->pix.dir);
}
