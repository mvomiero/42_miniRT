/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_is_in_shadow.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:46:55 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/10 12:09:40 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_plane_in_shadow(t_data *data, t_vect ray_o, t_vect ray_d, double dist_to_light)
{
	t_plane		*planes;
	
	planes = data->planes;
	while (planes)
	{
		if (is_plane_hit(planes, ray_o, ray_d, &(data->t_temp)) && data->t_temp < dist_to_light)
		{
			t_vect offset_hitpoint = vector_add(ray_o, vector_scale(ray_d, data->t_temp));
			t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(planes->norm_vect, EPSILON));
			if (is_plane_hit(planes, offset_origin, ray_d, &(data->t_temp)) && data->t_temp < dist_to_light)
				return true;
		}
		planes = planes->next;
	}
	return (false);
}

bool	is_triangle_in_shadow(t_data *data, t_vect ray_o, t_vect ray_d, double dist_to_light)
{
	t_triangle	*triangles;
	
	triangles = data->triangles;
	while (triangles)
	{
		if (is_triangle_hit(triangles, ray_o, ray_d, &(data->t_temp)) && data->t_temp < dist_to_light)
		{
			t_vect offset_hitpoint = vector_add(ray_o, vector_scale(ray_d, data->t_temp));
			t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(triangles->norm_vect, EPSILON));
			if (is_triangle_hit(triangles, offset_origin, ray_d, &(data->t_temp)) && data->t_temp < dist_to_light)
				return (true);
		}
		triangles = triangles->next;
	}
	return (false);
}

bool	is_sphere_in_shadow(t_data *data, t_vect ray_o, t_vect ray_d, double dist_to_light)
{
	t_sphere	*spheres;
	
	spheres = data->spheres;
	while (spheres)
	{
		if (is_sphere_hit(spheres, ray_o, ray_d, &(data->t_temp)) && data->t_temp < dist_to_light)
			return (true);
		spheres = spheres->next;
	}
	return (false);
}

bool	is_cylinder_disk_in_shadow(t_data *data, t_vect ray_o, t_vect ray_d,
		t_cylinder *cyls)
{
	if (is_cylinder_disk_bottom_hit(cyls, ray_o, ray_d, &(data->t_temp)) && data->t_temp < data->dist_to_light)
	{
		t_vect offset_hitpoint = vector_add(ray_o, vector_scale(ray_d, data->t_temp));
		t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(cyls->norm_vect, EPSILON));
		if (is_cylinder_disk_bottom_hit(cyls, offset_origin, ray_d, &(data->t_temp)) && data->t_temp < data->dist_to_light)
			return (true);
	}
	if (is_cylinder_disk_top_hit(cyls, ray_o, ray_d, &(data->t_temp)) && data->t_temp < data->dist_to_light)
	{
		t_vect offset_hitpoint = vector_add(ray_o, vector_scale(ray_d, data->t_temp));
		t_vect offset_origin = vector_add(offset_hitpoint, vector_scale(get_opposite_normal(cyls->norm_vect), EPSILON));
		if (is_cylinder_disk_top_hit(cyls, offset_origin, ray_d, &(data->t_temp)) && data->t_temp < data->dist_to_light)
			return (true);
	}
	return (false);
	
}
bool	is_cylinder_in_shadow(t_data *data, t_vect ray_o, t_vect ray_d,
		double dist_to_light)
{
	t_cylinder	*cyls;
	
	data->dist_to_light = dist_to_light;
	cyls = data->cylinders;
	while (cyls)
	{
		if (is_cylinder_hit(cyls, ray_o, ray_d, NULL)
				&& data->t_temp < dist_to_light)
			return (true);
		if (is_cylinder_disk_in_shadow(data, ray_o, ray_d, cyls))
			return (true);
		cyls = cyls->next;
	}
	return (false);
}

bool	is_in_shadow(t_data *data, t_vect ray_o, t_vect ray_d,
		double dist_to_light)
{
	if (data->scenes.render == R_SHADED)
		return (false);
	if (is_plane_in_shadow(data, ray_o, ray_d, dist_to_light))
		return (true);
	if (is_triangle_in_shadow(data, ray_o, ray_d, dist_to_light))
		return (true);
	if (is_sphere_in_shadow(data, ray_o, ray_d, dist_to_light))
		return (true);
	if (is_cylinder_in_shadow(data, ray_o, ray_d, dist_to_light))
		return (true);
	return (false);
}