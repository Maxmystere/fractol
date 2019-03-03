/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 20:23:43 by magrab            #+#    #+#             */
/*   Updated: 2019/02/24 16:08:38 by tferrieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
** nwin = number of left windows
** while fdf[x].mlx will check if there is any other windows opened and will
** close if there isnt any left
*/

int		close_hook(t_fdf *fdf)
{
	int		x;
	int		nwin;

	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	fdf->win = NULL;
	nwin = 0;
	x = -fdf->p_win.nb;
	while (fdf[x].mlx)
	{
		if (fdf[x].win)
			nwin++;
		x++;
	}
	if (nwin == 0)
	{
		free(&(fdf[-fdf->p_win.nb]));
		exit(0);
	}
	return (0);
}
