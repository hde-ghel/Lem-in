/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void    change_room_in_links(t_room *room)
{
  t_link  *link;

  link = room->link_list;
  while(link)
  {
    link->room_a = room->out;
    link = link->room_link_next;
  }
}

void	init_room_out(t_lemin *env, t_room *room, t_room *out)
{
	out->duplicated = 2;
	out->key = hash_key(out->name);
	out->in = room;
  room->duplicated = 1;
	room->out = out;
	if (env->map[out->key] == NULL)
		env->map[out->key] = out;
	else
	{
		out->next = env->map[out->key];
		env->map[out->key] = out;
	}
	change_room_in_links(room);
  out->link_list = room->link_list;
}

void  create_out_link(t_lemin *env, t_room *room, t_room *out)
{
  t_link *link;

	if (!(link = ft_memalloc(sizeof(t_link))))
	{
		ft_strdel(&out->name);
		free(out);
	  error_msg(env, "ERROR : malloc");
	}
	link->room_a = room;
	link->room_b = out;
	link->duplicated = 1;
	link->selected = 1;
	link->room_b->path_next = link->room_a;
  link->room_a->link_list = link;
	add_link_to_struct(env, link, room, out);
}

void	dup_room(t_lemin *env, t_room *room)
{
	t_room *out;

	if (!(out = ft_memalloc(sizeof(t_room))))
    error_msg(env, "ERROR : malloc");//free
	if (!(out->name = ft_strdup(room->name)))
	{
		free(out);
		error_msg(env, "ERROR : malloc");//free
	}
	init_room_out(env, room, out);
	create_out_link(env, room, out);
}

void		duplicate_path(t_lemin *env)
{
  t_room *room;

  room = env->end;
	while (room && room != env->start)
	{
		if (room->path_next && room->path_next->duplicated < 1 &&
			room->path_next != env->start)
		{
			dup_room(env, room->path_next);
			room->path_next = room->path_next->out;
		}
		room = room->path_next;
	}
}
