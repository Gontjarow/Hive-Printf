/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:21:53 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/05 21:27:47 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_zeros(size_t *len, t_data *flag)
{
	flag->z = 0;
	if (flag->precision > (int)(*len))
	{
		flag->z = flag->precision - *len;
		flag->w -= flag->z;
	}
}

static void	init(size_t *len, int *prefix, t_data *flag)
{
	flag->p = flag->precision;
	if (flag->precision == -1
		|| flag->precision < (int)(*len)
		|| flag->p > *len)
	{
		flag->p = *len;
	}
	flag->w = 0;
	if ((size_t)flag->width > flag->p)
	{
		flag->w = flag->width - flag->p - *prefix;
	}
	init_zeros(len, flag);
}

static void	justify_left(long long arg, const char *str, t_data *flag)
{
	size_t	len;
	int		prefix;

	prefix = 2 * (flag->bit & FLAG_PREFIX && arg != 0);
	len = 0;
	if (!(flag->precision == 0 && arg == 0))
		len = ft_strlen(str);
	init(&len, &prefix, flag);
	if (prefix)
		flag->written += putstr_case("0X", -1 * (flag->type == 'x'));
	width_padder(flag->z, '0', flag);
	flag->written += putstrn_case(str, flag->p, -1 * (flag->type == 'x'));
	width_padder(flag->w, ' ', flag);
}

static void	justify_right(long long arg, const char *str, t_data *flag)
{
	size_t	len;
	int		prefix;

	prefix = 2 * (flag->bit & FLAG_PREFIX && arg != 0);
	len = 0;
	if (!(flag->precision == 0 && arg == 0))
		len = ft_strlen(str);
	init(&len, &prefix, flag);
	if (flag->bit & FLAG_LEADING_ZERO && ~flag->precision)
		flag->bit &= ~FLAG_LEADING_ZERO;
	if ((flag->bit & FLAG_LEADING_ZERO) && (flag->w > 0))
	{
		flag->z += flag->w;
		flag->w = 0;
	}
	width_padder(flag->w, ' ', flag);
	if (prefix)
		flag->written += putstr_case("0X", -1 * (flag->type == 'x'));
	width_padder(flag->z, '0', flag);
	flag->written += putstrn_case(str, flag->p, -1 * (flag->type == 'x'));
}

/*
** Undefined flags: +, ' '
** Applicable flags: -, 0, #
** Precision: Minimum amount of digits, leading zeroes if necessary.
** If value is zero and precision is exactly zero, print nothing.
*/

void	output_uint(unsigned long long arg, t_data *flag)
{
	char	*str;

	if (flag->type == 'o')
		output_octal(arg, flag);
	else if (flag->type == 'u')
		output_unsigned(arg, flag);
	else
	{
		str = ft_utoa_base(arg, 16);
		if (flag->bit & FLAG_JUSTIFY_LEFT)
			justify_left(arg, str, flag);
		else
			justify_right(arg, str, flag);
		free(str);
	}
}
