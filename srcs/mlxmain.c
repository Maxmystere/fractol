/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab   <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 16:32:14 by magrab            #+#    #+#             */
/*   Updated: 2019/03/04 21:33:06 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void		draw_more(t_fdf *fdf, int x, int y)
{
	char	*tmp;
	char	*nbstr;

	nbstr = ft_itoa(fdf->cam.iter);
	tmp = ft_strjoin("iter : ", nbstr);
	mlx_string_put(fdf->mlx, fdf->win, 50, y + 100, 0xf44336, tmp);
	free(nbstr);
	free(tmp);
	nbstr = ft_itoa(fdf->cam.z);
	tmp = ft_strjoin("zoom : ", nbstr);
	mlx_string_put(fdf->mlx, fdf->win, 50, y + 120, 0xf44336, tmp);
	free(nbstr);
	free(tmp);
	(void)x;
}

void			draw_text(t_fdf *fdf, int x, int y)
{
	char *tmp;
	char *nbstr;

	draw_order(fdf, fdf->p_win.sx - 50, fdf->p_win.sy - 50, 0x500b00);
	draw_order(fdf, fdf->p_win.sx - 49, fdf->p_win.sy - 49, 0xff6950);
	draw_order(fdf, fdf->p_win.sx - 49, fdf->p_win.sy - 50, 0xff6950);
	draw_order(fdf, fdf->p_win.sx - 50, fdf->p_win.sy - 49, 0xff6950);
	nbstr = ft_itoa(-fdf->cam.x);
	tmp = ft_strjoin("X : ", nbstr);
	mlx_string_put(fdf->mlx, fdf->win, 50, y + 50, 0xf44336, tmp);
	free(nbstr);
	free(tmp);
	nbstr = ft_itoa(-fdf->cam.y);
	tmp = ft_strjoin("Y : ", nbstr);
	mlx_string_put(fdf->mlx, fdf->win, 50, y + 75, 0xf44336, tmp);
	free(nbstr);
	free(tmp);
	draw_more(fdf, x, y);
}

void			show_menu(t_fdf *fdf)
{
	int y;

	y = fdf->p_win.sy - 60;
	mlx_string_put(fdf->mlx, fdf->win, 15, y - 213, 0x7f8c8d,
								"_______________________________________");
	mlx_string_put(fdf->mlx, fdf->win, 10, y - 192, 0xe74c3c, "   Tutorial");
	mlx_string_put(fdf->mlx, fdf->win, 15, y - 185, 0x7f8c8d,
								"_______________________________________");
	mlx_string_put(fdf->mlx, fdf->win, 10, y - 160, 0xFFFFFF,
								"   Change color : 1, 2, 3, 4, 5, 6");
	mlx_string_put(fdf->mlx, fdf->win, 10, y - 140, 0xFFFFFF,
								"   Press P to reset position");
	mlx_string_put(fdf->mlx, fdf->win, 10, y - 120, 0xFFFFFF,
								"   Move : Arrow Keys or Mouse Press");
	mlx_string_put(fdf->mlx, fdf->win, 10, y - 100, 0xFFFFFF,
								"   Zoom in/out : + / -");
	mlx_string_put(fdf->mlx, fdf->win, 10, y - 80, 0xFFFFFF,
								"   Change interatiom : 8 / 2 (NUMPAD)");
	mlx_string_put(fdf->mlx, fdf->win, 40, y - 60, 0xFFFFFF, "Show Menu : M");
	mlx_string_put(fdf->mlx, fdf->win, 40, y - 20, 0xbdc3c7, "Quit : Esc");
	mlx_string_put(fdf->mlx, fdf->win, 15, y - 8, 0x7f8c8d,
								"_______________________________________");
	while ((y -= 17) > fdf->p_win.sy - 265)
		mlx_string_put(fdf->mlx, fdf->win, 10, y + 5, 0x7f8c8d,
								"|                                      |");
}

static void		lilmain(t_fdf *fdf, int x)
{
	show_menu(&(fdf[x]));
	if (fdf[x].fractype == MANDEL)
		draw_mandel(&(fdf[x]));
	else if (fdf[x].fractype == JULIA)
		draw_julia(&(fdf[x]));
	else if (fdf[x].fractype == BSHIP)
		draw_ship(&(fdf[x]));
	mlx_hook(fdf[x].win, 2, 0, key_press, &(fdf[x]));
	mlx_hook(fdf[x].win, 3, 0, key_release, &(fdf[x]));
	mlx_hook(fdf[x].win, 4, 0, mouse_press, &(fdf[x]));
	mlx_hook(fdf[x].win, 5, 0, mouse_release, &(fdf[x]));
	mlx_hook(fdf[x].win, 6, 0, mouse_move, &(fdf[x]));
	mlx_hook(fdf[x].win, 17, 0, close_hook, &(fdf[x]));
}

int				main(int ac, char **av)
{
	t_fdf	*fdf;
	int		x;

	if (!(fdf = init_mlx(ac, av)))
	{
		ft_putstr("Usage: fractol mandelbrot / julia / burningship\n");
		return (-1);
	}
	x = -1;
	mlx_do_key_autorepeatoff(fdf->mlx);
	while (++x < ac - 1)
	{
		if (fdf[x].win)
		{
			lilmain(fdf, x);
		}
	}
	mlx_loop_hook(fdf->mlx, loop_hook, fdf);
	if (ac > 1)
		mlx_loop(fdf[0].mlx);
	return (0);
}
