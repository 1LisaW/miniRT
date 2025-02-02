/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_events.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:24:15 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/27 17:12:48 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	rotate_normal(float *normal, int sign, int active_axis_idx)
{
	float	sin_10;
	float	cos_10;
	float	new_norm[3];

	sin_10 = sin(sign * 5 * M_PI / 180);
	cos_10 = cos(sign * 5 * M_PI / 180);
	copy_f_vector(normal, new_norm);
	if (active_axis_idx == 0)
	{
		new_norm[1] = normal[1] * cos_10 - normal[2] * sin_10;
		new_norm[2] = normal[1] * sin_10 + normal[2] * cos_10;
	}
	else if (active_axis_idx == 1)
	{
		new_norm[0] = normal[0] * cos_10 + normal[2] * sin_10;
		new_norm[2] = -1 * normal[0] * sin_10 + normal[2] * cos_10;
	}
	else
	{
		new_norm[0] = normal[0] * cos_10 - normal[1] * sin_10;
		new_norm[1] = normal[0] * sin_10 + normal[1] * cos_10;
	}
	normalize_vect(new_norm);
	copy_f_vector(new_norm, normal);
}

void	update_render_data_rotation(t_mini_rt_data *data, int sign)
{
	t_g_objects	*obj;

	obj = data->objs;
	if (data->active_obj == light)
		return ;
	if (data->active_obj == objects)
	{
		while (obj)
		{
			if (obj->id != sp)
				rotate_normal(obj->v_3d_normal, sign, data->active_axis_idx);
			if (obj->id == cy)
				precompute_cyl_data(obj);
			obj = obj->next;
		}
	}
	else if (data->active_obj == camera)
	{
		free(data->cam->mtx);
		data->cam->mtx = NULL;
		create_camera_mtx(data);
		rotate_normal(data->cam->v_3d_orient, sign, data->active_axis_idx);
	}
	draw(data);
}

void	update_render_data_translation(t_mini_rt_data *data, int sign)
{
	t_g_objects	*obj;

	obj = data->objs;
	if (data->cam && data->active_obj == camera)
	{
		data->cam->coords[data->active_axis_idx] += sign * 0.2;
	}
	else if (data->l && data->active_obj == light)
	{
		check_light_in(data);
		data->l->coords[data->active_axis_idx] += sign * 0.2;
	}
	else if (obj && data->active_obj == objects)
	{
		while (obj)
		{
			obj->coords[data->active_axis_idx] += sign * 0.2;
			if (obj->id == cy)
				precompute_cyl_data(obj);
			obj = obj->next;
		}
	}
	else
		return ;
	draw(data);
}

void	translation(int keycode, t_mini_rt_data *data)
{
	if (keycode == 65361)
		update_render_data_translation(data, -1);
	else if (keycode == 65363)
		update_render_data_translation(data, 1);
	else if (keycode == 65362)
		update_render_data_rotation(data, 1);
	else if (keycode == 65364)
		update_render_data_rotation(data, -1);
}
