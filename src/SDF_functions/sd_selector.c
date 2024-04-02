/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sd_selector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:10:21 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/02 18:48:30 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Applies the proper SDF function depending on objets' type and returns
// SDF from curr_pt to object.
// Returns float max if no match.
float	sd_selector(float *curr_pt, t_mini_rt_data *data, t_g_objects object)
{
	float	cam_pos[3];
	float	obj_dist;

	copy_f_vector(data->cam->coords, cam_pos);
	if (object.id == pl)
	{
		obj_dist = get_vector_length(cam_pos, data->objs->coords);
		return (sd_plane(curr_pt, data->objs->v_3d_normal, obj_dist, cam_pos));
	}
	return (FLT_MAX);
}
