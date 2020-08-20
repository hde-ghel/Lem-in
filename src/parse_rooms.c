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

t_xy save_room_coord(char *line)
{
	t_xy 		coord;
	int			i;

	i = 0;
	while (line[i] != ' ')
		i++;
	coord.x = ft_atoi(&line[i]);
	i++;
	while(line[i] != ' ')
	i++;
	coord.y = ft_atoi(&line[i]);;
	return (coord);
}

void		new_room(t_lemin *env, char *line) //peut etre rajouter une check savoir si la room existe deja
{
	t_room		*new;

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
	if (env->start_room == 1)
		{
			env->start_room++;
			env->start = new;
			new->weight = 0;
			new->type = 1;
		}
	else if (env->end_room == 1)
	{
		env->end_room++;
		env->end = new;
		new->type = 2;
	}
	if (env->map[new->key] == NULL)
		env->map[new->key] = new;
	else
		{
			new->next = env->map[new->key];
			env->map[new->key] = new;
		}
}

void		get_command(t_lemin *env, char *line)
{
	if (ft_strequ(line, "##start"))
		{
			if (env->start_room != 0)
			{
				ft_strdel(&line);
				error_msg(env, "ERROR more than one room ##start", 1);
      }
			else
				env->start_room = 1;
		}
	else if (ft_strequ(line, "##end"))
	{
			if (env->end_room != 0)
			{
				ft_strdel(&line);
				error_msg(env, "ERROR more than 1 room ##end", 1);
      }
			else
				env->end_room = 1;
	}
	//else error command unknown or skip
}

int		count_space(char *line)
{
	int		space;

	space = 0;
	while (*line)
	{
		if (*line == ' ')
			space++;
		line++;
	}
	return (space);
}

int		isroom(char *line)
{
	int		i;

	i = 0;
	if (line[0] == '#' || line[0] == 'L' || count_space(line) != 2)
		return (0);
	while(line[i] != ' ')
		{
			if (line[i] == '-')
				return (0);
			i++;
		}
	i++;
	if (line[i] == '-' || line[i] == '+')
		i++;
	while (line[i] != ' ')
		if (ft_isdigit(line[i++]) == 0)
			return (0);
	i++;
	if (line[i] == '-' || line[i] == '+')
		i++;
	while(line[i])
		if (ft_isdigit(line[i++]) == 0)
			return (0);
	return (1);
}

void		parse_rooms(t_lemin *env)
{
	int		ret;

	ret = 0;
	while ((ret = get_next_line(env->fd, &env->line)) > 0)
	{
		if (env->line[0] == '#' && ft_strlen(env->line) > 1 && env->line[1] != '#')
			get_comment(env->line);
		else if (env->line[0] == '#' && ft_strlen(env->line) > 1 && env->line[1] == '#')
			get_command(env, env->line);
		else if (isroom(env->line))
			new_room(env, env->line);
		else
			break;
		ft_strdel(&env->line);
	}
	if (ret == -1 || ret == 0)
	{
		ft_strdel(&env->line);
		error_msg(env, "ERROR: reading error or no pipes given", 1);
  }
}
