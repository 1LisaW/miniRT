/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:57:31 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/13 02:54:40 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// create camera rotation normalized matrix
// pecompute reusable variables

void	fill_cy_caps_coords(t_g_objects *cy)
{
	cy->mtxs->top_surf.position[0] = 0;
	cy->mtxs->top_surf.position[1] = 0;
	cy->mtxs->top_surf.position[2] = cy->height / 2;
	cy->mtxs->top_surf.direction[0] = 0;
	cy->mtxs->top_surf.direction[1] = 0;
	cy->mtxs->top_surf.direction[2] = 1;
	cy->mtxs->bot_surf.position[0] = 0;
	cy->mtxs->bot_surf.position[1] = 0;
	cy->mtxs->bot_surf.position[2] = cy->height / -2;
	cy->mtxs->bot_surf.direction[0] = 0;
	cy->mtxs->bot_surf.direction[1] = 0;
	cy->mtxs->bot_surf.direction[2] = -1;
}

void	precalc_rgb(t_g_objects *obj, int amb_int[3])
{
	obj->mtxs->amb_rgb[0] = obj->rgb[0] * amb_int[0];
	obj->mtxs->amb_rgb[1] = obj->rgb[1] * amb_int[1];
	obj->mtxs->amb_rgb[2] = obj->rgb[2] * amb_int[2];
	scale_rgb_vector(obj->rgb, 0.7, obj->mtxs->shadow_rgb);
	obj->mtxs->shadow_rgb[0] = (obj->mtxs->shadow_rgb[0]
			+ obj->mtxs->amb_rgb[0]) % 256;
	obj->mtxs->shadow_rgb[1] = (obj->mtxs->shadow_rgb[1]
			+ obj->mtxs->amb_rgb[1]) % 256;
	obj->mtxs->shadow_rgb[2] = (obj->mtxs->shadow_rgb[2]
			+ obj->mtxs->amb_rgb[2]) % 256;
}

void	precompute_cyl_data(t_g_objects	*cyl)
{
	create_cyl_mtx(cyl);
	cyl->mtxs->inv_mtx = mtx_inverse(cyl->mtxs->dir_mtx);
	fill_cy_caps_coords(cyl);
}

void	precompute_data(t_mini_rt_data *data)
{
	t_g_objects	*cyl;
	int			amb_int[3];

	scale_rgb_vector(data->a_l->rgb, (data->a_l->ratio / 255), amb_int);
	cyl = data->objs;
	create_camera_mtx(data);
	data->cam->tan_half_fov = tan((data->cam->fov / 2) * (M_PI / 180));
	while (cyl)
	{
		cyl->mtxs = malloc(sizeof(t_mtxs));
		if (cyl->id == cy)
		{
			precompute_cyl_data(cyl);
		}
		precalc_rgb(cyl, amb_int);
		cyl = cyl->next;
	}
}
