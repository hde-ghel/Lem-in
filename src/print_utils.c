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

void print_room_map(t_lemin *env)
{
  int     i;
  t_room  *tmp;

  i = 0;
  while (i < HASH_SIZE -1)
  {
    //ft_printf("nananana");
    if (env->map[i] != NULL)
    {
      ft_printf("New room\nName : %s\nx = %d  y = %d\nkey = %d\nweight = %d\n\n\n", env->map[i]->name,\
          env->map[i]->coord.x, env->map[i]->coord.y, env->map[i]->key, env->map[i]->weight);
      tmp = env->map[i]->next;
      while (tmp)
      {
        ft_printf("SAME HASH\n");
        ft_printf("New room\nName : %s\nx = %d  y = %d\nkey = %d\nweight = %d\n\n\n", env->map[i]->name,\
            env->map[i]->coord.x, env->map[i]->coord.y, env->map[i]->key, env->map[i]->weight);
        tmp = tmp->next;
      }
    }
    i++;
  }
}
