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

void		new_room(t_lemin *env, char *line)
{
	ft_printf("new room : %s\n", line);
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
}

int		count_space(char *line)
{
	int		space;

	space = 0;
	while (*line)
	{
		if (*line == ' ')
			space++;
		*line++;
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
	char	*line;

	ret = 0;
	line = NULL;
	while ((ret = get_next_line(env->fd, &line)) > 0)
	{
		if (line[0] == '#' && ft_strlen(line) > 1 && line[1] != '#')
			get_comment(line);
		else if (line[0] == '#' && ft_strlen(line) > 1 && line[1] == '#')
			get_command(env, line);
		else if (isroom(line))
			new_room(env, line);
		else
			break;
		ft_strdel(&line);
	}
	if (ret == -1 || ret == 0)
		error_msg(env, "ERROR: reading error or EOF"); // strdel(line) free(rooms)
}
