/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport_renderer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 13:50:51 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/23 11:09:10 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Function used to move the pointed at pixel in the viewport and get the new
// coordinates. Pass 'v' for vertical movement and 'h' for horizontal
void	move_pixel(t_vp *vp, float *pix, char d)
{
	float	new[3];

	if (d == 'v')
	{
		copy_f_vector(vp->pixel_delta_vertical, new);
	}
	else if (d == 'h')
	{
		copy_f_vector(vp->pixel_delta_horizontal, new);
	}
	else
	{
		printf("move_pixel: wrong movement direction\n");
		return ;
	}
	vector_add(pix, new, new);
	copy_f_vector(new, pix);
}

void	reset_horizontal(t_vp *vp, float *pix, int x)
{
	float	new[3];

	scale_vector(vp->pixel_delta_horizontal, x, new);
	vector_subtract(pix, new, pix);
}

void	render_viewport(t_mini_rt_data *data)
{
	float	curr[3];
	int		y;
	int		x;

	copy_f_vector(data->img_data->vp.vp_pixel00, curr);
	y = 0;
	while (y < data->img_data->w_height - 1)
	{
		x = 0;
		move_pixel(&data->img_data->vp, curr, 'v');
		while (x < data->img_data->w_width)
		{
			trace_ray(data, curr);
			move_pixel(&data->img_data->vp, curr, 'h');
			x++;
		}
		reset_horizontal(&data->img_data->vp, curr, x);
		y++;
	}
}
