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

char	*ftoa_bis(char *f_str, char *d_str, long double float_part)
{
	if (!(f_str = ull_itoa((unsigned long long)float_part)))
		return (free_str(d_str, NULL));
	if (!(d_str = ft_strjoin_free(d_str, ".", 1)))
		return (free_str(d_str, f_str));
	if (!(d_str = ft_strjoin_free(d_str, f_str + 1, 1)))
		return (free_str(d_str, f_str));
	ft_strdel(&f_str);
	return (d_str);
}
