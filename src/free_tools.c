/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void free_room_map(t_lemin *env)
{
	int	i;
	t_room  *tmp;
	t_room  *tmp2;

	i = 0;
	while (i < HASH_SIZE - 1)
	{
		if (env->map[i] != NULL)
		{
			ft_strdel(&env->map[i]->name);
			tmp = env->map[i]->next;
			while (tmp)
			{
				tmp2 = tmp->next;
				ft_strdel(&tmp->name);
				free(tmp);
				tmp = tmp2;
			}
		}
		free(env->map[i]);
		i++;
	}
}

void free_links(t_lemin *env)
{
  t_link *tmp;
  t_link *tmp2;

  tmp = env->links_map;
  while (tmp)
  {
    tmp2 = tmp->list_next;
    free(tmp);
    tmp = tmp2;
  }
}

void free_path_list(t_lemin *env)
{
	int		i;

	i = 0;
	while(i < env->max_final_path)
	{
		if (env->path_tab[i])
		{
			free(env->path_tab[i]->room);
			env->path_tab[i]->room = NULL;
			free(env->path_tab[i]);
			env->path_tab[i] = NULL;
		}
		i++;
	}
	free(env->path_tab);
}
