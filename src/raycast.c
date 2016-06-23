/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 13:35:44 by simzam            #+#    #+#             */
/*   Updated: 2016/06/23 15:15:57 by jomeirin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
//#include <X.h>
#include <math.h>
#include <stdlib.h>
#include "../includes/wolf.h"

static void		init_ray(t_env *e, int x)
{
	e->player.hcamera = 2 * x / (double)(WIN_WIDTH) - 1;
	e->r.pos.x = e->player.pos.x;
	e->r.pos.y = e->player.pos.y;
	e->r.dir.x = e->player.dir.x + e->r.plane.x * e->player.hcamera;
	e->r.dir.y = e->player.dir.y + e->r.plane.y * e->player.hcamera;
	e->r.posmap.x = (int)e->r.pos.x;
	e->r.posmap.y = (int)e->r.pos.y;
	e->r.disd.x = sqrt(1 + (e->r.dir.y * e->r.dir.y)
			/ (e->r.dir.x * e->r.dir.x));
	e->r.disd.y = sqrt(1 + (e->r.dir.x * e->r.dir.x)
			/ (e->r.dir.y * e->r.dir.y));
	e->player.hit = 0;
}

static void		ray_dir(t_env *e)
{
	if (e->r.dir.x < 0)
	{
		e->player.step.x = -1;
		e->r.sidedist.x = (e->r.pos.x - e->r.posmap.x) * e->r.disd.x;
	}
	else
	{
		e->player.step.x = 1;
		e->r.sidedist.x = (e->r.posmap.x + 1.0 - e->r.pos.x) * e->r.disd.x;
	}
	if (e->r.dir.y < 0)
	{
		e->player.step.y = -1;
		e->r.sidedist.y = (e->r.pos.y - e->r.posmap.y) * e->r.disd.y;
	}
	else
	{
		e->player.step.y = 1;
		e->r.sidedist.y = (e->r.posmap.y + 1.0 - e->r.pos.y) * e->r.disd.y;
	}
}

static void		perform_dda(t_env *e)
{
	while (e->player.hit == 0)
	{
		if (e->r.sidedist.x < e->r.sidedist.y)
		{
			e->r.sidedist.x += e->r.disd.x;
			e->r.posmap.x += e->player.step.x;
			e->player.wallside = 0;
		}
		else
		{
			e->r.sidedist.y += e->r.disd.y;
			e->r.posmap.y += e->player.step.y;
			e->player.wallside = 1;
		}
		if (e->map.map[e->r.posmap.x][e->r.posmap.y] > 0)
			e->player.hit = 1;
	}
}

static void		compute(t_env *e)
{
	double dist_to_wall;

	if (e->player.wallside == 0)
		dist_to_wall = fabs((e->r.posmap.x - e->r.pos.x
					+ (1 - e->player.step.x) / 2) / e->r.dir.x);
	else
		dist_to_wall = fabs((e->r.posmap.y - e->r.pos.y
					+ (1 - e->player.step.y) / 2) / e->r.dir.y);
	e->r.lheight = abs((int)(WIN_HEIGH / dist_to_wall));
	e->r.ystart = (-1 * (e->r.lheight)) / 2 + WIN_HEIGH / 2;
	if (e->r.ystart < 0)
		e->r.ystart = 0;
	e->r.yend = e->r.lheight / 2 + WIN_HEIGH / 2;
	if (e->r.yend >= WIN_HEIGH)
		e->r.yend = WIN_HEIGH - 1;
}

int				loop_hook(t_env *e)
{
	t_rgb	c;
	int		x;

	if (e->img.img != NULL)
	{
		//Changed form mlx_destroy_image to this.
		mlx_destroy_image(e->mlx, e->img.img);
		e->img.img = NULL;
	}
	e->img.img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGH);
	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(e, x);
		ray_dir(e);
		perform_dda(e);
		compute(e);
		colors(e, &c);
		draw_line(x, e, &c);
		x++;
	}
	get_time_frame(e);
	move(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.img, 0, 0);
	return (0);
}
