/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:10:22 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/16 15:59:46 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	win_close(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
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
	mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		free(vars->mlx);
	vars->mlx = NULL;
	free_coords(vars->img_data);
	exit(0);
}
