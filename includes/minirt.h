/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:29:11 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/17 11:57:15 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <X11/keysym.h>
# include <X11/X.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "minirt_structs.h"
# include "keycodes.h"
# include "Colors.h"
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

# define WIDTH 1000
# define HEIGHT 800
# define EPSILON 1e-6

# define STEP 2
# define SCALE_FACTOR 1.2
# define ROTATION_ANGLE 10
// white color for the instruction strings
# define W_INST 0xffffff

//#define MAX_DISTANCE 200

/* PARSER */
bool	parser(t_data *data, char *arg);
bool	parse_color(char *str, t_color *color);
bool	parse_vector(char *str, bool	normalized, t_vect *vect);
bool	parse_ambient(t_data *data, char **tab);
bool	parse_camera(t_data *data, char **tab);
bool	parse_light(t_data *data, char **tab);
bool	parse_sphere(t_data *data, char **tab);
bool	parse_plane(t_data *data, char **tab);
bool	parse_cylinder(t_data *data, char **tab);
bool	parse_triangle(t_data *data, char **tab);

/* ERROR */
void	err_msg(char *s1, char *s2, char *s3);

/* UTILS */
void	init_data(t_data *data);
void	init_mlx(t_data *data);
void	free_tab(char **array);
void	free_structs(t_data *data);
int		convert_rgb_to_hex(t_color *color);
void	set_pixel_color(t_data *data, int x, int y, int color);
int		clamp(int value, int min, int max);

/* RENDER */
void	render(t_data *data);
bool	is_plane_hit(t_plane *plane, t_vect ray_origin, t_vect ray_direction,
			double *t);
void	hit_plane(t_data *data, t_plane *planes, t_vect rayOrigin,
			t_vect rayDirection);
bool	is_sphere_hit(t_sphere *sphere, t_vect ray_origin, t_vect ray_direction,
			double *t);
void	hit_sphere(t_data *data, t_sphere *spheres, t_vect rayOrigin,
			t_vect rayDirection);
bool	is_cylinder_hit(t_cylinder *cylinder, t_vect ray_origin,
			t_vect ray_direction, t_data *data);
void	hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect rayOrigin,
			t_vect rayDirection);
void	hit_triangle(t_data *data, t_triangle *triangles, t_vect ray_origin,
			t_vect ray_direction);
bool	is_triangle_hit(t_triangle *triangle, t_vect ray_origin,
			t_vect ray_direction, double *t);
void	ray_tracer(t_data *data, t_coord pixel);
void	shade(t_data *data, t_coord pixel);
void	get_soft_shadow_color(t_data *data, t_light *light,
			t_pixel *pix, t_vect light_direction);
void	get_diffuse_color(t_data *data, t_light *light,
			t_pixel *pix, t_vect light_direction);
void	hit_disk_cylinder(t_data *data, t_cylinder *cylinders,
			t_vect ray_origin, t_vect ray_direction);
bool	is_cylinder_disk_top_hit(t_cylinder *cylinder, t_vect ray_origin,
			t_vect ray_direction, double *t);
bool	is_cylinder_disk_bottom_hit(t_cylinder *cylinder, t_vect ray_origin,
			t_vect ray_direction, double *t);
bool	check_cy(t_cylinder *cy, t_vect hpnt);

bool	is_in_shadow(t_data *data, t_vect ray_origin, t_vect ray_direction,
			double distance_to_light);
bool	is_cylinder_disk_in_shadow(t_data *data, t_vect ray_o, t_vect ray_d,
			t_cylinder *cyls);
void	matrix_look_at(t_data *s);
t_ray	get_ray(t_data *data, int x, int y);

// cylinder_utils_t
void	fill_normal_t1(double t1, t_data *data, t_cylinder *cyl, t_vect hp);
void	fill_normal_t2(double t2, t_data *data, t_cylinder *cyl, t_vect hp);
bool	t1_routine(t_vect ray_o, t_vect ray_d, t_cylinder *cyl, t_data *data);
bool	t2_routine(t_vect ray_o, t_vect ray_d, t_cylinder *cyl, t_data *data);

/* VECTORS */
t_vect	vector_subtract(t_vect v1, t_vect v2);
t_vect	vector_normalize(t_vect v);
t_vect	vector_add(t_vect v1, t_vect v2);
t_vect	vector_scale(t_vect v, double scalar);
double	vector_dot_product(t_vect vector1, t_vect vector2);
t_vect	vector_divide(t_vect v, double scalar);
double	vector_length(t_vect direction);
t_vect	get_opposite_normal(t_vect normal);
t_vect	move_point_along_normal(t_vect point, t_vect normal, double distance);
t_vect	vector_cross_product(t_vect v1, t_vect v2);
t_vect	vector_subtract(t_vect v1, t_vect v2);
t_vect	vector_multiply(t_vect v1, t_vect v2);
t_vect	new_vector(double x, double y, double z);

/* COLOR */
int		convert_rgb_to_hex(t_color *color);

/* CONTROLS */
int		key_event(int keycode, t_data *data);
void	transform_plane(int keycode, t_data *data, t_type *selected_type);
void	transform_sphere(int keycode, t_data *data, t_type *selected_type);
void	transform_camera(int keycode, t_data *data, t_type *selected_type);
void	transform_cylinder(int keycode, t_data *data, t_type *selected_type);
void	transform_triangle(int keycode, t_data *data, t_type *selected_type);

// utils transformation
void	rotate_element(int keycode, t_vect *norm_vect);
void	move_element(int keycode, t_vect *pos);
void	scale_element(int keycode, double *parameter);
// utils vectors
void	rotate_vector_y(double angle, t_vect *vect);
void	rotate_vector_x(double angle, t_vect *vect);
void	rotate_vector_z(double angle, t_vect *vect);
// utils keycheck
bool	is_movement_key(int keycode);
bool	is_scale_key(int keycode);
bool	is_rotation_key(int keycode);

/* EXIT */
int		close_rt(void	*param);

#endif