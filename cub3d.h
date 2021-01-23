/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhalli <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 12:49:30 by mhalli            #+#    #+#             */
/*   Updated: 2020/12/10 12:49:32 by mhalli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./libft/libft.h"
# include "./GNL/get_next_line.h"
# include <stdlib.h>
# include <mlx.h>
# include <limits.h>
# include <float.h>
# include <math.h>

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define S 4
# define KEY_UP 13
# define KEY_LEFT 0
# define KEY_DOWN 1
# define KEY_RIGHT 2
# define ESC 53
# define TRUE 1
# define FALSE 0
# define ESC 53
# define TILE_SIZE 64

typedef	struct	s_point
{
	float		x;
	float		y;
}				t_point;

typedef	struct	s_sprite
{
	t_point		pos;
	float		distance;
}				t_sprite;

typedef struct	s_player {
	float		x;
	float		y;
	t_point		pos;
	float		width;
	float		height;
	int			turndirection;
	int			walkdirection;
	float		rotationangle;
	float		walkspeed;
	float		turnspeed;
	int			moove_left;
	int			moove_right;
	int			moove_forward_or_backward;
	int			move_right_or_left;
}				t_player;

typedef struct	s_window {
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*mlx_win;
	void		*mlx_img;
	int			ceil;
	int			floor;
	int			sprite_num;
	t_sprite	sprite[500];
	float		proj_plane;
}				t_window;

typedef	struct	s_map {
	int			num_rows;
	int			num_cols;
	int			*line;
	char		**map;
}				t_map;

typedef	struct	s_rays
{
	float		ray_angle;
	float		wallhit_x;
	float		wallhit_y;
	float		distance;
	int			washit_vertical;
	int			washit_horizontal;
	int			israyfacing_up;
	int			israyfacing_down;
	int			israyfacing_left;
	int			israyfacing_right;
	int			wallhitcontent;
	float		horzhitdistance;
	float		verthitdistance;
}				t_rays;

typedef struct	s_texture
{
	int			width;
	int			height;
	int			*data;
}				t_texture;

typedef struct	s_walls
{
	float		perpdistance;
	float		distanceprojplane;
	float		projectedwallheight;
	int			wallstripheight;
}				t_walls;

typedef struct	s_rayang
{
	int			israyfacingdown;
	int			israyfacingup;
	int			israyfacingright;
	int			israyfacingleft;
	int			horzhitcont;
	int			vertihit;
	int			vertihitcont;
	int			horzhit;
	float		horzhitx;
	float		horzhity;
	float		vertihitx;
	float		vertihity;
	float		xintercept;
	float		yintercept;
	float		xtocheck;
	float		ytocheck;
}				t_rayang;

typedef	struct	s_bmp_header
{
	char		bftype[3];
	u_int32_t	bfsize;
	u_int16_t	bfreserved1;
	u_int16_t	bfreserved2;
	u_int32_t	bfoffbits;
	u_int32_t	bisize;
	int32_t		biwidth;
	int32_t		biheight;
	u_int16_t	biplanes;
	u_int16_t	bibitcount;
	u_int32_t	bicompression;
	u_int32_t	bisizeimage;
	int32_t		bixpermeter;
	int32_t		biypermeter;
	u_int32_t	biclrused;
	u_int32_t	biclrimportant;
}				t_bmp_file;

t_window		g_ptr;
t_map			g_map;
t_player		g_pl;
t_texture		*g_txt;
t_walls			g_wall;
t_rayang		g_ray;
t_point			g_p;
t_sprite		*g_spr;
int				g_me;
int				*g_data;

char			*textr_name(char *line);
int				count_words(char *str, char c);
int				count_chars(char *str, char c);
int				check_numb(char *str, int min, long max);
int				move_p();
int				moove_player(int key);
int				reset_player(int key);
int				close_win(void);
int				wall_at(float x, float y);
void			free_arr(void **arr, int len);
void			init_player(int i, int j);
void			cast_ray(t_rays *rays, float rayangle, int i);
void			cast_rays(t_rays *rays);
void			render();
float			distancebetweenpoints(float x1, float y1, float x2, float y2);
float			normalized_angle(float angle);
int				rgb(int r, int g, int b);
void			moove_pl();
void			render_walls(t_rays *rays);
void			render_sprite(t_rays *rays);
void			init_ray(float rayangle);
void			hit_distance(t_rays *rays);
void			horz_inter(float nexthorzx, float nexthorzy);
void			horizcheck(float xstep, float ystep);
void			horizray(float rayangle);
void			vert_inter(float nextvertx, float nextverty);
void			verticheck(float xstep, float ystep);
void			anlys_map(char *buffer);
void			vertiray(float rayangle);
void			print_error(const char *error);
void			get_cub_fl(int fd);
void			calc_movement(float *nplayer_x, float *nplayer_y);
void			pl_movements(void);
void			get_map(char *line, int *argnb, int fd);
int				pl_colision(float x, float y);
int				to_split(char c);
int				is_floor_c(char *s);
int				texture_side(char *filename);
int				filter_resolution(char *str);
void			init_sprite(int i, int j, char *array);
void			make_bmp();
void			init_txt_and_colors();
char			*filter_txtr(char *txtr);
void			take_screenshot(void);

#endif
