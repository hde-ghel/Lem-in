/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:01:39 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/07 17:34:29 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

int		main(void)
{
	t_lemin		*env;

	//init(env)
	if (read_input(env))
		return (-1); //Fonction error free
	ft_putstr(env->read_tab);

	return (0);
}
