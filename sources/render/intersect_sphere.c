/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:15:23 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/05 18:43:48 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	get_discriminant(t_vect ray_origin, t_vect ray_direction, t_sphere *sphere)
{
	double	radius; 
	t_vect	oc; 
	double	a;
	double	b;
	double	c;
	double	discriminant;

	radius = sphere->diameter / 2;
	oc = vector_sub(ray_origin, sphere->pos);
	a = vector_dot_product(ray_direction, ray_direction);
	b = 2.0 * vector_dot_product(oc, ray_direction);
	c = vector_dot_product(oc, oc) - radius * radius;
	discriminant = b * b - 4 * a * c;
	return (discriminant);
}

bool	is_sphere_hit(t_sphere *sphere, t_vect ray_origin, t_vect ray_direction, double *t)
{
	double	discriminant;
	double	t1;

	discriminant = get_discriminant(ray_origin, ray_direction, sphere);
	if (discriminant >= 0)
	{
		t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		if (t1 > 0)
		{
			*t = t1;
			return (true);
		}
	}
	return (false);
}

void	hit_sphere(t_data *data, t_sphere *spheres, t_vect ray_origin, t_vect ray_direction)
{
	double	t;

	while (spheres)
	{
		if (is_sphere_hit(spheres, ray_origin, ray_direction, &t) && t < data->pix.t)
		{
			data->pix.t = t;
			data->pix.color = spheres->color;
			data->pix.hitpoint = vector_add(ray_origin, vector_scale(ray_direction, t));
			data->pix.normal = vector_normalize(vector_sub(data->pix.hitpoint, spheres->pos));
		}
		spheres = spheres->next;
	}
}
