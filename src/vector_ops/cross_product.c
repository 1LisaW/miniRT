/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cross_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 19:45:38 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/02 01:21:47 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// The cross product gives a vector that is perpendicular
// to the vectors of both arguments.
// If the vectors of the arguments have opposite directions,
// the cross-product vector will have zero magnitude (length).
t_vect	cross_product(t_vect vect_a, t_vect vect_b)
{
	t_vect	cross_prod;

	cross_prod.x = vect_a.y * vect_b.z - vect_a.z * vect_b.y;
	cross_prod.y = vect_a.z * vect_b.x - vect_a.x * vect_b.z;
	cross_prod.z = vect_a.x * vect_b.y - vect_a.y * vect_b.x;
	return (cross_prod);
}

float	*vector_mtx_multy(float *vect, float *mtx, float *mult_vect)
{
	float	mult_v[3];

	mult_v[0] = vect[0] * mtx[0] + vect[1] * mtx[4] + vect[2] * mtx[8];
	mult_v[1] = vect[0] * mtx[1] + vect[1] * mtx[5] + vect[2] * mtx[9];
	mult_v[2] = vect[0] * mtx[2] + vect[1] * mtx[6] + vect[2] * mtx[10];
	mult_vect[0] = mult_v[0];
	mult_vect[1] = mult_v[1];
	mult_vect[2] = mult_v[2];
	return (mult_vect);
}
