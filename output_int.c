/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 17:46:21 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/05 20:49:18 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_zeros(int *len, long long *arg, t_data *flag)
{
	flag->z = 0;
	if (flag->precision > *len - (*arg < 0))
	{
		flag->z = flag->precision - *len + (*arg < 0);
	}
}

static void	init(int *len, long long *arg, t_data *flag)
{
	flag->p = flag->precision;
	if (flag->precision == -1
		|| flag->precision < *len - (*arg < 0)
		|| flag->p > (size_t)*len)
	{
		flag->p = *len;
	}
	flag->w = 0;
	if ((size_t)flag->width > flag->p)
	{
		flag->w = (size_t)flag->width - flag->p;
	}
	flag->w -= (*arg >= 0 && flag->bit & (FLAG_FORCE_SIGN | FLAG_PAD_SIGN));
	init_zeros(len, arg, flag);
	if (flag->z > 0)
		flag->w -= flag->z;
}

static void	justify_left(long long arg, const char *str, t_data *flag)
{
	int		len;

	len = 0;
	if (!(flag->precision == 0 && arg == 0))
		len = (int)ft_strlen(str);
	init(&len, &arg, flag);
	if (flag->bit & FLAG_FORCE_SIGN && arg >= 0)
		flag->written += ft_putstr("+");
	else if (flag->bit & FLAG_PAD_SIGN && arg >= 0)
		flag->written += ft_putstr(" ");
	else if (arg < 0)
		flag->written += ft_putstrn(str++, 1);
	width_padder(flag->z, '0', flag);
	flag->written += ft_putstrn(str, flag->p - (arg < 0));
	width_padder(flag->w, ' ', flag);
}

static void	justify_right(long long arg, const char *str, t_data *flag)
{
	int		len;

	len = 0;
	if (!(flag->precision == 0 && arg == 0))
		len = (int)ft_strlen(str);
	init(&len, &arg, flag);
	if (flag->bit & FLAG_LEADING_ZERO && ~flag->precision)
		flag->bit &= ~FLAG_LEADING_ZERO;
	if ((flag->bit & FLAG_LEADING_ZERO) && (flag->w > 0))
	{
		flag->z += flag->w;
		flag->w = 0;
	}
	width_padder(flag->w, ' ', flag);
	if (flag->bit & FLAG_FORCE_SIGN && arg >= 0)
		flag->written += ft_putstr("+");
	else if (flag->bit & FLAG_PAD_SIGN && arg >= 0)
		flag->written += ft_putstr(" ");
	else if (arg < 0)
		flag->written += ft_putstrn(str++, 1);
	width_padder(flag->z, '0', flag);
	flag->written += ft_putstrn(str, flag->p - (arg < 0));
}

/*
** todo: clean up
** Undefined flags: #
** Applicable flags: -, +, ' ', 0
** Precision: Minimum amount of digits, leading zeroes if necessary.
** If value is zero and precision is exactly zero, print nothing.
*/

void	output_int(long long arg, t_data *flag)
{
	char	*str;

	str = ft_itoa(arg);
	if (flag->bit & FLAG_JUSTIFY_LEFT)
		justify_left(arg, str, flag);
	else
		justify_right(arg, str, flag);
	free(str);
}
