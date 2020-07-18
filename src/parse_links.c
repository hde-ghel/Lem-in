/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		countchar(char *str, char c)
{
	int		i;

	i = 0;
	while(*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}

int		is_link(char *line, t_lemin *env)
{
	t_room	*room_a;
	t_room	*room_b;
	char		*r_a;
	char		*r_b;

  if (countchar(line, '-') != 1)
    return(0);
	r_a = ft_strsub(line, 0, strchr(line, '-') - line);
	r_b = ft_strsub(line, strchr(line, '-') - line + 1, ft_strlen(line));
	room_a = get_room_by_hash(env, hash_key(r_a), r_a);
	room_b = get_room_by_hash(env, hash_key(r_b), r_b);
  ft_strdel(&r_a);
  ft_strdel(&r_b);
	if (!room_a || !room_b)
		return(0);
	return (1);
}

void init_link(t_link *link, t_room *r_a, t_room *r_b)
{
  link->room_a = r_a;
	link->room_b = r_b;
	link->weight = 1;
	link->visited = 1;
	link->inversed = -1;
	link->list_next = NULL;
	link->room_link_next = NULL;
}

void add_link_to_struct(t_lemin *env, t_link *link, t_room *r_a, t_room *r_b)
{
  init_link(link, r_a, r_b);
  //ajout a la liste des liens de la room
  if (!(r_a->link_list))
	{
		r_a->link_list = link;
	}
	else
	{
		link->room_link_next = r_a->link_list;
		r_a->link_list = link;
	}
    //ajout a la liste de liens global
  if (env->links_map == NULL)
		env->links_map = link;
	else
	{
		link->list_next = env->links_map;
		env->links_map = link;
	}
}

int  new_link(t_lemin *env, char *line)
{
  	t_link			*newlink;
  	t_link			*reverselink;
  	t_room			*r_a;
  	t_room			*r_b;
    char        *tmp;

    tmp = ft_strsub(line, 0, strchr(line, '-') - line);
    r_a = get_room_by_hash(env, hash_key(tmp), tmp);
    ft_strdel(&tmp);
    tmp = ft_strsub(line, strchr(line, '-') - line + 1, ft_strlen(line));
  	r_b = get_room_by_hash(env, hash_key(tmp), tmp);
		ft_strdel(&tmp);
  	if (!(r_a) || !(r_b) || !(newlink = ft_memalloc(sizeof(t_link)))
  		|| !(reverselink = ft_memalloc(sizeof(t_link))))
  		return (-1);
    newlink->reverse = reverselink;
    reverselink->reverse = newlink;
    add_link_to_struct(env, newlink, r_a, r_b);
    add_link_to_struct(env, reverselink, r_b, r_a);
		r_a = get_room_by_hash(env, hash_key(r_a->name), r_a->name);
  	env->nb_links++;
  	return (0);
}

void		parse_links(t_lemin *env)
{
	int		ret;

	ret = 0;
	if (!env->line || is_link(env->line, env) != 1)
	{
		ft_strdel(&env->line);
		error_msg(env, "ERROR: Wrong link format");
	}
	//new_link(env->line);
	ft_strdel(&env->line);
	while ((ret = get_next_line(env->fd, &env->line)) > 0)
	{
		if (env->line[0] == '#' && ft_strlen(env->line) > 1 && env->line[1] != '#')
			get_comment(env->line);
		else 	if (is_link(env->line, env) == 1)
			new_link(env, env->line);
		else
			error_msg(env, "ERROR: Wrong link format");
		ft_strdel(&env->line);
	}
	if (ret == -1)
		error_msg(env, "ERROR: reading error");
	else
		ft_strdel(&env->line);
}
