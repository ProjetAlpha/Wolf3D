/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   handle_events.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/01 17:47:52 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/01 17:49:13 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

int get_events(void)
{
  SDL_Event e;
  if (SDL_PollEvent(&e)){
    if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED){
      return (RESIZE);
    }
    else if (e.type == SDL_QUIT)
      return (QUIT);
    if (e.type == SDL_KEYUP)
    {
      if (e.key.keysym.sym == SDLK_ESCAPE)
        return (QUIT);
      if (e.key.keysym.sym == SDLK_DOWN)
        return (ARROW_DOWN);
      if (e.key.keysym.sym == SDLK_UP)
        return (ARROW_UP);
      if (e.key.keysym.sym == SDLK_LEFT)
        return (ARROW_LEFT);
      if (e.key.keysym.sym == SDLK_RIGHT)
        return (ARROW_RIGHT);
      if(e.key.keysym.sym == SDLK_w)
        return (W);
      if(e.key.keysym.sym == SDLK_a)
        return (A);
      if(e.key.keysym.sym == SDLK_s)
        return (S);
      if(e.key.keysym.sym == SDLK_d)
        return (D);
    }
  }
  return (NO_EVENT);
}
