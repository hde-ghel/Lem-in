/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

double	path_cost(t_lemin *env)
{
	int		tmp;
	double	turns;

	tmp = env->nb_ants + env->total_weight;
	turns = ((double)tmp / ((double)env->nb_paths + 1)) - 1.0;
	if (turns < env->nb_lines)
		env->nb_lines = turns;
	return (turns);
}

int		count_select(t_lemin *env)
{
	t_room		*room;
	t_link		*link;

	room = env->end;
	while (room)
	{
		link = get_link(env, room->path_next, room);
		if (link)
		{
			if (link->duplicated < 1)
			{
				env->total_weight++;
				link->check_selected++;
			}
			if (link->reverse)
				link->reverse->check_selected++;
		}
		if (room->path_next == env->start)
			return (1);
		room = room->path_next;
	}
	return (0);
}

int		check_path_weight(t_lemin *env)
{
	int		tmpweight;
	t_link	*link;

	tmpweight = env->total_weight;
	if (count_select(env) == 1)
	{
		link = env->links_map;
		while (link)
		{
			if (link->check_selected > 1)
			{
				if (link->duplicated < 1)
					env->total_weight--;
				link->check_selected = 0;
			}
			link = link->list_next;
		}
	}
	else
	{
		env->total_weight = tmpweight;
		return (-1);
	}
	return (1);
}
