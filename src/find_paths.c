/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"


int		bellwhile_ford(t_link *link, t_lemin *env)
{
	int changed;

	changed = 0;
	while (link)
	{
			if (link->room_a->weight != MAX_WEIGHT
				&& link->room_a->weight + link->weight < link->room_b->weight
				&& link->room_b != env->start && link->room_a != env->end)
			{
				link->room_b->weight = link->weight + link->room_a->weight;
				link->room_b->path_next = link->room_a;
				changed = 1;
		}
		link = link->list_next;
	}
	return (changed);
}

void		bellman_ford(t_lemin *env)
{
	t_link	*link;
	int			countrooms;

	countrooms = env->nb_rooms;
	link = env->links_map;
	while (--countrooms > 0 && link)
	{
		link = env->links_map;
		if (bellwhile_ford(link, env) == 0)
			break ;
	}
}


void    find_paths(t_lemin *env)
{
  bellman_ford(env);
}
