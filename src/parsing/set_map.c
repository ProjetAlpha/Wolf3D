/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_map.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/31 02:33:19 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/31 02:33:27 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

static int check_size(t_map *map, char *line)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (line[i])
  {
    if (line[i] == '[' && i++)
    {
      j = i;
      while (ft_isdigit(line[j]))
        j++;
      if ((line[j] != ',' && line[j + 1] != ' ') || i == j)
        put_error("Invalid size separator (need a number and a coma followed by one space)\n");
      map->size.x = ft_atoi(ft_strsub(line, i, j));
      j+=2;
      i = j;
      while (ft_isdigit(line[j]))
        j++;
      if ((line[j] && line[j] != ']') || !ft_isdigit(line[j - 1]))
        put_error("Invalid size separator (need a number followed by a bracket)\n");
      map->size.y = ft_atoi(ft_strsub(line, i, j));
    }
    if (map->size.x != 0 && map->size.y != 0)
    {
      return (1);
    }
    i++;
  }
  return (0);
}

static int check_coord(t_map *map, char *line, int line_pos)
{
  int i;
  int count_coord;
  short int tab[8];

  count_coord = 0;
  i = 0;
  while (line[i])
  {
    if (count_coord + 1 > map->size.x)
      put_error("Line coordinates exceed");
    if ((line[i] == '0' || line[i] == '1'))
    {
      if (line[i] == '1')
      {
        set_pos(map, tab, count_coord, line_pos);
        cpy_coords(map, tab);
      }
      map->content[line_pos][count_coord] = (line[i] == '1') ? 1 : 0;
      count_coord++;
    }
    i++;
  }
  return (count_coord > 0 && count_coord == map->size.x);
}

static int set_line(t_map *map, char *line, int type, int line_pos)
{
  int i;

  i = 0;
  if (type & MAP_SIZE)
    return (check_size(map, line));
  if (type & MAP_COORD)
    return (check_coord(map, line, line_pos));
  return (0);
}

static void create_map(t_map *map, int line, int col)
{
  int i;

  i = 0;
  if (!(map->content = malloc(sizeof(int *) * line)))
    put_error("Memory allocation failed !\n");
  while (i < line)
  {
    map->content[i] = malloc(sizeof(int) * col);
    i++;
  }
}

void read_map(t_map *map, char *file)
{
  char *line;
  int ret;
  int fd;
  int count_line;

  fd = open(file, O_RDONLY);
  if (fd < 0)
    put_error("Fd error\n");
  count_line = 0;
  ret = get_next_line(fd, &line);
  if (!ret || !set_line(map, line, MAP_SIZE, 0))
  {
    put_error("Not a valid map size !\n");
    free(line);
  }
  create_map(map, map->size.y, map->size.x);
  while (get_next_line(fd, &line))
  {
    if (!set_line(map, line, MAP_COORD, count_line))
      put_error("No coordinates or too many coordinates\n");
    count_line++;
    free(line);
  }
  if (count_line != map->size.y)
    put_error("Invalid number of lines !\n");
}
