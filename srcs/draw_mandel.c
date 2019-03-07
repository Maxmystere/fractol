/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mandel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 15:57:12 by magrab            #+#    #+#             */
/*   Updated: 2019/03/03 15:57:14 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
/*
static int	calc_color(double pr, double pi, t_cam pos)
{
	double	new_r;
	double	new_i;
	double	old_r;
	double	old_i;
	int		i;

	new_r = 0;
	new_i = 0;
	i = 0;
	while ((new_r * new_r + new_i * new_i) < 4.0 && i < pos.iter)
	{
		old_r = new_r;
		old_i = new_i;
		new_r = old_r * old_r - old_i * old_i + pr;
		new_i = 2.0 * old_r * old_i + pi;
		i++;
	}
	return (i);
}

static void	*draw_part(void *arg)
{
	t_fdf	*fdf;
	int		x;
	int		y;
	double	pi;
	double	pr;

	fdf = ((t_th *)arg)->fdf;
	y = (((t_th *)arg)->th < 2 ? 0 : fdf->p_win.sy / 2);
	while (y < (((t_th *)arg)->th < 2 ? fdf->p_win.sy / 2 : fdf->p_win.sy))
	{
		x = (((t_th *)arg)->th % 2 ? fdf->p_win.sx / 2 : 0);
		while (x < (((t_th *)arg)->th % 2 ? fdf->p_win.sx : fdf->p_win.sx / 2))
		{
			pr = x / fdf->cam.z - (fdf->cam.x + fdf->p_win.sx / 4) / fdf->cam.z * 2;
			pi = y / fdf->cam.z - (fdf->cam.y + fdf->p_win.sy / 4) / fdf->cam.z * 2;
			fill_pixel(fdf, x, y, calc_color(pr, pi, fdf->cam) * fdf->color);
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}
*/


void		draw_mandel(t_fdf *fdf)
{
	t_frcl tmp;

	tmp.iter = fdf->cam.iter;
	tmp.camx = fdf->cam.x;
	tmp.camy = fdf->cam.y;
	tmp.camz = fdf->cam.z;
	tmp.winsx = fdf->p_win.sx;
	tmp.winsy = fdf->p_win.sy;
	tmp.color = fdf->color;

	gpu_calcul(tmp, fdf->mlx, fdf->win);
}
