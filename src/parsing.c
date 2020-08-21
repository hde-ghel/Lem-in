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

void	parse_input(t_lemin *env)
{
	if (isatty(env->fd))
		error_msg(env, "ERROR : No map file specified", 0);
	parse_ants(env);
	//printf("nb ants = %d\n\n", env->nb_ants);
	parse_rooms(env);
	if (env->start_room == 0 || env->end_room == 0)
	{
		ft_strdel(&env->line);
		error_msg(env, "ERROR : End room or start room missing", 1);
	}
	parse_links(env);
	//print_room_map(env);
	//print_link_list(env);
}
