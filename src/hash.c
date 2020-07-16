/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 18:35:52 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

unsigned long	hash_key(char *name)
{
	unsigned long	hash;

	hash = 0;
	if (!(name))
		return (0);
	while (*name)
	{
		hash = (hash * 18) + *name++ +
		'h' + 'd' + 'e';
	}
	return (hash % HASH_SIZE);
}
