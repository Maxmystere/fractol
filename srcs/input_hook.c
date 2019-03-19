/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 22:01:03 by magrab            #+#    #+#             */
/*   Updated: 2019/02/24 16:07:26 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
** 18 : 1 key
** 19 : 2 key
** 20 : 3 key
** 21 : 4 key
** 35 : P key
** 46 : M key
** 49 : Spacebar
** 53 : esc key
** 50 : key under esc
** 69 : plus numpad
** 78 : minus numpad
** 84 : num 2
** 91 : num 8
** 123 : left key
** 124 : right key
** 125 : down key
** 126 = up key
*/

int	key_press(int key, t_fdf *fdf)
{
	if (key == 0)
		return (0);
	if (key == 53)
		return (close_hook(fdf));
	if (key == 35)
	{
		fdf->cam.x = 0;
		fdf->cam.y = 0;
	}
	if (key == 49)
		fdf->cam.jon = (fdf->cam.jon ? 0 : 1);
	if (key != 46 || !ft_nodesearch_int(fdf->keys, 46))
		ft_nodeadd_int(&(fdf->keys), key);
	else
		ft_noderm_int(&(fdf->keys), 46);
	return (0);
}

int	key_release(int key, t_fdf *fdf)
{
	if (key != 46)
		ft_noderm_int(&(fdf->keys), key);
	return (0);
}

int	mouse_press(int button, int x, int y, t_fdf *fdf)
{
	if (button == 1)
	{
		if (x > 0 && y > 0 && fdf->p_win.sx > x && fdf->p_win.sy > y)
		{
			fdf->mouse.sx = fdf->cam.x * 2.0 - x;
			fdf->mouse.sy = fdf->cam.y * 2.0 - y;
			fdf->cam.jon = 0;
		}
		else
			return (mouse_release(1, 0, 0, fdf));
	}
	else if (button == 4 || button == 5)
	{
		move_iso(fdf, (button == 4 ? -4 : -5));
		if (fdf->fractype == MANDEL)
			draw_mandel(fdf);
		else if (fdf->fractype == JULIA)
			draw_julia(fdf);
		else if (fdf->fractype == BSHIP)
			draw_ship(fdf);
		draw_text(fdf, 0, 0);
		if (ft_nodesearch_int(fdf->keys, 46))
			show_menu(fdf);
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		fdf->mouse.sx = 0;
		fdf->mouse.sy = 0;
	}
	return (0);
}

int	mouse_move(int x, int y, t_fdf *fdf)
{
	fdf->mouse.x = -100.0 / ((x - fdf->p_win.sx / 2 - fdf->cam.x * 2)
														/ fdf->cam.z);
	fdf->mouse.y = -100.0 / ((y - fdf->p_win.sy / 2 - fdf->cam.y * 2)
														/ fdf->cam.z);
	if (fdf->cam.jon)
	{
		fdf->cam.jx = x - fdf->p_win.sx / 2.0;
		fdf->cam.jy = y - fdf->p_win.sy / 2.0;
	}
	if (fdf->mouse.sx && 0 < x && x < fdf->p_win.sx
				&& 0 < y && y < fdf->p_win.sy)
	{
		fdf->cam.x = (fdf->mouse.sx + x) / 2.0;
		fdf->cam.y = (fdf->mouse.sy + y) / 2.0;
	}
	return (0);
}
