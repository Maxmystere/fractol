/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpu_calcul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magrab <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 23:39:17 by magrab            #+#    #+#             */
/*   Updated: 2019/03/07 23:39:18 by magrab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
/*
static void lil_gpu()
{

}
*/
int		gpu_calcul(t_frcl param, t_fdf *fdf, const char *src)
{
	t_gpu	tcl;
	cl_mem	mem1;
	cl_mem	mem2;
	cl_context context;
	cl_command_queue cq;
	size_t srcsize;
	size_t worksize;
	cl_kernel k_color;

	clGetPlatformIDs(1, &tcl.ptm, &tcl.ptms);
	clGetDeviceIDs(tcl.ptm, CL_DEVICE_TYPE_ALL, 1, &tcl.dvc, &tcl.dvcs);
	cl_context_properties properties[] = {
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)tcl.ptm,
		0
	};
	context = clCreateContext(properties, 1, &tcl.dvc, NULL, NULL, &tcl.err);
	cq = clCreateCommandQueue(context, tcl.dvc, 0, &tcl.err);
	srcsize = ft_strlen(src);
	cl_program prog = clCreateProgramWithSource(context, 1, &src, &srcsize, &tcl.err);
	clBuildProgram(prog, 0, NULL, "", NULL, NULL);
	
	worksize = param.winsx * param.winsy;
	mem1 = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(param), NULL, &tcl.err);
	mem2 = clCreateBuffer(context, CL_MEM_USE_HOST_PTR, worksize, fdf->istr, &tcl.err);
	k_color = clCreateKernel(prog, "color", &tcl.err);
	clSetKernelArg(k_color, 0, sizeof(mem1), &mem1);
	clSetKernelArg(k_color, 1, sizeof(mem2), &mem2);
	clEnqueueWriteBuffer(cq, mem1, CL_FALSE, 0, sizeof(param), &param, 0, NULL, NULL);
	clEnqueueNDRangeKernel(cq, k_color, 1, NULL, &worksize, NULL, 0, NULL, NULL);
	clEnqueueReadBuffer(cq, mem2, CL_FALSE, 0, worksize, fdf->istr, 0, NULL, NULL);
	clFinish(cq);
	mlx_clear_window(fdf->mlx, fdf->win);
	mlx_put_image_to_window(fdf->istr, fdf->win, fdf->img, 0, 0);
	return (0);
}
