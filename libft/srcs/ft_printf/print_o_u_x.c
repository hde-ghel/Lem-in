/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o_u_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 20:16:39 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/01/19 20:16:44 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static uintmax_t	get_unsinged_type(uintmax_t nb, t_option *opt)
{
	if (opt->mod_h == 2)
		nb = (unsigned char)nb;
	else if (opt->mod_h == 1)
		nb = (unsigned short)nb;
	else if (opt->mod_maj_l == 1)
		nb = (unsigned long)nb;
	else if (opt->mod_maj_l == 2)
		nb = (unsigned long long)nb;
	else
		nb = (unsigned int)nb;
	return (nb);
}

static	void		print_hex(t_option *opt, uintmax_t nb, char *str)
{
	int		nb_len;
	int		full_len;

	nb_len = ft_strlen(str);
	full_len = (opt->precision > nb_len ? opt->precision : nb_len);
	if (!nb && !opt->precision)
		full_len--;
	opt->flag_sharp *= 2;
	if ((opt->width > full_len && !opt->flag_left && !opt->flag_zero) ||
		(opt->precision != -1 && !opt->flag_left && opt->flag_zero))
		padding(opt, opt->width - full_len - (nb ? opt->flag_sharp : 0), ' ');
	if (opt->flag_sharp && nb)
		putstr_len((opt->conversion == 'x') ? "0x" : "0X", opt, 2);
	if (opt->precision > nb_len)
		padding(opt, opt->precision - nb_len, '0');
	if (opt->width && opt->precision < 0 && !opt->flag_left && opt->flag_zero)
		padding(opt, opt->width - nb_len - (nb ? opt->flag_sharp : 0), '0');
	if (nb || opt->precision)
		putstr_len(str, opt, 0);
	if (opt->width > full_len && opt->flag_left)
		padding(opt, opt->width - full_len - (nb ? opt->flag_sharp : 0), ' ');
}

static	void		print_o_u(t_option *opt, uintmax_t nb, char *str)
{
	int nb_len;
	int full_len;

	nb_len = ft_strlen(str);
	full_len = (opt->precision > nb_len ? opt->precision : nb_len);
	(!nb && !opt->precision && !opt->flag_sharp) ? full_len-- : 0;
	if ((opt->width > full_len && !opt->flag_left && !opt->flag_zero) || \
		(opt->precision != -1 && !opt->flag_left && opt->flag_zero))
		padding(opt, opt->width - full_len - \
		(nb && opt->precision <= nb_len ? opt->flag_sharp : 0), ' ');
	if (opt->flag_sharp && nb && opt->conversion == 'o')
		putchar_len('0', opt);
	if (opt->precision > nb_len)
		padding(opt, opt->precision - nb_len - (nb ? opt->flag_sharp : 0), '0');
	if (opt->width && opt->precision < 0 && !opt->flag_left && opt->flag_zero)
		padding(opt, opt->width - nb_len - (nb ? opt->flag_sharp : 0), '0');
	if (nb || opt->precision || opt->flag_sharp)
		putstr_len(str, opt, 0);
	if (opt->width > full_len && opt->flag_left)
		padding(opt, opt->width - full_len - \
		(nb && opt->precision <= nb_len ? opt->flag_sharp : 0), ' ');
}

static	char		*format_itoa(t_printf *env, uintmax_t nb)
{
	if (*env->format == 'x')
		return (u_itoa(nb, "0123456789abcdef", 16));
	else if (*env->format == 'X')
		return (u_itoa(nb, "0123456789ABCDEF", 16));
	else if (*env->format == 'o')
		return (u_itoa(nb, "01234567", 8));
	else if (*env->format == 'u')
		return (u_itoa(nb, "0123456789", 10));
	return (NULL);
}

int					print_oux(t_printf *env, t_option *opt)
{
	uintmax_t	nb;
	char		*str;

	nb = va_arg(env->va, uintmax_t);
	nb = get_unsinged_type(nb, opt);
	if (!(str = format_itoa(env, nb)))
		return (-1);
	if (*env->format == 'x')
		print_hex(opt, nb, str);
	else if (*env->format == 'X')
		print_hex(opt, nb, str);
	else if (*env->format == 'o')
		print_o_u(opt, nb, str);
	else if (*env->format == 'u')
		print_o_u(opt, nb, str);
	ft_strdel(&str);
	env->format++;
	return (0);
}
