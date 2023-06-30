/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:29:11 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/30 16:41:45 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <X11/keysym.h> 		
# include <X11/X.h>
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "minirt_structs.h"
# include "Colors.h"
# include <stdio.h>
# include <math.h>
# include <stdbool.h>

# define WIDTH 1250
# define HEIGHT 900
#define EPSILON 1e-6



/* PARSER */
bool parser(t_data *data, char *arg);
bool	parse_color(char *str, t_color *color);
bool	parse_vector(char *str, bool normalized, t_vect *vect);
bool	parse_ambient(t_data *data, char **tab);
bool	parse_camera(t_data *data, char **tab);
bool	parse_light(t_data *data, char **tab);
bool	parse_sphere(t_data *data, char **tab);
bool	parse_plane(t_data *data, char **tab);
bool	parse_cylinder(t_data *data, char **tab);


/* ERROR */
void	err_msg(char *s1, char *s2, char *s3);

/* UTILS */
void	init_data(t_data *data);
void	init_mlx(t_data *data);
void	free_tab(char **array);
void	free_structs(t_data *data);
int convert_rgb_to_hex(t_color *color);
void set_pixel_color(t_data *data, int x, int y, int color);

/* RENDER */
void	render(t_data *data);
//bool hit_sphere(t_vect center, double radius, t_vect rayOrigin, t_vect rayDirection);
void hit_plane(t_data *data, t_plane *planes, t_vect rayOrigin, t_vect rayDirection);
void hit_sphere(t_data *data, t_sphere *spheres, t_vect rayOrigin, t_vect rayDirection);
void hit_cylinder(t_data *data, t_cylinder *cylinders, t_vect rayOrigin, t_vect rayDirection);
void ray_tracer(t_data *data, t_coord pixel);
void shade(t_data *data, t_coord pixel);


/* VECTORS */
t_vect vector_substract(t_vect v1, t_vect v2);
t_vect vector_normalize(t_vect v);
t_vect vector_add(t_vect v1, t_vect v2);
t_vect vector_scale(t_vect v, double scalar);
double vector_dot_product(t_vect vector1, t_vect vector2);
t_vect vector_divide(t_vect v, double scalar);
double vector_length(t_vect direction);






bool rayIntersectsSphere(t_vect rayOrigin, t_vect rayDirection, t_sphere sphere);
bool rayIntersectsSphere2(t_camera camera, t_sphere sphere);





#endif