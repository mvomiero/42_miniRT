/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-ross <lde-ross@student.42berlin.de     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:15:21 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/27 16:50:25 by lde-ross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	err_msg(char *s1, char *s2, char *s3)
{
	ft_putendl_fd("miniRT: Error", STDERR_FILENO);
	ft_putendl_fd(s1, STDERR_FILENO);
	if (s2)
		ft_putendl_fd(s2, STDERR_FILENO);
	if (s3)
		ft_putendl_fd(s3, STDERR_FILENO);
}