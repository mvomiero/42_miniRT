/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:53:22 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/26 16:23:00 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTS_H
# define MINIRT_STRUCTS_H

# include "minirt.h"

/* ELEMENTS */

typedef struct	s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

typedef struct	s_color
{
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct	s_ambient
{
	double	light_ratio;
	t_color	color;
}			t_ambient;

typedef struct	s_camera
{
	t_vect	pos;
	t_vect	norm_vect;
	int		fov; // field of view
}			t_camera;

typedef struct	s_light
{
	t_vect	pos;
	double	brightness;
	t_color	color;
}			t_light;


#endif