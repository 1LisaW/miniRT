/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 16:06:59 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/05/24 00:07:42 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Scale a vector by a scalar factor
void	scale_vector(float *vector, float scalar, float *result)
{
	result[0] = vector[0] * scalar;
	result[1] = vector[1] * scalar;
	result[2] = vector[2] * scalar;
}

void	scale_rgb_vector(int *vector, float scalar, int *result)
{
	result[0] = (int)(vector[0] * scalar);
	result[1] = (int)(vector[1] * scalar);
	result[2] = (int)(vector[2] * scalar);
}

void	get_rgb_proportion(int *vector, float scalar, float *result)
{
	result[0] = vector[0] * scalar;
	result[1] = vector[1] * scalar;
	result[2] = vector[2] * scalar;
}
