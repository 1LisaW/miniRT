/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_start_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 15:19:02 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/10 16:28:37 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	custom_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fill_color(t_data *img, t_img_data *img_data, int x, int y)
{
	img_data->colors_data[y][x] = 0x87ceeb;
	custom_mlx_pixel_put(img, x, y,
		0x87ceeb);
}

void	free_coords(t_img_data *img_data)
{
	int	i;

	i = 0;
	if (!img_data)
		return ;
	if (img_data->colors_data)
	{
		while (img_data->colors_data && i < img_data->w_height
			&& img_data->colors_data[i])
		{
			free(img_data->colors_data[i]);
			i++;
		}
		free(img_data->colors_data);
	}
	free(img_data);
}

void	fill_start_img_colors(t_data *img, t_img_data *img_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < img_data->w_height)
	{
		j = 0;
		while (j < img_data->w_width)
		{
			fill_color(img, img_data, j, i);
			j++;
		}
		i++;
	}
}

void	set_start_img_colors(t_data *img, t_vars *vars)
{
	int	i;

	i = 0;
	vars->img_data->colors_data = malloc((vars->img_data->w_height)
			* sizeof(int *));
	if (!vars->img_data->colors_data)
		return ;
	while (i < vars->img_data->w_height)
	{
		vars->img_data->colors_data[i] = NULL;
		vars->img_data->colors_data[i] = malloc(vars->img_data->w_width
				* sizeof(int));
		if (!vars->img_data->colors_data[i])
			break ;
		i++;
	}
	fill_start_img_colors(img, vars->img_data);
}
