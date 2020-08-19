/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_final_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:01:39 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:54 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

t_room *get_right_room(t_lemin *env, t_link *link)
{
	t_room *room;

	if (link->room_a->name == env->start->name)
		room = link->room_b;
	else
		room = link->room_a;
	return (room);
}

int		check_link_used(t_lemin *env, t_link *link, int nb_path)//(arg, t_data_map **map, t_linkstab *links, int way)
{//
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = get_right_room(env, link); //(links, arg);
	while (i < nb_path && env->path_tab[i]->room[0] != NULL)
	{
		if (ft_strcmp(env->path_tab[i]->room[0], tmp->name) == 0)
			return (-1);
		i++;
	}
	return (1);
}

t_room 	*get_next_room(t_lemin *env, t_room *tmp, t_path *new_path)
{
	t_link *link;

	link = env->links_map;
	if (new_path->room[0] == NULL)
		return (tmp);
	while (link)
	{
		if (link->selected == 1)
		{
			if ((ft_strcmp(link->room_a->name, tmp->name) == 0)
				&& check_follow(new, arg, link->room_b) == 0)
				return (link->room_b);
			if ((ft_strcmp(link->room_b->name, tmp->name) == 0)
				&& (check_follow(new, arg, link->room_a) == 0))
				return (link->room_a);
			}
			link = link->list_next;
		}
		return (NULL);
}

void 	save_path(t_lemin *env, t_link *link, int nb_path)
{
	t_path	*new_path;
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = get_right_room(env, link);
	if (!tmp)
		return ;//potentiellement inutile
	if (!(new_path = ft_memalloc(sizeof(t_path))))
		error_msg(env, "ERROR : malloc");
	if (!(new_path->room = ft_memalloc(sizeof(char *) * 500)))
		error_msg(env, "ERROR : malloc");
	while ((tmp = get_next_room(env, tmp, new_path)) != env->end)//follow_path(new, arg, map, tmp)) != arg->end && tmp)
		new_path->room[i++] = tmp->name;
	new_path->weight = i + 1;
	env->final_path_weight += i;
	new_path->path_nb = nb_path;
	new_path->room[i] = env->end->name;
	env->path_tab[nb_path] = new_path;
}

void find_final_paths(t_lemin *env)
//find_nbr_way(t_data_map **map, t_lemin *arg, t_linkstab *links, int f) int nb_paths
{
  int nb_path;
  t_link *link;

	nb_path = 0;
  link = env->links_map;
	while (link)
	{
		if (link->selected == 1)
		{
			if (env->start->name == link->room_a->name
				|| env->start->name == link->room_b->name)
			{
				if (check_link_used(env, link, nb_path) == 1)//(arg, map, links, path) == 0)
				{
					save_path(env, link, nb_path);//(map, arg, links, path);
					nb_path++;
				}
				if (nb_path == env->max_final_path)
					return ;
			}
		}
		link = link->list_next;
	}
}
