/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/31 01:37:08 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/31 01:37:10 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include "wolf.h"

void check_extension(char **av, int type)
{
  char *name;
  int  len;

  name = NULL;
  if (!(type & MAP) && !(type & IMG))
    clean_msg_exit(NULL, UNDEFINED);
  if (type & MAP)
  {
    len = ft_strlen(av[1]);
    name = ft_strsub(av[1], len - 4, len);
    if (ft_strcmp(name, ".map") != 0)
      clean_msg_exit(name, type);
  }
  if (type & IMG)
  {
    // -i img_path /images/name.[bmp, jpeg..]
  }
}
