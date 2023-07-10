/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_is_in_shadow_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:11:13 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/10 15:17:31 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	is_cylinder_disk_in_shadow(t_data *data, t_vect ray_o, t_vect ray_d,
		t_cylinder *cyls)
{
	t_vect	offset_hitpoint;
	t_vect	offset_origin;

	if (is_cylinder_disk_bottom_hit(cyls, ray_o, ray_d, &(data->t_temp))
		&& data->t_temp < data->dist_to_light)
	{
		offset_hitpoint = vector_add(ray_o, vector_scale(ray_d, data->t_temp));
		offset_origin = vector_add(offset_hitpoint,
				vector_scale(cyls->norm_vect, EPSILON));
		if (is_cylinder_disk_bottom_hit(cyls, offset_origin, ray_d,
				&(data->t_temp)) && data->t_temp < data->dist_to_light)
			return (true);
	}
	if (is_cylinder_disk_top_hit(cyls, ray_o, ray_d, &(data->t_temp))
		&& data->t_temp < data->dist_to_light)
	{
		offset_hitpoint = vector_add(ray_o, vector_scale(ray_d, data->t_temp));
		offset_origin = vector_add(offset_hitpoint,
				vector_scale(get_opposite_normal(cyls->norm_vect), EPSILON));
		if (is_cylinder_disk_top_hit(cyls, offset_origin, ray_d,
				&(data->t_temp)) && data->t_temp < data->dist_to_light)
			return (true);
	}
	return (false);
}
