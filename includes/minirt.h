/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:29:11 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/27 16:10:52 by lde-ross         ###   ########.fr       */
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
t_color	*parse_color(char *str);
t_vect	*parse_vector(char *str, bool normalized);
bool	parse_ambient(t_data *data, char **tab);
bool	parse_camera(t_data *data, char **tab);


/* ERROR */
void	err_msg(char *s1, char *s2, char *s3);

/* UTILS */
void	free_tab(char **array);



#endif