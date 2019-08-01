/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_window.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/31 00:34:31 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/31 00:36:04 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

void create_window(t_window *window, const char* title, SDL_Rect rect, Uint32 flags)
{
   SDL_Init(SDL_INIT_EVERYTHING);
   window->ptr = SDL_CreateWindow(
        title,              // window title
        rect.x,            // initial x position
        rect.y,           // initial y position
        rect.h,          // width, in pixels
        rect.w,         // height, in pixels
        flags          // flags - see below
    );
    if (!window->ptr)
    {
      ft_putstr(SDL_GetError());
      exit(-1);
    }
    window->flags = flags;
    window->rect = rect;
}

void clear_window(t_window *window)
{
  SDL_DestroyWindow(window->ptr);
  window->rect.x = 0;
  window->rect.y = 0;
  window->rect.h = 0;
  window->rect.w = 0;
  window->flags = 0;
}

// close window...
