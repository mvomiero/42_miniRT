/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_viewport_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:59:57 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/17 11:06:58 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*void	matrix_look_at(t_data *s)
{
	t_vect		random;
	t_vect		right;
	t_vect		up;

	random = new_vector(0, 1, 0);
	right = vector_cross_product(random, s->camera->norm_vect);
	right = vector_normalize(right);
	up = vector_cross_product(s->camera->norm_vect, right);
	up = vector_normalize(up);

	if (vector_length(up) == 0) {
		random = new_vector(0, 0, 1);
		right = vector_cross_product(random, s->camera->norm_vect);
		right = vector_normalize(right);
		up = vector_cross_product(s->camera->norm_vect, right);
	}
	s->camera->m.d[0][0] = right.x;
	s->camera->m.d[0][1] = right.y;
	s->camera->m.d[0][2] = right.z;
	s->camera->m.d[0][3] = 0;
	s->camera->m.d[1][0] = up.x;
	s->camera->m.d[1][1] = up.y;
	s->camera->m.d[1][2] = up.z;
	s->camera->m.d[1][3] = 0;
	s->camera->m.d[2][0] = s->camera->norm_vect.x;
	s->camera->m.d[2][1] = s->camera->norm_vect.y;
	s->camera->m.d[2][2] = s->camera->norm_vect.z;
	s->camera->m.d[2][3] = 0;
	s->camera->m.d[3][0] = s->camera->pos.x;
	s->camera->m.d[3][1] = s->camera->pos.y;
	s->camera->m.d[3][2] = s->camera->pos.z;
	s->camera->m.d[3][3] = 1;
}*/

void	calculate_camera_vectors(t_data *s, t_vect *right, t_vect *up)
{
	t_vect	random;

	random = new_vector(0, 1, 0);
	*right = vector_cross_product(random, s->camera->norm_vect);
	*right = vector_normalize(*right);
	*up = vector_cross_product(s->camera->norm_vect, *right);
	*up = vector_normalize(*up);
	if (vector_length(*up) == 0)
	{
		random = new_vector(0, 0, 1);
		*right = vector_cross_product(random, s->camera->norm_vect);
		*right = vector_normalize(*right);
		*up = vector_cross_product(s->camera->norm_vect, *right);
	}
}

void	matrix_look_at(t_data *s)
{
	t_vect	right;
	t_vect	up;

	calculate_camera_vectors(s, &right, &up);
	s->camera->m.d[0][0] = right.x;
	s->camera->m.d[0][1] = right.y;
	s->camera->m.d[0][2] = right.z;
	s->camera->m.d[0][3] = 0;
	s->camera->m.d[1][0] = up.x;
	s->camera->m.d[1][1] = up.y;
	s->camera->m.d[1][2] = up.z;
	s->camera->m.d[1][3] = 0;
	s->camera->m.d[2][0] = s->camera->norm_vect.x;
	s->camera->m.d[2][1] = s->camera->norm_vect.y;
	s->camera->m.d[2][2] = s->camera->norm_vect.z;
	s->camera->m.d[2][3] = 0;
	s->camera->m.d[3][0] = s->camera->pos.x;
	s->camera->m.d[3][1] = s->camera->pos.y;
	s->camera->m.d[3][2] = s->camera->pos.z;
	s->camera->m.d[3][3] = 1;
}
