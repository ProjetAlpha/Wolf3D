#include "wolf.h"
#include <stdio.h>

int main(int ac, char **av)
{
  t_window window;
  int event;
  t_map map;
  SDL_Renderer *renderer;
  t_config config;
  int is_draw;
  int ray_angle;

  window = init_win();
  map = init_map();
  config = init_config();
  is_draw = 0;
  if (ac > 1 && ac < 5)
  {
    if (ac > 2 && ft_strcmp(av[3], "-i"))
    {
      check_extension(av, MAP | IMG);
      config.have_img = 1;
      config.img_path = av[3];
    }
    else
      check_extension(av, MAP);
    read_map(&map, av[1]);
    compute_config(&config, &map);
    create_window(&window, "Wolf3D",
    (SDL_Rect){.x = SDL_WINDOWPOS_CENTERED,.y = SDL_WINDOWPOS_CENTERED,.w = WIN_WIDTH,.h = WIN_HEIGHT},
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window.ptr, -1, SDL_RENDERER_ACCELERATED);
    while (1)
    {
      event = get_events();
      if (event & QUIT)
        break;
      if (config.rotation > 0 || config.rotation < 0)
        ray_angle = 45 + config.rotation;
      else
        ray_angle = 45;
      // deplacement = 1 carre =>
      // x et y inverses qd on rotate (-rot).
      // a * cos(ray_angle + 30)
      // a * sin(ray_angle + 30)
      //
      if (event & ARROW_UP && config.pos.y + (config.cell_size.w * 0.5) <= WIN_HEIGHT)
      {
        config.pos.x += fabs(10 * cos(ray_angle + 30));
        config.pos.y += fabs(10 * sin(ray_angle + 30));
        //config.pos.x += config.cell_size.w * 0.5;
        //config.pos.y += config.cell_size.w * 0.5;
        //printf("pos_x : %d | pos_y : %d\n", config.pos.x, config.pos.y);
        is_draw = 0;
      }
      if (event & ARROW_DOWN && config.pos.y - (config.cell_size.w * 0.5) > 0)
      {
        config.pos.x -= fabs(10 * cos(ray_angle + 30));
        config.pos.y -= fabs(10 * sin(ray_angle + 30));
        is_draw = 0;
      }else if (event & ARROW_DOWN && config.pos.y - (config.cell_size.w * 0.5) <= 0)
      {
        config.pos.y = 0;
        is_draw = 0;
      }

      if (event & ARROW_LEFT)
      {
        config.rotation -= 5;
        is_draw = 0;
      }
      if (event & ARROW_RIGHT)
      {
        // x = -(sin(angle) - py) + px
        // y = (cos(angle) - px) + py
        config.rotation += 5;
        is_draw = 0;
      }
      if (event & D && config.pos.x + (config.cell_size.w * 0.5) <= WIN_WIDTH)
      {
        if (config.rotation < 0)
          config.pos.y -= config.cell_size.w * 0.5;
        else
          config.pos.x -= config.cell_size.w * 0.5;
        is_draw = 0;
      }
      if (event & A && (config.pos.x - (config.cell_size.w * 0.5) > 0 || (config.rotation < 0 && config.pos.y - (config.cell_size.w * 0.5) > 0)))
      {
        if (config.rotation < 0)
          config.pos.y -= config.cell_size.w * 0.5;
        else
          config.pos.x -= config.cell_size.w * 0.5;
        is_draw = 0;
      }else if (event & A && config.pos.x - (config.cell_size.w * 0.5) <= 0)
      {
        config.pos.x = 0;
        is_draw = 0;
      }
      // test image command [creer un carre avec l'image, sinon fill rect avec des couleurs ou image par defaut ?].
      // taille image = WIN_WIDTH / nb de colonne | WIN_HEIGHT / nb_line
      //if (config.have_img && config.img_path != NULL)
        //load_img_texture(window.ptr, config.img_path, &(SDL_Rect){.x = 150, .y = 150, .w = 800, .h = 600}, IMG_JPG);
      if (is_draw == 0)
      {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        config.rotation %= 360;
        create_world(map, config, config.pos, renderer);
        SDL_RenderPresent(renderer);
        is_draw = 1;
      }
    }
    clear_window(&window);
  }else
    ft_putstr("Wrong number of arguments\n");
}
