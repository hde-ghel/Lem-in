/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void		revert_selection(t_lemin *env)
{
	t_link		*link;
	t_room		*tmp;

	link = env->links_map;
	while (link)
	{
		if (link->selected > 1)
		{
			tmp = link->room_a;
			link->room_a = link->room_b;
			link->room_b = tmp;
			link->inversed = 0;
			if (link->duplicated > 0)
				link->weight = 0;
			else
				link->weight = 1;
			link->selected = 0;
		}
		link = link->list_next;
	}
}

int			save_and_revert(t_lemin *env, double new, double cost)
{
	if (new < cost)
	{
		if (add_new_path(env) == -1)
		{
			env->nb_paths--;
			return (-1);
		}
		revert_selection(env);
	}
	else
		env->nb_paths--;
	return (1);
}
