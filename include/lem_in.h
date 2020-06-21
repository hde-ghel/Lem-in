/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:58:44 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:03:28 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <fcntl.h>


# include <stdio.h> //a retiré !!!

# define PRINT_LOG 1

typedef	struct	s_lemin
{
	int			fd;
	char		*line;
	int			start_room;
	int			end_room;
	int			nb_ants;

	int			log;
}				t_lemin;

/*
 * error.c
*/
void		error_msg(t_lemin *env, char *str);
void		error_free_str(t_lemin *env, char *msg, char *str);

/*
 * parsing.c
*/
void		parse_input(t_lemin *env);
void		get_comment(char *str);
void		get_command(t_lemin *env,char *str);

/*
 * parse_ants.c
*/
void		parse_ants(t_lemin *env);

/*
 * parse_rooms.c
*/
void		parse_rooms(t_lemin *env);

/*
 * parse_links.c
*/
void		parse_links(t_lemin *env);

#endif
