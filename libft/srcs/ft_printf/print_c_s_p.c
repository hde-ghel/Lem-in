/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 10:41:47 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/01/22 17:59:59 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

void		print_char(t_printf *env, t_option *opt)
{
	if (opt->flag_left != 1)
		padding(opt, opt->width - 1, (opt->flag_zero ? '0' : ' '));
	ft_putchar(va_arg(env->va, int));
	opt->arg_length += 1;
	if (opt->flag_left == 1)
		padding(opt, opt->width - 1, (opt->flag_zero ? '0' : ' '));
	env->format++;
}

void		print_string(t_printf *env, t_option *opt)
{
	char	*str;
	int		len;
	int		arg_len;

	if ((str = va_arg(env->va, char *)) != NULL)
	{
		arg_len = ft_strlen(str);
		len = (opt->precision >= 0) ? opt->precision : arg_len;
		if (len > arg_len)
			len = arg_len;
		if (opt->width > len && !opt->flag_left)
			padding(opt, opt->width - len, opt->flag_zero ? '0' \
					: ' ');
		if (len)
			putstr_len(str, opt, len);
		if (opt->width > len && opt->flag_left)
			padding(opt, opt->width - len, ' ');
	}
	else
		putstr_len("(null)", opt, 6);
	env->format++;
}

int			print_p(t_printf *env, t_option *opt)
{
	char		*str;
	int			len;
	uintmax_t	nb;
	int			precision;

	nb = va_arg(env->va, uintmax_t);
	if (!(str = u_itoa(nb, "0123456789abcdef", 16)))
		return (-1);
	len = ft_strlen(str) + 2;
	precision = opt->precision > len - 2 ? opt->precision - len + 2 : 0;
	if ((opt->width > len && !opt->flag_left && !opt->flag_zero) ||
		(opt->precision != -1 && !opt->flag_left && opt->flag_zero))
		padding(opt, opt->width - len - precision + \
				(*str == '0' && !opt->precision ? 1 : 0), ' ');
	putstr_len("0x", opt, 2);
	if (opt->width && opt->precision < 0 && !opt->flag_left && opt->flag_zero)
		padding(opt, opt->width - len + precision, '0');
	(opt->precision != -1) ? padding(opt, precision, '0') : 0;
	(nb || opt->precision) ? putstr_len(str, opt, len - 2) : 0;
	if (opt->width > len && opt->flag_left)
		padding(opt, opt->width - len - precision + (!nb && !opt->precision ? \
					1 : 0), ' ');
	ft_strdel(&str);
	env->format++;
	return (0);
}
