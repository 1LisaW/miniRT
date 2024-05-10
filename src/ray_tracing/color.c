/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 23:17:24 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/10 18:40:43 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

void	compute_color(int *hex_color, t_closest_obj *cl_obj)
{
	int		rgb[3];
	float	ratio;
	float	rev_l_vect[3];

	ratio = 0;
	scale_vector(cl_obj->light_ray.direction, -1, rev_l_vect);
	copy_i_vector(cl_obj->obj->rgb, rgb);
	if (!cl_obj->in_light)
		*hex_color = rgb_to_hex(cl_obj->obj->mtxs->shadow_rgb[0],
				cl_obj->obj->mtxs->shadow_rgb[1],
				cl_obj->obj->mtxs->shadow_rgb[2]);
	else
	{
		ratio = ft_abs_f(get_dot_product(cl_obj->normal, rev_l_vect));
		rgb[0] = (int) fmin(255, (rgb[0] + cl_obj->obj->rgb[0] * ratio));
		rgb[1] = (int) fmin(255, (rgb[1] + cl_obj->obj->rgb[1] * ratio));
		rgb[2] = (int) fmin(255, (rgb[2] + cl_obj->obj->rgb[2] * ratio));
		*hex_color = rgb_to_hex(rgb[0], rgb[1], rgb[2]);
	}
}
