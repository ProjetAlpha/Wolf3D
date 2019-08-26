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
  config->cell_size.w = (int)(WIN_WIDTH / map->size.x);
  config->cell_size.h = (int)(WIN_HEIGHT / map->size.y);
  config->ray_angle = (66.0 / (double)WIN_WIDTH);
  config->pos.x = config->cell_size.w / 2;
  config->pos.y = config->cell_size.w / 2;
  config->rotation = 0;
  // matrice de rotation quand le player bouge.
  config->camera.x = WIN_WIDTH / 2;
  config->camera.y = WIN_HEIGHT / 2;
}
