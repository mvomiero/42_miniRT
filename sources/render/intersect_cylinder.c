/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:15:06 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/07 15:48:48 by lde-ross         ###   ########.fr       */
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
	if (capmin < pow(cy->diameter / 2, 2)
			|| capmax < pow(cy->diameter / 2, 2))
		return (true);
	return (false);
}

static double	get_discriminat(double a, double b, t_vect	axis_direction, t_vect oc)
{
	double	discriminant;

	
}

bool	is_cylinder_hit(t_cylinder *cylinder, t_vect ray_origin, t_vect ray_direction, double *t, t_data *data)
{
	t_vect	axis_direction;
	t_vect	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t1;
	double	t2;
	t_vect	hitpoint;

	axis_direction = cylinder->norm_vect;
	oc = vector_subtract(ray_origin, cylinder->pos);
	a = vector_dot_product(ray_direction, ray_direction) - pow(vector_dot_product(ray_direction, axis_direction), 2);
	b = 2 * (vector_dot_product(ray_direction, oc) - vector_dot_product(ray_direction, axis_direction) * vector_dot_product(oc, axis_direction));
	c = vector_dot_product(oc, oc) - pow(vector_dot_product(oc, axis_direction), 2) - pow(cylinder->diameter / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant >= 0)
	{
		t1 = (-b - sqrt(discriminant)) / (2 * a);
		t2 = (-b + sqrt(discriminant)) / (2 * a);
		if (t1 > 0 && t1 < t2)
		{
			hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t1));
			if (check_cy(cylinder, hitpoint))
			{
				*t = t1;
				if (data)
				{
					if (t1 < data->pix.t)
						data->pix.normal = vector_normalize(vector_subtract(hitpoint, vector_add(cylinder->pos, vector_scale(axis_direction, vector_dot_product(vector_subtract(hitpoint, cylinder->pos), axis_direction)))));
				}
				return (true);
			}
		}
		if (t2 > 0 && t2 < t1)
		{
			hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t1));
			if (check_cy(cylinder, hitpoint))
			{
				*t = t2;
				if (data)
				{
					if (t2 < data->pix.t)
						data->pix.normal = vector_normalize(vector_subtract(hitpoint, vector_add(cylinder->pos, vector_scale(axis_direction, t2))));
				}
				return (true);
			}
		}
	}
	return (false);
}

void	hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect ray_origin, t_vect ray_direction)
{
	double	t;

	while (cylinders)
	{
		if (is_cylinder_hit(cylinders, ray_origin, ray_direction, &t, data) && t < data->pix.t)
		{
			data->pix.t = t;
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
