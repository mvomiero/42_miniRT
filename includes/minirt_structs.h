/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:53:22 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/04 17:38:55 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_STRUCTS_H
# define MINIRT_STRUCTS_H

# include "minirt.h"
# include <stdbool.h>


/* ELEMENTS */

typedef struct s_coord
{
	double	x;
	double	y;
}				t_coord;

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
	t_vect	norm_vect;
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

typedef struct s_pixel
{
	double			t;
	t_color			color;
	t_vect			hitpoint;
	t_vect			normal;
	t_vect			dir;
}						t_pixel;

typedef enum {
	TYPE_UNDEFINED,
	TYPE_SPHERE,
	TYPE_CYLINDER,
	TYPE_PLANE,
	TYPE_CAMERA,
	TYPE_INSTRUCTIONS
} t_type;

typedef enum {
	R_SHADED,
	R_SHADOWS
} t_render;

typedef struct s_data
{
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_plane		*planes;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_pixel		pix;
	void		*mlx;
	void		*win;
	void		*img;
	char		*buf;
	t_type		type;
	t_render	render;
	bool		instructions;
}				t_data;

#endif