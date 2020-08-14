/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/07/30 17:04:17 by ababaie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

//Pas sur de recup les comment

void	get_comment(char *str)
{
	ft_printf("%s\n", str);
}

void	parse_input(t_lemin *env)
{
	if (isatty(env->fd))
		error_msg(env, "No map file specified\n");
	parse_ants(env);
	ft_printf("Number of ants = %d\n\n", env->nb_ants);
	parse_rooms(env);
	parse_links(env);
	//print_room_map(env);
	//print_link_list(env);
}
