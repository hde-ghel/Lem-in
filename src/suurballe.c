/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int			add_new_path(t_lemin *env)
{
	t_link	*tmp;
	t_room	*room;

	room = env->end;
	while (room)
	{
		tmp = get_link(env, room->path_next, room);
		if (tmp)
		{
			if (tmp->duplicated < 1)
				tmp->selected++;
			if (tmp->reverse)
				tmp->reverse->selected++;
		}
		if (room->path_next == env->start)
			return (0);
		room = room->path_next;
	}
	return (-1);
}

void		inverse_links(t_lemin *env)
{
	t_link	*tmp;
	t_room	*room;
	t_room	*tmproom;

	room = env->end;
	while (room)
	{
		tmp = get_link(env, room->path_next, room);
		if (tmp)
		{
			tmproom = tmp->room_a;
			tmp->room_a = tmp->room_b;
			tmp->room_b = tmproom;
			tmp->weight *= -1;
			tmp->inversed = 1;
		}
		if (room->path_next == env->start)
			break ;
		room = room->path_next;
	}
}

void		reset_room(t_room *room)
{
	room->weight = MAX_WEIGHT;
	room->path_next = NULL;
	if (room->in)
	{
		room->in->weight = MAX_WEIGHT;
		room->in->path_next = NULL;
	}
	if (room->out)
	{
		room->out->weight = MAX_WEIGHT;
		room->out->path_next = NULL;
	}
}

int			reset(t_lemin *env)
{
	t_link	*links;

	links = env->links_map;
	while (links)
	{
		reset_room(links->room_a);
		reset_room(links->room_b);
		links = links->list_next;
	}
	env->start->weight = 0;
	return (1);
}

void		suurballe(t_lemin *env)
{
	double	cost;
	double	new;

	bellman_ford(env);
	if (add_new_path(env) == -1)
		error_msg(env, "ERROR : No possible path", 2);
	check_path_weight(env);
	cost = MAX_WEIGHT;
	new = path_cost(env);
	env->nb_paths++;
	while (new < cost)
	{
		duplicate_path(env);
		inverse_links(env);
		reset(env);
		bellman_ford(env);
		if (check_path_weight(env) == -1)
			break ;
		cost = new;
		new = path_cost(env);
		env->nb_paths++;
		if (save_and_revert(env, new, cost) == -1)
			break ;
	}
}
