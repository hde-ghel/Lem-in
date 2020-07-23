/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:21:44 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/03/08 15:09:59 by hde-ghel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	error_msg(t_lemin *env, const char *msg)
{
	ft_putstr_fd(msg, 2);
	if (env->fd)
		close(env->fd);
	exit(-1);
}

void	error_free_str(t_lemin *env, const char *msg, char *str)
{
	ft_putstr_fd(msg, 2);
	ft_strdel(&str);
	if (env->fd)
		close(env->fd);
	exit(-1);
}

void free_room_map(t_lemin *env)
{
	int	i;
	t_room  *tmp;
	t_room  *tmp2;

	i = 0;
	while (i < HASH_SIZE - 1)
	{
		if (env->map[i] != NULL)
		{
			ft_strdel(&env->map[i]->name);
			tmp = env->map[i]->next;
			while (tmp)
			{
				tmp2 = tmp->next;
				ft_strdel(&tmp->name);
				free(tmp);
				tmp = tmp2;
			}
		}
		free(env->map[i]);
		i++;
	}
}
/*
void print_room_map(t_lemin *env)
{
  int     i;
  t_room  *tmp;

  i = 0;
  while (i < HASH_SIZE -1)
  {
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
*/
