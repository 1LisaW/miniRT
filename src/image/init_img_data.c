/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 19:10:56 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/19 13:43:37 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	init_img_data(t_img_data **img_data_l)
{
	t_img_data	*img_data;

	img_data = NULL;
	img_data = malloc(sizeof(t_img_data));
	if (!img_data)
		return ;
	img_data->x_coord_nb = 0;
	img_data->y_coord_nb = 0;
	img_data->w_width = 800;
	img_data->w_height = 400;
	img_data->img_step = 0;
	img_data->z = 100;
	*img_data_l = img_data;
}
