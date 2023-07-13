/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:15:06 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/13 13:30:30 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	check_cy(t_cylinder *cy, t_vect hpnt)
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

// bool is_cylinder_hit(t_cylinder *cylinder, t_vect ray_origin, t_vect ray_direction, double *t, t_data *data)
// {
// 	// Calculate the direction vector of the cylinder's axis
// 	t_vect axisDirection = cylinder->norm_vect;

// 	// Calculate the vector from the ray origin to the cylinder's position
// 	t_vect oc = vector_subtract(ray_origin, cylinder->pos);

// 	// Calculate the dot products needed for the quadratic equation
// 	double a = vector_dot_product(ray_direction, ray_direction) - pow(vector_dot_product(ray_direction, axisDirection), 2);
// 	double b = 2 * (vector_dot_product(ray_direction, oc) - vector_dot_product(ray_direction, axisDirection) * vector_dot_product(oc, axisDirection));
// 	double c = vector_dot_product(oc, oc) - pow(vector_dot_product(oc, axisDirection), 2) - pow(cylinder->diameter / 2, 2);

// 	// Solve the quadratic equation to find the intersection points
// 	double discriminant = b * b - 4 * a * c;

// 	if (discriminant >= 0)
// 	{
// 		// Calculate the solutions
// 		// Quadratic equations always have two solutions, one with -sqrt and the other with +sqrt
// 		double t1 = (-b - sqrt(discriminant)) / (2 * a);
// 		double t2 = (-b + sqrt(discriminant)) / (2 * a);

// 		// Check if the solutions are within the valid range and closer than the current closest hit
// 		// > 0 means that they are not in the ray but behind the origin
// 		if (t1 > 0 && t1 < t2)
// 		{
// 			// Calculate the y-coordinate of the intersection point
// 			t_vect hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t1));

// 			// Check if the intersection point is within the height of the cylinder
// 			if (check_cy(cylinder, hitpoint))
// 			{
// 				*t = t1;
// 				if (data)
// 				{
// 					if (t1 < data->pix.t)
// 						data->pix.normal = vector_normalize(vector_subtract(hitpoint, vector_add(cylinder->pos, vector_scale(axisDirection, vector_dot_product(vector_subtract(hitpoint, cylinder->pos), axisDirection)))));
// 				}

// 				return true;
// 			}
// 		}
// 		if (t2 > 0 && t2 < t1)
// 		{
// 			// Calculate the y-coordinate of the intersection point
// 			t_vect hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t1));

// 			// Check if the intersection point is within the height of the cylinder
// 			if (check_cy(cylinder, hitpoint))
// 			{
// 				*t = t2;
// 				if (data)
// 				{
// 					if (t2 < data->pix.t)
// 						data->pix.normal = vector_normalize(vector_subtract(hitpoint, vector_add(cylinder->pos, vector_scale(axisDirection, t2))));
// 				}
// 				return true;
// 			}
// 		}
// 		//(void)t2;
// 	}
// 	return false;
// }

bool	is_cylinder_hit(t_cylinder *cyl, t_vect ray_o,
		t_vect ray_d, t_data *data)
{
	cyl->inter.discriminant = get_cyl_discr(cyl, ray_o, ray_d);
	if (cyl->inter.discriminant >= 0)
	{
		cyl->inter.t1 = (-cyl->inter.b - sqrt(cyl->inter.discriminant))
			/ (2 * cyl->inter.a);
		cyl->inter.t2 = (-cyl->inter.b + sqrt(cyl->inter.discriminant))
			/ (2 * cyl->inter.a);
		if (cyl->inter.t1 > 0 && cyl->inter.t1 < cyl->inter.t2)
		{
			if (t1_routine(ray_o, ray_d, cyl, data))
			{
				data->t_temp = cyl->inter.t1;
				return (true);
			}
		}
		if (cyl->inter.t2 > 0 && cyl->inter.t2 < cyl->inter.t1)
		{
			if (t2_routine(ray_o, ray_d, cyl, data))
			{
				data->t_temp = cyl->inter.t2;
				return (true);
			}
		}
	}
	return (false);
}

void	cylinder_hit_set_pix(t_data *data, t_cylinder *cyls,
		t_vect ray_o, t_vect ray_d)
{
	data->no_shadows = true;
	if (is_cylinder_hit(cyls, ray_o, ray_d, data)
		&& data->t_temp < data->pix.t)
	{
		data->pix.t = data->t_temp;
		data->pix.color = cyls->color;
		data->pix.hitpoint = vector_add(ray_o,
				vector_scale(ray_d, data->t_temp));
	}
}

void	hit_cylinder(t_data *data, t_cylinder *cyls, t_vect ray_o, t_vect ray_d)
{
	while (cyls)
	{
		cylinder_hit_set_pix(data, cyls, ray_o, ray_d);
		if (is_cylinder_disk_top_hit(cyls, ray_o, ray_d, &(data->t_temp))
			&& data->t_temp < data->pix.t)
		{
			data->pix.t = data->t_temp;
			data->pix.color = cyls->color;
			data->pix.hitpoint = vector_add(ray_o,
					vector_scale(ray_d, data->t_temp));
			data->pix.normal = get_opposite_normal(cyls->norm_vect);
		}
		if (is_cylinder_disk_bottom_hit(cyls, ray_o, ray_d, &(data->t_temp))
			&& data->t_temp < data->pix.t)
		{
			data->pix.t = data->t_temp;
			data->pix.color = cyls->color;
			data->pix.hitpoint = vector_add(ray_o,
					vector_scale(ray_d, data->t_temp));
			data->pix.normal = cyls->norm_vect;
		}
		cyls = cyls->next;
	}
}
