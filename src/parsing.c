/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

//Pas sur de recup les comment
void		get_comment(char *str)
{
	ft_printf("%s\n", str);
}

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

int		is_link(char *line)
{
	t_room	room_a;
	t_room	room_b;

	if (countchar(line, '-') != 1)
		return(0);
	room_a = get_hash_room();
	room_b = get_hash_room();
	if (!room_a || !room_b)
		return(0);
	return (1);
}

/*
void		parse_links(t_lemin *env)
{
	int		ret;

	ret = 0;
	if (is_link(env->line == -1)
	{
		ft_strdel(&env->line);
		error_msg(env, "ERROR: Wrong link format");
	}
	new_link(env->line);
	ft_strdel(&env->line);
	while ((ret = get_next_line(env->fd, &env->line)) > 0)
	{
		if (env->line[0] == '#' && ft_strlen(env->line) > 1 && env->line[1] != '#')
			get_comment(env->line);
		else if ((is_link(env->line))
			new_link(env, env->line);
		else
			error_msg(env, "ERROR: Wrong link format");
		ft_strdel(&env->line);
	}
	ft_strdel(&env->line);
	if (ret == -1)
		error_msg("ERROR: reading error");
}
*/
void	parse_input(t_lemin *env)
{
	if (isatty(env->fd))
		error_msg(env, "No map file specified");
	parse_ants(env);
	printf("nb ants = %d\n", env->nb_ants);
	parse_rooms(env);
	//parse_links();
}
