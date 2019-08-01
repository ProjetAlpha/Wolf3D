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
    else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
      return (QUIT);
  }
  return (NO_EVENT);
}
