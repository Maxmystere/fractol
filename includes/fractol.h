/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:59:41 by magrab            #+#    #+#             */
/*   Updated: 2019/03/05 12:27:54 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include <mlx.h>
# include <stdlib.h>
# include <fcntl.h>
# include <pthread.h>
# include <OpenCL/cl.h>

/*
** Bonus include
*/

# define MAX_ITER 42
# define WINX 1000
# define WINY 750
# define CAMSPEED 1
# define ZOOMSPEED 1

# define MANDEL 0
# define JULIA 1
# define BSHIP 2

typedef struct	s_dot{
	double	x;
	double	y;
	int		sx;
	int		sy;
}				t_dot;

typedef struct	s_pos{
	int x;
	int y;
	int z;
	int c;
}				t_pos;

typedef struct	s_win{
	int		nb;
	int		sx;
	int		sy;
	char	*title;
}				t_win;

typedef struct	s_cam{
	double			x;
	double			y;
	int				jon;
	double			jx;
	double			jy;
	double			z;
	int				iter;
}				t_cam;

typedef struct	s_fdf{
	void	*mlx;
	void	*win;
	t_tab	keys;
	t_dot	mouse;
	t_cam	cam;
	void	*img;
	int		*istr;
	int		bpp;
	int		s_l;
	int		e;
	t_win	p_win;
	int		color;
	int		fractype;
}				t_fdf;

typedef struct	s_th{
	t_fdf	*fdf;
	int		th;
}				t_th;

/*
** GPU Stuff
*/

# define MANDELDRAWER "typedef struct s_frcl{double camx;double camy;\
double  camz;int winsx;int winsy;int iter;int color;}t_frcl;\
__kernel void color(__global const t_frcl *in, __global unsigned int *out)\
{const uint index = get_global_id(0);const double x = index % in->winsx;\
const double y = index / in->winsx;\
const double pr = x / in->camz - (in->camx * 4.0 + in->winsx)/ (in->camz * 2);\
const double pi = y / in->camz - (in->camy * 4.0 + in->winsy)/ (in->camz * 2);\
double new_r;double new_i;double old_r;double old_i;int i;new_r = 0;new_i = 0;\
i = 0;while ((new_r * new_r + new_i * new_i) < 4.0 && i < in->iter){\
old_r = new_r;old_i = new_i;new_r = old_r * old_r - old_i * old_i + pr;\
new_i = 2.0 * old_r * old_i + pi;i++;}out[index] = i * in->color;}"

# define SHIPDRAWER "typedef struct s_frcl{double camx;double camy;\
double  camz;int winsx;int winsy;int iter;int color;}t_frcl;\
__kernel void color(__global const t_frcl *in, __global unsigned int *out)\
{const uint index = get_global_id(0);const double x = index % in->winsx;\
const double y = index / in->winsx;\
const double pr = x / in->camz - (in->camx * 4.0 + in->winsx)/ (in->camz * 2);\
const double pi = y / in->camz - (in->camy * 4.0 + in->winsy)/ (in->camz * 2);\
double new_r;double new_i;double old_r;double old_i;int i;new_r = 0;new_i = 0;\
i = 0;while ((new_r * new_r + new_i * new_i) < 4.0 && i < in->iter){\
old_r = (new_r < 0 ? -new_r : new_r);old_i = (new_i < 0 ? -new_i : new_i);\
new_r = old_r * old_r - old_i * old_i + pr;\
new_i = 2.0 * old_r * old_i + pi;i++;}out[index] = i * in->color;}"

typedef struct	s_gpu{
	cl_int					err;
	cl_platform_id			ptm;
	cl_uint					ptms;
	cl_device_id			dvc;
	cl_uint					dvcs;
	size_t					srcsize;
	cl_program				prog;
	cl_kernel				k_color;
	cl_context_properties	properties[3];
}				t_gpu;

typedef struct	s_frcl{
	double	camx;
	double	camy;
	double	camz;
	double	jx;
	double	jy;
	int		winsx;
	int		winsy;
	int		iter;
	int		color;
}				t_frcl;

int				gpu_calcul(t_frcl param, t_fdf *fdf, const char *src);

/*
** End GPU Stuff
*/

void			show_menu(t_fdf *fdf);

t_cam			move_iso(t_fdf *fdf, int key);
void			change_color(t_fdf *fdf, int key);

int				key_press(int key, t_fdf *fdf);
int				key_release(int key, t_fdf *fdf);
int				mouse_press(int button, int x, int y, t_fdf *fdf);
int				mouse_release(int button, int x, int y, t_fdf *fdf);
int				mouse_move(int x, int y, t_fdf *fdf);
int				loop_hook(t_fdf *fdf);

void			fill_pixel(t_fdf *fdf, int x, int y, int color);
void			fill_line(t_fdf *fdf, t_pos pos0, t_pos pos1);
void			draw_line(t_fdf *fdf, t_pos pos0, t_pos pos1);
void			test_draw(t_fdf *fdf, int x, int y);

t_pos			*init_value(int x, int y, int z, int c);
t_fdf			*init_mlx(int winnb, char **winname);

void			draw_mandel(t_fdf *fdf);
void			draw_julia(t_fdf *fdf);
void			draw_ship(t_fdf *fdf);

void			draw_order(t_fdf *fdf, int x, int y, int c);
void			draw_text(t_fdf *fdf, int x, int y);

int				close_hook(t_fdf *fdf);

#endif
