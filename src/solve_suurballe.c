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

void 	save_path(t_lemin *env, t_link *link, int nb_path)
{

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

void solve_map(t_lemin *env)
{
  env->max_final_path = env->nb_paths;
	if (!(env->path_tab = ft_memalloc(sizeof(t_path *) * env->nb_paths)))
		error_msg(env, "ERROR : malloc");//free map + link
	find_final_paths(env);//(map, arg, (*map)->links, path)
	//		return (-1);
}
