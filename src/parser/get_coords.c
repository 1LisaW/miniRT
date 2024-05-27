/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_coords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:31:57 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/27 14:45:28 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

char	**get_coords_str_arr(char *coords, t_mini_rt_data *data, int *len)
{
	char	**arr_coords;

	arr_coords = ft_split(coords, SEPARATOR[0]);
	*len = ft_str_arr_len(arr_coords);
	if (ft_str_arr_len(arr_coords) != 3)
		handle_error(ERR_PARSE_DATA, "Incorrect number of coordinates", data);
	if (!data->err_code && (!is_float(arr_coords[0]) || !is_float(arr_coords[1])
			|| !is_float(arr_coords[2])))
		handle_error(ERR_PARSE_DATA, "Incorrect format of coordinates", data);
	free(coords);
	coords = NULL;
	if (data->err_code)
	{
		ft_free_all_split_alloc(arr_coords, *len);
		arr_coords = NULL;
	}
	return (arr_coords);
}

float	*get_coords(char *coords, t_mini_rt_data *data)
{
	char	**arr_coords;
	float	*f_arr_coords;
	int		len;

	len = 0;
	f_arr_coords = NULL;
	arr_coords = get_coords_str_arr(coords, data, &len);
	if (data->err_code)
		return (ft_free_all_split_alloc(arr_coords, len));
	f_arr_coords = (float *) malloc(sizeof(float) * 3);
	if (!f_arr_coords)
	{
		if (!data->err_code)
			ft_free_all_split_alloc(arr_coords, len);
		return (NULL);
	}
	while (len > 0)
	{
		len--;
		f_arr_coords[len] = ft_atof(arr_coords[len]);
	}
	ft_free_all_split_alloc(arr_coords, 3);
	return (f_arr_coords);
}

float	*get_coords_with_range(char *coords, t_mini_rt_data *data,
			float min, float max)
{
	int		len;
	float	*f_arr_coords;

	f_arr_coords = get_coords(coords, data);
	len = 0;
	while (f_arr_coords && len < 3 && f_arr_coords[len] <= max
		&& f_arr_coords[len] >= min)
		len++;
	if (len != 3)
		handle_error(ERR_PARSE_DATA, "Coordinates are out of range", data);
	if (data->err_code)
	{
		free(f_arr_coords);
		f_arr_coords = NULL;
	}
	return (f_arr_coords);
}
