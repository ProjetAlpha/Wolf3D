/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bits_op.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: thbrouss <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/26 18:27:28 by thbrouss     #+#   ##    ##    #+#       */
/*   Updated: 2019/08/26 18:27:49 by thbrouss    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "wolf.h"

unsigned long set_bits(short int pos_1, short int pos_2, short int pos_3, short int pos_4)
{
   unsigned long long result;

   result = 0;
   result |= pos_1;
   result <<= 16;
   result |= pos_2;
   result <<= 16;
   result |= pos_3;
   result <<= 16;
   result |= pos_4;
   return (result);
}

void get_bits(unsigned long stack, int tab[4])
{
  tab[0] = (stack & 0x0000FFFF);
  tab[1] = (stack & 0xFFFF0000) >> 16;
  tab[2] = (stack & 0x0000FFFF00000000) >> 32;
  tab[3] = (stack & 0xFFFF00000000000) >> 48;
}
