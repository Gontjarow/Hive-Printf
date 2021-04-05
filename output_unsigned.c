/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:51:48 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/05 18:01:27 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init(size_t *len, int *w, t_data *flag)
{
	if (flag->precision == -1 || flag->precision < (int)(*len))
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
		*w = flag->width - flag->p;
	}
	else
	{
		*w = 0;
	}
}

static void	init_zeros(size_t *len, int *z, int *w, t_data *flag)
{
	if (flag->precision > (int)(*len))
		*z = flag->precision - *len;
	else
		*z = 0;
	if (*z > 0)
		*w -= *z;
}

static void	justify_left(long long arg, const char *str, t_data *flag)
{
	int		w;
	int		z;
	size_t	len;

	if (flag->precision == 0 && arg == 0)
		len = 0;
	else
		len = ft_strlen(str);
	init(&len, &w, flag);
	init_zeros(&len, &z, &w, flag);
	width_padder(z, '0', flag);
	flag->written += ft_putstrn(str, flag->p);
	width_padder(w, ' ', flag);
}

static void	justify_right(long long arg, const char *str, t_data *flag)
{
	int		w;
	int		z;
	size_t	len;

	if (flag->precision == 0 && arg == 0)
		len = 0;
	else
		len = ft_strlen(str);
	init(&len, &w, flag);
	init_zeros(&len, &z, &w, flag);
	if (flag->bit & FLAG_LEADING_ZERO && ~flag->precision)
		flag->bit &= ~FLAG_LEADING_ZERO;
	if ((flag->bit & FLAG_LEADING_ZERO) && (w > 0))
	{
		z += w;
		w = 0;
	}
	width_padder(w, ' ', flag);
	width_padder(z, '0', flag);
	flag->written += ft_putstrn(str, flag->p);
}

/*
** Undefined flags: +, ' ', #
** Applicable flags: -, 0
** Precision: Minimum amount of digits, leading zeroes if necessary.
** If value is zero and precision is exactly zero, print nothing.
*/

void	output_unsigned(unsigned long long arg, t_data *flag)
{
	char	*str;

	str = ft_utoa(arg);
	if (flag->bit & FLAG_JUSTIFY_LEFT)
		justify_left(arg, str, flag);
	else
		justify_right(arg, str, flag);
	free(str);
}
