/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmigoya- <jmigoya-@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:41:36 by jmigoya-          #+#    #+#             */
/*   Updated: 2024/04/19 15:07:56 by jmigoya-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

// vp_u is the normalized vector pointing to camera right,
// vp_v is the normalized vector pointing to camera up,
// vp_w points opposite to view direction (using right-hand coords)
typedef struct s_vp
{
	float	vp_center[3];
	float	vp_pixel00[3];
	float	vp_upper_left[3];
	float	vp_dist;
	float	vp_u[3];
	float	vp_v[3];
	float	vp_w[3];
	float	vp_up[3];
	float	vp_horizontal_vec[3];
	float	vp_vertical_vec[3];
	float	pixel_delta_horizontal[3];
	float	pixel_delta_vertical[3];
}	t_vp;

// Set viewport to 1920x1800, though not all might be needed
typedef struct s_img_data
{
	int		**colors_data;
	t_vp	vp;
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
	t_img_data	*img_data; // check users and remove
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
	t_img_data		*img_data;
}			t_mini_rt_data;
