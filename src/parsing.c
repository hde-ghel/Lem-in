/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		get_command(t_lemin *env)
{
	return (0);
}

int		get_comment(t_lemin *env)
{
	if (env->input[env->input_index + 1] == '#')
		return (get_command(env));
	else
	{
		while (env->input[env->input_index] && env->input[env->input_index] != '\n')
			env->input[env->input_index] += 1;
	}
	return (0);
}

int		get_ant(t_lemin *env)
{
	int		i;

	i = env->input_index;
	while (env->input[i] && env->input[i] != '\n')
	{
		if (!ft_isdigit(env->input[i]))
			return (error("ERROR"));
		i++;
	}
	if ((env->nb_ants = ft_atoi(&env->input[env->input_index])) < 0)
		return (error("ERROR"));
	env->input_index += i + 1;
	return (0);
}

int		parse_input(t_lemin *env)
{
	env->input_index = 0;
	if (get_ant(env) == -1)
		return (-1);
	while (env->input[env->input_index])
	{
		if (env->input[env->input_index] == '#')
			get_comment(env);
		env->input[env->input_index] += 1; //passe le \n
	}
	return (0);
}
