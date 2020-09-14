/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_final_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:01:39 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/09/14 22:08:13 by ababaie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

t_room		*get_right_room(t_lemin *env, t_link *link)
{
	t_room *room;

	if (link->room_a->name == env->start->name)
		room = link->room_b;
	else
		room = link->room_a;
	return (room);
}

int			check_start_link_used(t_lemin *env, t_link *link, int nb_path)
{
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = get_right_room(env, link);
	while (i < nb_path && env->path_tab[i]->room[0] != NULL)
	{
		if (ft_strcmp(env->path_tab[i]->room[0]->name, tmp->name) == 0)
			return (-1);
		i++;
	}
	return (1);
}

int			check_next_room(t_lemin *env, t_path *new_path, t_room *room)
{
	int i;

	i = 0;
	if (ft_strcmp(room->name, env->start->name) == 0)
		return (1);
	while (new_path->room[i] != NULL)
	{
		if (ft_strcmp(new_path->room[i]->name, room->name) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	link_assign(t_link *link)
{
	link->visited = 1;
	link->reverse->visited = 1;
}

t_room		*get_next_room(t_lemin *env, t_room *tmp, t_path *new_path)
{
	t_link *link;

	link = env->links_map;
	if (new_path->room[0] == NULL)
		return (tmp);
	while (link)
	{
		if (link->selected == 1 && link->visited != 1)
		{
			if ((ft_strcmp(link->room_a->name, tmp->name) == 0)
			&& check_next_room(env, new_path, link->room_b) == 0)
			{
				link_assign(link);
				return (link->room_b);
			}
			if ((ft_strcmp(link->room_b->name, tmp->name) == 0)
			&& (check_next_room(env, new_path, link->room_a) == 0))
			{
				link_assign(link);
				return (link->room_a);
			}
		}
		link = link->list_next;
	}
	return (NULL);
}
