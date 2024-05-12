/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:10:22 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/12 00:47:27 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	win_close(int keycode, t_vars *vars)
{
	printf("\nKEY: %i\n", keycode);
	if (keycode == 65307)
	{
		destroy_win(vars);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		if (vars->mlx)
			free(vars->mlx);
		vars->mlx = NULL;
		free_coords(vars->img_data);
		exit(0);
	}
	return (0);
}

int	win_destroy(t_vars *vars)
{
	destroy_win(vars);
	mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	vars->mlx = NULL;
	free_coords(vars->img_data);
	exit(0);
}

int	win_resize(t_vars *vars)
{
	int	w;
	int	h;

	mlx_get_screen_size(vars->mlx, &w, &h);
	if (w > 0)
		vars->img_data->w_width = w;
	else
		vars->img_data->w_width = 1;
	if (h > 0)
		vars->img_data->w_height = h;
	else
		vars->img_data->w_height = 1;
	return (0);
}
