/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:06:32 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/24 23:23:13 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	create_win(t_mini_rt_data *data)
{
	t_vars		*vars;

	vars = NULL;
	vars = (t_vars *) malloc(sizeof(t_vars));
	if (!vars)
		return ;
	vars->img = NULL;
	vars->img = (t_data *) malloc(sizeof(t_data));
	if (!vars->img)
		return ;
	vars->mlx = NULL;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return ;
	init_img_data(&(vars->img_data));
	vars->win = mlx_new_window(vars->mlx, vars->img_data->w_width,
			vars->img_data->w_height, "miniRT");
	vars->img->img = mlx_new_image(vars->mlx, vars->img_data->w_width,
			vars->img_data->w_height);
	vars->img->addr = mlx_get_data_addr(vars->img->img,
			&(vars->img->bits_per_pixel),
			&(vars->img->line_length), &(vars->img->endian));
	data->vars = vars;
}

// int	draw_loop(t_mini_rt_data *data)
// {
// 	draw(data);
// 	printf("\nDRAW_LOOP %i\n", data->vars->img_data->w_width);
// 	return (0);
// }

void	destroy_win(t_vars	*vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
}

int	redraw(t_vars	*vars)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (0);
}

void	apply_img_to_win(t_mini_rt_data	*data)
{
	t_vars	*vars;

	vars = data->vars;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	mlx_hook(vars->win, 17, 0L, win_destroy, data);
	mlx_key_hook(vars->win, on_key_handler, data);
	mlx_loop_hook(vars->mlx, &redraw, vars);
	mlx_loop(vars->mlx);
}
