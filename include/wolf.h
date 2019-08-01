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

# define WOLF_H

# include "SDL.h"
# include "SDL_image.h"
# include <math.h>
# include "../libft/libft.h"
# include <stdlib.h>

# define WIN_HEIGHT 1900
# define WIN_WIDTH 1200

# define MAP 1 << 0
# define IMG 1 << 1

# define UNDEFINED 1 << 0
# define MAP_SIZE 1 << 1
# define MAP_COORD 1 << 2

# define IMG_GIF 1 << 0
# define IMG_BMP 1 << 1
# define IMG_JPG 1 << 2
# define IMG_PNG 1 << 3

# define NO_EVENT 1 << 0
# define QUIT 1 << 1
# define RESIZE 1 << 2

typedef struct  s_window
{
  SDL_Window  *ptr;
  SDL_Rect    rect;
  Uint32      flags;
}               t_window;

typedef struct  s_vec2
{
  int x;
  int y;
}               t_vec2;

typedef struct  s_dim
{
  int w;
  int h;
}               t_dim;


typedef struct s_config
{
  int     have_img;
  char    *img_path;
  t_dim   projection;
  int     ray_angle;
  t_vec2  camera;
  t_dim   cell_size;
}             t_config;

typedef struct  s_map
{
  int **content;
  t_vec2 size;
}               t_map;

// 1 = carre = 4 faces
// screnW = Window width.
// tan 30 car (FOV / 2)
// distance p->wall = (screnW / 2) / tan(30) = x | 1 col = 60 / screnW
// increment l'angle de 60/screnW
// xa = grid height / tan (grid height / xa)
// vertical => offset = x % Width | horizontal => offset = y % Width.
// w = 1900px, grid de 5 => 1900 / 5 = 380px
// h = 1200px, grid de 5 => 1200 / 5 = 240px
// => dim 1 unit = 380 de width, 280 de height.
typedef struct  s_wall
{

}               t_wall;

/*typedef struct s_wolf
{
  t_window window;
} t_wolf;*/

void create_window(t_window *window, const char* title, SDL_Rect rect, Uint32 flags);
void clear_window(t_window *window);
void check_extension(char **av, int type);
void clean_msg_exit(char *str, int type);
void put_error(char *str);
t_window init_win(void);
t_map init_map(void);
t_config init_config(void);
void read_map(t_map map, char *file);
void init_sdl();
void load_img_texture(SDL_Window *window, char *file, SDL_Rect *pos, int img_format);
int get_events(void);
void compute_config(t_config *config, t_map *map);
#endif
