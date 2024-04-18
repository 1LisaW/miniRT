/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dot_and_cross_product.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:34:58 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/18 17:35:13 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	get_cross_product(float *vec_1, float *vec_2, float *cross_P)
{
	cross_P[0] = vec_1[1] * vec_2[2] - vec_1[2] * vec_2[1];
	cross_P[1] = vec_1[2] * vec_2[0] - vec_1[0] * vec_2[2];
	cross_P[2] = vec_1[0] * vec_2[1] - vec_1[1] * vec_2[0];
}

// Multiply to vectors and get the dot product
float	get_dot_product(float *vec_1, float *vec_2)
{
	return ((vec_1[0] * vec_2[0])
		+ (vec_1[1] * vec_2[1])
		+ (vec_1[2] * vec_2[2]));
}
