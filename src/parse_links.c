/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/09/13 14:55:31 by ababaie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		is_link(char *line, t_lemin *env)
{
	t_room		*room_a;
	t_room		*room_b;
	char		*r_a;
	char		*r_b;

	if (countchar(line, '-') != 1)
		return (0);
	if (!(r_a = ft_strsub(line, 0, strchr(line, '-') - line)))
	{
		ft_strdel(&line);
		error_msg(env, "ERROR: allocation failed\n", 2);
	}
	room_a = get_room_by_hash(env, hash_key(r_a), r_a);
	ft_strdel(&r_a);
	if (!(r_b = ft_strsub(line, strchr(line, '-') - line + 1, ft_strlen(line))))
	{
		ft_strdel(&line);
		error_msg(env, "ERROR: allocation failed\n", 2);
	}
	room_b = get_room_by_hash(env, hash_key(r_b), r_b);
	ft_strdel(&r_b);
	if (!room_a || !room_b)
		return (0);
	new_link(env, env->line, room_a, room_b);
	return (1);
}

void	init_link(t_link *link, t_room *r_a, t_room *r_b)
{
	link->room_a = r_a;
	link->room_b = r_b;
	link->weight = 1;
	link->visited = 1;
	link->inversed = -1;
	if (!(r_a->link_list))
		r_a->link_list = link;
	else
	{
		link->room_link_next = r_a->link_list;
		r_a->link_list = link;
	}
}

void	add_link_to_struct(t_lemin *env, t_link *link)
{
	if ((link->room_a->type == 1 && link->room_b->type == 2) ||
		(link->room_b->type == 1 && link->room_a->type == 2))
		env->end_start_link = 1;
	if (env->links_map == NULL)
	{
		env->links_map = link;
		link->list_next = NULL;
	}
	else
	{
		link->list_next = env->links_map;
		env->links_map = link;
	}
}

int		new_link(t_lemin *env, char *line, t_room *r_a, t_room *r_b)
{
	t_link			*newlink;
	t_link			*reverselink;

	if (check_double_link(env, r_a, r_b) == -1)
		return (-1);
	if (!(newlink = ft_memalloc(sizeof(t_link))))
	{
		ft_strdel(&line);
		error_msg(env, "ERROR: allocation failed\n", 2);
	}
	if (!(reverselink = ft_memalloc(sizeof(t_link))))
	{
		free(newlink);
		ft_strdel(&line);
		error_msg(env, "ERROR: allocation failed\n", 2);
	}
	newlink->reverse = reverselink;
	reverselink->reverse = newlink;
	init_link(newlink, r_a, r_b);
	init_link(reverselink, r_b, r_a);
	add_link_to_struct(env, newlink);
	add_link_to_struct(env, reverselink);
	env->nb_links++;
	return (0);
}

void	parse_links(t_lemin *env)
{
	int		ret;

	ret = 0;
	ft_putendl(env->line);
	ft_strdel(&env->line);
	while ((ret = get_next_line(env->fd, &env->line)) > 0)
	{
		if (env->line[0] == '#')
			get_comment(env->line);
		else if (is_link(env->line, env) == 1)
			ft_putendl(env->line);
		else
		{
			if (env->log == 1)
				ft_printf("ERROR: wrong link format, solving actual farm\n");
			break ;
		}
		ft_strdel(&env->line);
	}
	(ret == -1) ? error_msg(env, "ERROR: read\n", 2) : ft_strdel(&env->line);
	while (get_next_line(env->fd, &env->line) > 0)
		ft_strdel(&env->line);
}
