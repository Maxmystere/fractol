/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:52:04 by magrab            #+#    #+#             */
/*   Updated: 2019/02/24 16:07:30 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
** 18 : 1 key
** 19 : 2 key
** 20 : 3 key
** 21 : 4 key
** 46 : M key
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

void			lil_drawer(t_fdf *fdf)
{
	if (fdf->fractype == MANDEL)
		draw_mandel(fdf);
	else if (fdf->fractype == JULIA)
		draw_julia(fdf);
	else if (fdf->fractype == BSHIP)
		draw_ship(fdf);
	else if (fdf->fractype == DOUADY)
		draw_douady(fdf);
	else if (fdf->fractype == GALAXY)
		draw_glx(fdf);
	else if (fdf->fractype == TRICORN)
		draw_tricorn(fdf);
}

static void		lil_loop(t_fdf *fdf, int mkey, int willshowmenu)
{
	t_tab	pos;

	pos = fdf->keys;
	while (pos)
	{
		mkey = pos->data;
		if (mkey == 46)
			willshowmenu++;
		move_iso(fdf, mkey);
		if (18 <= mkey && mkey <= 23)
		{
			change_color(fdf, mkey);
			ft_noderm_int(&(fdf->keys), mkey);
		}
		pos = pos->next;
	}
	lil_drawer(fdf);
	draw_text(fdf, 0, 0);
	if (willshowmenu)
		show_menu(fdf);
}

int				loop_hook(t_fdf *fdf)
{
	int x;

	x = 0;
	while (fdf[x].mlx)
	{
		if (fdf[x].win)
		{
			if (fdf[x].keys || fdf[x].cam.jon || fdf[x].mouse.sx)
			{
				lil_loop(&(fdf[x]), 0, 0);
			}
		}
		x++;
	}
	return (0);
}
