/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:21:09 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 14:54:37 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

char		*read_input(void)
{
	char		buff[BUFF_SIZE + 1];
	char		*str;
	int			read_ret;

	read_ret = 0;
	if (!(str = ft_strnew(0)))
		return (NULL);
	while ((read_ret = read(0, buff, BUFF_SIZE)) > 0)
	{
		buff[read_ret] = '\0';
		if (!(str = ft_strjoin_free(str, buff, 1)))
		{
			ft_strdel(&str);
			return (NULL);
		}
	}
	if (read_ret < 0)
	{
		ft_strdel(&str);
		return(NULL);
	}
	return (str);
}
