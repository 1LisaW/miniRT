/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sd_selector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:10:21 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/22 00:44:17 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Applies the proper SDF function depending on objets' type and returns
// SDF from curr_pt to object.
// Returns float max if no match.
float	sd_selector(float *curr_pt, t_mini_rt_data *data, t_g_objects object)
{
	float	cam_pos[3];
	float	vector_to_plane[3];

	copy_f_vector(data->cam->coords, cam_pos);
	vector_subtract(object.coords, curr_pt, vector_to_plane);
	if (object.id == pl)
	{
		return (get_dot_product(vector_to_plane, data->objs->v_3d_normal));
	}
	return (FLT_MAX);
}
