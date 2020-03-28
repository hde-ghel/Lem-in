/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:21:44 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 15:09:59 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	error_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(-1);
}

void	error_free_str(char *msg, char *str)
{
	ft_putstr_fd(msg, 2);
	ft_strdel(&str);
	exit(-1);
}
