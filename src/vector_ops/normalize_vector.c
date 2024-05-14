/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:20:35 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/05/14 11:35:17 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// This function normalizes a vector by scaling it to have a length of 1
// while preserving its direction
// WARNING: this function modifies the input vector
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
