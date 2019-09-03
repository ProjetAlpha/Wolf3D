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
  printf("count %d\n", map.wall_info_size);
  while (i < map.wall_info_size)
  {
    get_bits(map.wall_info[i].pos[0], coord_top);
    get_bits(map.wall_info[i].pos[1], coord_bot);
    // right = x1 y1 | x2 y2, bot = x1 y1 | x3 y3
    printf("x1 : %d | y1 : %d | x2 : %d | y2 : %d | x3 : %d | y3 : %d | x4 : %d | y4 : %d\n",
    coord_top[0], coord_top[1], coord_top[2], coord_top[3], coord_bot[0], coord_bot[1], coord_bot[2], coord_bot[3]);
    if (is_in_rect(coord_top[0], coord_top[1], coord_top[2], coord_bot[1], x, y))
      return (1);
    i++;
  }
  return (0);
}

// 3d : x, y, ou z = hauteur d'un mur => matrix camera /
// jumpx = (mapx - posx) * (config.cell_size.w)
// jumpy = (mapy - posy) * (config.cell_size.w)

//
//
// distance qu il faut au ray pour se deplacer en x et y.
// y = a * x
// => vector_dir * x = y --> config.cell_size.w *
// => vector_dir * x = y -->
// deltaX = abs(1 / raydirX)
// deltaY = abs(1 / raydirY)
// (mapx - posx) * deltaX
// (mapy - posy) * deltaY
// if (sideDistX < sideDistY) => sideDistX += deltaDistX; else sideDistY += deltaDistY;
// jump 1 carre a chaque fois et deplace le ray de sideDistX ou sideDistY.
void create_world(t_map map, t_config config, t_vec2 pos, SDL_Renderer *renderer)
{
  int i;
  int proj;
  int map_x;
  int map_y;
  double angle;
  double dist;
  double dist_h;
  double dist_v;
  int coef;
  double right_angle;
  double ray_angle;
  double x;
  double y;
  int percent;
  //int type;
  double inc_x;
  double inc_y;
  double vnext_x;
  double vnext_y;
  double hnext_x;
  double hnext_y;

  i = 0;
  ray_angle = 0.0;
  x = pos.x;
  y = pos.y;
  map_x = 0;
  map_y = 0;
  dist = 0;
  coef = 0;
  proj = (WIN_WIDTH / 2) / tan(30);
  angle = 0.0;
  //printf("check_collision : %d| pos_x : %d | pos_y : %d\n", check_collision(map, pos.x, pos.y), pos.x, pos.y);
  if (config.rotation < 0)
  {
    /*if (config.rotation <= -45)
      ray_angle = config.rotation;
    else*/
      ray_angle = 45.0 + config.rotation;
  }
  else if (config.rotation > 0)
    ray_angle = 45.0 + config.rotation;
  else
    ray_angle = 45.0;
  //ray_angle = config.rotation > 0 ? 45 + config.rotation : 45;
  x = pos.x;
  y = pos.y;
  right_angle = ray_angle + 30.0;
  //printf("ray angle : %f\n", ray_angle);
  while (i < WIN_WIDTH)
  {
    angle = ray_angle * (M_PI / 180);
    // ---> vertical / horizontal
    //x = cos(angle);
    //y = sin(angle);
    // ---> INTERSECTION VERTICAL <---
    // x = config.cell_size.w
    // y = config.cell_size.w * tan(angle)
    // dst = next_y - pos_y
    // ---> INTERSECTION HORIZONTAL <---
    // x = config.cell_size.w / tan(angle)
    // y = config.cell_size.w
    // dst = next_x - pos.x
    inc_y = config.cell_size.w * tan(angle);
    inc_x = config.cell_size.w / tan(angle);

    // up = abs(pos.x - config.cell_size.w)
    // down = abs(pos.x + (-config.cell_size.w))
    vnext_x = pos.x + fabs(pos.x - config.cell_size.w);
    vnext_y = pos.y + round(fabs(pos.x - config.cell_size.w) * tan(angle));

    hnext_x = pos.x + round(fabs(pos.y - config.cell_size.w) / tan(angle));
    // down => positif / up => negatif
    hnext_y = pos.y + fabs(pos.y - config.cell_size.w);
    dist_h = 0.0;
    dist_v = 0.0;
    dist = 0.0;
    while (1)
    {
      // prendre la + petite distance de l'intersection (horizontale / vertical compare)
      map_x = round(hnext_x / config.cell_size.w);
      map_y = round(hnext_y / config.cell_size.w);
      if (map_x > 0 && map_y > 0 && map_x < map.size.x && map_y < map.size.y)
      {
        if (map.content[map_y][map_x] == 1)
        {
          dist_h = fabs(hnext_x - pos.x);
          /*if (fabs(next_y - pos.y) > fabs(next_x - pos.x))
            dist = fabs(next_y - pos.y);
          else
            dist = fabs(next_x - pos.x);
          percent = dist > 100 ? (50 * (WIN_HEIGHT / (dist * 4))) : 128;
          SDL_SetRenderDrawColor(renderer, percent,
          percent, percent, SDL_ALPHA_OPAQUE);
          // si distance < 100 => t'avance plu.
          draw_vline(renderer, (t_line){.x1 = i,
            .y1 = (WIN_HEIGHT / 3 + (dist > 0.0 ? ((double)(WIN_HEIGHT/4) / round(dist)) * (proj * 0.5) : WIN_HEIGHT/2)),
          .x2 = i, .y2 = WIN_HEIGHT / 3 - (dist > 0.0 ? ((double)(WIN_HEIGHT/4) / round(dist)) * (proj * 0.5) : -WIN_HEIGHT/2)});*/

          //break;
        }
      }
      hnext_x += inc_x;
      hnext_y += config.cell_size.w; // -- ray_up : y neg| -- ray_down : y pos.
      map_x = round(vnext_x / config.cell_size.w);
      map_y = round(vnext_y / config.cell_size.w);
      if (map_x > 0 && map_y > 0 && map_x < map.size.x && map_y < map.size.y)
      {
        if (map.content[map_y][map_x] == 1)
        {
          dist_v = fabs(vnext_y - pos.y);
        }
      }
      if (dist_h > 0.0 || dist_v > 0.0)
      {
        dist = (dist_h < dist_v) ? dist_h : dist_v;
        dist = (dist / sin(angle)); // * (cos(30) ou cos(-30))
        percent = dist > 100 ? (50 * (WIN_HEIGHT / (dist * 4))) : 128;
        SDL_SetRenderDrawColor(renderer, percent,
        percent, percent, SDL_ALPHA_OPAQUE);
        draw_vline(renderer, (t_line){.x1 = i,
          .y1 = (WIN_HEIGHT / 3 + (dist > 0.0 ? ((double)(WIN_HEIGHT/4) / round(dist)) * (proj * 0.5) : WIN_HEIGHT/2)),
        .x2 = i, .y2 = WIN_HEIGHT / 3 - (dist > 0.0 ? ((double)(WIN_HEIGHT/4) / round(dist)) * (proj * 0.5) : -WIN_HEIGHT/2)});
        break;
      }
      // ray a gauche = -config.cell_size.w | ray a droite = config.cell_size.w
      vnext_x += config.cell_size.w;
      vnext_y += inc_y;
      if ((int)hnext_x > WIN_WIDTH || hnext_x < 0.0 || (int)hnext_y > WIN_HEIGHT || hnext_y < 0.0)
        break;
      if ((int)vnext_x > WIN_WIDTH || vnext_x < 0.0 || (int)vnext_y > WIN_HEIGHT || vnext_y < 0.0)
          break;
    }
    ray_angle+= config.ray_angle;
    ++i;
  }
}
