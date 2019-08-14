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

double compute_distance(double x1, double y1, double x2, double y2)
{
    double square_difference_x = (x2 - x1) * (x2 - x1);
    double square_difference_y = (y2 - y1) * (y2 - y1);
    double sum = square_difference_x + square_difference_y;
    double value = sqrt(sum);
    return value;
}

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
  int proj;
  int tmp_x;
  int dy;
  double angle;
  int map_x;
  double dist;
  int map_y;
  int is_first_coord;
  int start_x;
  int start_y;
  int tmp_y;
  int is_mult;
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
  is_mult = 0;
  y = pos.y;
  tmp_y = 0;
  next_x = 0;
  next_y = 0;
  start_x = (config.cell_size.w / 4);
  start_y = (config.cell_size.h / 4);
  is_first_coord = 0;
  map_x = 0;
  // -0.6x | 0.6x
  pente = -0.66;
  proj = (WIN_WIDTH / 2) / tan(30);
  // -0.6 à -150x
  // 0.6 à 150
  // 150 / WIN_WIDTH;
  map_y = 0;
  dist = 0;
  dx = 0;
  dy = 0;
  coef = 0;
  is_right = 0;
  tmp_x = 0;
  inc = 1.1 / (WIN_WIDTH / 2);
  pente_right = pente + (inc * (WIN_WIDTH / 2));
  angle = 0.0;
  //max_pente = pente * WIN_WIDTH;
  // 1 - pente ax = y, y = a / x, 300 = 1.1x, x = 300 / 1.1 => x = y / a ---> y = ax, a * 300 = y => y = a / x;
  // --> start x, y.
  // rotation ax + b, ou b = angle de rotation = direction de la droite
  //printf("right pente : %f\n", inc);
  // vers le haut : -y, vers le bas : +y.
  x = pos.x;
  y = pos.y;
  while (i < WIN_WIDTH)
  {
    if (ray_angle == 0.0)
      ray_angle = 45.0;
    else
      ray_angle+= config.ray_angle;
    /*if (pente <= -10.0 && is_mult == 0)
    {
        is_mult = 1;
        inc *= 10;
    }
    if (pente >= 10 && is_mult == 1)
    {
      is_mult = 0;
      inc *= 10;
    }*/
    if (pente <= -1.1 && is_right == 0)
    {
      // * 10 qd -10.0
      is_right = 1;
      pente = 0.66;
      printf("pente value : %f\n", pente);
    }
    //printf("pente value : %f\n", pente);
    // 1200 = ax + b, x + b = (1200 / a) + b; b = pos.x.
    coef = (WIN_WIDTH / fabs(pente));
    //tmp_y = round(config.cell_size.w / pente);
    //first coord => abs(config.cell_size.w - y)
    //
    //printf("pente : %f | coef : %d | ray : %f\n", pente, coef, ray_angle);
    pente+= !is_right ? -inc : inc;
    //printf("pente : %f | coef : %d | ray : %f\n", pente, coef, ray_angle);
    //printf("-----> y %d, cos res : %f\n", y, sin(ray_angle));
    while (1)
    {
      if (!is_first_coord)
      {
        next_x = x;
        next_y = y;
        is_first_coord = 1;
      }
      //printf("run, x : %d | y : %d\n", x, y);
      // first coord = abs(config.cell_size.w - y).
      map_x = round(next_x / config.cell_size.w);
      map_y = round(next_y / config.cell_size.h);
      if (map_x > 0 && map_y > 0 && map_x < (map.size.x) && map_y < (map.size.y))
      {
        //printf("x : %d | y : %d | size_x : %d | size_y : %d\n", map_x, map_y, map.size.x, map.size.y);
        //printf("size_x : %d, size_y : %d, x : %d, y: %d\n", map.size.x, map.size.y, map_x, map_y);
        if (map.content[map_y][map_x] == 1)
        {
          dist = compute_distance((double)pos.x, (double)pos.y, (double)next_x, (double)next_y); /*(is_right ? cos(30) : cos(-30))*/
          angle = abs(next_y - pos.y) / dist;
          dist = dist * cos(angle);
          //dist = (0.394 * (dx + dy) + 0.544 * MAX(dx, dy)) * (is_right ? cos(-30) : cos(30));
          //printf("dist %d, x % d, y %d, next_x %d, next_y %d, map_x %d, map_y %d\n", dist, x, y, next_x, next_y, map_x, map_y);
          // x2 | y2 --> y1 + ((WIN_HEIGHT / 2) / dist)
          /*printf("draw (x1 : %d, y1 : %d, x2 : %d, y2 : %d) -- dist = %d\n", next_x,
          next_y, map_x * config.cell_size.w,
          map_y * config.cell_size.h + (int)((WIN_HEIGHT / 2) / dist), dist);*/
          // ratio avec la dist, + eleve, + petit.
          printf("dist : %g | x : %d | next_x : %d | y : %d | next_y : %d\n", dist, x, next_x, y, next_y);
          // 255 & (int)(255 / dist * i + 1 / 2)
          SDL_SetRenderDrawColor(renderer, 255 & (int)(255 / dist * i),
          255 & (int)(255 / dist * i),  255 & (int)(255 / dist * i), SDL_ALPHA_OPAQUE);
          //
          SDL_RenderDrawLine(renderer,
                       i,
                       WIN_HEIGHT / 4 - (dist > 0 ? round(((WIN_HEIGHT / 2) / dist) * proj) : WIN_HEIGHT),
                       i,
                       WIN_HEIGHT / 4 + (dist > 0 ? round(((WIN_HEIGHT / 2) / dist) * proj) : WIN_HEIGHT));
            // plusieurs intersection possible : stop le ray qd il est a la fin.
            // printf ("error : %s\n", SDL_GetError());
            break;
        }
      }
      // ray dir up
      // ray dir down
      next_x += is_right ? config.cell_size.w : -config.cell_size.w;
      next_y += coef;
      if (next_x > WIN_WIDTH || next_x < 0 || next_y > WIN_HEIGHT || next_y < 0)
        break;
    }
    is_first_coord = 0;
    i++;
  }
}
