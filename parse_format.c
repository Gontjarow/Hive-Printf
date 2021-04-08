/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngontjar <ngontjar@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 21:42:32 by ngontjar          #+#    #+#             */
/*   Updated: 2021/04/08 08:47:53 by ngontjar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	parse_width(const char **format, t_data *flag)
{
	char	bytes;

	bytes = 0;
	if (**format == '*')
	{
		flag->width = va_arg(flag->ap, int);
		if (flag->width < 0)
		{
			flag->bit |= FLAG_JUSTIFY_LEFT;
			flag->width = -flag->width;
		}
		++(*format), ++bytes;
	}
	else
	{
		while (ft_isdigit(**format))
		{
			flag->width *= 10;
			flag->width += (**format - '0');
			++(*format), ++bytes;
		}
	}
	return (bytes);
}

/*
** Note: The while(isdigit) loop contains a branchless ternary.
** Todo: Find a way to simplify this within 25 lines in a sensible way.
*/
static char	parse_precision(const char **format, t_data *flag)
{
	char	bytes;

	if (**format != '.')
		return (0);
	++(*format), (bytes = 1);
	if (**format == '*' && ++(*format) && ++bytes)
	{
		flag->precision = va_arg(flag->ap, int);
		if (flag->precision < 0)
			flag->precision = -1;
	}
	else if (**format != 'f' || **format != 'L')
	{
		flag->precision = 0;
		while (ft_isdigit(**format))
		{
			flag->precision = ((flag->precision == -1) * (**format - '0'))
				+ ((flag->precision != -1)
					* ((flag->precision * 10) + (**format - '0')));
			++(*format), ++bytes;
		}
	}
	if (flag->precision < -1)
		flag->precision = -flag->precision;
	return (bytes);
}

static char	parse_specifier(const char **format, t_data *flag)
{
	char	bytes;
	size_t	skip;

	bytes = 0;
	if (**format == 'h')
	{
		++(*format), ++bytes;
		if (**format == 'h' && ++(*format) && ++bytes)
			flag->specifier = SPECIFIER_HH;
		else
			flag->specifier = SPECIFIER_H;
	}
	else if ((**format == 'l' && *(*format + 1) != 'f')
		|| (**format == 'L' && *(*format + 1) == 'f'))
	{
		++(*format), ++bytes;
		if (**format == 'l' && ++(*format) && ++bytes)
			flag->specifier = SPECIFIER_LL;
		else
			flag->specifier = SPECIFIER_L;
	}
	skip = (size_t)strany_skip(*format, "hlL");
	skip -= (skip != 0) * (size_t)(*format);
	(bytes += skip), ((*format) += skip);
	return (bytes);
}

static char	parse_flags(const char **format, t_data *flag)
{
	int	bytes;

	bytes = 0;
	while (**format == '-'
		|| **format == '+'
		|| **format == ' '
		|| **format == '#'
		|| **format == '0')
	{
		if (**format == '-')
			flag->bit |= FLAG_JUSTIFY_LEFT;
		if (**format == '+')
			flag->bit |= FLAG_FORCE_SIGN;
		if (**format == ' ')
			flag->bit |= FLAG_PAD_SIGN;
		if (**format == '#')
			flag->bit |= FLAG_PREFIX;
		if (**format == '0')
			flag->bit |= FLAG_LEADING_ZERO;
		++(*format), ++bytes;
	}
	return (bytes);
}

char	parse_format(const char *format, t_data *flag)
{
	int		bytes;
	char	*type;

	bytes = 1;
	bytes += parse_flags(&format, flag);
	bytes += parse_width(&format, flag);
	bytes += parse_precision(&format, flag);
	bytes += parse_specifier(&format, flag);
	type = ft_strchr("sdfciXxu%op", *format);
	if (type)
	{
		flag->type = *type;
		return (bytes);
	}
	else
	{
		flag->type = '\0';
		return (0);
	}
}
