/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_drawer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 19:53:08 by magrab            #+#    #+#             */
/*   Updated: 2019/02/24 16:07:41 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static t_pos	new_p(int x, int y, int c)
{
	t_pos tmp;

	tmp.x = x;
	tmp.y = y;
	tmp.c = c;
	return (tmp);
}

void			draw_order(t_fdf *fdf, int x, int y, int c)
{
	draw_line(fdf, new_p(x, y - 25, c), new_p(x - 22, y - 12, c));
	draw_line(fdf, new_p(x, y - 25, c), new_p(x + 22, y - 12, c));
	draw_line(fdf, new_p(x - 22, y + 12, c), new_p(x - 22, y - 12, c));
	draw_line(fdf, new_p(x - 22, y + 12, c), new_p(x, y + 25, c));
	draw_line(fdf, new_p(x + 22, y + 12, c), new_p(x, y + 25, c));
	draw_line(fdf, new_p(x + 22, y + 12, c), new_p(x + 22, y - 12, c));
	draw_line(fdf, new_p(x - 14, y + 17, c), new_p(x - 14, y - 8, c));
	draw_line(fdf, new_p(x, y - 16, c), new_p(x - 14, y - 8, c));
	draw_line(fdf, new_p(x - 7, y - 20, c), new_p(x + 14, y - 8, c));
	draw_line(fdf, new_p(x + 14, y + 8, c), new_p(x + 14, y - 8, c));
	draw_line(fdf, new_p(x + 22, y + 4, c), new_p(x, y + 17, c));
	draw_line(fdf, new_p(x, y + 17, c), new_p(x - 14, y + 8, c));
}
