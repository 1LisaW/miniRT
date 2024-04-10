/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tklimova <tklimova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:49:49 by tklimova          #+#    #+#             */
/*   Updated: 2024/04/10 16:34:28 by tklimova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define ERR_WRONG_ARG 1
# define ERR_WRONG_FILE_EXT 2
# define ERR_READ_FILE 3
# define ERR_PARSE_DATA 4
# define ERR_ALLOC_ERR 5

# define STEP 0.5
# define RAY_MAX_LENGHT 100.0

# define AMBIENT_LIGHTNING_TOKEN "A"
# define CAMERA_TOKEN "C"
# define LIGHT_TOKEN "L"
# define SPHERE_TOKEN "sp"
# define PLANE_TOKEN "pl"
# define CYLINDER_TOKEN "cy"

# define SEPARATOR ','

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_img_data
{
	int		**colors_data;
	int		is_guide;
	int		w_width;
	int		w_height;
	int		y_coord_nb;
	int		x_coord_nb;
	int		z;
	int		img_step;
}				t_img_data;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img_data	*img_data;
}				t_vars;

typedef struct s_ambient_light
{
	float	ratio;
	int		*rgb;	// int[3]
}				t_ambient_light;

typedef struct s_camera
{
	float	*coords; // float [3]
	float	*v_3d_orient;	//float[3]
	int		fov;
}				t_camera;

typedef struct s_light
{
	float	*coords; // float [3]
	float	l_brightness;
	int		*rgb;	// int[3]
}				t_light;

enum	e_obj_ids
{
	pl,
	sp,
	cy,
};

typedef struct s_g_objects
{
	enum e_obj_ids		id;
	float				*coords; // float [3]
	float				diam;
	float				*v_3d_normal;	//float[3]
	float				height;
	int					*rgb;	// int[3]
	struct s_g_objects	*next;
}				t_g_objects;

typedef struct s_mini_rt_data
{
	int				err_code;
	int				fd;
	t_ambient_light	*a_l;
	t_camera		*cam;
	t_light			*l;
	t_g_objects		*objs;
	t_vars			*vars;
}			t_mini_rt_data;

int			is_valid_extension(char *str, char *extantion,
				t_mini_rt_data *data);

void		handle_error(int err_no, char *text, t_mini_rt_data *data);

void		init_mini_rt_data(t_mini_rt_data *data);

void		ft_read_file(t_mini_rt_data *data);

char		*ft_read_substr(t_mini_rt_data *data, int *eol);

void		ft_parse_ambient_light(t_mini_rt_data *data, int *eol);

void		ft_parse_camera(t_mini_rt_data *data, int *eol);

bool		is_float(char *str);

bool		is_int_in_range(int nb, int min, int max);

bool		is_float_in_range(float nb, float min, float max);

int			*get_rgb_data(t_mini_rt_data *data, char *rgb);

int			ft_read_token(char **substr, t_mini_rt_data *data,
				int *eol, char *err_msg);

int			ft_read_last_token(char **substr, t_mini_rt_data *data,
				int *eol, char *err_msg);

float		*get_coords(char *coords, t_mini_rt_data *data);

float		*get_coords_with_range(char *coords, t_mini_rt_data *data,
				float min, float max);

void		ft_parse_light(t_mini_rt_data *data, int *eol);

void		delete_ambient_light(t_mini_rt_data *data);

void		delete_camera(t_mini_rt_data *data);

void		delete_mini_rt_data(t_mini_rt_data *data);

void		delete_light(t_mini_rt_data *data);

t_g_objects	*create_obj(t_mini_rt_data *data, char *token);

void		push_to_data_obj(t_mini_rt_data *data, t_g_objects *obj);

void		delete_obj(t_g_objects *obj);

t_g_objects	*prefilled_obj(t_mini_rt_data *data, char *coords, char *rgb,
				char *token);

void		ft_parse_sphere(t_mini_rt_data *data, int *eol, char *token);

void		ft_parse_plane(t_mini_rt_data *data, int *eol, char *token);

void		ft_parse_cylinder(t_mini_rt_data *data, int *eol, char *token);

void		delete_shapes(t_mini_rt_data *data);

void		ft_free_4_str(char *str1, char *str2, char *str3,
				char *str4);

void		ft_print_data(t_mini_rt_data *data);

void	init_img_data(t_img_data	**img_data);

void	set_start_img_colors(t_data *img, t_vars *vars);

void	free_coords(t_img_data *img_data);

void	create_win(t_vars *vars);

int	win_close(int keycode, t_vars *vars);

int	win_destroy(t_vars *vars);

// vector_ops

void	vector_add(float *origin, float *direction,	float *result);

void	vector_subtract(float *origin, float *direction, float *result);

void	vector_multiply(float *origin, float *vector1, float *vector2, \
	float *result);

float	get_dot_product(float *vector_1, float *vector_2);

void	vector_divide(float *origin, float *vector1, float *vector2, \
	float *result);

float	get_vector_length(float *position1, float *position2);

void	normalize_vector(float *origin, float *vector);

void	copy_f_vector(float *src, float *dest);

void	scale_vector(float *vector, float scalar, float *result);

// SD functions

float	sd_selector(float *curr_pt, t_mini_rt_data *data, t_g_objects object);

// ray tracing functions

void	trace_ray(t_mini_rt_data *data, float *vp_coords);

int		apply_sdf_to_objects(t_mini_rt_data *data, float *current_point);

#endif