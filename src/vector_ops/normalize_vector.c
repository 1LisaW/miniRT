/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:20:35 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/18 12:39:43 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// This function normalizes a vector by scaling it to have a length of 1
// while preserving its direction
// WARNING: this function modifies the input vector
void	normalize_vector(float *vector)
{
	float	length;

	length = get_vector_length(vector);
	print_vector("vec to normalize", vector);
	printf("length: %f\n", length);
	if (length != 0)
	{
		vector[0] = vector[0] / length;
		vector[1] = vector[1] / length;
		vector[2] = vector[2] / length;
		return ;
	}
	else
	{
		vector[0] = 0.0;
		vector[1] = 0.0;
		vector[2] = 0.0;
	}
}
