/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_viewport.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:48:25 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/11 20:37:19 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Calculates the legth of the side AC (see set_viewport), which corresponds
// to the distance from the camera to the center of the viewport.
float	get_dist_to_vp(t_mini_rt_data *data)
{
	return (((float)data->img_data->w_width / 2)
		* (cos(((float)data->cam->fov / 2))));
}

// Assuming a triangle ABC, where A is the camera, C the 90 degree angle formed
// at the intersction of the center of the viewport and the vector orientation
// of the camera and B the angle formed at the edge of the viewport at half its
// height, this function calculates the upper left coordinates of the viewport.
//                        B 
//                      --- 
//                 ------ │ 
//              ----      │ 
//           ----         │ <- half viewport 
//       ----             │ 
//    ---                 │ 
// A -────────────────────-C
void	set_viewport(t_mini_rt_data *data)
{
	float	vp_dist;
	float	vp_center[3];
	float	vp_upper_left[3];

	vp_dist = sqrt(((float)data->img_data->w_width / 2)
			- (get_dist_to_vp(data)));
	vp_center[0] = data->cam->coords[0] + (vp_dist * data->cam->v_3d_orient[0]);
	vp_center[1] = data->cam->coords[1] + (vp_dist * data->cam->v_3d_orient[1]);
	vp_center[2] = data->cam->coords[2] + (vp_dist * data->cam->v_3d_orient[2]);
	vp_upper_left[0] = vp_center[0]
		- (((float)data->img_data->w_width / 2) * data->cam->v_3d_orient[0]);
	vp_upper_left[1] = vp_center[1]
		- (((float)data->img_data->w_width / 2) * data->cam->v_3d_orient[1]);
	vp_upper_left[2] = vp_center[2]
		- (((float)data->img_data->w_width / 2) * data->cam->v_3d_orient[2]);
}
