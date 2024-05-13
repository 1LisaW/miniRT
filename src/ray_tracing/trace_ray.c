/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:53:56 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/05/06 12:34:34 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	custom_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	normalize_vect(float *vector)
{
	float	len;
	float	inverted_len;

	len = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
	if (len > 0)
	{
		inverted_len = 1.0 / len;
		vector[0] *= inverted_len;
		vector[1] *= inverted_len;
		vector[2] *= inverted_len;
	}
}

t_ray	calc_ray(t_mini_rt_data *data, int x, int y)
{
	t_ray	ray;
	float	tmp[3];

	tmp[0] = 0;
	tmp[1] = 0;
	tmp[2] = 0;
	copy_f_vector(data->cam->coords, ray.position);
	ray.direction[0] = (2 * ((x + 0.5) / data->vars->img_data->w_width) - 1)
		* ((float)data->vars->img_data->w_width
			/ data->vars->img_data->w_height) * data->cam->tan_half_fov;
	ray.direction[1] = (1 - 2 * ((y + 0.5) / data->vars->img_data->w_height))
		* data->cam->tan_half_fov;
	ray.direction[2] = 1;
	vector_mtx_multy(ray.direction, data->cam->mtx, tmp);
	copy_f_vector(tmp, ray.direction);
	normalize_vect(ray.direction);
	return (ray);
}

void	ray_trace_cp(t_mini_rt_data *data, t_img_data *img_data, int x, int y)
{
	t_ray			ray;
	t_closest_obj	cl_obj;

	ray = calc_ray(data, x, y);
	cl_obj = get_closest_obj(data, ray);
	if (cl_obj.dist < FLT_MAX)
	{
		cl_obj.in_light = check_if_in_light(data, cl_obj);
		if (cl_obj.in_light == false)
		{
			img_data->colors_data[y][x] = 0x000000;
		}
		else
		{
			img_data->colors_data[y][x] = rgb_to_hex(cl_obj.obj->rgb[0],
					cl_obj.obj->rgb[1], cl_obj.obj->rgb[2]);
		}
	}
	else
		img_data->colors_data[y][x] = 0x87CEEB;
	custom_mlx_pixel_put(data->vars->img, x, y,
		img_data->colors_data[y][x]);
}

void	draw(t_mini_rt_data *data)
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
			ray_trace_cp(data, data->vars->img_data, i, j);
			i++;
		}
		j++;
		i = 0;
	}
}
