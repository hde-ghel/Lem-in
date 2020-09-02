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

void	print_link_list(t_lemin *env)
{
	t_link	*tmp;

	tmp = env->links_map;
	while (tmp)
	{
		ft_putstr("roma = ");
		if (tmp->room_a)
			ft_putstr(tmp->room_a->name);
		ft_putstr(" roomb = ");
		if (tmp->room_b)
			ft_putstr(tmp->room_b->name);
		ft_putstr("\n");
		tmp = tmp->list_next;
	}
}

void	print_new_path(t_lemin *env)
{
	t_room	*tmp;

	tmp = env->end;
	while (tmp)
	{
		ft_printf("%s", tmp->name);
		if (tmp->path_next != 0)
			ft_printf("->");
		tmp = tmp->path_next;
	}
	ft_putstr("\n");
}

void	print_final_paths(t_lemin *env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_printf("nb_path = %f  max_final_path = %d\n", env->nb_lines,
		env->max_final_path);
	while (i < env->max_final_path)
	{
		j = 0;
		ft_printf("path weight = %d\n", env->path_tab[i]->weight);
		ft_printf("path nb = %d\n", env->path_tab[i]->path_nb + 1);
		while (env->path_tab[i]->room[j])
			ft_printf("%s->", env->path_tab[i]->room[j++]->name);
		ft_printf("\n\n");
		i++;
	}
}
