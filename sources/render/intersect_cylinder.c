/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:15:06 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/07 17:24:57 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	check_cy(t_cylinder *cy, t_vect hpnt)
{
	double	capmin;
	double	capmax;
	t_vect	hpnt_pmin;
	t_vect	hpnt_pmax;

	hpnt_pmin = vector_subtract(hpnt, vector_add(cy->pos,
				vector_scale(cy->norm_vect, -0.5 * cy->height)));
	hpnt_pmax = vector_subtract(hpnt,
			vector_add(cy->pos, vector_scale(cy->norm_vect, 0.5 * cy->height)));
	capmin = vector_dot_product(hpnt_pmin, hpnt_pmin);
	capmax = vector_dot_product(hpnt_pmax, hpnt_pmax);
	if (vector_dot_product(cy->norm_vect, hpnt_pmin) > 0
		&& vector_dot_product(cy->norm_vect, hpnt_pmax) < 0)
		return (true);
	if (capmin < pow(cy->diameter / 2, 2) || capmax < pow(cy->diameter / 2, 2))
		return (true);
	return (false);
}

static double	get_cyl_discr(t_cylinder *cyl, t_vect ray_o, t_vect ray_d)
{
	cyl->inter.oc = vector_subtract(ray_o, cyl->pos);
	cyl->inter.a = vector_dot_product(ray_d, ray_d)
		- pow(vector_dot_product(ray_d, cyl->norm_vect), 2);
	cyl->inter.b = 2 * (vector_dot_product(ray_d, cyl->inter.oc)
			- vector_dot_product(ray_d, cyl->norm_vect)
			* vector_dot_product(cyl->inter.oc, cyl->norm_vect));
	cyl->inter.c = vector_dot_product(cyl->inter.oc, cyl->inter.oc)
		- pow(vector_dot_product(cyl->inter.oc, cyl->norm_vect), 2)
		- pow(cyl->diameter / 2, 2);
	return (cyl->inter.b * cyl->inter.b - 4 * cyl->inter.a * cyl->inter.c);
}

static void	fill_normal_t1(double t1, t_data *data, t_cylinder *cyl, t_vect hp)
{
	if (data)
	{
		if (t1 < data->pix.t)
			data->pix.normal = vector_normalize(
					vector_subtract(hp,
						vector_add(cyl->pos,
							vector_scale(cyl->norm_vect,
								vector_dot_product(
									vector_subtract(hp, cyl->pos),
									cyl->norm_vect)))));
	}
}

static void	fill_normal_t2(double t2, t_data *data, t_cylinder *cyl, t_vect hp)
{
	if (data)
	{
		if (t2 < data->pix.t)
			data->pix.normal = vector_normalize(
					vector_subtract(hp,
						vector_add(cyl->pos,
							vector_scale(cyl->norm_vect, t2))));
	}
}

bool	t1_routine(t_vect ray_o, t_vect ray_d, t_cylinder *cyl, t_data *data)
{
	t_vect	hitpoint;

	hitpoint = vector_add(ray_o, vector_scale(ray_d, cyl->inter.t1));
	if (check_cy(cyl, hitpoint))
	{
		fill_normal_t1(cyl->inter.t1, data, cyl, hitpoint);
		return (true);
	}
	return (false);
}

bool	t2_routine(t_vect ray_o, t_vect ray_d, t_cylinder *cyl, t_data *data)
{
	t_vect	hitpoint;

	hitpoint = vector_add(ray_o, vector_scale(ray_d, cyl->inter.t1));
	if (check_cy(cyl, hitpoint))
	{
		fill_normal_t2(cyl->inter.t2, data, cyl, hitpoint);
		return (true);
	}
	return (false);
}

bool	is_cylinder_hit(t_cylinder *cyl, t_vect ray_o, t_vect ray_d, t_data *data)
{
	cyl->inter.discriminant = get_cyl_discr(cyl, ray_o, ray_d);
	if (cyl->inter.discriminant >= 0)
	{
		cyl->inter.t1 = (-cyl->inter.b - sqrt(cyl->inter.discriminant)) / (2 * cyl->inter.a);
		cyl->inter.t2 = (-cyl->inter.b + sqrt(cyl->inter.discriminant)) / (2 * cyl->inter.a);
		if (cyl->inter.t1 > 0 && cyl->inter.t1 < cyl->inter.t2)
		{
			if (t1_routine(ray_o, ray_d, cyl, data))
			{
				cyl->inter.t = cyl->inter.t1;
				return (true);
			}
		}
		if (cyl->inter.t2 > 0 && cyl->inter.t2 < cyl->inter.t1)
		{
			if (t2_routine(ray_o, ray_d, cyl, data))
			{
				cyl->inter.t = cyl->inter.t2;
				return (true);
			}
		}
	}
	return (false);
}

void hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect ray_origin, t_vect ray_direction)
{
	while (cylinders)
	{
		if (is_cylinder_hit(cylinders, ray_origin, ray_direction, data) && cylinders->inter.t < data->pix.t)
		{
			data->pix.t = cylinders->inter.t;
			data->pix.color = cylinders->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
		}
		if (is_cylinder_disk_top_hit(cylinders, ray_origin, ray_direction, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = cylinders->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			data->pix.normal = get_opposite_normal(cylinders->norm_vect);
		}
		if (is_cylinder_disk_bottom_hit(cylinders, ray_origin, ray_direction, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = cylinders->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			data->pix.normal = cylinders->norm_vect;
		}
		cylinders = cylinders->next;
	}
}