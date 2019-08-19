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
  double tmp_x;
  int dy;
  double angle;
  int map_x;
  double dist;
  double collision_angle;
  int map_y;
  int is_first_coord;
  int start_x;
  int start_y;
  double tmp_y;
  int is_mult;
  int coef;
  double pente_right;
  //double corr_angle;
  float pente;
  //float max_pente;
  float inc;
  double ray_angle;
  //double vec_len;
  double x;
  double y;
  int percent;
  int is_right;
  double next_x;
  double next_y;

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
  collision_angle = 0.0;
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
  inc = 3.0 / (WIN_WIDTH / 2);
  pente_right = pente + (inc * (WIN_WIDTH / 2));
  angle = 0.0;
  //max_pente = pente * WIN_WIDTH;
  // 1 - pente ax = y, y = a / x, 300 = 1.1x, x = 300 / 1.1 => x = y / a ---> y = ax, a * 300 = y => y = a / x;
  // --> start x, y.
  // rotation ax + b, ou b = angle de rotation = direction de la droite
  //printf("right pente : %f\n", inc);
  // vers le haut : -y, vers le bas : +y.
  printf("rot : %d\n", config.rotation);
  if (config.rotation < 0)
  {
    if (config.rotation < -45)
      ray_angle = (360 + config.rotation);
    else
      ray_angle = 45 - config.rotation;
  }
  else if (config.rotation > 0)
    ray_angle = 45 + config.rotation;
  else
    ray_angle = 45;
  //ray_angle = config.rotation > 0 ? 45 + config.rotation : 45;
  x = pos.x;
  y = pos.y;
  printf("ray angle : %f\n", ray_angle);
  while (i < WIN_WIDTH)
  {
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
    if (ray_angle >= 90 && !is_right)
    {
      // * 10 qd -10.0
      is_right = 1;
      //printf("pente value : %f\n", pente);
    }
    //printf("pente value : %f\n", pente);
    // 1200 = ax + b, x + b = (1200 / a) + b; b = pos.x.
    // y = a * cos(ray_angle) * x;
    // y /
    // y = ax + pos.x
    // y = a * 200 => a = y / 200 => 300 = ax => x = 300 / pente.
    //coef = (config.cell_size.w / fabs(pente));
    angle = ray_angle * (M_PI / 180);
    x = cos(angle);
    y = sin(angle);
    //vec_len = sqrt((x * x) + (y * y));
    //tmp_x = pos.x;
    //tmp_y = pos.y;
    //tmp_dist = fabs(y * proj);
    //corr_angle = cos(fabs(atan2(0.0 - y, 0.0 - x) * (180 / M_PI)));
    //printf("vec_len : %f | x : %f | y : %f | ray_angle : %f | dist : %f | corr_angle : %f\n", vec_len, tmp_x, tmp_y, ray_angle, tmp_dist, corr_angle);
    //y = pos.y + coef;
    //coef = fabs(config.cell_size.w * cos(ray_angle));
    //tmp_y = round(config.cell_size.w / pente);
    //first coord => abs(config.cell_size.w - y)
    //
    //printf("pente : %f | coef : %d | ray : %f\n", pente, coef, ray_angle);
    //pente+= !is_right ? -inc : inc;
    //printf("pente : %f | coef : %d | ray : %f\n", pente, coef, fabs(config.cell_size.w * cos(ray_angle)));
    //printf("-----> y %d, cos res : %f\n", y, sin(ray_angle));
    //next_x = (x * (pos.x / normalize(pos.x, pos.y)));
    //next_y = (y * (pos.y / normalize(pos.x, pos.y)));
    next_x = pos.x;
    next_y = pos.y;
    //printf("next_x : %f | next_y : %f\n", next_x, next_y);
    while (1)
    {
      //next_x+= is_right ? -x : x;
      //next_y+= y;
      /*if (!is_first_coord)
      {
        next_x = x;
        next_y = y;
        is_first_coord = 1;
      }*/
      //printf("run, x : %d | y : %d\n", x, y);
      // first coord = abs(config.cell_size.w - y).
      map_x = round(next_x / (double)config.cell_size.w);
      map_y = round(next_y / (double)config.cell_size.h);
      //printf("map_x : %d | map_y : %d | next_x : %f | next_y : %f\n", map_x, map_y, next_x, next_y);
      if (map_x > 0 && map_y > 0 && map_x < (map.size.x) && map_y < (map.size.y))
      {
        //printf("x : %d | y : %d | size_x : %d | size_y : %d\n", map_x, map_y, map.size.x, map.size.y);
        //printf("size_x : %d, size_y : %d, x : %d, y: %d\n", map.size.x, map.size.y, map_x, map_y);
        if (map.content[map_y][map_x] == 1)
        {
          // 1 - dist entre vecteurs 2d normalize.
          // *
          //dist = compute_distance((double)pos.x, (double)pos.y, (double)next_x, (double)next_y);
          //angle = acos(dist / (double)abs(pos.x - next_x));
          //dist = abs(next_y - pos.y) * cos(angle);
          dist = fabs(next_y - pos.y) * (cos(30 * M_PI / 180))/* (is_right ? cos(30 * (M_PI / 180)) : cos(-30 * (M_PI / 180)))*/;
          //printf("dist : %f \n", next_y);
          //dist = compute_distance((double)pos.x, (double)pos.y, (double)next_x, (double)next_y); /*(is_right ? cos(30) : cos(-30))*/
          //printf("pos = %d | dist = %f | coef = %f\n", abs(pos.x - next_x), dist, dist / abs(pos.x - next_x));
          //angle = atan(dist / (double)abs(pos.x - next_x));
          //dist = abs(next_y - pos.y) * cos(angle);
          //collision_angle = 180.0 - (angle + 90.0);
          //dist = (0.394 * (dx + dy) + 0.544 * MAX(dx, dy)) * (is_right ? cos(-30) : cos(30));
          //printf("dist %d, x % d, y %d, next_x %d, next_y %d, map_x %d, map_y %d\n", dist, x, y, next_x, next_y, map_x, map_y);
          // x2 | y2 --> y1 + ((WIN_HEIGHT / 2) / dist)
          /*printf("draw (x1 : %d, y1 : %d, x2 : %d, y2 : %d) -- dist = %d\n", next_x,
          next_y, map_x * config.cell_size.w,
          map_y * config.cell_size.h + (int)((WIN_HEIGHT / 2) / dist), dist);*/
          // ratio avec la dist, + eleve, + petit.
          //printf("dist : %f | x : %d | next_x : %d | y : %d | next_y : %d | collision_angle : %f | ray_angle : %f | diff : %d\n", dist, x, next_x, y, next_y, collision_angle, angle, next_y - pos.y);
          // 255 & (int)(255 / dist * i + 1 / 2)
          // 1 - 255 / dist.
          percent = 50 * (255 / (dist * 0.5));
          SDL_SetRenderDrawColor(renderer, percent,
          percent, percent, SDL_ALPHA_OPAQUE);
          SDL_RenderDrawLine(renderer,
                       i,
                       WIN_HEIGHT / 4 - (dist > 0.0 ? round(((WIN_HEIGHT / 2) / dist) * proj / 2) : WIN_HEIGHT),
                       i,
                       WIN_HEIGHT / 4 + (dist > 0.0 ? round(((WIN_HEIGHT / 2) / dist) * proj / 2) : WIN_HEIGHT));
            // ---> plusieurs intersection possible : stop le ray qd il est a la fin.
            // printf ("error : %s\n", SDL_GetError());
            break;
        }
      }
      next_x += x;
      next_y += y;
      // ray dir up
      // ray dir down
      //next_x += tmp_x;
      //next_x += is_right ? 1 : -1;
      //next_y += tmp_y;
      if ((int)next_x > WIN_WIDTH || next_x < 0.0 || (int)next_y > WIN_HEIGHT || next_y < 0.0)
        break;
    }
    ray_angle+= config.ray_angle;
    is_first_coord = 0;
    i++;
  }
}
