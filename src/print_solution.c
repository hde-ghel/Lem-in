/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:01:39 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:54 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

static void		use_path(t_lemin *env, t_path **paths, int i, int lines)
{
	static int	id = 1;
	t_room		*start;
	int			max;

	max = (int)env->nb_lines;
	start = env->start;
	if (env->nb_lines > (double)(int)env->nb_lines)
		lines--;
	if ((paths[i]->weight + lines) < max && id <= start->ants)
	{
		ft_printf("L%d-%s ", id, paths[i]->room[0]->name);
		paths[i]->room[0]->ants = id++;
	}
	else
		paths[i]->room[0]->ants = 0;
}

static void		print_move(t_path *path, t_room *end, int j)
{
	while (j > 0)
	{
		if (path->room[j] == end)
		{
			ft_printf("L%d-%s ", path->room[j - 1]->ants, path->room[j]->name);
			end->ants--;
		}
		else
		{
			if (path->room[j - 1]->ants)
				ft_printf("L%d-%s ", path->room[j - 1]->ants,
					path->room[j]->name);
			path->room[j]->ants = path->room[j - 1]->ants;
		}
		j--;
	}
}

static int		find_empty(t_path *path)
{
	int		j;

	j = path->weight;
	while (j > 0 && !path->room[j - 1]->ants)
		j--;
	return (j);
}

void			print_solution(t_lemin *env)
{
	int		i;
	int		lines;
	int		j;

	i = 0;
	lines = 0;
	ft_printf("\n");
	while (env->path_tab[i])
	{
		j = find_empty(env->path_tab[i]);
		print_move(env->path_tab[i], env->end, j);
		use_path(env, env->path_tab, i, lines);
		if (!env->path_tab[++i] && env->end->ants)
		{
			i = 0;
			lines++;
			ft_printf("\n");
		}
	}
	if (env->log == 1)
		ft_printf("\nnb_lines = %d\n", lines + 1);
}
