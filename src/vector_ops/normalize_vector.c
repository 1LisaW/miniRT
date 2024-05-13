/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:20:35 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/05/13 03:12:13 by tklimova         ###   ########.fr       */
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

void	normalize_vect(float *vector)
{
	float	len;
	float	inverted_len;

	len = sqrt(pow(vector[0], 2) + pow(vector[1], 2) + pow(vector[2], 2));
	if (len > 0)
	{
		inverted_len = 1.0 / len;
		vector[0] *= inverted_len;
		vector[1] *= inverted_len;
		vector[2] *= inverted_len;
	}
}
