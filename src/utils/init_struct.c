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
  return (map);
}
