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

//passe les commentaires et recupere les commandes start et end
void		get_comment(t_lemin *env, char *line)
{
	if (ft_strequ(line, "##start"))
		{
			if (env->start_room != 0)
				error_free_str("ERROR more than one room start", line);
			else
				env->start_room = 1;
		}
	else if (ft_strequ(line, "##end"))
	{
			if (env->end_room != 0)
				error_free_str("ERROR more than 1 room end", line);
			else
				env->end_room = 1;
	}
}

void		get_ants(t_lemin *env)
{
	int		i;
	int		ret;
	char	*line;

	i = 0;
	line = NULL;
	while ((ret = get_next_line(env->fd, &line)) > 0)
	{
		if (!ft_isdigit(line[i]))
			error_free_str("ERROR", line);
	}
	if (ret == -1)
		error_msg("ERROR malloc GNL in get_ants()");
	if ((env->nb_ants = ft_atoi(line)) < 0)
		error_free_str("ERROR negative numbers of ants", line);
}

void	parse_input(t_lemin *env)
{
	get_ants(env);
	//get_rooms();
	//get_link();
	//get_comment(env);
	if (env->log == PRINT_LOG)
		printf("nb ants =%d\n", env->nb_ants);
}
