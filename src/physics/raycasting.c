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
/*int check_wall_collision()
{

}*/

// map -- config
void create_world(t_map map, t_config config, t_vec2 pos, SDL_Renderer *renderer)
{
  // 1 - balancer un rayon.
  // 2 - trouver la coordonnee de la collision.
  // 3 - une fois que tout les rayons ont ete trouvees, trouver les delimiters pour tracer le carre =
  // 4 points du carre / rectangle.
  // setup : nbre de rayons = config->cell_size.w
  // angle += config.ray_angle
  // A -> B, en fonction de l'angle..., calculer la distance...
  int i;
  int dx;
  int tmp_x;
  int dy;
  int map_x;
  int dist;
  int map_y;
  int is_first_coord;
  int start_x;
  int start_y;
  int tmp_y;
  int coef;
  double pente_right;
  float pente;
  //float max_pente;
  float inc;
  double ray_angle;
  int x;
  int y;
  int is_right;
  int next_x;
  int next_y;

  i = 0;
  ray_angle = 0.0;
  x = pos.x;
  y = pos.y;
  tmp_y = 0;
  next_x = 0;
  next_y = 0;
  start_x = (config.cell_size.w / 4);
  start_y = (config.cell_size.h / 4);
  is_first_coord = 0;
  map_x = 0;
  // -0.6x | 0.6x
  pente = -0.6;
  map_y = 0;
  dist = 0;
  dx = 0;
  dy = 0;
  coef = 0;
  is_right = 0;
  tmp_x = 0;
  inc = pente / WIN_WIDTH;
  pente_right = pente + (inc * (WIN_WIDTH / 2)); // 1.35
  //max_pente = pente * WIN_WIDTH;
  // 1 - pente ax = y, y = a / x, 300 = 1.1x, x = 300 / 1.1 => x = y / a ---> y = ax, a * 300 = y => y = a / x;
  // --> start x, y.
  //printf("right pente : %f\n", pente_right);
  while (i < WIN_WIDTH)
  {
    if (ray_angle == 0.0)
      ray_angle = 45.0;
    else
      ray_angle+= config.ray_angle;
    tmp_x = 100 / fabs(tan(ray_angle));
    x = pos.x;
    if (pente >= pente_right)
    {
      is_right = 1;
      pente = 0.9;
      printf("pente value : %f\n", pente);
    }
    //printf("pente value : %f\n", pente);

    coef = (config.cell_size.w / pente);
    //tmp_y = round(config.cell_size.w / pente);
    //first coord => abs(config.cell_size.w - y)
    //
    tmp_y = config.cell_size.w * tan(90);
    y = pos.y;
    pente+=inc;
    //printf("pente : %f | x : %d | y : %d | coef : %d | ray : %f\n", pente, tmp_x, tmp_y, coef, ray_angle);
    //printf("-----> y %d, cos res : %f\n", y, sin(ray_angle));
    while (1)
    {
      if (!is_first_coord)
      {
        next_x = x;
        next_y = y;
        is_first_coord = 1;
      }
      // first coord = abs(config.cell_size.w - y).
      map_x = round(next_x / config.cell_size.w);
      map_y = round(next_y / config.cell_size.h);
      if (map_x > 0 && map_y > 0 && map_x < (map.size.x) && map_y < (map.size.y))
      {
        //printf("x : %d | y : %d | size_x : %d | size_y : %d\n", map_x, map_y, map.size.x, map.size.y);
        //printf("size_x : %d, size_y : %d, x : %d, y: %d\n", map.size.x, map.size.y, map_x, map_y);
        if (map.content[map_y][map_x] == 1)
        {
          dx = abs(next_x - pos.x);
          dy = abs(next_y - pos.y);
          dist = (0.394 * (dx + dy) + 0.544 * MAX(dx, dy)) * (ray_angle > 90.0 ? cos(-30) : cos(30));
          //printf("dist %d, x %d, y %d, next_x %d, next_y %d, map_x %d, map_y %d\n", dist, x, y, next_x, next_y, map_x, map_y);
          // x2 | y2 --> y1 + ((WIN_HEIGHT / 2) / dist)
          /*printf("draw (x1 : %d, y1 : %d, x2 : %d, y2 : %d) -- dist = %d\n", next_x,
          next_y, map_x * config.cell_size.w,
          map_y * config.cell_size.h + (int)((WIN_HEIGHT / 2) / dist), dist);*/
          // ratio avec la dist, + eleve, + petit.
          SDL_RenderDrawLine(renderer,
                       i,
                       300,
                       i,
                       300 + round((config.cell_size.w / dist) * 277));
            // plusieurs intersection possible : stop le ray qd il est a la fin.
            // printf ("error : %s\n", SDL_GetError());
            break;
        }
      }
      // ray dir up
      // ray dir down
      next_x += is_right ? config.cell_size.w : -config.cell_size.w;
      next_y += coef;
      if (next_x > WIN_WIDTH || next_y > WIN_HEIGHT)
        break;
    }
    is_first_coord = 0;
    i++;
  }
}
