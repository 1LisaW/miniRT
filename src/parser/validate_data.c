/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:31:57 by tklimova          #+#    #+#             */
/*   Updated: 2024/03/25 13:17:21 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

bool	is_float(char *str)
{
	int	is_dot;

	is_dot = 0;
	while (str && *str && is_dot < 2)
	{
		if (*str == '.')
			is_dot++;
		if (!ft_isdigit(*str) && *str != '.')
			break ;
		str++;
	}
	if (is_dot > 1 || (str && *str))
		return (false);
	return (true);
}

float	*validated_coords(char *coords, t_mini_rt_data *data)
{
	char	**arr_coords;
	float	*f_arr_coords;

	arr_coords = ft_split(coords, SEPARATOR);
	f_arr_coords = NULL;
	if (ft_str_arr_len(arr_coords) != 3)
		handle_error(ERR_PARSE_DATA, "Incorrect number of coordinates", data);
	if (!data->err_code && !is_float(arr_coords[0]) || !is_float(arr_coords[1])
		|| !is_float(arr_coords[2]))
		handle_error(ERR_PARSE_DATA, "Incorrect format of coordinates", data);
	if (data->err_code)
		return (NULL);
	f_arr_coords = (float *) malloc(sizeof(float) * 3);
	if (!f_arr_coords)
	{
		free(arr_coords);
		exit(3);
	}
	return (f_arr_coords);
}
