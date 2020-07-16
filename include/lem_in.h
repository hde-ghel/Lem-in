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

# define	PRINT_LOG 1
# define	HASH_SIZE 500000
# define	MAX_WEIGHT INT_MAX -10

typedef struct s_room		t_room;

typedef	struct	s_xy
{
	int		x;
	int		y;
}								t_xy;

struct	s_room
{
	char					*name;
	t_xy					coord;
	int						type;
	unsigned long	key;
	int						weight;
	t_room				*next;
};

typedef	struct	s_links
{
	t_room		*room_a;
	t_room		*room_b;
	int				weight;
}								t_links;


typedef	struct	s_lemin
{
	t_room					*map[HASH_SIZE];


	int							fd;
	char						*line;
	int							start_room;
	int							end_room;
	int							nb_ants;
	unsigned long		nb_rooms;
	t_room					*start;
	t_room					*end;
	int							log;
}				t_lemin;

/*
 * error.c
*/
void		error_msg(t_lemin *env, char *str);
void		error_free_str(t_lemin *env, char *msg, char *str);
void free_room_map(t_lemin *env);

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
/*
 * Hash.c
*/
unsigned long	hash_key(char *name);

/*
 * print_utils.c
*/
void print_room_map(t_lemin *env);

#endif
