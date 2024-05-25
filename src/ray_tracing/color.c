/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 23:17:24 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/26 00:48:21 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

// int	get_ambient_color(int *hex_color, t_closest_obj *cl_obj,
// 			t_mini_rt_data *data)
// {

// }

void	compute_color(int *hex_color, t_closest_obj *cl_obj,
			t_mini_rt_data *data)
{
	int		rgb[3];
	float	rev_l_vect[3];
	float	bright_ratio;

	bright_ratio = 0;
	scale_vector(cl_obj->light_ray.direction, -1, rev_l_vect);
	copy_i_vector(cl_obj->obj->rgb, rgb);
	if (data->light_on == false || !cl_obj->in_light)
		*hex_color = rgb_to_hex(cl_obj->obj->mtxs->amb_rgb[0],
				cl_obj->obj->mtxs->amb_rgb[1],
				cl_obj->obj->mtxs->amb_rgb[2]);
	else
	{
		bright_ratio = ft_abs_f(get_dot_product(cl_obj->normal, rev_l_vect))
			* data->l->l_brightness;
		rgb[0] = (int) fmin(255, (cl_obj->obj->mtxs->amb_rgb[0] + bright_ratio
					* cl_obj->obj->rgb[0] * data->l->rgb[0] / 255));
		rgb[1] = (int) fmin(255, (cl_obj->obj->mtxs->amb_rgb[1] + bright_ratio
					* cl_obj->obj->rgb[1] * (data->l->rgb[1] / 255)));
		rgb[2] = (int) fmin(255, (cl_obj->obj->mtxs->amb_rgb[2] + bright_ratio
					* cl_obj->obj->rgb[2] * (data->l->rgb[2] / 255)));
		*hex_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
	}
}
