/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:29:11 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/28 17:39:51 by lde-ross         ###   ########.fr       */
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


/* RENDER */
void	render(t_data *data);
bool hit_sphere(t_vect center, double radius, t_vect rayOrigin, t_vect rayDirection);
bool hit_plane(t_plane *plane, t_vect rayOrigin, t_vect rayDirection);

bool rayIntersectsSphere(t_vect rayOrigin, t_vect rayDirection, t_sphere sphere);
bool rayIntersectsSphere2(t_camera camera, t_sphere sphere);



#endif