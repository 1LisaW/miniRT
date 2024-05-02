/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precompute_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:57:31 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/02 00:58:50 by tklimova         ###   ########.fr       */
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

void	precompute_data(t_mini_rt_data *data)
{
	t_g_objects	*cyl;

	cyl = data->objs;
	create_camera_mtx(data);
	data->cam->tan_half_fov = tan((data->cam->fov / 2) * (M_PI / 180));
	while (cyl)
	{
		if (cyl->id == cy)
		{
			cyl->mtxs = malloc(sizeof(t_mtxs));
			create_cyl_mtx(cyl);
			cyl->mtxs->inv_mtx = mtx_inverse(cyl->mtxs->dir_mtx);
			fill_cy_caps_coords(cyl);
		}
		cyl = cyl->next;
	}
}
