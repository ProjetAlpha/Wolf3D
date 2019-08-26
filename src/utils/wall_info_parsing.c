/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wall_info_parsing.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/26 18:33:38 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 18:33:48 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

t_wall_info *cpy_coords(t_map *map, short int pos[8])
{
  int i;
  int size;

  i = 0;
  t_wall_info *new_wall;
  size = map->wall_info_size + 1;
  if (!(new_wall = malloc(sizeof(t_wall_info) * (size))))
    put_error("Malloc allocation error in wall_info_parsing.c (cpy_coords)\n");
  while (i < size - 1)
  {
    new_wall[i].pos[0] = map->wall_info[i].pos[0];
    new_wall[i].pos[1] = map->wall_info[i].pos[1];
    i++;
  }
  new_wall[i].pos[0] = set_bits(pos[0], pos[1], pos[2], pos[3]);
  new_wall[i].pos[1] = set_bits(pos[4], pos[5], pos[6], pos[7]);
  free(map->wall_info);
  map->wall_info = new_wall;
  map->wall_info_size = size;
  return (new_wall);
}

void set_pos(t_map *map, short int tab[8], int count_cord, int line_pos)
{
  int x;
  int y;
  int w;
  int h;

  w = WIN_WIDTH / map->size.x;
  h = WIN_HEIGHT / map->size.y;
  y = h * line_pos;
  x = w * count_cord;
  tab[0] = x;
  tab[1] = y;
  tab[2] = x + w;
  tab[3] = y;
  tab[4] = x;
  tab[5] = y + w;
  tab[6] = x + w;
  tab[7] = y + h;
}
