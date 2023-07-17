/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_structs.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:53:22 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/17 11:23:34 by mvomiero         ###   ########.fr       */
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

typedef struct s_vect
{
	double	x;
	double	y;
	double	z;
}				t_vect;

typedef struct s_ray
{
	t_vect	origin;
	t_vect	direction;	
}				t_ray;

typedef struct s_matrix
{
	double	d[4][4];
}				t_matrix;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}				t_color;

typedef struct s_shadow
{
	t_vect	target;
	t_vect	direction;
	double	intensity;
	double	pixel_size; 
	double	offset_x;
	double	distance_to_light;
	double	light_dot_product;
	double	ambient_dot_product;
}			t_shadow;

typedef struct s_ambient
{
	double	light_ratio;
	t_color	color;
	t_vect	norm_vect;
}			t_ambient;

typedef struct s_camera
{
	t_vect		pos;
	t_vect		norm_vect;
	int			fov;
	t_matrix	m;
}			t_camera;

typedef struct s_light
{
	t_vect	pos;
	double	brightness;
	t_color	color;
}			t_light;

typedef struct s_sphere
{
	t_vect			pos;
	double			diameter;
	t_color			color;
	struct s_sphere	*next;
}			t_sphere;

typedef struct s_plane
{
	t_vect			pos;
	t_vect			norm_vect;
	t_color			color;
	struct s_plane	*next;
}			t_plane;

typedef struct s_inter_cylinder
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vect	oc;
	double	t1;
	double	t2;
	double	t;
}				t_inter_cylinder;

typedef struct s_cylinder
{
	t_vect				pos;
	t_vect				norm_vect;
	double				diameter;
	double				height;
	t_color				color;
	struct s_cylinder	*next;
	t_inter_cylinder	inter;
}			t_cylinder;

typedef struct s_pixel
{
	double			t;
	t_color			color;
	t_vect			hitpoint;
	t_vect			normal;
	t_vect			dir;
	t_vect			light_dir;
}						t_pixel;

typedef struct s_inter_triangle
{
	t_vect	edge1;
	t_vect	edge2;
	t_vect	h;
	t_vect	s;
	t_vect	q;
	double	a;
	double	f;
	double	u;
	double	v;
}				t_inter_triangle;

typedef struct s_triangle
{
	t_vect				v1;
	t_vect				v2;
	t_vect				v3;
	t_color				color;
	t_vect				norm_vect;
	struct s_triangle	*next;
	t_inter_triangle	inter;
}	t_triangle;

typedef enum s_type {
	TYPE_UNDEFINED,
	TYPE_SPHERE,
	TYPE_CYLINDER,
	TYPE_PLANE,
	TYPE_CAMERA,
	TYPE_INSTRUCTIONS,
	TYPE_TRIANGLE
}	t_type;

typedef enum s_render {
	R_SHADED,
	R_SHADOWS,
	R_SOFT_SHADOWS
}	t_render;

typedef struct s_scenes
{
	t_render	render;
	int			n_rays;
}	t_scenes;

typedef struct s_data
{
	t_sphere	*spheres;
	t_cylinder	*cylinders;
	t_triangle	*triangles;
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
	t_scenes	scenes;
	bool		instructions;
	double		t_temp;
	double		dist_to_light;
	bool		no_shadows;
}				t_data;

#endif