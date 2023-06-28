/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:29:11 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/28 11:00:21 by mvomiero         ###   ########.fr       */
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
void	init(t_data *data);
void	free_tab(char **array);
void	free_structs(t_data *data);

#endif