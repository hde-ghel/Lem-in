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

char		*read_input(void)
{
	char		buff[BUFF_SIZE + 1];
	char		*str;
	int			read_ret;

	read_ret = 0;
	str = ft_strnew(0);
	while ((read_ret = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[read_ret] = '\0';
		str = ft_strjoin_free(str, buff, 1);
	}
	if (read_ret < 0)
	{
		ft_strdel(&str);
		return(NULL);
	}
	return (str);
}
