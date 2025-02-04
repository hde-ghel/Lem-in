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

void		fill_room(t_lemin *env, t_room *new)
{
	if (env->start_room == 1)
	{
		env->start_room++;
		env->start = new;
		new->weight = 0;
		new->type = 1;
		new->ants = env->nb_ants;
	}
	else if (env->end_room == 1)
	{
		env->end_room++;
		env->end = new;
		new->type = 2;
		new->ants = env->nb_ants;
	}
	if (env->map[new->key] == NULL)
		env->map[new->key] = new;
	else
	{
		new->next = env->map[new->key];
		env->map[new->key] = new;
	}
}

void		new_room(t_lemin *env, char *line)
{
	t_room		*new;

	ft_putendl(env->line);
	if (!(new = malloc(sizeof(t_room))))
	{
		ft_strdel(&line);
		error_msg(env, "ERROR: memory allocation failed", 1);
	}
	ft_bzero(new, sizeof(t_room));
	if (!(new->name = ft_strsub(line, 0, strchr(line, ' ') - line)))
	{
		ft_strdel(&line);
		free(new);
		error_msg(env, "ERROR: memory allocation failed", 1);
	}
	new->coord = save_room_coord(line);
	new->key = hash_key(new->name);
	env->nb_rooms++;
	new->weight = MAX_WEIGHT;
	new->ants = 0;
	fill_room(env, new);
}

void		get_room_start_end(t_lemin *env)
{
	int		ret;

	ret = 0;
	while ((ret = get_next_line(env->fd, &env->line)) > 0)
	{
		if (ft_strequ(env->line, "##start") || ft_strequ(env->line, "##end"))
		{
			ft_strdel(&env->line);
			error_msg(env, "ERROR : command start/end after start/end", 1);
		}
		else if (env->line[0] == '#')
			get_comment(env->line);
		else
			break ;
		ft_strdel(&env->line);
	}
	if (ret == -1)
		error_msg(env, "ERROR: reading error or no room for start/end", 1);
	if (isroom(env->line))
		new_room(env, env->line);
	else
	{
		ft_strdel(&env->line);
		error_msg(env, "ERROR: no room given after command start/end", 1);
	}
}

void		get_command(t_lemin *env)
{
	if (ft_strequ(env->line, "##start"))
	{
		if (env->start_room != 0)
		{
			ft_strdel(&env->line);
			error_msg(env, "ERROR more than one room ##start", 1);
		}
		else
			env->start_room = 1;
	}
	else if (ft_strequ(env->line, "##end"))
	{
		if (env->end_room != 0)
		{
			ft_strdel(&env->line);
			error_msg(env, "ERROR more than 1 room ##end", 1);
		}
		else
			env->end_room = 1;
	}
	ft_printf("%s\n", env->line);
	ft_strdel(&env->line);
	get_room_start_end(env);
}

void		parse_rooms(t_lemin *env)
{
	int		ret;

	ret = 0;
	while ((ret = get_next_line(env->fd, &env->line)) > 0)
	{
		if (ft_strequ(env->line, "##start") || ft_strequ(env->line, "##end"))
			get_command(env);
		else if (env->line[0] == '#')
			get_comment(env->line);
		else if (isroom(env->line))
			new_room(env, env->line);
		else if (is_link(env->line, env) == 1)
			break ;
		else
		{
			ft_strdel(&env->line);
			error_msg(env, "ERROR: Wrong room format", 1);
		}
		ft_strdel(&env->line);
	}
	if (ret == -1 || ret == 0)
	{
		ft_strdel(&env->line);
		error_msg(env, "ERROR: reading error or no pipes given", 1);
	}
}
