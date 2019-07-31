/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   wolf.h                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/31 00:36:19 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/31 00:37:12 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef WOLF_H

#define WOLF_H

#include "SDL.h"
#include "../libft/libft.h"
#include <stdlib.h>


#define MAP 1 << 0
#define IMG 1 << 1
#define UNDEFINED 1 << 2 
#define MAP_SIZE 1 << 3
#define MAP_COORD 1 << 4

typedef struct  s_window
{
  SDL_Window  *ptr;
  SDL_Rect    rect;
  Uint32      flags;
}               t_window;

typedef struct  vec2
{
  int x;
  int y;
}               t_vec2;

typedef struct  s_map
{
  // [15, 15]
  // 0 1 0 0 0 ----> gnl...
  // 0 0 1 0 0 1 0 1 0
  // 0 1 0 0 1 0
  // 0 1 0 1
  int **content;
  t_vec2 size;
}               t_map;

/*typedef struct s_wolf
{
  t_window window;
} t_wolf;*/

void create_window(t_window window, const char* title, SDL_Rect rect, Uint32 flags);
void clear_window(t_window window);
void check_extension(char **av, int type);
void clean_msg_exit(char *str, int type);
void put_error(char *str);
t_window init_win(void);
t_map init_map(void);
void read_map(t_map map, char *file);

#endif
