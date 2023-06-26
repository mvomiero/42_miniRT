/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 13:29:11 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/26 17:51:26 by mvomiero         ###   ########.fr       */
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


/* ERROR */
void	err_msg(char *s1, char *s2, char *s3);

/* UTILS */
void	free_tab(char **array);



#endif