/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int			count_space(char *line)
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

t_xy		save_room_coord(char *line)
{
	t_xy		coord;
	int			i;

	i = 0;
	while (line[i] != ' ')
		i++;
	coord.x = ft_atoi(&line[i]);
	i++;
	while (line[i] != ' ')
		i++;
	coord.y = ft_atoi(&line[i]);
	return (coord);
}

int			isroom(char *line)
{
	int		i;

	i = 0;
	if (!line || line[0] == '#' || line[0] == 'L' || count_space(line) != 2)
		return (0);
	while (line[i] != ' ')
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
	while (line[i])
		if (ft_isdigit(line[i++]) == 0)
			return (0);
	return (1);
}
