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
#include <stdio.h>

static void check_map(char *name, int type)
{
  int  len;

  len = ft_strlen(name);
  name = ft_strsub(name, len - 4, len);
  if (ft_strcmp(name, ".map") != 0)
    clean_msg_exit(name, type^= IMG);
}

static void check_img(char *name, int type)
{
  int len;

  len = ft_strlen(name);
  name = ft_strsub(name, len - 4, len);
  if (ft_strcmp(name, ".jpg") != 0 && ft_strcmp(name, ".png") != 0 && ft_strcmp(name, ".bmp") != 0)
    clean_msg_exit(name, type^= MAP);
}

void check_extension(char **av, int type)
{
  char *name;

  name = NULL;
  if (!(type & MAP) && !(type & IMG))
    clean_msg_exit(NULL, UNDEFINED);
  if (type & MAP)
  {
    if (!av[1])
      put_error("invalid map argument\n");
    check_map(av[1], type);
  }
  if (type & IMG)
  {
    if (!av[2] || !av[3])
      put_error("invalid image argument\n");
    if (ft_strcmp(av[2], "-i") != 0)
      put_error("invalid image argument\n");
    check_img(av[3], type);
  }
}
