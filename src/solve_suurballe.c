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
				if (check_start_link_used(env, link, nb_path) == 1)
				{
					save_path(env, link, nb_path);
					nb_path++;
				}
				if (nb_path == env->max_final_path)
					return ;
			}
		}
		link = link->list_next;
	}
}

void sort_final_path(t_lemin *env)
{
  int     i;
  int     j;
  t_path  *tmp;

  i = 0;
  while(i < env->max_final_path)
  {
    j = 0;
    while (j < env->max_final_path)
    {
      if (env->path_tab[j]->weight > env->path_tab[i]->weight)
      {
        tmp = env->path_tab[i];
        env->path_tab[i] = env->path_tab[j];
        env->path_tab[j] = tmp;
      }
      j++;
    }
    i++;
  }
}

void solve_map(t_lemin *env)
{
  env->max_final_path = env->nb_paths;
	if (!(env->path_tab = ft_memalloc(sizeof(t_path *) * env->nb_paths)))
		error_msg(env, "ERROR : malloc");//free map + link
	find_final_paths(env);
  sort_final_path(env);
  //print_final_paths(env);
}
