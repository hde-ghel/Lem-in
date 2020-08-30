/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:01:39 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/08/30 18:30:23 by alborz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

# define L_FORMAT "L%d-%d "

static void	use_path(t_lemin *env, t_path **paths, int i, int ln)
{
	static int	id = 1;
	int		max;
	t_room		*start;

	max = (int)env->nb_lines;
	start = env->start;
	if (env->nb_lines > (double)(int)env->nb_lines)
		--ln;
	if ((paths[i]->weight + ln) < max && id <= start->ants_id)
	{
		ft_printf(L_FORMAT, id, paths[i]->room[0]->name);
		paths[i]->room[0]->ants_id = id++;
	}
	else
		paths[i]->room[0]->ants_id = 0;
}

static void	print_move(t_path *path, t_room *end, int j)
{
	while (j > 0)
	{
		if (path->room[j] == end)
		{
			ft_printf(L_FORMAT, path->room[j - 1]->ants_id,
					path->room[j]->name);
			end->ants_id--;
		}
		else
		{
			if (path->room[j - 1]->ants_id)
				ft_printf(L_FORMAT, path->room[j - 1]->ants_id,
						path->room[j]->name);
			path->room[j]->ants_id = path->room[j - 1]->ants_id;
		}
		--j;
	}
}

static int	find_empty(t_path *path)
{
	int	j;

	j = path->weight;
	while (j > 0 && !path->room[j - 1]->ants_id)
		--j;
	return (j);
}

int		print_solution(t_lemin *env)
{
	int	i;
	int	j;
	int	ln;
	t_path	**paths;

	i = 0;
	ln = 0;
	paths = env->path_tab;
	while (paths[i])
	{
		j = find_empty(paths[i]);
		print_move(paths[i], env->end, j);
		use_path(env, paths, i, ln);
		if (!paths[++i] && env->end->ants_id)
		{
			i = 0;
			++ln;
			ft_printf("\n");
		}
	}
	ft_printf("\n");
	return (0);
}
