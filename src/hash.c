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

t_link			*get_link(t_lemin *env, t_room *a, t_room *b)
{
	t_link	*link;

	if (!a || !b)
		return (NULL);
	link = env->links_map;
	while (link)
	{
		if (link->room_b == b && link->room_a == a &&
			link->room_a->duplicated == a->duplicated &&
			link->room_b->duplicated == b->duplicated)
			return (link);
		link = link->list_next;
	}
	return (NULL);
}

t_link			*get_link_by_room(t_room *a, t_room *b)
{
	t_link	*link;

	if (!a || !b)
		return (NULL);
	link = a->link_list;
	while (link)
	{
		if (link->room_b == b && link->room_a == a)
			return (link);
		link = link->room_link_next;
	}
	return (NULL);
}

unsigned long	hash_key(char *name)
{
	unsigned long	hash;

	hash = 0;
	if (!(name))
		return (0);
	while (*name)
	{
		hash = (hash * 18) + *name++ +
		'h' + 'd' + 'e';
	}
	return (hash % HASH_SIZE);
}

t_room			*get_room_by_hash(t_lemin *env, unsigned long key, char *room)
{
	t_room *tmp;

	tmp = env->map[key];
	while (tmp)
	{
		if (tmp->key == key && ft_strcmp(room, tmp->name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
