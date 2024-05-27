/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 21:23:48 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/27 13:46:45 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

char	**get_rgb_str_arr(t_mini_rt_data *data, char *rgb)
{
	char	**rgb_arr_str;
	int		len;

	len = 0;
	rgb_arr_str = ft_split(rgb, ',');
	if (ft_str_arr_len(rgb_arr_str) != 3)
		handle_error(ERR_PARSE_DATA, "RGB should include 3 numbers", data);
	free(rgb);
	if (data->err_code)
	{
		while (rgb_arr_str && rgb_arr_str[len])
			len++;
		return (ft_free_all_split_alloc(rgb_arr_str, len));
	}
	return (rgb_arr_str);
}

int	*get_rgb_data(t_mini_rt_data *data, char *rgb)
{
	char	**rgb_arr_str;
	int		*rgb_arr_nb;
	int		i;

	rgb_arr_nb = NULL;
	i = 0;
	rgb_arr_str = get_rgb_str_arr(data, rgb);
	if (data->err_code || !rgb_arr_str)
		return (NULL);
	rgb_arr_nb = malloc(sizeof(int) * 3);
	if (!rgb_arr_nb)
		handle_error(ERR_ALLOC_ERR, NULL, data);
	while (!data->err_code && i < 3)
	{
		rgb_arr_nb[i] = ft_atoi(rgb_arr_str[i]);
		if (!is_int_in_range(rgb_arr_nb[i], 0, 255))
			handle_error(ERR_PARSE_DATA, "RGB is out of range", data);
		i++;
	}
	if (rgb_arr_str)
		ft_free_all_split_alloc(rgb_arr_str, 3);
	return (rgb_arr_nb);
}
