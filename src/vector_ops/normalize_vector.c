/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:20:35 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/04 15:15:18 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// This function normalizes a vector by scaling it to have a length of 1
// while preserving its direction
// WARNING: this function modifies the input vector
void	normalize_vector(float *origin, float *vector)
{
	float	length;

	length = get_vector_length(origin, vector);
	if (length != 0)
	{
		vector[0] = (vector[0] - origin[0]) / length;
		vector[1] = (vector[1] - origin[1]) / length;
		vector[2] = (vector[2] - origin[2]) / length;
		return ;
	}
	else
	{
		vector[0] = 0.0;
		vector[1] = 0.0;
		vector[2] = 0.0;
	}
}
