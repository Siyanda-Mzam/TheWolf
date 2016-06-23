/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: simzam <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 13:16:31 by simzam            #+#    #+#             */
/*   Updated: 2016/06/23 15:39:30 by jomeirin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"
#include <stdlib.h>
#include <math.h>

int			key_press(int keycode, t_env *e)
{
	if (keycode == 65361 || keycode == 0x7B)
		e->player.move.left = 1;
	if (keycode == 65362 || keycode == 0x7E)
		e->player.move.up = 1;
	if (keycode == 65363 || keycode == 0x7C)
		e->player.move.right = 1;
	if (keycode == 65364 || keycode == 0x7D)
		e->player.move.down = 1;
	if (keycode == 65505 || keycode == 0x38)
		e->player.sprint = 1;
	return (0);
}

int			key_release(int keycode, t_env *e)
{
	if (keycode == 65307 || keycode == 0x35)
		exit(0);
	if (keycode == 65361 || keycode == 0x7B)
		e->player.move.left = 0;
	if (keycode == 65362 || keycode == 0x7E)
		e->player.move.up = 0;
	if (keycode == 65363 || keycode == 0x7C)
		e->player.move.right = 0;
	if (keycode == 65364 || keycode == 0x7D)
		e->player.move.down = 0;
	if (keycode == 65505 || keycode == 0x38)
		e->player.sprint = 0;
	return (0);
}

static void	turn(t_env *e, char dir)
{
	double	tmp_dir;
	double	tmp_plane;
	int		co_eff;

	co_eff = 1;
	tmp_dir = e->player.dir.x;
	tmp_plane = e->r.plane.x;
	if (dir == 'R')
		co_eff = -1;
	e->player.dir.x = e->player.dir.x * cos(co_eff * e->player.rspeed)
		- e->player.dir.y * sin(co_eff * e->player.rspeed);
	e->player.dir.y = tmp_dir * sin(co_eff * e->player.rspeed)
		+ e->player.dir.y * cos(co_eff * e->player.rspeed);
	e->r.plane.x = e->r.plane.x * cos(co_eff * e->player.rspeed)
		- e->r.plane.y * sin(co_eff * e->player.rspeed);
	e->r.plane.y = tmp_plane * sin(co_eff * e->player.rspeed)
		+ e->r.plane.y * cos(co_eff * e->player.rspeed);
}

void		move(t_env *e)
{
	if (e->player.move.up)
	{
		if (!(e->map.map[(int)(e->player.pos.x + e->player.dir.x
			* e->player.mspeed)][(int)(e->player.pos.y)]))
			e->player.pos.x += e->player.dir.x * e->player.mspeed;
		if (!(e->map.map[(int)(e->player.pos.x)][(int)(e->player.pos.y
			+ e->player.dir.y * e->player.mspeed)]))
			e->player.pos.y += e->player.dir.y * e->player.mspeed;
	}
	if (e->player.move.left)
		turn(e, 'L');
	if (e->player.move.right)
		turn(e, 'R');
	if (e->player.move.down)
	{
		if (!(e->map.map[(int)(e->player.pos.x - e->player.dir.x
			* e->player.mspeed)][(int)(e->player.pos.y)]))
			e->player.pos.x -= e->player.dir.x * e->player.mspeed;
		if (!(e->map.map[(int)(e->player.pos.x)][(int)(e->player.pos.y
			- e->player.dir.y * e->player.mspeed)]))
			e->player.pos.y -= e->player.dir.y * e->player.mspeed;
	}
	if (e->player.sprint)
		e->player.mspeed *= 0.05;
}
