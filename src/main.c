#include "wolf.h"
#include "stdio.h"

int main(int ac, char **av)
{
  t_window window;
  int event;
  t_map map;
  SDL_Renderer *renderer;
  t_config config;
  int is_draw;

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
      // test image command [creer un carre avec l'image, sinon fill rect avec des couleurs ou image par defaut ?].
      // taille image = WIN_WIDTH / nb de colonne | WIN_HEIGHT / nb_line
      //if (config.have_img && config.img_path != NULL)
        //load_img_texture(window.ptr, config.img_path, &(SDL_Rect){.x = 150, .y = 150, .w = 800, .h = 600}, IMG_JPG);
      if (is_draw == 0)
      {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);
        create_world(map, config, (t_vec2){.x = WIN_WIDTH / 2,.y = 0}, renderer);
        SDL_RenderPresent(renderer);
        is_draw = 1;
      }
    }
    clear_window(&window);
  }else
    ft_putstr("Wrong number of arguments\n");
}
