/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:29:31 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/07 16:34:12 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool	is_triangle_hit(t_triangle *tri, t_vect ray_origin,
		t_vect ray_dir, double *t)
{
	tri->inter.edge1 = vector_subtract(tri->v2, tri->v1);
	tri->inter.edge2 = vector_subtract(tri->v3, tri->v1);
	tri->inter.h = vector_cross_product(ray_dir, tri->inter.edge2);
	tri->inter.a = vector_dot_product(tri->inter.edge1, tri->inter.h);
	if (fabs(tri->inter.a) < EPSILON)
		return false;
	tri->inter.f = 1.0 / tri->inter.a;
	tri->inter.s = vector_subtract(ray_origin, tri->v1);
	tri->inter.u = tri->inter.f * vector_dot_product(tri->inter.s, tri->inter.h);
	if (tri->inter.u < 0.0 || tri->inter.u > 1.0)
		return false;
	tri->inter.q = vector_cross_product(tri->inter.s, tri->inter.edge1);
	tri->inter.v = tri->inter.f * vector_dot_product(ray_dir, tri->inter.q);
	if (tri->inter.v < 0.0 || tri->inter.u + tri->inter.v > 1.0)
		return false;
	*t = tri->inter.f * vector_dot_product(tri->inter.edge2, tri->inter.q);
	if (*t > 0.0) {
		if (tri->inter.a > 0.0)
			return (true);
		else
			return (false);
	}
	return (false);
}