/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inverse_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 02:16:31 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/24 17:30:31 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Pre-calculation of reused data in inverse algorithm calculations
void	fill_2d_determinants(float *mtx, t_cross_determ *d_mtx)
{
	d_mtx->d8_13 = (mtx[8] * mtx[13] - mtx[12] * mtx[9]);
	d_mtx->d8_14 = (mtx[8] * mtx[14] - mtx[12] * mtx[10]);
	d_mtx->d8_15 = (mtx[8] * mtx[15] - mtx[12] * mtx[11]);
	d_mtx->d9_14 = (mtx[9] * mtx[14] - mtx[13] * mtx[10]);
	d_mtx->d9_15 = (mtx[9] * mtx[15] - mtx[13] * mtx[11]);
	d_mtx->d10_15 = (mtx[10] * mtx[15] - mtx[14] * mtx[11]);
	d_mtx->d4_13 = (mtx[4] * mtx[13] - mtx[12] * mtx[5]);
	d_mtx->d4_14 = (mtx[4] * mtx[14] - mtx[12] * mtx[6]);
	d_mtx->d4_15 = (mtx[4] * mtx[15] - mtx[12] * mtx[7]);
	d_mtx->d5_14 = (mtx[5] * mtx[14] - mtx[13] * mtx[6]);
	d_mtx->d5_15 = (mtx[5] * mtx[15] - mtx[13] * mtx[7]);
	d_mtx->d6_15 = (mtx[6] * mtx[15] - mtx[14] * mtx[7]);
	d_mtx->d4_9 = (mtx[4] * mtx[9] - mtx[5] * mtx[8]);
	d_mtx->d4_10 = (mtx[4] * mtx[10] - mtx[6] * mtx[8]);
	d_mtx->d4_11 = (mtx[4] * mtx[11] - mtx[7] * mtx[8]);
	d_mtx->d5_10 = (mtx[5] * mtx[10] - mtx[6] * mtx[9]);
	d_mtx->d5_11 = (mtx[5] * mtx[11] - mtx[7] * mtx[9]);
	d_mtx->d6_11 = (mtx[6] * mtx[11] - mtx[7] * mtx[10]);
}

float	mult_fl(float *mtx, int idx, int idx1, int idx2)
{
	float	sign;

	sign = 1;
	if (idx % 2)
		sign = -1;
	return (sign * mtx[idx] * (mtx[idx1] * mtx[idx2]
			- mtx[idx1 + 4] * mtx[idx2 - 4]));
}

// Calculation of the first column of the inverse matrix.
// Function returns determinant
float	get_determinant(float *inv_mtx, float *mtx, t_cross_determ *cd)
{
	float	determinant;

	determinant = 0;
	inv_mtx[0] = mtx[5] * cd->d10_15 - mtx[6] * cd->d9_15 + mtx[7] * cd->d9_14;
	inv_mtx[4] = -1 * (mtx[4] * cd->d10_15 - mtx[6] * cd->d8_15
			+ mtx[7] * cd->d8_14);
	inv_mtx[8] = mtx[4] * cd->d9_15 - mtx[5] * cd->d8_15 + mtx[7] * cd->d8_13;
	inv_mtx[12] = -1 * (mtx[4] * cd->d9_14 - mtx[5] * cd->d8_14
			+ mtx[6] * cd->d8_13);
	determinant = mtx[0] * inv_mtx[0] + mtx[1] * inv_mtx[4]
		+ mtx[2] * inv_mtx[8] + mtx[3] * inv_mtx[12];
	if (determinant != 0)
	{
		inv_mtx[0] /= determinant;
		inv_mtx[4] /= determinant;
		inv_mtx[8] /= determinant;
		inv_mtx[12] /= determinant;
	}
	return (determinant);
}

void	fill_mtx_inverse_rest(float *i_mx, float *mx, t_cross_determ *cd,
			float d)
{
	i_mx[1] = -1 * (mx[1] * cd->d10_15 - mx[2] * cd->d9_15
			+ mx[3] * cd->d9_14) / d;
	i_mx[5] = (mx[0] * cd->d10_15 - mx[2] * cd->d8_15 + mx[3] * cd->d8_14) / d;
	i_mx[9] = -1 * (mx[0] * cd->d9_15 - mx[1] * cd->d8_15
			+ mx[3] * cd->d8_13) / d;
	i_mx[13] = (mx[0] * cd->d9_14 - mx[1] * cd->d8_14 + mx[2] * cd->d8_13) / d;
	i_mx[2] = (mx[1] * cd->d6_15 - mx[2] * cd->d5_15 + mx[3] * cd->d5_14) / d;
	i_mx[6] = -1 * (mx[0] * cd->d6_15 - mx[2] * cd->d4_15
			+ mx[3] * cd->d4_14) / d;
	i_mx[10] = (mx[0] * cd->d5_15 - mx[1] * cd->d4_15 + mx[3] * cd->d4_13) / d;
	i_mx[14] = -1 * (mx[0] * cd->d5_14 - mx[1] * cd->d4_14
			+ mx[2] * cd->d4_13) / d;
	i_mx[3] = -1 * (mx[1] * cd->d6_11 - mx[2] * cd->d5_11
			+ mx[3] * cd->d5_10) / d;
	i_mx[7] = (mx[0] * cd->d6_11 - mx[2] * cd->d4_11 + mx[3] * cd->d4_10) / d;
	i_mx[11] = -1 * (mx[0] * cd->d5_11 - mx[1] * cd->d4_11
			+ mx[3] * cd->d4_9) / d;
	i_mx[15] = (mx[0] * cd->d5_10 - mx[1] * cd->d4_10 + mx[2] * cd->d4_9) / d;
}

float	*mtx_inverse(float *mtx)
{
	float			*inv_mtx;
	t_cross_determ	*cd;
	float			determinant;

	determinant = 0;
	inv_mtx = malloc(sizeof(float) * 16);
	if (!inv_mtx)
		return (NULL);
	cd = malloc(sizeof(t_cross_determ));
	if (!cd)
		return (NULL);
	fill_2d_determinants(mtx, cd);
	determinant = get_determinant(inv_mtx, mtx, cd);
	if (determinant == 0)
	{
		free(inv_mtx);
		free(cd);
		return (NULL);
	}
	fill_mtx_inverse_rest(inv_mtx, mtx, cd, determinant);
	free(cd);
	return (inv_mtx);
}
