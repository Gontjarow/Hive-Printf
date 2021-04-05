/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_octal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:51:20 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/05 17:20:42 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init(size_t *len, int *prefix, int *w, t_data *flag)
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
	if (flag->width > (int)flag->p)
	{
		*w = flag->width - (int)flag->p - *prefix;
	}
	else
	{
		*w = 0;
	}
}

static void	init_zeros(size_t *len, int *prefix, int *z, t_data *flag)
{
	if (flag->precision > (int)(*len))
		*z = flag->precision - *len - *prefix;
	else
		*z = 0;
}

static void	justify_left(long long arg, const char *str, t_data *flag)
{
	int		w;
	int		z;
	size_t	len;
	int		prefix;

	prefix = !!(flag->bit & FLAG_PREFIX);
	if (flag->precision == 0 && arg == 0)
		len = 0;
	else
		len = ft_strlen(str);
	if (prefix && arg == 0)
		len = 0;
	init(&len, &prefix, &w, flag);
	init_zeros(&len, &prefix, &z, flag);
	if (z > 0)
		w = w - z;
	else
		w = w;
	if (prefix)
		flag->written += ft_putstr("0");
	width_padder(z, '0', flag);
	flag->written += ft_putstrn(str, flag->p);
	width_padder(w, ' ', flag);
}

static void	justify_right(long long arg, const char *str, t_data *flag)
{
	int		w;
	int		z;
	size_t	len;
	int		prefix;

	prefix = !!(flag->bit & FLAG_PREFIX);
	if (flag->precision == 0 && arg == 0)
		len = 0;
	else
		len = ft_strlen(str);
	if (prefix && arg == 0)
		len = 0;
	else
		len = len;
	init(&len, &prefix, &w, flag);
	init_zeros(&len, &prefix, &z, flag);
	if (z > 0)
		w = w - z;
	else
		w = w;
	if (flag->bit & FLAG_LEADING_ZERO && ~flag->precision)
		flag->bit &= ~FLAG_LEADING_ZERO;
	if ((flag->bit & FLAG_LEADING_ZERO) && (w > 0))
	{
		z += w;
		w = 0;
	}
	width_padder(w, ' ', flag);
	if (prefix)
		flag->written += ft_putstr("0");
	width_padder(z, '0', flag);
	flag->written += ft_putstrn(str, flag->p);
}

/*
** Undefined flags: +, ' '
** Applicable flags: -, 0, #
** Precision: Minimum amount of digits, leading zeroes if necessary.
** If value is zero and precision is exactly zero, print nothing.
*/

void	output_octal(unsigned long long arg, t_data *flag)
{
	char	*str;

	str = ft_utoa_base(arg, 8);
	if (flag->bit & FLAG_JUSTIFY_LEFT)
		justify_left(arg, str, flag);
	else
		justify_right(arg, str, flag);
	free(str);
}
