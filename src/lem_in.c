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

static void	print_usage(t_lemin *env)
{
	ft_printf("USAGE:\n./lem_in < \"map-file\" or ./lem_in -m \"map-file\"\
		\n\nOPTIONS:\n-h : print usage (only print usage)\
		\n-i : print input\n-m : enter a file-name\n");
	if (env->fd)
		close(env->fd);
	exit(0);
}

static void	open_map_file(t_lemin *env, int *i, char **av)
{
	(*i)++;
	if (!isatty(env->fd) || env->fd)
		error_msg(env, "Only one map can be specified");
	if ((env->fd = open(av[*i], O_RDONLY)) == -1)
		error_msg(env, "ERROR: map_file cannot be opened");
	(*i)++;
}

static void	check_arg(t_lemin *env, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_strequ(av[i], "-h"))
			print_usage(env);
		else if (ft_strequ(av[i], "-i"))
			env->log = PRINT_LOG;
		else if (ft_strequ(av[i], "-m"))
			open_map_file(env, &i, av);
		else
		{
			ft_printf("ERROR: wrong option \"%s\"\n\n", av[i]);
			print_usage(env);
		}
		i++;
	}
}

int		main(int ac, char **av)
{
	t_lemin	env;

	ft_bzero(&env, sizeof(env));
	env.nb_lines = INT_MAX;
	if (ac != 1)
		check_arg(&env, ac, av);
	parse_input(&env);
	suurballe(&env);
	if (env.fd)
		close(env.fd);
	free_room_map(&env);
	return (0);
}
