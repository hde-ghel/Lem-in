/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:01:39 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:54 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		check_path_used(t_lemin *env)//(arg, t_data_map **map, t_linkstab *links, int way)
{//
	t_room	*tmp;
	int		i;

	i = 0;
	tmp = switch_room(links, arg);
	while (i < way && (*map)->way[i]->path_list[0] != NULL)
	{
		if (ft_strcmp((*map)->way[i]->path_list[0], tmp->room) == 0)
			return (-1);
		i++;
	}
	return (1);
}

void find_final_paths(t_lemin *env)
//find_nbr_way(t_data_map **map, t_lemin *arg, t_linkstab *links, int f) int nb_paths
{
  int path;
  t_link *links;

	path = 0;
  links = env->links_map;
	while (links)
	{
		if (links->selected == 1)
		{
			if (env->start->name == links->room_a->name
				|| env->start->name == links->room_b->name)
			{
				if (check_path_used(env) == 1)//(arg, map, links, path) == 0)
				{
					//if (stock_path(map, arg, links, path) == -1)
					//	return (-1);
					path++;
				}
				if (path == env->max_final_path)
					return ;
			}
		}
		links = links->list_next;
	}
}

void solve_map(t_lemin *env)
{
  env->max_final_path = env->nb_paths;
	find_final_paths(env);//(map, arg, (*map)->links, path)
	//		return (-1);
}
