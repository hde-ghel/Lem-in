/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:21:09 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/07 18:27:10 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		get_input(t_lemin *env)
{
	//if (is_ant())
	//if (is_link())
	//if (is_comment())
	//if (is_room())
	return (0);
}

int		read_input(t_lemin *env)
{
	int			nb_buff;
	int			nb_buff_max;
	char		buff[BUFF_SIZE];
	char		*tmp;
	int			read_ret;

	nb_buff = 1;
	nb_buff_max = 1;
	read_ret = 0;
	printf("salut");
	while ((read_ret = read(0, buff, BUFF_SIZE -1)) > 0)
	{
		printf("salut2");
		if (nb_buff == nb_buff_max)
		{
			nb_buff_max *= 2;
			nb_buff = 0;
			tmp = env->read_tab;
			env->read_tab = (char *)malloc((sizeof(char) * nb_buff_max * BUFF_SIZE) + 1);
			env->read_tab[nb_buff_max * BUFF_SIZE] = '\0';
			env->read_tab = ft_strcat(tmp, buff);
			ft_strdel(&tmp);
		}
		else
		{
			env->read_tab = ft_strcat(env->read_tab, buff);
			nb_buff += 1;
		}
		printf("%d\n", read_ret);
	}
	printf("%d\n", read_ret);
	if (read_ret < 0)
		return(-1);
	return (0);
}
