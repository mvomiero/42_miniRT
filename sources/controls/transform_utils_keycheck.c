/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils_keycheck.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 12:57:45 by mvomiero          #+#    #+#             */
/*   Updated: 2023/07/03 13:00:12 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool is_movement_key(int keycode)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT ||
		keycode == KEY_RIGHT || keycode == KEY_PAGE_UP || keycode == KEY_PAGE_DOWN)
		return true;
	return false;
}

bool is_scale_key(int keycode)
{
	if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		return true;
	return false;
}

bool is_rotation_key(int keycode)
{
	if (keycode == KEY_H || keycode == KEY_J || keycode == KEY_U ||
		keycode == KEY_N || keycode == KEY_Y || keycode == KEY_M)
		return true;
	return false;
}