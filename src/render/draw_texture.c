/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   draw_texture.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/01 16:18:39 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/01 16:18:42 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include "wolf.h"



/*  En fonction de l'extension (flag) charge une image a une postion donnée.
 *  Format supporté: bmp, png, jpg, gif.
 *
 */
void load_img_texture(SDL_Window *window, char *file, SDL_Rect *pos, int img_format)
{
    SDL_Surface     *surface;
    SDL_Texture     *texture;
    SDL_Renderer    *renderer;

    surface = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (img_format & IMG_BMP)
      surface = SDL_LoadBMP(file);
    if (img_format & IMG_PNG || img_format & IMG_JPG || img_format & IMG_GIF)
      surface = IMG_Load(file);
    else
        return (put_error("bad img_format in load_img_texture"));
    if (!surface)
      put_error((char*)IMG_GetError());
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, pos);
    SDL_RenderPresent(renderer);
}

void draw_vline(SDL_Renderer* renderer, t_line line)
{
  int length;
  int inc;

  inc = 0;
  length = 0;
  if (line.y1 == line.y2)
    return ;
  if (line.y1 > line.y2)
    length = line.y1 - line.y2;
  else
    length = line.y2 - line.y1;
  // opti : draw 10 pnts a chaque fois ?
  while (length--)
  {
    SDL_RenderDrawPoints(renderer, &(SDL_Point){.x = line.x1, .y = line.y1 + inc}, 1);
    inc++;
  }
}
