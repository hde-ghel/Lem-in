/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:01:39 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:54 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void		print_one_link_solution(t_lemin *env)
{
	int		i;

	i = 0;
	ft_printf("\n");
	while (i++ < env->nb_ants)
		ft_printf("L%i-%s ", i, env->end->name);
	ft_printf("\nnb_lines = %d\n", 1);
}

void		print_usage(t_lemin *env)
{
	ft_putendl("usage:\n./lem_in < \"map-file\" or ./lem_in -m \"map-file\"\n\
\nOptions:\n-h : print usage (only print usage)\n-i : print error_msg\n-m : \
enter a file-name\n");
	if (env->fd)
		close(env->fd);
	exit(0);
}

void		open_map_file(t_lemin *env, int *i, char **av)
{
	(*i)++;
	if (!isatty(env->fd) || env->fd)
		error_msg(env, "Only one map can be specified", 0);
	if ((env->fd = open(av[*i], O_RDONLY)) == -1)
		error_msg(env, "ERROR : map_file cannot be opened", 0);
	(*i)++;
}

void		check_arg(t_lemin *env, char **av, int ac)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (ft_strequ(av[i], "-h"))
			print_usage(env);
		else if (ft_strequ(av[i], "-e"))
			env->log = PRINT_LOG;
		else if (ft_strequ(av[i], "-m"))
			open_map_file(env, &i, av);
		else
		{
			ft_printf("error: wrong option \"%s\"\n\n", av[i]);
			print_usage(env);
		}
		i++;
	}
}

int			main(int ac, char **av)
{
	t_lemin		env;

	ft_bzero(&env, sizeof(env));
	env.map = (t_room **)ft_memalloc(sizeof(t_room *) * HASH_SIZE); //protection
	env.nb_lines = INT_MAX;
	if (ac != 1)
		check_arg(&env, av, ac);
	parse_input(&env);
	if (env.end_start_link == 1)
		print_one_link_solution(&env);
	else
	{
		suurballe(&env);
		solve_map(&env);
		print_solution(&env);
		free_path_list(&env);
	}
	if (env.fd)
		close(env.fd);
	free_room_map(&env);
	free_links(&env);
	return (0);
}
