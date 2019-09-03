/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   setup.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/01 20:20:57 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/01 20:21:01 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void compute_config(t_config *config, t_map *map)
{
  config->projection.w = WIN_WIDTH;
  config->projection.h = WIN_HEIGHT;
  config->cell_size.w = ((double)WIN_WIDTH / map->size.x);
  config->cell_size.h = ((double)WIN_HEIGHT / map->size.y);
  config->ray_angle = (60.0 / (double)WIN_WIDTH);
  config->start_x = 0;
  config->start_y = 0;
  config->pos.x = 0;
  config->pos.y = 0;
  config->rotation = 0;
  // matrice de rotation quand le player bouge.
  config->camera.x = WIN_WIDTH / 2;
  config->camera.y = WIN_HEIGHT / 2;
}
