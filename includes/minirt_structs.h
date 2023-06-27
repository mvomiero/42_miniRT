/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:53:22 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/27 19:19:07 by lde-ross         ###   ########.fr       */
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

typedef struct	s_sphere
{
	t_vect			pos;
	double			diameter;
	t_color			color;
	struct s_sphere	*next;
}			t_sphere;

typedef struct	s_plane
{
	t_vect			pos;
	t_vect			norm_vect;
	t_color			color;
	struct s_plane	*next;
}			t_plane;

typedef struct	s_cylinder
{
	t_vect				pos;
	t_vect				norm_vect;
	double				diameter;
	double				height;
	t_color				color;
	struct s_cylinder	*next;
}			t_cylinder;

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct s_window {
	void		*reference;
	t_vector	size;
}				t_window;

typedef struct s_data
{
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_plane		*plane;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	void		*mlx;
	t_window	window;
}				t_data;

#endif