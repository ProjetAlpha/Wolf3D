/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   display.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/31 01:50:17 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/07/31 01:50:20 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */


#include "wolf.h"

void clean_msg_exit(char *str, int type)
{
  if (type & UNDEFINED && !str)
  {
    ft_putstr("Undefined format\n");
    exit(-1);
  }
  if (!str)
    return ;
  if (type & MAP)
    ft_putstr("Wrong map format\n");
  if (type & IMG)
    ft_putstr("Wrong image format\n");
  free(str);
  exit(-1);
}

void put_error(char *str)
{
  ft_putstr(str);
  exit(-1);
}
