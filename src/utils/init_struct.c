/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_struct.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/31 02:15:11 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/31 02:15:21 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

t_window init_win(void)
{
  t_window window;

  window.ptr = NULL;
  window.rect.x = 0;
  window.rect.y = 0;
  window.rect.w = 0;
  window.rect.h = 0;
  window.flags = 0;
  return (window);
}

t_map init_map(void)
{
  t_map map;

  map.content = NULL;
  map.size.x = 0;
  map.size.y = 0;
  map.wall_info_size = 0;
  return (map);
}

t_config init_config(void)
{
  t_config config;

  config.have_img = 0;
  config.img_path = NULL;
  config.projection.w = 0;
  config.projection.h = 0;
  config.ray_angle = 0.0;
  config.cell_size.w = 0;
  config.cell_size.h = 0;
  config.camera.x = 0;
  config.camera.y = 0;
  config.pos.x = 0;
  config.pos.y = 0;
  config.start_x = 0;
  config.start_y = 0;
  return (config);
}

t_wall_info init_wall(void)
{
  t_wall_info wall;

  wall.pos[0] = 0;
  wall.pos[1] = 0;
  return (wall);
}
