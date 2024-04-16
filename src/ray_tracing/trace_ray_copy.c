/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:53:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/16 16:01:44 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// void	trace_ray(t_mini_rt_data *data, float *vp_coords)
// {
// }

int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	ray_trace_cp(t_data *img, t_img_data *img_data, int x, int y)
{
	img_data->colors_data[y][x] = rgb_to_hex((int)((256 * x)/img_data->w_width),
			(int)((256 * y) / img_data->w_height), 0);
	custom_mlx_pixel_put(img, x, y,
		img_data->colors_data[y][x]);
}

void	draw(t_mini_rt_data *data, t_data *img)
{
	int		i;
	int		j;

	i = 0;
	j = 0;

	data->vars->img_data->colors_data = malloc((data->vars->img_data->w_height)
			* sizeof(int *));
	if (!data->vars->img_data->colors_data)
		return ;
	while (j < data->vars->img_data->w_height)
	{
		data->vars->img_data->colors_data[j] = NULL;
		data->vars->img_data->colors_data[j]
			= malloc(data->vars->img_data->w_width * sizeof(int));
		if (!data->vars->img_data->colors_data[j])
			break ;
		while (i < data->vars->img_data->w_width)
		{
			ray_trace_cp(img, data->vars->img_data, i, j);
			i++;
		}
		j++;
		i = 0;
	}
}
