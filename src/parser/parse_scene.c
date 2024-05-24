/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:38:28 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/23 23:17:14 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	ft_run_token_logic(t_mini_rt_data *data, char *str, int *eol)
{
	if (!ft_strcmp(str, AMBIENT_LIGHTNING_TOKEN) && (*eol) == 0)
		ft_parse_ambient_light(data, eol);
	else if (!ft_strcmp(str, CAMERA_TOKEN) && (*eol) == 0)
		ft_parse_camera(data, eol);
	else if (!ft_strcmp(str, LIGHT_TOKEN) && (*eol) == 0)
		ft_parse_light(data, eol);
	else if (!ft_strcmp(str, SPHERE_TOKEN) && (*eol) == 0)
		ft_parse_sphere(data, eol, str);
	else if (!ft_strcmp(str, PLANE_TOKEN) && (*eol) == 0)
		ft_parse_plane(data, eol, str);
	else if (!ft_strcmp(str, CYLINDER_TOKEN) && (*eol) == 0)
		ft_parse_cylinder(data, eol, str);
	else
		handle_error(ERR_PARSE_DATA, "Incorrect object in file", data);
	*eol = 0;
	return (1);
}

void	ft_read_str(t_mini_rt_data *data)
{
	char	*token;
	int		eol;

	eol = 0;
	token = ft_read_substr(data, &eol);
	if (token == NULL)
		return ;
	ft_run_token_logic(data, token, &eol);
	free(token);
	token = NULL;
}

void	ft_read_file(t_mini_rt_data *data)
{
	while (!data->err_code && read(data->fd, NULL, 0) > -1)
		ft_read_str(data);
	close(data->fd);
	if (!data->err_code && check_norm_vectors(data) == false)
		handle_error(ERR_PARSE_DATA,
			"All normalized orientation vectors must have length of 1.", data);
	if (!data->err_code)
		ft_print_data(data);
}
