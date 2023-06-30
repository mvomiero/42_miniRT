/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvomiero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:47:14 by mvomiero          #+#    #+#             */
/*   Updated: 2023/06/30 13:05:23 by mvomiero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/*int	key_event(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		close_rt(data);
		return (0);
	}
	return (0);
}*/




/*int key_event(int keycode, t_data *data)
{
	// create an instance t_data temp which is a copy of data to modify locally the files
	// create a flag variable that stores the type of the element seclected (for example sphere of plane or cylinder)
	if (keycode == KEY_ESC)
	{
		close_rt(data);
		//calling close_rt for temp as well
		return (0);
	}
	else if (keycode == KEY_S)
	{
		//i I press S, then the flag variable type is set to shpere
		// if the type is already a type sphere, iterates the list so data->spheres = data->spheres->next (if it's not NULL)
	}
	//calls an external function for the moving that accepts as parameters the type flag variable, the keycode, and a struct t_vect which is data-sphere->pos
	// the next lines moved into a moving function
	else if (keycode == KEY_DOWN)
		data->spheres->pos.y -= STEP;
	else if (keycode == KEY_UP)
		data->spheres->pos.y += STEP;
	else if (keycode == KEY_LEFT)
		data->spheres->pos.x -= STEP;
	else if (keycode == KEY_RIGHT)
		data->spheres->pos.x += STEP;
	else if (keycode == KEY_MINUS)
		data->spheres->pos.z -= STEP;
	else if (keycode == KEY_PLUS)
		data->spheres->pos.z += STEP;
	// same principle for the scaling, an external function, instead a t_vector is a float as parameter
	// the next lines moved into a scaling function
	else if (keycode == KEY_A)
		data->spheres->diameter += SCALE_FACTOR;
	else if (keycode == KEY_W)
		data->spheres->diameter -= SCALE_FACTOR;
	render(data);

	return (0);
}*/


#define STEP 2
#define SCALE_FACTOR 0.5



void move_element(int keycode, t_vect *pos)
{


		if (keycode == KEY_DOWN)
			pos->y -= STEP;
		else if (keycode == KEY_UP)
			pos->y += STEP;
		else if (keycode == KEY_LEFT)
			pos->x -= STEP;
		else if (keycode == KEY_RIGHT)
			pos->x += STEP;
		else if (keycode == KEY_MINUS)
			pos->z -= STEP;
		else if (keycode == KEY_PLUS)
			pos->z += STEP;

	// Add logic for other element types (cylinder, plane) if needed
}

void scale_element(int keycode, double *parameter)
{


		if (keycode == KEY_A)
			*parameter += SCALE_FACTOR;
		else if (keycode == KEY_W)
			*parameter -= SCALE_FACTOR;
	// Add logic for other element types (cylinder, plane) if needed
}

bool is_movement_key(int keycode)
{
	if (keycode == KEY_UP || keycode == KEY_DOWN || keycode == KEY_LEFT ||
		keycode == KEY_RIGHT || keycode == KEY_PLUS || keycode == KEY_MINUS)
		return true;
	return false;
}

bool is_scale_key(int keycode)
{
	if (keycode == KEY_A || keycode == KEY_W)
		return true;
	return false;
}

int key_event(int keycode, t_data *data)
{
	
	if (keycode == KEY_ESC)
	{
		close_rt(data);
		return (0);
	}
	else if (keycode == KEY_S || is_movement_key(keycode))
	{
		
		if (data->type == TYPE_SPHERE && data->spheres->next != NULL)
			data->spheres = data->spheres->next;
		else
			data->type = TYPE_SPHERE;
		if (is_movement_key(keycode))
			move_element(keycode, &(data->spheres->pos));
		if (is_scale_key(keycode))
			scale_element(keycode, &(data->spheres->diameter));

		// Add similar logic for other element types (cylinder, plane) if needed
	}

	render(data); // Render the scene using the modified temp data

	return (0);
}
