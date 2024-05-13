/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:38:52 by tklimova          #+#    #+#             */
/*   Updated: 2024/05/13 14:46:26 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	validate_args(int argc, char **argv, t_mini_rt_data *data)
{
	if (argc != 2)
		handle_error(ERR_WRONG_ARG, NULL, data);
	if (argc == 2 && is_valid_extension(argv[1], ".rt", data))
		data->fd = open(argv[1], O_RDONLY);
	if (!data->err_code && data->fd == -1)
		handle_error(ERR_READ_FILE, argv[1], data);
}

void	parse_scene(int argc, char **argv, t_mini_rt_data *data)
{
	validate_args(argc, argv, data);
	if (data->err_code)
		exit(data->err_code);
	ft_read_file(data);
}

int	main(int argc, char **argv)
{
	t_mini_rt_data	*data;
	int				err_code;

	data = NULL;
	data = (t_mini_rt_data *) malloc(sizeof(t_mini_rt_data));
	if (!data)
		exit(1);
	init_mini_rt_data(data);
	parse_scene(argc, argv, data);
	err_code = data->err_code;
	if (err_code != 0)
	{
		delete_mini_rt_data(data);
		return (err_code);
	}
	precompute_data(data);
	create_win(data);
	draw(data);
	destroy_win(data);
	delete_mini_rt_data(data);
	data = NULL;
	return (err_code);
}
