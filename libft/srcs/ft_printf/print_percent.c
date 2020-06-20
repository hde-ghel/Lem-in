/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:23:32 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/01/19 20:17:30 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int		print_percent(t_printf *env, t_option *opt)
{
	if (!opt->flag_left)
		padding(opt, opt->width - 1, opt->flag_zero ? '0' : ' ');
	putchar_len(*env->format, opt);
	if (opt->flag_left)
		padding(opt, opt->width - 1, ' ');
	env->format++;
	return (0);
}
