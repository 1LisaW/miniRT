/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:10:22 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/13 03:09:27 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	update_render_data_translation(t_mini_rt_data *data, int sign)
{
	t_g_objects	*obj;

	obj = data->objs;
	if (data->active_obj == camera)
	{
		data->cam->coords[data->active_axis_idx] += sign * 0.2;
	}
	else if (data->active_obj == light)
	{
		data->l->coords[data->active_axis_idx] += sign * 0.2;
	}
	else if (data->active_obj == objects && obj)
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
	free_coords(data->vars->img_data);
	draw(data);
}

void	translation(int keycode, t_mini_rt_data *data)
{
	if (keycode == 65361)
		update_render_data_translation(data, -1);
	else if (keycode == 65363)
		update_render_data_translation(data, 1);
}

int	on_key_handler(int keycode, t_mini_rt_data *data)
{
	printf("\nKEY: %i\n", keycode);
	if (keycode == 65307)
		return (win_close(keycode, data));
	else if (keycode == 99)
		data->active_obj = camera;
	else if (keycode == 108)
		data->active_obj = light;
	else if (keycode == 111)
		data->active_obj = objects;
	else if (keycode >= 120 && keycode <= 122)
		data->active_axis_idx = keycode - 120;
	else if (keycode >= 65361 && keycode <= 65364)
		translation(keycode, data);
	return (0);
}

int	win_close(int keycode, t_mini_rt_data *data)
{
	t_vars	*vars;

	vars = data->vars;
	if (keycode == 65307)
	{
		destroy_win(vars);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		if (vars->mlx)
			free(vars->mlx);
		vars->mlx = NULL;
		if (vars->img)
			free(vars->img);
		vars->img = NULL;
		free_coords(vars->img_data);
		delete_mini_rt_data(data);
		data = NULL;
		exit(0);
	}
	return (0);
}

int	win_destroy(t_mini_rt_data *data)
{
	t_vars	*vars;

	vars = data->vars;
	destroy_win(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	vars->mlx = NULL;
	if (vars->img)
		free(vars->img);
	vars->img = NULL;
	free_coords(vars->img_data);
	delete_mini_rt_data(data);
	data = NULL;
	exit(0);
}
