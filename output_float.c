/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:52:28 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/05 21:14:25 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Precision: The number of digits to appear after the decimal-point.
** Note: The default precision is 6. If precision is 0, no digits
**       nor the decimal-point will be printed.
**
** Flag: #
** Summary: The decimal-point is always printed, even if no digits follow it.
**
** Flag: -
** Summary: Left-justification.
**
** Flag: +
** Summary: The sign is always printed.
**
** Flag: (space)
** Summary: If the first wide character of a signed conversion is not a sign,
**          or if a signed conversion results in no wide characters,
**          a space is prefixed to the result.
** Note: If the space and + flags both appear, the space flag is ignored.
**
** Flag: 0
** Summary: Leading zeros (following any indication of sign or base) are used
**          to pad to the field width rather than performing space padding,
**          except when converting an infinity or NaN.
** Note: If the 0 and - flags both appear, the 0 flag is ignored.
*/

/*
** w = width padder (space character)
** z = zero (digit character)
** e = error string (nan, inf, -inf)
*/

#include "ft_printf.h"

static void	init(size_t len, long double *arg, t_data *flag)
{
	flag->w = 0;
	flag->p = len + (flag->precision == 0 && flag->bit & FLAG_PREFIX);
	if (flag->width > (int)flag->p)
	{
		flag->w = flag->width - (int)flag->p;
	}
	flag->w -= (*arg >= 0 && flag->bit & (FLAG_FORCE_SIGN | FLAG_PAD_SIGN));
}

static void	init_zeros(int *e, t_data *flag)
{
	flag->z = 0;
	if (*e)
		return ;
	if (flag->precision > (int)flag->p)
	{
		flag->z = flag->precision - (int)flag->p;
		flag->w -= flag->z;
	}
	if ((flag->bit & FLAG_LEADING_ZERO) && (flag->w > 0))
	{
		flag->z += flag->w;
		flag->w = 0;
	}
}

static void	justify_left(long double arg, const char *str, t_data *flag)
{
	init(ft_strlen(str), &arg, flag);
	if (flag->bit & FLAG_FORCE_SIGN && arg >= 0)
		flag->written += ft_putstr("+");
	else if (flag->bit & FLAG_PAD_SIGN && arg >= 0)
		flag->written += ft_putstr(" ");
	else if (arg < 0)
		flag->written += ft_putstrn(str++, 1);
	flag->written += ft_putstr(str);
	if (flag->precision == 0 && flag->bit & FLAG_PREFIX)
		flag->written += ft_putstr(".");
	width_padder(flag->w, ' ', flag);
}

static void	justify_right(long double arg, const char *str, int e, t_data *flag)
{
	init(ft_strlen(str), &arg, flag);
	init_zeros(&e, flag);
	width_padder(flag->w, ' ', flag);
	if (flag->bit & FLAG_FORCE_SIGN && arg >= 0)
		flag->written += ft_putstr("+");
	else if (flag->bit & FLAG_PAD_SIGN && arg >= 0)
		flag->written += ft_putstr(" ");
	else if (arg < 0)
		flag->written += ft_putstrn(str++, 1);
	width_padder(flag->z, '0', flag);
	flag->written += ft_putstr(str);
	if (flag->precision == 0 && flag->bit & FLAG_PREFIX)
		flag->written += ft_putstr(".");
}

void	output_double(long double arg, t_data *flag)
{
	char	*str;
	char	error_value;

	error_value = FALSE;
	str = NULL;
	if (arg != arg)
		str = ft_strdup("nan");
	else if (arg == INFINITY)
		str = ft_strdup("inf");
	else if (arg == -INFINITY)
		str = ft_strdup("-inf");
	if (str != NULL)
		error_value = TRUE;
	else
	{
		if (flag->precision == -1)
			str = ft_ftoa(arg, 6);
		else
			str = ft_ftoa(arg, flag->precision);
	}
	if (flag->bit & FLAG_JUSTIFY_LEFT)
		justify_left(arg, str, flag);
	else
		justify_right(arg, str, error_value, flag);
	free(str);
}
