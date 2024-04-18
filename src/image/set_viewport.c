/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_viewport.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:48:25 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/18 13:48:52 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Calculates the legth of the side AC (see set_viewport), which corresponds
// to the distance from the camera to the center of the viewport.
float	get_dist_to_vp(t_mini_rt_data *data)
{
	float	half_width;
	float	half_fov;
	float	side_AC;

	half_width = (float)data->img_data->w_width / 2.0;
	half_fov = (float)data->cam->fov / 2.0;
	side_AC = 400 / (sin(half_fov * (M_PI / 180.0)));
	return (side_AC);
}

void	set_vp_upper_left(t_mini_rt_data *data)
{
	float	vp_center_cpy[3];
	float	dist_times_w[3];
	float	half_vp_horizontal_vec[3];
	float	half_vp_vertical_vec[3];

	copy_f_vector(data->img_data->vp.vp_center, vp_center_cpy);
	scale_vector(data->img_data->vp.vp_w, data->img_data->vp.vp_dist, dist_times_w);
	print_vector("dist times w", dist_times_w);
	vector_divide(data->img_data->vp.vp_horizontal_vec, 2.0, half_vp_horizontal_vec);
	print_vector("half_vp_horizontal_vec", half_vp_horizontal_vec);
	vector_divide(data->img_data->vp.vp_vertical_vec, 2.0, half_vp_vertical_vec);
	print_vector("half_vp_vertical_vec", half_vp_vertical_vec);
	vector_subtract(vp_center_cpy, dist_times_w, data->img_data->vp.vp_upper_left);
	print_vector("vp_center - dist_times_w", data->img_data->vp.vp_upper_left);
	vector_subtract(data->img_data->vp.vp_upper_left, half_vp_horizontal_vec, data->img_data->vp.vp_upper_left);
	print_vector("minus half_vp_horizontal_vec", data->img_data->vp.vp_upper_left);
	vector_subtract(data->img_data->vp.vp_upper_left, half_vp_vertical_vec, data->img_data->vp.vp_upper_left);
}

// Assuming a triangle ABC, where A is the camera, C the 90 degree angle formed
// at the intersction of the center of the viewport and the vector orientation
// of the camera and B the angle formed at the edge of the viewport at half its
// height, this function calculates the upper left coordinates of the viewport.
//                        B 
//                      --- 
//                 ---    │ 
//              ---       │ 
//           ---          │ <- half viewport 
//       ---              │ 
//    ---                 │ 
// A -────────────────────-C
void	set_viewport(t_mini_rt_data *data)
{
	t_vp	*vp;
	float	displacement_vec[3];

	vp = &data->img_data->vp;
	vp->vp_up[0] = 0;
	vp->vp_up[1] = 1;
	vp->vp_up[2] = 0;
	if (vec_are_equal(data->cam->v_3d_orient, vp->vp_up) == true)
	{
		vp->vp_up[0] = 1;
		vp->vp_up[1] = 0;
	}
	vp->vp_dist = get_dist_to_vp(data);
	printf("ditance to vp: %f\n", vp->vp_dist);
	scale_vector(data->cam->v_3d_orient, vp->vp_dist, displacement_vec);
	vector_add(data->cam->coords, displacement_vec, vp->vp_center);
	print_vector("vp_w", data->img_data->vp.vp_w);
	print_vector("camera coords", data->cam->coords);
	print_vector("vp_center", data->img_data->vp.vp_center);
	vector_subtract(data->cam->coords, vp->vp_center, vp->vp_w);
	normalize_vector(vp->vp_w);
	get_cross_product(vp->vp_up, vp->vp_w, vp->vp_u);
	normalize_vector(vp->vp_u);
	get_cross_product(vp->vp_w, vp->vp_u, vp->vp_v);
	scale_vector(vp->vp_u, ((float)data->img_data->w_width), vp->vp_horizontal_vec);
	scale_vector(vp->vp_v, -1 * ((float)data->img_data->w_height), vp->vp_vertical_vec);
	vector_divide(vp->vp_horizontal_vec, data->img_data->w_width, vp->pixel_delta_horizontal);
	vector_divide(vp->vp_vertical_vec, data->img_data->w_height, vp->pixel_delta_vertical);
	print_vector("vp_w", data->img_data->vp.vp_w);
	print_vector("vp_u", data->img_data->vp.vp_u);
	print_vector("vp_v", data->img_data->vp.vp_v);
	print_vector("vp_horizontal_vec", data->img_data->vp.vp_horizontal_vec);
	print_vector("vp_vertical_vec", data->img_data->vp.vp_vertical_vec);
	print_vector("pixel_delta_vertical", data->img_data->vp.pixel_delta_vertical);
	print_vector("pixel_delta_horizontal", data->img_data->vp.pixel_delta_horizontal);
	set_vp_upper_left(data);
}
