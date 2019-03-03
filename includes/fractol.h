/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:59:41 by magrab            #+#    #+#             */
/*   Updated: 2019/03/03 14:59:56 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>
# include "../libft/libft.h"

/*
** Bonus include
*/

# define MAX_ITER 142
# define WINX 500
# define WINY 500
# define CAMSPEED 1
# define ZOOMSPEED 1

/*
** Maximum number of projections
*/

# define ISO 0
# define MAXP 1

typedef struct	s_dot{
	int x;
	int y;
}				t_dot;

typedef struct	s_map{
	int	z;
	int	c;
}				t_map;

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
	int		x;
	int		y;
	int		z;
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
}				t_fdf;

/*
** void			*g_mlx(int setup);
** void			*g_win(t_win *win);
*/

void			show_menu(t_fdf *fdf);

t_cam			move_iso(t_fdf *fdf, int key);

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

void			draw_mandel(t_fdf *fdf, t_cam pos);

void			draw_order(t_fdf *fdf, int x, int y, int c);
void			*draw_tilt(t_fdf *fdf, t_map **tab, t_cam pos);
void			*draw_flat(t_fdf *fdf, t_map **tab, t_cam pos);
void			draw_text(t_fdf *fdf, int x, int y);

int				close_hook(t_fdf *fdf);

#endif
