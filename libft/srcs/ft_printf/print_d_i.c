/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 13:27:37 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/01/19 20:06:47 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static intmax_t	get_s_type(intmax_t n, t_option *opt)
{
	if (opt->mod_h == 2)
		n = (char)n;
	else if (opt->mod_h == 1)
		n = (short int)n;
	else if (opt->mod_maj_l == 1)
		n = (long int)n;
	else if (opt->mod_maj_l == 2)
		n = (long long int)n;
	else
		n = (int)n;
	return (n);
}

char			*l_itoa(intmax_t n)
{
	int			len;
	intmax_t	nb;
	char		*str;

	if (n == LONG_MIN)
		return (!(str = ft_strdup("9223372036854775808")) ? NULL : str);
	nb = (n < 0 ? -n : n);
	len = count_digit(nb, 10);
	if (!(str = ft_strnew(len)))
		return (NULL);
	str[0] = '0';
	while (nb)
	{
		str[--len] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

static	void	display_d_i(t_option *opt, intmax_t nb, char *str)
{
	int		full_len;
	int		nb_len;
	int		sign;

	sign = (nb < 0 || opt->flag_plus) ? 1 : 0;
	nb_len = count_digit(nb < 0 ? -nb : nb, 10);
	full_len = (opt->precision > nb_len ? opt->precision : nb_len);
	if (opt->flag_space && opt->precision <= full_len && !sign)
	{
		putchar_len(' ', opt);
		opt->width--;
	}
	(nb == 0 && opt->precision == 0) ? full_len-- : 0;
	if ((opt->width > full_len && !opt->flag_left && !opt->flag_zero)
		|| (opt->precision != -1 && !opt->flag_left && opt->flag_zero))
		padding(opt, opt->width - full_len - sign, ' ');
	(nb < 0) ? putchar_len('-', opt) : 0;
	(nb >= 0 && opt->flag_plus) ? putchar_len('+', opt) : 0;
	if (opt->precision > nb_len)
		padding(opt, opt->precision - nb_len, '0');
	if (opt->width && opt->precision < 0 && !opt->flag_left && opt->flag_zero)
		padding(opt, opt->width - nb_len - sign, '0');
	(nb || opt->precision) ? putstr_len(str, opt, 0) : 0;
	if (opt->width > full_len && opt->flag_left)
		padding(opt, opt->width - full_len - sign, ' ');
}

int				print_d_i(t_printf *env, t_option *opt)
{
	intmax_t	nb;
	char		*str;

	nb = va_arg(env->va, intmax_t);
	nb = get_s_type(nb, opt);
	if (!(str = l_itoa(nb)))
		return (-1);
	display_d_i(opt, nb, str);
	ft_strdel(&str);
	env->format++;
	return (0);
}
