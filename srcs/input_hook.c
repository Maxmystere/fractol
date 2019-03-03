/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 22:01:03 by magrab            #+#    #+#             */
/*   Updated: 2019/02/24 16:07:26 by tferrieu         ###   ########.fr       */
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

int	key_press(int key, t_fdf *fdf)
{
	if (key == 53)
		return (close_hook(fdf));
	if (18 <= key && key <= 20)
		fdf->mouse.x = 0;
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
			fdf->mouse.x = fdf->cam.x - x;
			fdf->mouse.y = fdf->cam.y - y;
		}
		else
			return (mouse_release(1, 0, 0, fdf));
	}
	else if (button == 4 || button == 5)
	{
		move_iso(fdf, (button == 4 ? -4 : -5));
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
		fdf->mouse.x = 0;
		fdf->mouse.y = 0;
	}
	return (0);
}

int	mouse_move(int x, int y, t_fdf *fdf)
{
	if (fdf->mouse.x)
	{
		fdf->cam.x = fdf->mouse.x + x;
		fdf->cam.y = fdf->mouse.y + y;
	}
	return (0);
}
