/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:58:44 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/01/24 16:36:36 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static	int		print_nan_inf(t_printf *env, t_option *opt, long double nb)
{
	int		len;
	char	*str;

	str = ft_isnan(nb) ? "nan" : "inf";
	len = 3;
	if (opt->width > len && !opt->flag_left)
		padding(opt, opt->width - len, opt->flag_zero ? '0' : ' ');
	putstr_len(str, opt, len);
	if (opt->width > len && opt->flag_left)
		padding(opt, opt->width - len, ' ');
	env->format++;
	return (0);
}

static	long	precision_multiplier(t_option *opt)
{
	int		i;
	long	ret;

	i = 0;
	ret = 1;
	if (opt->precision == -1)
		opt->precision = 6;
	while (i != opt->precision)
	{
		ret *= 10;
		i++;
	}
	return (ret);
}

static	char	*ftoa(t_option *opt, long double nb)
{
	char			*d_str;
	char			*f_str;
	long double		float_part;

	f_str = NULL;
	float_part = nb - (unsigned long long)nb + 1;
	float_part *= precision_multiplier(opt);
	if ((float_part - (unsigned long long)float_part) >= 0.5)
		float_part++;
	((float_part / precision_multiplier(opt)) > 2) ? nb += 1 : 0;
	if (!(d_str = ull_itoa((unsigned long long)nb)))
		return (NULL);
	if (opt->precision == 0 && opt->flag_sharp)
	{
		if (!(f_str = ft_strjoin_free(d_str, ".", 1)))
			return (free_str(d_str, NULL));
		else
			return (f_str);
	}
	if (opt->precision == 0)
	{
		opt->width--;
		return (d_str);
	}
	return (ftoa_bis(f_str, d_str, float_part));
}

static	void	displa_float(t_option *opt)
{
	int		sign;
	int		len;

	sign = (opt->f_sign || opt->flag_plus) ? 1 : 0;
	len = ft_strlen(opt->f_str);
	(!opt->precision && !opt->flag_sharp) ? len-- : 0;
	if (opt->precision <= len && opt->flag_space && !sign)
	{
		putchar_len(' ', opt);
		opt->width--;
	}
	if (opt->width > len && !opt->flag_left && !opt->flag_zero)
		padding(opt, opt->width - len - sign, ' ');
	opt->f_sign ? putchar_len('-', opt) : 0;
	(opt->flag_plus && !opt->f_sign) ? putchar_len('+', opt) : 0;
	if (opt->width > len && !opt->flag_left && opt->flag_zero)
		padding(opt, opt->width - len - sign, '0');
	putstr_len(opt->f_str, opt, 0);
	if (opt->width > len && opt->flag_left)
		padding(opt, opt->width - len - sign, ' ');
}

int				manage_float(t_printf *env, t_option *opt)
{
	long double	nb;

	nb = (opt->mod_maj_l == 0) ? va_arg(env->va, double) : \
		va_arg(env->va, long double);
	if (ft_isnan(nb) || ft_isinf(nb))
		return (print_nan_inf(env, opt, nb));
	opt->f_sign = (nb < 0) ? 1 : 0;
	nb = (nb < 0) ? -nb : nb;
	if (!(opt->f_str = ftoa(opt, nb)))
		return (-1);
	displa_float(opt);
	ft_strdel(&opt->f_str);
	env->format++;
	return (0);
}
