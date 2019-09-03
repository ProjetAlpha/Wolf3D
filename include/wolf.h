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

# define ARROW_DOWN 1 << 3
# define ARROW_UP 1 << 4
# define ARROW_RIGHT 1 << 5
# define ARROW_LEFT 1 << 6

# define W 1 << 7
# define A 1 << 8
# define S 1 << 9
# define D 1 << 10

# define MIN(a,b) (((a)<(b))?(a):(b))
# define MAX(a,b) (((a)>(b))?(a):(b))

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
  double w;
  double h;
}               t_dim;

typedef struct  s_line
{
  int x1;
  int y1;
  int x2;
  int y2;
}               t_line;

typedef struct s_rect_pos
{
  int x1;
  int y1;
}             t_rect_pos;

typedef struct s_config
{
  int     have_img;
  char    *img_path;
  t_dim   projection;
  float   ray_angle;
  t_vec2  camera;
  t_dim   cell_size;
  t_vec2  pos;
  int     rotation;
  int     start_x;
  int     start_y;
}             t_config;

typedef struct  s_wall_info
{
  unsigned long int pos[2];
}               t_wall_info;

typedef struct  s_map
{
  int **content;
  t_vec2 size;
  t_wall_info *wall_info;
  int wall_info_size;
}               t_map;

void create_window(t_window *window, const char* title, SDL_Rect rect, Uint32 flags);
void clear_window(t_window *window);
void check_extension(char **av, int type);
void clean_msg_exit(char *str, int type);
void put_error(char *str);
t_window init_win(void);
t_map init_map(void);
t_config init_config(void);
t_wall_info init_wall(void);
void read_map(t_map *map, char *file);
void init_sdl();
void load_img_texture(SDL_Window *window, char *file, SDL_Rect *pos, int img_format);
int get_events(void);
void compute_config(t_config *config, t_map *map);
void create_world(t_map map, t_config config, t_vec2 pos, SDL_Renderer *renderer);
void draw_vline(SDL_Renderer* renderer, t_line line);
unsigned long set_bits(short int pos_1, short int pos_2, short int pos_3, short int pos_4);
void get_bits(unsigned long stack, int tab[4]);
void set_pos(t_map *map, short int tab[8], int count_cord, int line_pos);
t_wall_info *cpy_coords(t_map *map, short int pos[8]);

#endif
