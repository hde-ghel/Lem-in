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

# define BUFF_SIZE 500



typedef	struct	s_lemin
{
	char		*input;
	int			input_index;
	int			nb_ants;

}				t_lemin;

/*
 * read.c
*/
char		*read_input(void);

/*
 * error.c
*/
int			error(char *str);

/*
 * parsing.c
*/
int			parse_input(t_lemin *env);

#endif
