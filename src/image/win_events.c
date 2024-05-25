/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:10:22 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/26 00:56:36 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	on_key_handler(int keycode, t_mini_rt_data *data)
{
	if (keycode == 65307)
		return (win_close(keycode, data));
	else if (!data->cam)
		return (0);
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
	delete_mini_rt_data(data);
	data = NULL;
	exit(0);
}
