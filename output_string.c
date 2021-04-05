/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:06:59 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/05 17:51:14 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init(size_t *len, int *w, t_data *flag)
{
	if (flag->precision == -1)
	{
		flag->p = *len;
	}
	else
	{
		flag->p = flag->precision;
	}
	if (flag->p > *len)
	{
		flag->p = *len;
	}
	if ((size_t)flag->width > flag->p)
	{
		*w = (size_t)flag->width - flag->p;
	}
	else
	{
		*w = 0;
	}
}

static void	justify_left(char *arg, t_data *flag)
{
	int		w;
	size_t	len;

	len = ft_strlen(arg);
	init(&len, &w, flag);
	flag->written += ft_putstrn(arg, flag->p);
	width_padder(w, ' ', flag);
}

static void	justify_right(char *arg, t_data *flag)
{
	int		w;
	size_t	len;

	len = ft_strlen(arg);
	init(&len, &w, flag);
	width_padder(w, ' ', flag);
	flag->written += ft_putstrn(arg, flag->p);
}

/*
** Undefined flags: #, 0, ' ', +
** Applicable flags: -
** Precision: maximum amount of characters
*/

void	output_str(char *arg, t_data *flag)
{
	if (flag->bit & FLAG_JUSTIFY_LEFT)
		justify_left(arg, flag);
	else
		justify_right(arg, flag);
}
