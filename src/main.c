#include "wolf.h"

int main(int ac, char **av)
{
  t_window window;
  t_map map;

  window = init_win();
  map = init_map();
  if (ac == 2)
  {
    check_extension(av, MAP);
    read_map(map, av[1]);
    create_window(window, "Wolf3D",
    (SDL_Rect){.x = SDL_WINDOWPOS_UNDEFINED,.y = SDL_WINDOWPOS_UNDEFINED,.w = 1200,.h = 900},
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
    SDL_Delay(5000);
    clear_window(window);
  }else
    ft_putstr("Wrong arguments");
}
