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
	if (!(r_a = ft_strsub(line, 0, strchr(line, '-') - line)))
	{
		ft_strdel(&line);
		error_msg(env, "ERROR: allocation failed", 2);
  }
	room_a = get_room_by_hash(env, hash_key(r_a), r_a);
	ft_strdel(&r_a);
	if (!(r_b = ft_strsub(line, strchr(line, '-') - line + 1, ft_strlen(line))))
	{
		ft_strdel(&line);
		error_msg(env, "ERROR: allocation failed", 2);
	}
	room_b = get_room_by_hash(env, hash_key(r_b), r_b);
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
	//ajout a la liste des liens de la room
  if (!(r_a->link_list))
		r_a->link_list = link;
	else
	{
		link->room_link_next = r_a->link_list;
		r_a->link_list = link;
	}
}

void add_link_to_struct(t_lemin *env, t_link *link, t_room *r_a, t_room *r_b)
{
	if ((link->room_a->type == 1 && link->room_b->type == 2) ||
		(link->room_b->type == 1 && link->room_a->type == 2))
			env->end_start_link = 1;
  //ajout a la liste de liens global
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

int  new_link(t_lemin *env, char *line)
{
  	t_link			*newlink;
  	t_link			*reverselink;
  	t_room			*r_a;
  	t_room			*r_b;
    char        *tmp;

    if (!(tmp = ft_strsub(line, 0, strchr(line, '-') - line)))
		{
			ft_strdel(&line);
			error_msg(env, "ERROR: allocation failed", 2);
		}
    r_a = get_room_by_hash(env, hash_key(tmp), tmp);
    ft_strdel(&tmp);
    if (!(tmp = ft_strsub(line, strchr(line, '-') - line + 1, ft_strlen(line))))
		{
			ft_strdel(&line);
			error_msg(env, "ERROR: allocation failed", 2);
		}
  	r_b = get_room_by_hash(env, hash_key(tmp), tmp);
		ft_strdel(&tmp);
  	if (!(r_a) || !(r_b) || r_a == r_b || get_link_by_room(env, r_a, r_b))
			return(-1);
		if (!(newlink = ft_memalloc(sizeof(t_link))))
			{
				ft_strdel(&line);
				error_msg(env, "ERROR: allocation failed", 2);
			}
  	if(!(reverselink = ft_memalloc(sizeof(t_link))))
		{
			free(newlink);
			ft_strdel(&line);
			error_msg(env, "ERROR: allocation failed", 2);
		}
		ft_printf("%s\n", env->line);
    newlink->reverse = reverselink;
    reverselink->reverse = newlink;
		init_link(newlink, r_a, r_b);
		init_link(reverselink, r_b, r_a);
    add_link_to_struct(env, newlink, r_a, r_b);
    add_link_to_struct(env, reverselink, r_b, r_a);
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
		error_msg(env, "ERROR: Wrong room format", 1);
	}
	new_link(env, env->line);
	ft_strdel(&env->line);
	while ((ret = get_next_line(env->fd, &env->line)) > 0)
	{
		if (env->line[0] == '#')
			get_comment(env->line);
		else 	if (is_link(env->line, env) == 1)
			new_link(env, env->line);
		else
		{
			ft_printf("ERROR: wrong link format, solving with actual ant farm\n");
			break;
		}
		ft_strdel(&env->line);
	}
	if (ret == -1)
		error_msg(env, "ERROR: reading error", 2);
	else
		ft_strdel(&env->line);
}
