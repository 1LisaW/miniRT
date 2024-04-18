/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:34:18 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/18 10:49:46 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	print_vector(char *msg, float *vector)
{
	printf("%s ", msg);
	printf("Vector: %f %f %f\n", vector[0], vector[1], vector[2]);
}
