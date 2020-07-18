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
		error_msg(env, "ERROR: memory allocation failed"); // malloc error free
	ft_bzero(new, sizeof(t_room));
	new->name = ft_strsub(line, 0, strchr(line, ' ') - line); // protection
	new->coord = save_room_coord(line);
	new->key = hash_key(new->name);
	env->nb_rooms++;
	if (env->start_room == 1)
		{
			env->start_room++;
			env->start = new;
		}
	else if (env->end_room == 1)
	{
		env->end_room++;
		new->weight = MAX_WEIGHT;
		env->end = new;
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
				error_free_str(env, "ERROR more than one room ##start", line);
			else
				env->start_room = 1;
		}
	else if (ft_strequ(line, "##end"))
	{
			if (env->end_room != 0)
				error_free_str(env, "ERROR more than 1 room ##end", line);
			else
				env->end_room = 1;
	}
	//else error command unknown
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
		error_msg(env, "ERROR: reading error or no pipes given"); // strdel(line) free(rooms)
}
