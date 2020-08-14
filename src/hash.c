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

t_link *get_link(t_lemin *env, t_room *a, t_room *b)
{
  t_link  *link;

  link = env->links_map;
  while (link)
  {
    if (ft_strequ(link->room_b->name, b->name) && ft_strequ(link->room_a->name, a->name))
      return (link);
    link = link->list_next;
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

t_room		*get_room_by_hash(t_lemin *env, unsigned long key, char *room)
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
