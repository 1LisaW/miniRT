/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:56:16 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/05/03 15:27:08 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// Copies float vector.
// WARNING: assumes both src and dest are size 3
void	copy_f_vector(float *src, float *dest)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		dest[i] = src[i];
		i++;
	}
}

// Copies float vector.
// WARNING: assumes both src and dest are size 3
void	copy_i_vector(int *src, int *dest)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		dest[i] = src[i];
		i++;
	}
}
