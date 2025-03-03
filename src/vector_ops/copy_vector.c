/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:56:16 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/05/21 19:00:32 by tklimova         ###   ########.fr       */
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

// Initiate vector with 0
void	init_f_vector(float vector[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		vector[i] = 0;
		i++;
	}
}

// Initiate vector with 0
void	init_i_vector(int vector[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		vector[i] = 0;
		i++;
	}
}

t_vect	fill_vector(float x, float y, float z)
{
	t_vect	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}
