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

void solve_map(t_lemin *env)
{
  env->max_final_path = env->nb_paths;
	if (!(env->path_tab = ft_memalloc(sizeof(t_path *) * env->nb_paths)))
		error_msg(env, "ERROR : malloc");//free map + link
	find_final_paths(env);//(map, arg, (*map)->links, path)
  print_final_paths(env);
	//		return (-1);
}
