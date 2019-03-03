/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:52:04 by magrab            #+#    #+#             */
/*   Updated: 2019/02/24 16:07:30 by tferrieu         ###   ########.fr       */
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

static void		lil_loop(t_fdf *fdf, int mkey, int willshowmenu)
{
	t_tab	pos;

	pos = fdf->keys;
	while (pos)
	{
		mlx_clear_window(fdf->mlx, fdf->win);
		mkey = pos->data;
		if (mkey == 46)
			willshowmenu++;
		move_iso(fdf, mkey);
		if (mkey == 18 || mkey == 19 || mkey == 20)
			ft_noderm_int(&(fdf->keys), mkey);
		pos = pos->next;
		draw_text(fdf, 0, 0);
	}
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
			if (fdf[x].keys || fdf[x].mouse.x)
			{
				lil_loop(&(fdf[x]), 0, 0);
			}
		}
		x++;
	}
	return (0);
}
