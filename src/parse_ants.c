/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/08/23 23:57:18 by ababaie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

#define ERROR_NUM "ERROR: numbers of ants is negative or null\n"
#define ERROR_FORM "ERROR: wrong format for ants number\n"
#define ERROR_FILE "ERROR: file error or empty file\n"
#define ERROR_ANTS "ERROR numbers of ants is negative or null\n"
#define ERROR_EMPTY "ERROR: file error or empty file\n"

static	int		isnbr(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == '-' || str[i] == '+' || str[i] == ' '))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

void			parse_ants(t_lemin *env)
{
	int		ret;
	char	*line;

	line = NULL;
	while ((ret = get_next_line(env->fd, &line)) > 0)
	{
		if (isnbr(line) == 1)
		{
			if ((env->nb_ants = ft_atoi(line)) <= 0)
				error_free_str(env, ERROR_ANTS, line);
			ft_printf("%s\n", line);
			break ;
		}
		else if (line[0] == '#')
			get_comment(line);
		else
			error_free_str(env, ERROR_FORM, line);
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (ret == -1 || ret == 0)
		error_msg(env, ERROR_EMPTY, 0);
}
