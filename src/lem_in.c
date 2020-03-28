/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:01:39 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:54 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void		print_usage()
{
	ft_putendl("usage: ./lem_in ");
}

void	check_arg(t_lemin *env, char **av, int ac)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (ft_strequ(av[i], "-h"))
			print_usage();
		else if (ft_strequ(av[i], "-l"))
			env->log = PRINT_LOG;
		//else if (ft_strequ(av[i], "-m"))
		//	read_file();
		else
			error_msg("error: wrong option\nusage: ./lem_in\n");
		i++;
	}
}

int		main(int ac, char **av)
{
	t_lemin		*env;

	ft_bzero(&env, sizeof(env));
	if (ac != 1)
		check_arg(env, av, ac);
	parse_input(env);
	return (0);
}
