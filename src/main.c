#include "wolf.h"
#include "stdio.h"

int main(int ac, char **av)
{
  t_window window;
  int event;
  t_map map;
  t_config config;

  window = init_win();
  map = init_map();
  config = init_config();
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
    read_map(map, av[1]);
    create_window(&window, "Wolf3D",
    (SDL_Rect){.x = SDL_WINDOWPOS_CENTERED,.y = SDL_WINDOWPOS_CENTERED,.w = WIN_WIDTH,.h = WIN_HEIGHT},
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    while (1)
    {
      event = get_events();
      if (event & QUIT)
        break;
      // test image command [creer un carre avec l'image, sinon fill rect avec des couleurs ou image par defaut ?].
      // taille image = WIN_WIDTH / nb de colonne | WIN_HEIGHT / nb_line
      if (config.have_img && config.img_path != NULL)
        load_img_texture(window.ptr, config.img_path, &(SDL_Rect){.x = 150, .y = 150, .w = 800, .h = 600}, IMG_JPG);
    }
    clear_window(&window);
  }else
    ft_putstr("Wrong number of arguments\n");
}
