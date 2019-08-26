/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   raycasting.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/01 19:06:48 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/01 19:06:56 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"
#include <stdio.h>

int is_in_rect(int x1, int y1, int x2,
               int y2, int x, int y)
{
    if (x >= x1 && x <= x2 && y >= y1 && y <= y2)
        return (1);
    return (0);
}

int check_collision(t_map map, int x, int y)
{
  int coord_top[4];
  int coord_bot[4];
  int i;

  i = 0;
  // check si collision : is_in_rect();
  // collision : pos x + pos y, is in rect.
  while (i < map.wall_info_size)
  {
    get_bits(map.wall_info[i].pos[0], coord_top);
    get_bits(map.wall_info[i].pos[1], coord_bot);
    // right = x1 y1 | x2 y2, bot = x1 y1 | x3 y3
    if (is_in_rect(coord_top[0], coord_top[1], coord_top[2], coord_top[3], x, y))
      return (1);
    i++;
  }
  return (0);
}

double normalize(double x, double y)
{
  return (sqrt((x * x) + (y * y)));
}

double compute_distance(double x1, double y1, double x2, double y2)
{
    double square_difference_x = (x2 - x1) * (x2 - x1);
    double square_difference_y = (y2 - y1) * (y2 - y1);
    double sum = square_difference_x + square_difference_y;
    double value = sqrt(sum);
    return value;
}

void create_world(t_map map, t_config config, t_vec2 pos, SDL_Renderer *renderer)
{
  int i;
  int proj;
  int map_x;
  int map_y;
  double angle;
  double dist;
  int coef;
  double ray_angle;
  double x;
  double y;
  int percent;
  //int type;
  double next_x;
  double next_y;

  i = 0;
  ray_angle = 0.0;
  x = pos.x;
  y = pos.y;
  next_x = 0;
  next_y = 0;
  map_x = 0;
  map_y = 0;
  dist = 0;
  coef = 0;
  proj = (WIN_WIDTH / 2) / tan(30);
  angle = 0.0;
  printf("rot : %d\n", config.rotation);
  if (config.rotation < 0)
  {
    if (config.rotation <= -45)
      ray_angle = config.rotation;
    else
      ray_angle = 45 + config.rotation;
  }
  else if (config.rotation > 0)
    ray_angle = 45 + config.rotation;
  else
    ray_angle = 45;
  //ray_angle = config.rotation > 0 ? 45 + config.rotation : 45;
  x = pos.x;
  y = pos.y;
  //printf("ray angle : %f\n", ray_angle);
  while (i < WIN_WIDTH)
  {
    angle = ray_angle * (M_PI / 180);
    x = cos(angle);
    y = sin(angle);
    next_x = pos.x;
    next_y = pos.y;
    while (1)
    {
      map_x = round(next_x / (double)config.cell_size.w);
      map_y = round(next_y / (double)config.cell_size.w);
      if (map_x > 0 && map_y > 0 && map_x < (map.size.x) && map_y < (map.size.y))
      {
        if (map.content[map_y][map_x] == 1)
        {
          if (fabs(next_y - pos.y) > fabs(next_x - pos.x))
            dist = fabs(next_y - pos.y);
          else
            dist = fabs(next_x - pos.x);
          percent = dist > 100 ? (50 * (WIN_HEIGHT / (dist * 4))) : 128;
          SDL_SetRenderDrawColor(renderer, percent,
          percent, percent, SDL_ALPHA_OPAQUE);
          draw_vline(renderer, (t_line){.x1 = i, .y1 = (WIN_HEIGHT / 3 + (dist > 0.0 ? (int)(((WIN_HEIGHT/4) / dist) * (proj / 2)): WIN_HEIGHT/2)),
          .x2 = i, .y2 = WIN_HEIGHT / 3 - (dist > 0.0 ? (int)(((WIN_HEIGHT/4) / dist) * (proj / 2)): -WIN_HEIGHT/2)});
          break;
        }
      }
      next_x += x;
      next_y += y;
      if ((int)next_x > WIN_WIDTH || next_x < 0.0 || (int)next_y > WIN_HEIGHT || next_y < 0.0)
        break;
    }
    ray_angle+= config.ray_angle;
    i++;
  }
}
