/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_suurballe_tools.c                            :+:      :+:    :+:   */
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
