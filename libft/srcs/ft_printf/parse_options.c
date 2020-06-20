/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:22:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/01/22 18:03:15 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static	void		get_flags(t_printf *env, t_option *opt)
{
	while (*env->format == '+' || *env->format == '-' || *env->format == ' ' ||
			*env->format == '0' || *env->format == '#')
	{
		if (*env->format == '+')
			opt->flag_plus = 1;
		else if (*env->format == '-')
			opt->flag_left = 1;
		else if (*env->format == ' ')
			opt->flag_space = 1;
		else if (*env->format == '0')
			opt->flag_zero = 1;
		else if (*env->format == '#')
			opt->flag_sharp = 1;
		env->format++;
	}
}

static	void		get_width(t_printf *env, t_option *opt)
{
	if (*env->format == '*')
	{
		opt->width = va_arg(env->va, int);
		if (opt->width < 0)
		{
			opt->width *= -1;
			opt->flag_left = 1;
		}
		env->format++;
	}
	if (ft_isdigit(*env->format))
		opt->width = 0;
	while (ft_isdigit(*env->format))
	{
		opt->width *= 10;
		opt->width += *env->format - '0';
		env->format++;
	}
}

static	void		get_precision(t_printf *env, t_option *opt)
{
	env->format++;
	if (*env->format == '*')
	{
		opt->precision = va_arg(env->va, int);
		if (opt->precision < 0)
			opt->precision = -1;
		env->format++;
	}
	else
	{
		opt->precision = 0;
		while (ft_isdigit(*env->format))
		{
			opt->precision *= 10;
			opt->precision += *env->format - '0';
			env->format++;
		}
	}
}

static	void		get_length_modifiers(t_printf *env, t_option *opt)
{
	char	lenght;

	lenght = *env->format;
	while (*env->format == lenght)
	{
		if (*env->format == 'h')
			opt->mod_h++;
		else if (*env->format == 'l')
			opt->mod_maj_l++;
		else if (*env->format == 'L')
			opt->mod_maj_l++;
		env->format++;
	}
	while (*env->format == 'h' || *env->format == 'l' || *env->format == 'L')
		env->format++;
}

void				parse_opt(t_printf *env, t_option *opt)
{
	if (*env->format == '+' || *env->format == '-' || *env->format == ' ' ||
		*env->format == '0' || *env->format == '#')
		get_flags(env, opt);
	if (ft_isdigit(*env->format) || *env->format == '*')
		get_width(env, opt);
	if (*env->format == '.')
		get_precision(env, opt);
	if (*env->format == 'h' || *env->format == 'l' || *env->format == 'L')
		get_length_modifiers(env, opt);
	if (ft_isdigit(*env->format) || *env->format == '*')
		get_width(env, opt);
}
