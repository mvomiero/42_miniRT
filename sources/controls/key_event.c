/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:47:14 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/30 11:05:22 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	key_event(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		close_rt(data);
		return (0);
	}
	return (0);
}