/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:34:47 by magrab            #+#    #+#             */
/*   Updated: 2019/02/24 16:07:20 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#define N NULL

/*
** Put here initial camera value
*/

static int		load_imgs(t_fdf *fdf)
{
	if (!(fdf->img = mlx_new_image(fdf->mlx, fdf->p_win.sx, fdf->p_win.sy)))
		return (-1);
	fdf->istr = (int *)mlx_get_data_addr(fdf->img, &(fdf->bpp),
										&(fdf->s_l), &(fdf->e));
	clGetPlatformIDs(1, &fdf->g.ptm, &fdf->g.ptms);
	clGetDeviceIDs(fdf->g.ptm, CL_DEVICE_TYPE_GPU,
				1, &fdf->g.dvc, &fdf->g.dvcs);
	fdf->g.properties[0] = CL_CONTEXT_PLATFORM;
	fdf->g.properties[1] = (cl_context_properties)fdf->g.ptm;
	fdf->g.properties[2] = 0;
	fdf->g.c = clCreateContext(fdf->g.properties, 1, &fdf->g.dvc, N, N, N);
	fdf->g.cq = clCreateCommandQueue(fdf->g.c, fdf->g.dvc, 0, N);
	return (0);
}

static void		short_load(void *mlx, t_fdf *fdf, int v)
{
	fdf[v].mlx = mlx;
	fdf[v].p_win.sx = WINX;
	fdf[v].p_win.sy = WINY;
	fdf[v].p_win.nb = v;
	fdf[v].keys = NULL;
	fdf[v].color = 0xF0F0F0;
	fdf[v].cam.x = 0;
	fdf[v].cam.y = 0;
	fdf[v].cam.jon = 0;
	if (fdf[v].fractype == JULIA)
		fdf[v].cam.jon = 1;
	fdf[v].mouse.sx = 0;
	fdf[v].mouse.sy = 0;
	fdf[v].cam.z = 150;
	fdf[v].cam.iter = MAX_ITER;
}

static int		searchtype(t_fdf *fdf, char *winname, int v)
{
	if (!(ft_strcmp("m", winname)) || !(ft_strcmp("mandelbrot", winname)))
		fdf[v].fractype = MANDEL;
	else if (!(ft_strcmp("j", winname)) || !(ft_strcmp("julia", winname)))
		fdf[v].fractype = JULIA;
	else if (!(ft_strcmp("b", winname)) || !(ft_strcmp("burningship", winname)))
		fdf[v].fractype = BSHIP;
	else if (!(ft_strcmp("d", winname)) || !(ft_strcmp("douady", winname)))
		fdf[v].fractype = DOUADY;
	else if (!(ft_strcmp("g", winname)) || !(ft_strcmp("galaxy", winname)))
		fdf[v].fractype = GALAXY;
	else if (!(ft_strcmp("t", winname)) || !(ft_strcmp("tricorn", winname)))
		fdf[v].fractype = TRICORN;
	else
	{
		fdf[v].fractype = -1;
		return (0);
	}
	return (1);
}

static int		load_all(void *mlx, t_fdf *fdf, int winnb, char **winname)
{
	int v;
	int winopened;

	v = -1;
	winopened = 0;
	while (++v < winnb - 1)
	{
		fdf[v].mlx = mlx;
		if (!(searchtype(fdf, winname[v + 1], v)))
			ft_printf("Error : %s invalid\n", winname[v + 1]);
		else if (++winopened)
		{
			short_load(mlx, fdf, v);
			fdf[v].p_win.title = winname[v + 1];
			if (!(fdf[v].win = mlx_new_window(mlx, fdf[v].p_win.sx,
											fdf[v].p_win.sy, winname[v + 1])))
				return (-1);
			if (load_imgs(&(fdf[v])) != 0)
				return (-1);
		}
	}
	return (winopened);
}

t_fdf			*init_mlx(int winnb, char **winname)
{
	t_fdf	*fdf;
	void	*mlx;

	if (winnb < 2)
		return (NULL);
	if (!(fdf = malloc(sizeof(t_fdf) * (unsigned long)winnb)))
		return (NULL);
	fdf[winnb - 1].mlx = NULL;
	if (!(mlx = mlx_init()))
		return (NULL);
	if (load_all(mlx, fdf, winnb, winname) <= 0)
		exit(0);
	return (fdf);
}
