/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 18:06:32 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/15 19:55:03 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	create_win(t_vars *vars)
{
	t_data		img;

	vars->mlx = NULL;
	vars->mlx = mlx_init();
	init_img_data(&vars->img_data);
	vars->win = NULL;
	// vars->win = mlx_new_window(vars->mlx, vars->img_data->w_width,
	// 		vars->img_data->w_height, "miniRT");
	// img.img = mlx_new_image(vars->mlx, vars->img_data->w_width,
	// 		vars->img_data->w_height);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
	// 		&img.line_length, &img.endian);
	// set_start_img_colors(&img, vars);
	// mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
	// mlx_destroy_image(vars->mlx, img.img);
	// mlx_hook(vars->win, 17, 0L, win_destroy, vars);
	// mlx_loop(vars->mlx);
}
