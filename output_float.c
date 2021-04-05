/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:52:28 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/05 18:14:19 by ngontjar         ###   ########.fr       */
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
*/

#include "ft_printf.h"

static void	init(size_t *len, int *w, t_data *flag)
{
	flag->p = *len + (flag->precision == 0 && flag->bit & FLAG_PREFIX);
	if (flag->width > (int)flag->p)
	{
		*w = flag->width - (int)flag->p;
	}
	else
	{
		*w = 0;
	}
}

static void	init_zeros(int *z, int *w, int *e, t_data *flag)
{
	if (!(*e) && flag->precision > (int)flag->p)
	{
		*z = flag->precision - (int)flag->p;
	}
	else
	{
		*z = 0;
	}
	if (*z > 0)
	{
		*w -= *z;
	}
	if (!(*e) && (flag->bit & FLAG_LEADING_ZERO) && (*w > 0))
	{
		*z += *w;
		*w = 0;
	}
}

static void	justify_left(long double arg, const char *str, t_data *flag)
{
	int		w;
	size_t	len;

	len = ft_strlen(str);
	init(&len, &w, flag);
	w -= (arg >= 0 && flag->bit & (FLAG_FORCE_SIGN | FLAG_PAD_SIGN));
	if (flag->bit & FLAG_FORCE_SIGN && arg >= 0)
		flag->written += ft_putstr("+");
	else if (flag->bit & FLAG_PAD_SIGN && arg >= 0)
		flag->written += ft_putstr(" ");
	else if (arg < 0)
		flag->written += ft_putstrn(str++, 1);
	flag->written += ft_putstr(str);
	if (flag->precision == 0 && flag->bit & FLAG_PREFIX)
		flag->written += ft_putstr(".");
	width_padder(w, ' ', flag);
}

static void	justify_right(long double arg, const char *str, int e, t_data *flag)
{
	int		w;
	int		z;
	size_t	len;

	len = ft_strlen(str);
	init(&len, &w, flag);
	w -= (arg >= 0 && flag->bit & (FLAG_FORCE_SIGN | FLAG_PAD_SIGN));
	init_zeros(&z, &w, &e, flag);
	width_padder(w, ' ', flag);
	if (flag->bit & FLAG_FORCE_SIGN && arg >= 0)
		flag->written += ft_putstr("+");
	else if (flag->bit & FLAG_PAD_SIGN && arg >= 0)
		flag->written += ft_putstr(" ");
	else if (arg < 0)
		flag->written += ft_putstrn(str++, 1);
	width_padder(z, '0', flag);
	flag->written += ft_putstr(str);
	if (flag->precision == 0 && flag->bit & FLAG_PREFIX)
		flag->written += ft_putstr(".");
}

void	output_double(long double arg, t_data *flag)
{
	char	*str;
	char	error;

	error = FALSE;
	str = NULL;
	if (arg != arg)
		str = ft_strdup("nan");
	else if (arg == INFINITY)
		str = ft_strdup("inf");
	else if (arg == -INFINITY)
		str = ft_strdup("-inf");
	if (str == NULL)
	{
		if (flag->precision == -1)
			str = ft_ftoa(arg, 6);
		else
			str = ft_ftoa(arg, flag->precision);
	}
	else
		error = TRUE;
	if (flag->bit & FLAG_JUSTIFY_LEFT)
		justify_left(arg, str, flag);
	else
		justify_right(arg, str, error, flag);
	free(str);
}
