/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 11:37:43 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/05 14:00:19 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Precision: Ignored.
**
** Flag: -
** Summary: Left-justification.
*/

#include "ft_printf.h"

static void	justify_left(unsigned char arg, t_data *flag)
{
	write(1, &arg, 1);
	++flag->written;
	width_padder(flag->width - 1, ' ', flag);
}

static void	justify_right(unsigned char arg, t_data *flag)
{
	width_padder(flag->width - 1, ' ', flag);
	write(1, &arg, 1);
	++flag->written;
}

void	output_char(unsigned char arg, t_data *flag)
{
	if (flag->bit & FLAG_JUSTIFY_LEFT)
		justify_left(arg, flag);
	else
		justify_right(arg, flag);
}
