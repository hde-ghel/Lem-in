/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:21:44 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/08/24 00:37:16 by ababaie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	error_msg(t_lemin *env, char *msg, int free)
{
	if (free == 1)
		free_room_map(env);
	if (free == 2)
	{
		free_room_map(env);
		free_links(env);
	}
	if (free == 3)
	{
		free_room_map(env);
		free_links(env);
		free_path_list(env);
	}
	if (env->log == 1)
		ft_putstr_fd(msg, 2);
	else
		ft_putstr("ERROR\n");
	if (env->fd)
		close(env->fd);
	exit(-1);
}

void	error_free_str(t_lemin *env, char *msg, char *str)
{
	ft_putstr_fd(msg, 2);
	ft_strdel(&str);
	if (env->fd)
		close(env->fd);
	exit(-1);
}
