/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-ghel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 14:54:59 by hde-ghel          #+#    #+#             */
/*   Updated: 2020/08/21 17:37:11 by ababaie-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	print_room_map(t_lemin *env)
{
	int	i;
	t_room	*tmp;
	t_link	*tmp2;

  i = 0;
  tmp = NULL;
  tmp2 = NULL;
  while (i < HASH_SIZE)
  {
    //ft_printf("nananana");
    if (env->map[i] != NULL)
    {
      ft_printf("Room:\nName : %s\nx = %d  y = %d\nkey = %d\nweight = %d\nduplicated = %d\nroom links:\n", env->map[i]->name,\
          env->map[i]->coord.x, env->map[i]->coord.y, env->map[i]->key, env->map[i]->weight, env->map[i]->duplicated);
      tmp2 = env->map[i]->link_list;
      while(tmp2 != NULL)
      {
        ft_printf("       %s-%s\n", tmp2->room_a->name, tmp2->room_b->name);
        tmp2 = tmp2->room_link_next;
      }
      ft_printf("\n");
      tmp = env->map[i]->next;
      while (tmp != NULL)
      {
        ft_printf("SAME HASH\n");
        ft_printf("Room:\nName : %s\nx = %d  y = %d\nkey = %d\nweight = %d\nduplicated = %d\nroom links:\n", tmp->name,\
            tmp->coord.x, tmp->coord.y, tmp->key, tmp->weight, tmp->duplicated);
        tmp2 = tmp->link_list;
        while(tmp2 != NULL)
        {
          ft_printf("       %s-%s\n", tmp2->room_a->name, tmp2->room_b->name);
          tmp2 = tmp2->room_link_next;
        }
        ft_printf("\n");
        tmp = tmp->next;
      }
    }
    i++;
  }
}

void	print_link_list(t_lemin *env)
{
	t_link	*tmp;

  tmp = env->links_map;
  while (tmp)
  {
    ft_putstr("roma = ");
    if (tmp->room_a)
      ft_putstr(tmp->room_a->name);
    ft_putstr(" roomb = ");
    //if (tmp->room_b)
      ft_putstr(tmp->room_b->name);
    ft_putstr("\n");
    //ft_printf("link room a = %s room_b = %s\n", tmp->room_a->name, tmp->room_b->name);
    tmp = tmp->list_next;
  }
}

void	print_new_path(t_lemin *env)
{
  t_room *tmp;

  tmp = env->end;
  while (tmp)
  {
    ft_printf("%s", tmp->name);
    if (tmp->path_next != 0)
      ft_printf("->");
    tmp = tmp->path_next;
  }
  ft_putstr("\n");
}

void print_final_paths(t_lemin *env)
{
  int		i;
  int   j;

	i = 0;
  j = 0;
  ft_printf("nb_path = %d\n", env->max_final_path);
	while(i < env->max_final_path)
	{
		if (env->path_tab[i])
		{
      j = 0;
      ft_printf("path weight = %d\n", env->path_tab[i]->weight);
      ft_printf("path nb = %d\n", env->path_tab[i]->path_nb);
      while (env->path_tab[i]->room[j])
        ft_printf("%s->", env->path_tab[i]->room[j++]);
		}
    ft_printf("\n\n");
		i++;
	}
}
