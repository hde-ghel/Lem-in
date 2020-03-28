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

# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h> //a retiré !!!

# define PRINT_LOG 1

typedef	struct	s_lemin
{

	int			fd;
	int			start_room;
	int			end_room;
	int			nb_ants;

	int			log;
}				t_lemin;

/*
 * error.c
*/
void		error_msg(char *str);
void		error_free_str(char *msg, char *str);

/*
 * parsing.c
*/
void		parse_input(t_lemin *env);

#endif
