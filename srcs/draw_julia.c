/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_julia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 19:46:57 by magrab            #+#    #+#             */
/*   Updated: 2019/03/04 19:46:59 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int			calc_color(double pr, double pi, t_cam pos)
{
	double	new_r;
	double	new_i;
	double	old_r;
	double	old_i;
	int		i;

	new_r = pr;
	new_i = pi;
	i = 0;
	while ((new_r * new_r + new_i * new_i) < 18.0 && i < pos.iter)
	{
		old_r = new_r;
		old_i = new_i;
		new_r = old_r * old_r - old_i * old_i + pos.jx / 100.0;
		new_i = 2.0 * old_r * old_i + pos.jy / 100.0;
		i++;
	}
	return (i);
}

static void			*draw_part(void *arg)
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
			pr = 1 / fdf->cam.z * x - (fdf->cam.x + fdf->p_win.sx / 4) / fdf->cam.z * 2;// * (x - fdf->p_win.sx / 2 + fdf->cam.x);
			pi = 1 / fdf->cam.z * y - (fdf->cam.y + fdf->p_win.sy / 4) / fdf->cam.z * 2;// * (y - fdf->p_win.sy / 2 + fdf->cam.y);
			fill_pixel(fdf, x, y, calc_color(pr, pi, fdf->cam) * fdf->color);
			x++;
		}
		y++;
	}
	pthread_exit(NULL);
}

void				draw_julia(t_fdf *fdf)
{
	pthread_t	threads[4];
	t_th		pth[4];
	int			x;

	x = 0;
	while (x < 4)
	{
		pth[x].fdf = fdf;
		pth[x].th = x;
		pthread_create(&threads[x], NULL, draw_part, &(pth[x]));
		x++;
	}
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);
	pthread_join(threads[3], NULL);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}
