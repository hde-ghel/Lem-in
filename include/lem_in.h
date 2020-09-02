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

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <fcntl.h>

# define PRINT_LOG 1
# define HASH_SIZE 500000
# define MAX_WEIGHT INT_MAX

typedef	struct s_room	t_room;
typedef	struct s_link	t_link;
typedef	struct s_path	t_path;

typedef	struct			s_xy
{
	int					x;
	int					y;
}						t_xy;

struct					s_room
{
	char				*name;
	t_xy				coord;
	int					type;
	unsigned long		key;
	int					weight;
	int					duplicated;
	int					ants;
	t_room				*out;
	t_room				*in;
	t_room				*path_next;
	t_link				*link_list;
	t_room				*next;
};

struct					s_link
{
	t_room				*room_a;
	t_room				*room_b;
	int					weight;
	int					visited;
	int					inversed;
	int					duplicated;
	int					selected;
	int					check_selected;
	t_link				*reverse;
	t_link				*room_link_next;
	t_link				*list_next;
};

struct					s_path
{
	int					path_nb;
	int					weight;
	t_room				**room;
};

typedef	struct			s_lemin
{
	t_room				**map;
	t_link				*links_map;
	t_path				**path_tab;
	int					end_start_link;
	int					fd;
	char				*line;
	int					start_room;
	int					end_room;
	int					nb_ants;
	unsigned long		nb_rooms;
	unsigned long		nb_links;
	unsigned long		nb_paths;
	int					max_final_path;
	int					total_weight;
	int					final_path_weight;
	double				nb_lines;
	t_room				*start;
	t_room				*end;
	int					log;
}						t_lemin;

/*
** error.c
*/
void					error_msg(t_lemin *env, char *str, int free);
void					error_free_str(t_lemin *env, char *msg, char *str);
void					error_exit(void);

/*
** parsing.c
*/
void					parse_input(t_lemin *env);
void					get_comment(char *str);
int						countchar(char *str, char c);
int						check_double_link(t_lemin *env, t_room *r_a,
							t_room *r_b);

/*
** parse_ants.c
*/
void					parse_ants(t_lemin *env);

/*
** parse_rooms.c
*/
void					parse_rooms(t_lemin *env);
int						isroom(char *line);
void					get_command(t_lemin *env);

/*
** parse_rooms_tools.c
*/
int						isroom(char *line);
int						count_space(char *line);
t_xy					save_room_coord(char *line);

/*
** parse_links.c
*/
void					parse_links(t_lemin *env);
void					add_link_to_struct(t_lemin *env, t_link *link);
int						is_link(char *line, t_lemin *env);
int						new_link(t_lemin *env, char *line, t_room *r_a,
							t_room *r_b);

/*
** Hash.c
*/
unsigned long			hash_key(char *name);
t_room					*get_room_by_hash(t_lemin *env, unsigned long key,
							char *room);
t_link					*get_link(t_lemin *env, t_room *a, t_room *b);
t_link					*get_link_by_room(t_room *a, t_room *b);

/*
** print_utils.c
*/
void					print_link_list(t_lemin *env);
void					print_new_path(t_lemin *env);
void					print_final_paths(t_lemin *env);

/*
** suurballe.c
*/
void					suurballe(t_lemin *env);
int						add_new_path(t_lemin *env);

/*
** suurballe_tools.c
*/
int						save_and_revert(t_lemin *env, double new, double cost);

/*
** bellman_ford.c
*/
void					bellman_ford(t_lemin *env);

/*
** path_tools.c
*/
double					path_cost(t_lemin *env);
int						check_path_weight(t_lemin *env);

/*
** free_tools.c
*/
void					free_links(t_lemin *env);
void					free_room_map(t_lemin *env);
void					free_path_list(t_lemin *env);

/*
** dup_room.c
*/
void					duplicate_path(t_lemin *env);

/*
** solve_suurballe.c
*/
void					solve_map(t_lemin *env);

/*
** find_final_paths.c
*/
t_room					*get_right_room(t_lemin *env, t_link *link);
t_room					*get_next_room(t_lemin *env, t_room *tmp,
							t_path *new_path);
int						check_next_room(t_lemin *env, t_path *new_path,
								t_room *room);
int						check_start_link_used(t_lemin *env, t_link *link,
								int nb_path);

/*
** find_final_paths.c
*/
void					print_solution(t_lemin *env);
#endif
